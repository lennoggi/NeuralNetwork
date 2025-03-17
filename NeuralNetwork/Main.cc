#include <cassert>
#include <array>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <random>

#include "include/Activation_functions.hh"
#include "include/Loss_functions.hh"
#include "Parameters.hh"

using namespace std;


int main() {
    // Read the input datasets file and save the input and expected output values
    ifstream training_datasets_file(TRAINING_DATASETS_FILENAME);

    if (not training_datasets_file.is_open()) {
        cerr << "Unable to open file '" << TRAINING_DATASETS_FILENAME << "'" << endl;
        return 1;
    }

    bool   first_line = true;
    size_t nvalues;  // Number of input values plus the expected output value per dataset
    string line;
    vector<vector<double>> dsets;  // The last element in each row is the expected output

    while (getline(training_datasets_file, line)) {
        if (line.empty() or line.at(0) == '#') {
            continue;
        }

        istringstream line_ss(line);
        vector<double> dset;
        double value;
        size_t count = 0;

        while (line_ss >> value) {
            dset.push_back(value);
            ++count;
        }

        if (first_line) {
            nvalues = count;
            first_line = false;
        } else if (count != nvalues) {
            cerr << "Dataset (i.e., line) " << endl
                 << "    " << line          << endl
                 << "in file '" << TRAINING_DATASETS_FILENAME << "' contains " << count
                 << " elements, but the first dataset (i.e., line) contains " << nvalues << " elements" << endl;
            return 1;
        }

        dsets.push_back(dset);
    }

    training_datasets_file.close();

    const auto ndsets = dsets.size();
    const auto ninput = nvalues - 1;

    cout << "There are " << ndsets << " datasets with " << ninput
         << " input values and 1 expected output value each" << endl;

    auto batch_size = BATCH_SIZE;
    if (BATCH_SIZE > ndsets) {
        cout << "WARNING: BATCH_SIZE=" << BATCH_SIZE << ", but there are only " << ndsets
             << " datasets. Resetting the batch size to " << ndsets << "." << endl;
        batch_size = ndsets;
    }


    /* Initialize the weights as random numbers between 0 and 1
     * NOTE: 'mt19937' is a Mersenne Twister generator, but other options are available
     *       (see https://cplusplus.com/reference/random for more options)      */
    #if (RAND_SEED > 0)
    mt19937 gen(RAND_SEED);
    #elif (RAND_SEED == -1)
    random_device rd;  // Use machine entropy as 
    mt19937 gen(rd());
    #else
    #error "Invalid seed for the random number generator"
    #endif

    uniform_real_distribution<double> dist(0., 1.);
    vector<double> weights(ninput);

    string weights_filename = "Weights.asc";
    ofstream weights_file(weights_filename);

    if (weights_file.is_open()) {
        for (auto i = decltype(ninput){0}; i < ninput; ++i) {
            const auto ip = i + 1;
            weights_file << "# Column " << ip << ": weight " << ip << endl;
        }
    } else {
        cerr << "Unable to open file '" << weights_filename << "' for writing" << endl;
        return 1;
    }

    cout << endl << "Initial weights" << endl;

    for (auto i = decltype(ninput){0}; i < ninput; ++i) {
        weights.at(i) = dist(gen);
        cout << weights.at(i) << endl;
        weights_file << weights.at(i) << "\t";
    }

    cout << endl;
    weights_file << endl;


    // Set up the neuron activation function
    double (*  compute_act)(const double&);
    double (*compute_d_act)(const double&);

    #if (ACTIVATION == LINEAR)
    compute_act   =   linear;
    compute_d_act = d_linear;
    #elif (ACTIVATION == SIGN)
    compute_act   =   sign;
    compute_d_act = d_sign;
    #elif (ACTIVATION == RELU)
    compute_act   =   ReLU;
    compute_d_act = d_ReLU;
    #elif (ACTIVATION == HARD_TANH)
    compute_act   =   hard_tanh;
    compute_d_act = d_hard_tanh;
    #elif (ACTIVATION == SIGMOID)
    compute_act   =   sigmoid;
    compute_d_act = d_sigmoid;
    #elif (ACTIVATION == TANH)
    compute_act   =   mytanh;
    compute_d_act = d_mytanh;
    #else
    #error "Invalid neuron activation function"
    #endif


    // Set up the loss function
    //double (*  compute_loss)(const double&, const double&);
    double (*compute_d_loss)(const double&, const double&);

    #if (LOSS == LSQ)
    //compute_loss   =   lsq;
    compute_d_loss = d_lsq;
    #elif (LOSS == LOGISTIC)
    //compute_loss   =   logistic;
    compute_d loss = d_logistic;
    #else
    #error "Invalid loss function"
    #endif



    /* ------------------
     * Begin the training
     * ------------------ */
    /* Vector storing the average loss gradient \partial L / \partial w_i
     * computed after processing each batch of datasets                         */
    vector<double> avg_grad_loss_batch(ninput);

    for (auto epoch = decltype(N_EPOCHS){0}; epoch < N_EPOCHS; ++epoch) {
        /* Loop over the datsets in batches, but limit the size of the last
         * batch if there aren't enough datasets left                           */
        for (auto n = decltype(ndsets){0}; n < ndsets; n += batch_size) {
            for (auto &deriv : avg_grad_loss_batch) {
                deriv = 0.;
            }

            const auto &dset_n    = dsets.at(n);
            const auto  batch_end = min(n + batch_size, ndsets);

            // Process one batch of datasets
            for (auto m = decltype(batch_end){n}; m < batch_end; ++m) {
                double sum = 0.;
                for (auto i = decltype(ninput){0}; i < ninput; ++i) {
                    sum += weights.at(i)*dset_n.at(i);
                }
        
                const auto expected_output = dset_n.at(ninput);  // Last value in dset
                const auto measured_output = compute_act(sum);
                const auto d_act           = compute_d_act(sum);
        
                //const auto loss       = compute_loss(  measured_output, expected_output);
                const auto d_loss     = compute_d_loss(measured_output, expected_output);
                const auto dloss_dact = d_loss*d_act;
        
                /* Calculate \partial L / \partial w_i via the chain rule and
                 * update the loss gradient accumulators                        */
                for (auto i = decltype(ninput){0}; i < ninput; ++i) {
                    avg_grad_loss_batch.at(i) += dloss_dact*dset_n.at(i);
                }
            }

            // Update the weights
            for (auto i = decltype(ninput){0}; i < ninput; ++i) {
                avg_grad_loss_batch.at(i) = (double) avg_grad_loss_batch.at(i)/ninput;
                weights.at(i)            -= LEARNING_RATE*avg_grad_loss_batch.at(i);
                avg_grad_loss_batch.at(i) = 0.;
                weights_file << weights.at(i) << "\t";
            }

            weights_file << endl;

            cout << "Training epoch " << epoch << " / " << N_EPOCHS
                 << ": done processing dataset " << n << " / " << ndsets << endl;
        }
    }

    weights_file.close();
    cout << endl << "Final weights" << endl;

    for (const auto &w : weights) {
        cout << w << endl;
    }

    return 0;
}
