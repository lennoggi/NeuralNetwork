#ifndef CHECK_PARAMETERS_HH
#define CHECK_PARAMETERS_HH

#include "../Parameters.hh"


static_assert(N_EPOCHS > 0);
static_assert(LEARNING_RATE > 0);
static_assert(BATCH_SIZE > 0);
static_assert(RAND_SEED > 0 or RAND_SEED == -1);

static_assert(ACTIVATION == LINEAR    or ACTIVATION == SIGN    or ACTIVATION == RELU or
              ACTIVATION == HARD_TANH or ACTIVATION == SIGMOID or ACTIVATION == TANH);

static_assert(LOSS == LSQ or LOSS == LOGISTIC);

#if (LOSS == LOGISTIC || ACTIVATION != SIGMOID)
#error "The logistic loss function must be used along with the sigmoid activation function"
#endif


#endif
