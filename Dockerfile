# Start by pulling a standard Python3 image (works better than Ubuntu images
# with pip). See https://hub.docker.com/_/python .
##FROM ubuntu:latest
FROM python:latest  # Not always reliable

# All the subsequent commands will be run under /app in the container
WORKDIR /app

# Install NumPy
RUN pip3 install --no-cache-dir numpy

# Copy the whole repository into /app under the container
COPY . .

# Generate the training dataset
RUN python3 Training_datasets_generator.py3

# Build the network
RUN cd NeuralNetwork && make -j3 options=OptionLists/Ubuntu_GNU_CI.cfg

# Run
RUN cd NeuralNetwork && ./NeuralNetwork_exe
