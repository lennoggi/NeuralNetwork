# Start by pulling a standard Ubuntu image
FROM ubuntu:24.04

# All the subsequent commands will be run under /app in the container
WORKDIR /app

# Install the necessary packages
RUN apt update && \
    DEBIAN_FRONTEND=noninteractive && \
    pip3 install numpy && \
    rm -rf /var/lib/apt/lists/*

# Copy the whole repository into /app under the container
COPY . .

# Generate the training dataset
RUN python3 Training_datasets_generator.py3

# Build the network
RUN cd NeuralNetwork && make -j3 options=OptionLists/Ubuntu_GNU_CI.cfg

# Run
RUN cd NeuralNetwork && ./NeuralNetwork_exe
