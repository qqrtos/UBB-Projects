import time

import torch.cuda
from torch.autograd import Variable

from ml_app.create_db import ImageDataset
from ml_app.conf import *
from torch import save as torch_save
from torch.optim import SGD, Adam
import matplotlib.pyplot as plt
from tqdm.auto import tqdm


def graph_loss(arr):
    plt.xlabel('epoch')
    plt.ylabel('loss')
    arr = [float(e) for e in arr]
    plt.plot(range(len(arr)), arr)
    plt.title('Loss evolution over {} epochs'.format(len(arr)))
    plt.show()


def graph_accuracy(arr):
    plt.xlabel('epoch')
    plt.ylabel('accuracy')
    arr = [float(e) for e in arr]
    plt.plot(range(len(arr)), arr)
    plt.title('Accuracy evolution over {} epochs'.format(len(arr)))
    plt.show()


class Trainer:
    __dataset: ImageDataset
    __model: Network
    __optimizer_batch: Adam
    __loss_list: []
    __average_loss_list: []

    def __init__(self, dataset, model, tester):
        self.__dataset = dataset
        self.__model = model
        self.__best_model_name = "latest_best_model_{}".format(time.time())
        self.__optimizer_batch = Adam(self.__model.parameters(), lr=learning_rate)
        self.__loss_list = []
        self.__average_loss_list = []
        self.__average_test_accuracy = []
        self.__tester = tester

    def update_learning_rate(self, epoch):
        for param_group in self.__optimizer_batch.param_groups:
            param_group["lr"] /= 2

    def train(self):
        best_accuracy = 0.0
        is_cuda = torch.cuda.is_available()
        progress_bar = tqdm(total=epoch_count * self.__dataset.get_batch_count(batch_size))
        for epoch in range(epoch_count):
            self.__model.train()
            train_accuracy = 0.0
            train_loss = 0.0
            local_sum = 0
            count = 0
            for batch_index in range(self.__dataset.get_batch_count(batch_size)):
                batch_images, batch_labels = self.__dataset.get_batch(batch_index, batch_size)
                if is_cuda:
                    batch_images = Variable(batch_images.cuda())
                    batch_labels = Variable(batch_labels.cuda())

                self.__optimizer_batch.zero_grad()
                outputs = self.__model(batch_images)
                loss = loss_function(outputs, batch_labels)
                loss.backward()
                self.__optimizer_batch.step()
                local_sum += loss.cpu().data.item()
                count += 1
                self.__loss_list.append(loss.cpu().data.item())

                train_loss += loss.cpu().data.item() * batch_images.size(0)
                _, prediction = torch.max(outputs.data, 1)

                train_accuracy += torch.sum(prediction == batch_labels.data)
                progress_bar.update(1)
            self.__average_loss_list.append(local_sum / count)
            train_accuracy /= len(self.__dataset)
            train_loss /= len(self.__dataset)

            if train_accuracy > best_accuracy:
                self.save(self.__best_model_name)
                best_accuracy = train_accuracy
            self.update_learning_rate(epoch)
            self.__average_test_accuracy.append(self.__tester.test())
        graph_loss(self.__average_loss_list)
        graph_accuracy(self.__average_test_accuracy)

    def save(self, file_name):
        torch_save(self.__model.state_dict(), file_name)
