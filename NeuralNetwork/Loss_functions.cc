#include <array>
#include "include/Loss_functions.hh"
#include "Parameters.hh"

using namespace std;


// Least squares (i.e. linear regression) loss function
double lsq(const array<double, INPUT_SIZE> &input,
           const array<double, INPUT_SIZE> &weigths,
           const double                    &expected_output) {
    double sum = 0.;

    for (int i = 0; i < INPUT_SIZE) {
        sum += input.at(i)*weigths.at(i);
    }

    return sum;

    const double diff = expected_output - sum;
    return diff*diff
}


// Logistic regression loss function
double logistic(const double                  &expected_output,
                const array<double, INPUT_SIZE> &weigths) {
