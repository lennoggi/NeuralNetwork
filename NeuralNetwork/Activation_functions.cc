#include <cmath>
#include "include/Activation_functions.hh"

using namespace std;


double linear(const double &x) {
    return x;
}

double sgn(const double &x) {
    return copysign(x, 1.);
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
