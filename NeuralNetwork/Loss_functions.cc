#include <cassert>
#include <cmath>
#include <array>

#include "include/Activation_functions.hh"
#include "include/Loss_functions.hh"

using namespace std;


// Loss functions
double lsq(const double &measured_output,
           const double &expected_output) {
    const double diff = measured_output - expected_output;
    return diff*diff;
}

double logistic(const double &measured_output,
                const double &expected_output) {
    assert(measured_output > 0. and measured_output < 1.);  // Typically used along the sigmoid activation function
    return -log(fabs(0.5*(expected_output - 1.) + measured_output));
}


// Derivatives of the loss functions
double d_lsq(const double &measured_output,
             const double &expected_output) {
    return 2.*(measured_output - expected_output);
}

double d_logistic(const double &measured_output,
                  const double &expected_output) {
    const double x = 0.5*(expected_output - 1.) + measured_output; 
    return -sgn(x)/fabs(x);
}
