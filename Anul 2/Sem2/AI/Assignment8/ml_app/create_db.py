from abc import ABC

from torchvision import transforms
from torch.utils.data import Dataset
from tqdm import tqdm

from ml_app.utils import random_point
from ml_app.conf import *
from torch import Tensor, \
    save as torch_save, \
    as_tensor, \
    unsqueeze, \
    stack as torch_stack

from os import scandir
from PIL import Image as PILImage
from numpy.random import randint
import numpy as np


# usable when the directory represents an entire class
class ImagesPathFactory:
    __storage: [{}]

    def __init__(self):
        self.__storage = []

    # directory must contain only files
    def load_directory(self, path_to_directory, label) -> None:
        if path_to_directory[-1] != '/':
            path_to_directory = path_to_directory + '/'

        for file in scandir(path_to_directory):
            self.__storage.append({
                'image_path': path_to_directory + file.name,
                'label': label
            })

    @property
    def dataset(self) -> [{}]:
        return self.__storage


class ImageDataset(Dataset, ABC):
    __images: [PILImage]
    __labels: []
    __image_size: int
    __transforms = transforms.Compose

    def __init__(self, paths):
        self.__images = []
        self.__labels = []
        self.__image_size = 224
        for image_info in paths:
            self.__images.append(PILImage.open(image_info['image_path']))
            self.__labels.append(image_info['label'])

        self.__transforms = transforms.Compose([
            transforms.Resize(self.__image_size),
            transforms.CenterCrop(self.__image_size),
            transforms.ToTensor(),
            transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
        ])

        for index in tqdm(range(len(self.__images))):
            image = self.__images[index]
            image = image.convert("RGB") # transform to jpg
            self.__images[index] = self.__transforms(image)

    def shuffle(self):
        size = len(self)
        for _ in range(size * 2):
            index1 = randint(0, size)
            index2 = randint(0, size)
            self.__images[index1], self.__images[index2] = self.__images[index2], self.__images[index1]
            self.__labels[index1], self.__labels[index2] = self.__labels[index2], self.__labels[index1]

    def images(self, raw=False) -> [PILImage]:
        if raw is True:
            return self.__images
        return torch_stack(self.__images)

    def labels(self, raw=False) -> []:
        if raw is True:
            return self.__labels
        return as_tensor(self.__labels)

    def __getitem__(self, index) -> ([PILImage], []):
        return self.images()[index], self.labels()[index]

    def __len__(self) -> int:
        return len(self.images(True))

    def get_batch_count(self, points_per_batch):
        if len(self) > points_per_batch:
            return len(self) // points_per_batch
        if len(self) == 0:
            return 0
        return 1

    def get_batch(self, batch_index: int, points_per_batch: int) -> (Tensor, Tensor):
        batch_images: Tensor = self.images()[batch_index * points_per_batch:(batch_index + 1) * points_per_batch]
        batch_labels: Tensor = self.labels()[batch_index * points_per_batch:(batch_index + 1) * points_per_batch]
        return batch_images, batch_labels

    # ratio must be between 0 and 1
    # the dataset will be split into 2
    # one containing (ratio * 100)% of the dataset
    # the other one ((1 - ratio) * 100)% of the dataset (the rest)
    def split(self, ratio) -> (any, any):
        first_set = [self.images(True)[:], self.labels(True)[:]]
        second_set = [[], []]
        first_set_target_size = len(first_set[0]) * ratio

        while size := len(first_set[0]) > first_set_target_size:
            target_entry_index = randint(0, size)
            target_entry_image = first_set[0].pop(target_entry_index)
            target_entry_label = first_set[1].pop(target_entry_index)
            second_set[0].append(target_entry_image)
            second_set[1].append(target_entry_label)
        first = ImageDataset([])
        first.__images = first_set[0]
        first.__labels = first_set[1]
        first.shuffle()
        second = ImageDataset([])
        second.__images = second_set[0]
        second.__labels = second_set[1]
        second.shuffle()
        return first, second
