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

/* Seed feeding the random numbers generator used to initialize the weights.
 * Use a positive integer or -1 to use time(NULL) as the seed.                  */
#define RAND_SEED -1 

// Neuron activation function
#define ACTIVATION LINEAR

// Loss function
#define LOSS LSQ


#endif
