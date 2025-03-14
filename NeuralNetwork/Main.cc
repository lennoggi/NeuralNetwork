#include <array>
#include <string>
#include <iostream>
#include <fstream>
#include <random>

//#include "include/Activation_functions.hh"
#include "Parameters.hh"

using namespace std;


int main() {
    // Neuron activation function
/*    double (*activate)(const double&);

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


    // Loss function
    // XXX XXX XXX XXX XXX XXX
    double (*loss)(const array<double, INPUT_SIZE>&);

    #if (LOSS == LSQ)
    loss = lsq;
    #elif (LOSS == LOGISTIC)
    loss = logistic;
    #else
    #error "Invalid loss function"
    #endif

*/



    // Read the first line just to count the number of input values per dataset
    size_t   ninput;
    string   line;
    ifstream training_datasets_file(TRAINING_DATASETS_FILENAME);

    if (not training_datasets_file.is_open()) {
        cerr << "Unable to open file '" << TRAINING_DATASETS_FILENAME << "'" << endl;
        return 1;
    }

    if (getline(training_datasets_file, line)) {
        if (not line.empty() and line.at(0) != '#') {
            ninput = line.size();
            if (ninput < 2) {  // At least two values needed per dataset: one input and one output
                cerr << "Need at least one input value per dataset in file '"
                     << TRAINING_DATASETS_FILENAME << "' (" << ninput << " provided)" << endl;
                return 1;
            }
        }
    }


    /* --------------
     * Begin training
     * -------------- */
    training_datasets_file.clear();
    training_datasets_file.seekg(0, ios::beg);

    while (getline(training_datasets_file, line)) {
        if (line.empty() or line.at(0) == '#') {
            continue;
        }

        for (const auto &word : line) {
            
        }
    }

    training_datasets_file.close();




    /* Initialize the weights as random numbers between 0 and 1
     * NOTE: 'mt19937' is a Mersenne Twister generator, but other options are available
     *       (see https://cplusplus.com/reference/random for more options)      */
/*    #if (RAND_SEED > 0)
    mt19937 gen(RAND_SEED);
    #elif (RAND_SEED == -1)
    random_device rd;  // Use machine entropy as 
    mt19937 gen(rd());
    #else
    #error "Invalid seed for the random number generator"
    #endif

    uniform_real_distribution<double> dist(0., 1.);
    array<double, INPUT_SIZE>         weights;

    cout << endl
         << "===============" << endl
         << "Initial weights" << endl
         << "===============" << endl;

    for (auto &w : weights) {
        w = dist(gen);
        cout << w << endl;
    }*/

/*


    // Calculate the sum of the inputs weighted by the weights
    double sum = 0.;

    for (int i = 0; i < INPUT_SIZE) {
        sum += input.at(i)*weigths.at(i);
    }


*/
    return 0;
}
