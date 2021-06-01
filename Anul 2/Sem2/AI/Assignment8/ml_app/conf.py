from ml_app.network_model import Network
from torch.nn import CrossEntropyLoss

batch_size = 16
epoch_count = 10
learning_rate = 0.01

cel_loss = CrossEntropyLoss()
loss_function = cel_loss


def get_ann():
    return Network()
