import torch
from torch.nn import Module as NeuralNetworkBase, \
    Conv2d as ConvolutionalLayer2D, \
    BatchNorm2d as BatchNormalization2D, \
    ReLU, Linear, \
    MaxPool2d, AvgPool2d, \
    Sequential
import torch.nn.functional as convolution_functions

class Unit(NeuralNetworkBase):
    # noinspection PyTypeChecker
    def __init__(self, in_channels, out_channels):
        super(Unit, self).__init__()

        self.convolutionLayer = ConvolutionalLayer2D(in_channels=in_channels, kernel_size=3, out_channels=out_channels,
                                                     stride=1, padding=1)
        self.batchNormalization = BatchNormalization2D(num_features=out_channels)
        self.activate = ReLU()

    def forward(self, input_image):
        output = self.convolutionLayer(input_image)
        output = self.batchNormalization(output)
        output = self.activate(output)

        return output


class Network(NeuralNetworkBase):
    def __init__(self, num_classes=2):
        super(Network, self).__init__()

        # Create 14 layers of the unit with max pooling in between
        self.unit1 = Unit(in_channels=3, out_channels=32)
        self.unit2 = Unit(in_channels=32, out_channels=32)
        self.unit3 = Unit(in_channels=32, out_channels=32)

        self.pool1 = MaxPool2d(kernel_size=2)

        self.unit4 = Unit(in_channels=32, out_channels=64)
        self.unit5 = Unit(in_channels=64, out_channels=64)
        self.unit6 = Unit(in_channels=64, out_channels=64)
        self.unit7 = Unit(in_channels=64, out_channels=64)

        self.pool2 = MaxPool2d(kernel_size=2)

        self.unit8 = Unit(in_channels=64, out_channels=128)
        self.unit9 = Unit(in_channels=128, out_channels=128)
        self.unit10 = Unit(in_channels=128, out_channels=128)
        self.unit11 = Unit(in_channels=128, out_channels=128)

        self.pool3 = MaxPool2d(kernel_size=2)

        self.unit12 = Unit(in_channels=128, out_channels=128)
        self.unit13 = Unit(in_channels=128, out_channels=128)
        self.unit14 = Unit(in_channels=128, out_channels=128)

        self.average_pool = AvgPool2d(kernel_size=4)

        # Add all the units into the Sequential layer in exact order
        self.net = Sequential(self.unit1, self.unit2, self.unit3, self.pool1, self.unit4, self.unit5, self.unit6,
                              self.unit7, self.pool2, self.unit8, self.unit9, self.unit10, self.unit11, self.pool3,
                              self.unit12, self.unit13, self.unit14, self.average_pool)

        self.fc = Linear(in_features=128 * 7 * 7, out_features=num_classes)

        if torch.cuda.is_available():
            self.cuda()

    def forward(self, input_image):
        output = self.net(input_image)
        # print(output.shape)
        output = output.view(output.size(0), -1)
        output = self.fc(output)
        return output
