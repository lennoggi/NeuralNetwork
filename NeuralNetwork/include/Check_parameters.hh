#ifndef CHECK_PARAMETERS_HH
#define CHECK_PARAMETERS_HH

#include "../Parameters.hh"


static_assert(RAND_SEED > 0 or RAND_SEED == -1);

static_assert(ACTIVATION == LINEAR    or ACTIVATION == SIGN    or ACTIVATION == RELU or
              ACTIVATION == HARD_TANH or ACTIVATION == SIGMOID or ACTIVATION == TANH);

static_assert(LOSS == LSQ or LOSS == LOGISTIC);


#endif
