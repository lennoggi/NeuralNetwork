[![CI](https://github.com/lennoggi/NeuralNetwork/actions/workflows/CI.yml/badge.svg)](https://github.com//lennoggi/NeuralNetwork/actions/workflows/CI.yml)
[![Docker image CI](https://github.com/lennoggi/NeuralNetwork/actions/workflows/Docker_image_CI.yml/badge.svg)](https://github.com//lennoggi/NeuralNetwork/actions/workflows/Docker_image_CI.yml)

# NeuralNetwork
A simple neural network model with one computational node performing linear regression

## Instructions
1. Generate training datasets via `python3 Training_datasets_generator.py3`. You can edit the script to modify the datasets parameters.
2. cd into `NeuralNetwork`
3. Edit `Parameters.hh` if needed
4. Set up the right optionlist for your machine if needed (start from `OptionLists/`Ubuntu_Intel.cfg`)
5. Compile the code with `make -j3 options=OptionLists/<optionlist>`
6. Run the code with `./NeuralNetwork_exe`
