import numpy as np

def neural_network(inputs, weights):
    """
     Takes an input vector and runs it through a 1-layer neural network
     with a given weight matrix and returns the output.

     Arg:
       inputs - 2 x 1 NumPy array
       weights - 2 x 1 NumPy array
     Returns (in this order):
       out - a 1 x 1 NumPy array, representing the output of the neural network
    """
    dot_product = np.dot(np.transpose(weights), inputs)
    return np.tanh(dot_product)

def main():
    inputs = np.random.random([3, 1])
    weights = np.random.random([3, 1])
    z1 = neural_network(inputs, weights)
    print(z1)

if __name__ == "__main__":
    main()
