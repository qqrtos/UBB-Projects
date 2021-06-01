import torch.cuda
from torch.autograd import Variable
from tqdm import tqdm

from ml_app.create_db import ImageDataset
from conf import *
from torch.optim import SGD


class Tester:
    __dataset: ImageDataset
    __model: Network

    def __init__(self, dataset: ImageDataset, model: Network):
        self.__dataset = dataset
        self.__model = model

    def test(self):
        self.__model.eval()
        test_accuracy = 0.0
        is_cuda = torch.cuda.is_available()

        for batch_index in tqdm(range(self.__dataset.get_batch_count(batch_size))):
            batch_images, batch_labels = self.__dataset.get_batch(batch_index, batch_size)
            if is_cuda:
                batch_images = Variable(batch_images.cuda())
                batch_labels = Variable(batch_labels.cuda())

            outputs = self.__model(batch_images)
            _, prediction = torch.max(outputs.data, 1)

            test_accuracy += torch.sum(torch.eq(prediction, batch_labels.data))
        return test_accuracy / len(self.__dataset)
