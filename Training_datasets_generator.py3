# =====================================================================
# This script generates ndsets training datasets for the neural network
# implemented in the NeuralNetwork directory
# =====================================================================
import numpy as np


# ***** Parameters *****

# Input values will be drawn from a uniform distribution in this range
input_range = (-10., 10.)

# Coefficients used to calculate the output:
#  y = coeffs[0]*x[0] + coeffs[1]*x[1] + ... + coeffs[-1]*x[-1] + noise
coeffs      = (3., 2., -1., 0.5, 2.5)

# Seed for the random numbers generator (integer). Set to a negative number to
# use a random (?) seed.
rand_seed = -1

# The larger this parameter, the larger the standard deviation of the Gaussian
# distribution the noise is drawn from
noise_scale = 1.

# Number of training datasets to be generated
ndsets = 100

# Name of the file where the training datasets will be saved
outfilename = "Training_datasets.asc"

# **********************


input_size = len(coeffs)

xmin = input_range[0]
xmax = input_range[1]

if rand_seed > 0: np.random.seed(rand_seed)
noise = np.random.normal(loc = 0.5*(xmin + xmax), scale = noise_scale)


with open(outfilename, "w") as f:
    f.write("# " + str(ndsets)     + " training datasets\n"          +
            "# " + str(input_size) + " input values per dataset\n"   +
            "# Columns 1 to " + str(input_size) + ": input values\n" +
            "# Column " + str(input_size + 1) + ": expected output value plus some noise\n")

    for n in range(ndsets):
        x = np.random.uniform(low = xmin, high = xmax, size = input_size)
        y = np.dot(coeffs, x) + noise

        for i in range(input_size):
            f.write("{:.16f}\t".format(x[i]))
        f.write("{:.16f}\n".format(y))

print("File '" + outfilename + "' generated successfully")
