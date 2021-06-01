from network_model import Network
from utils import PI
from torch import Tensor, \
    sin as torch_sin, \
    as_tensor
from torch.nn import MSELoss

batch_size = 16
epoch_count = 2000
learning_rate = 0.003

mse_loss = MSELoss()
loss_function = mse_loss


def get_ann():
    return Network(n_feature=2, n_output=1)# n_feature = x and y | output f(x,y)


def function(points: Tensor):
    return torch_sin(as_tensor([point[0] + point[1] / PI for point in points]))
