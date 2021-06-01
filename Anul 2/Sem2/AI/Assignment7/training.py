from create_db import TrainingDatasetFactory
from network_model import Network
from conf import *
from torch import load as torch_load, \
    save as torch_save
from torch.optim import SGD
import matplotlib.pyplot as plt
from tqdm.auto import tqdm


def graph_loss(loss_array):
    plt.xlabel('epoch')
    plt.ylabel('loss')
    loss_array = [float(e) for e in loss_array]
    plt.plot(range(len(loss_array)), loss_array)
    plt.title('Loss evolution over {} epochs'.format(len(loss_array)))
    plt.show()


class Trainer:
    def __init__(self, training_dataset_file, model_file=None):
        self.__dataset = torch_load(training_dataset_file)
        self.__ann = get_ann()
        if model_file is not None:
            self.__ann.load_state_dict(torch_load(model_file))
            self.__ann.eval()
        self.__optimizer_batch = SGD(self.__ann.parameters(), lr=learning_rate)
        self.__loss_list = []
        self.__average_loss_list = []

    def train(self):
        for epoch in tqdm(range(epoch_count)):
            local_sum = 0
            count = 0
            for batch_index in range(self.__dataset.get_batch_count(batch_size)):
                batch_points, batch_results = self.__dataset.get_batch(batch_index, batch_size)
                prediction = self.__ann(batch_points)
                loss = loss_function(prediction, batch_results)
                local_sum += loss
                count += 1
                self.__loss_list.append(loss)
                self.__optimizer_batch.zero_grad()
                loss.backward()
                self.__optimizer_batch.step()
            self.__average_loss_list.append(local_sum / count)

        graph_loss(self.__average_loss_list)

    def save(self, file_name):
        torch_save(self.__ann.state_dict(), file_name)
