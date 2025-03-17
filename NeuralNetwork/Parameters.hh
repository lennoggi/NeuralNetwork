#ifndef PARAMETERS_HH
#define PARAMETERS_HH


// ****************************** DON'T TOUCH **********************************

// Neuron activation functions
#define LINEAR    1
#define SIGN      2
#define RELU      3
#define HARD_TANH 4
#define SIGMOID   5
#define TANH      6

// Loss functions
#define LSQ      100
#define LOGISTIC 101

// *****************************************************************************


// Name of the file containing the training datasets
#define TRAINING_DATASETS_FILENAME "../Training_datasets.asc"

// Number of training epochs
#define N_EPOCHS 10

/* Size of the batches of training datasets fed to the network. If set to 1, the
 * weights are updated after processing each dataset; if set to the number of
 * training datasets, the weights are only updated after processing all datasets.*/
#define BATCH_SIZE 10

/* Learning rate, i.e., speed at which the weights are updated via loss gradient
 * descent. Too small numbers lead to slow learning and can potentially cause
 * algorithm to get stuck at local minima of L(w) (loss function, function of the
 * weights); too high values may cause the algorithm to not converge.           */
#define LEARNING_RATE 1.e-04

/* Seed feeding the random numbers generator used to initialize the weights.
 * Use a positive integer or -1 to use time(NULL) as the seed.                  */
#define RAND_SEED -1 

// Neuron activation function
#define ACTIVATION LINEAR

// Loss function
#define LOSS LSQ


#endif
