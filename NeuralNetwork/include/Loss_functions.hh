#ifndef LOSS_FUNCTIONS_HH
#define LOSS_FUNCTIONS_HH

#include <cmath>

double lsq(const double &measured_output,
           const double &expected_output);

double logistic(const double &measured_output,
                const double &expected_output);

#endif
