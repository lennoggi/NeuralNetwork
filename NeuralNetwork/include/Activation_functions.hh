#ifndef ACTIVATIONS_FUNCTIONS_HH
#define ACTIVATIONS_FUNCTIONS_HH

double linear(const double &x);
double sgn(const double &x);
double ReLU(const double &x);
double hard_tanh(const double &x);
double sigmoid(const double &x);
double mytanh(const double &x);

double d_linear(const double &x);
double d_sgn(const double &x);
double d_ReLU(const double &x);
double d_hard_tanh(const double &x);
double d_sigmoid(const double &x);
double d_mytanh(const double &x);

#endif
