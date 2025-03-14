#ifndef LOSS_FUNCTIONS_HH
#define LOSS_FUNCTIONS_HH

#include <array>
#include "../Parameters.hh"


double lsq(const std::array<double, INPUT_SIZE> &input,
           const std::array<double, INPUT_SIZE> &weigths,
           const double                         &expected_output) {

double logistic(const std::array<double, INPUT_SIZE> &input,
                const std::array<double, INPUT_SIZE> &weigths,
                const double                         &expected_output) {

#endif
