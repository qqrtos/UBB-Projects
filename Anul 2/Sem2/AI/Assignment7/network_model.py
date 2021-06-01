import torch
from torch.nn import Module as NeuralNetworkBase
import torch.nn.functional as convolution_functions


class Network(NeuralNetworkBase):
    def __init__(self, n_feature, n_output):
        # we have two layers: a hidden one and an output one
        super(Network, self).__init__()
        h1 = 75
        h3 = 75
        self.hidden = torch.nn.Sequential(
            torch.nn.Linear(n_feature, h1),
        )
        self.output = torch.nn.Linear(h3, n_output)

    def forward(self, x):
        # a function that implements the forward propagation of the signal
        # observe the ReLU function applied on the output of the hidden layer
        x = convolution_functions.relu(self.hidden(x))
        x = self.output(x)
        return x
