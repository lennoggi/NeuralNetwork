#include <cassert>
#include <array>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <random>

#include "include/Activation_functions.hh"
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
            cerr << "Dataset (i.e., line) " << endl << endl
                 << "    " << line          << endl << endl
                 << "in file '" << TRAINING_DATASETS_FILENAME << "' contains " << count
                 << " elements, but the first dataset (i.e., line) contains " << nvalues << " elements" << endl << endl;
            return 1;
        }

        dsets.push_back(dset);
    }

    training_datasets_file.close();

    const auto ndsets = dsets.size(); // XXX
    const auto ninput = nvalues - 1;

    cout << endl << "There are " << ndsets << " datasets with " << ninput
         << " input values and 1 expected output value each" << endl;


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
    cout << endl << "Initial weights" << endl;

    for (auto &w : weights) {
        w = dist(gen);
        cout << w << endl;
    }


    // Set up the neuron activation function
    double (*activate)(const double&);

    #if (ACTIVATION == LINEAR)
    activate = linear;
    #elif (ACTIVATION == SIGN)
    activate = sign;
    #elif (ACTIVATION == RELU)
    activate = ReLU;
    #elif (ACTIVATION == HARD_TANH)
    activate = hard_tanh;
    #elif (ACTIVATION == SIGMOID)
    activate = sigmoid;
    #elif (ACTIVATION == TANH)
    activate = mytanh;
    #else
    #error "Invalid neuron activation function"
    #endif


//    // Loss function
//    // XXX XXX XXX XXX XXX XXX
//    double (*loss)(const array<double, INPUT_SIZE>&);
//
//    #if (LOSS == LSQ)
//    loss = lsq;
//    #elif (LOSS == LOGISTIC)
//    loss = logistic;
//    #else
//    #error "Invalid loss function"
//    #endif


    // Begin the training
    for (const auto &dset : dsets) {
        double sum = 0.;
        for (auto i = decltype(ninput){0}; i < ninput; ++i) {
            sum += weights.at(i)*dset.at(i);
        }

        const auto measured_output = activate(sum);
        //cout << measured_output << endl;
    }











//    // Neuron activation function
//    double (*activate)(const double&);
//
//    #if (ACTIVATION == LINEAR)
//    activate = linear;
//    #elif (ACTIVATION == SIGN)
//    activate = sign;
//    #elif (ACTIVATION == RELU)
//    activate = ReLU;
//    #elif (ACTIVATION == HARD_TANH)
//    activate = hard_tanh;
//    #elif (ACTIVATION == SIGMOID)
//    activate = sigmoid;
//    #elif (ACTIVATION == TANH)
//    activate = mytanh;
//    #else
//    #error "Invalid neuron activation function"
//    #endif
//
//
//    // Loss function
//    // XXX XXX XXX XXX XXX XXX
//    double (*loss)(const array<double, INPUT_SIZE>&);
//
//    #if (LOSS == LSQ)
//    loss = lsq;
//    #elif (LOSS == LOGISTIC)
//    loss = logistic;
//    #else
//    #error "Invalid loss function"
//    #endif




    return 0;
}
