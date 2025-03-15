#include <cassert>
#include <cmath>
#include <array>
#include "include/Loss_functions.hh"

using namespace std;


// Least squares (i.e. linear regression) loss function
double lsq(const double &measured_output,
           const double &expected_output) {
    const double diff = measured_output - expected_output;
    return diff*diff;
}


// Logistic regression loss function
double logistic(const double &measured_output,
                const double &expected_output) {
    assert(measured_output > 0. and measured_output < 1.);  // Typically used along the sigmoid activation function
    return -log(fabs(0.5*(expected_output - 1.) + measured_output));
}
