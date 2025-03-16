#include <cmath>
#include "include/Activation_functions.hh"

using namespace std;


// Activation functions
double linear(const double &x) {
    return x;
}

double sgn(const double &x) {
    // Magnitude 1, sign of x, except if x == 0
    return (x != 0.)*copysign(1., x);
}

double ReLU(const double &x) {
    return max(0., x);
}

double hard_tanh(const double &x) {
    return max(-1., min(1., x));
}

double sigmoid(const double &x) {
    return 1./(1. + exp(-x));
}

double mytanh(const double &x) {
    return tanh(x);
}


// Derivatives of the activation functions
double d_linear(const double &x) {
    return 1.;
}

double d_sgn(const double &x) {
    return 0.;
}

double d_ReLU(const double &x) {
    return (x > 0.);
}

double d_hard_tanh(const double &x) {
    return ((x > -1.) & (x < 1.));
}

double d_sigmoid(const double &x) {
    // Faster version
    //const double sgm = sigmoid(x);
    //return sgm*(1. - sgm);
    // ---------------------
    // More accurate version
    if (x >= 0.) {
        const double emx          = exp(-x);
        const double one_plus_emx = 1. + emx;
        return emx/(one_plus_emx*one_plus_emx);
    } else {
        const double ex          = exp(x);
        const double one_plus_ex = 1. + ex;
        return ex/(one_plus_ex*one_plus_ex);
    }
}

double d_mytanh(const double &x) {
    const double ch = cosh(x);
    return 1./(ch*ch);
}
