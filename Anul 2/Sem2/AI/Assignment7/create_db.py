from utils import random_point
from conf import *
from torch import Tensor, \
    save as torch_save, \
    as_tensor, \
    unsqueeze


class TrainingDatasetFactory:
    def __init__(self, point_count= 1000, start_position = -10, end_position = 10):
        self.__count = point_count
        self.__start_position = start_position
        self.__end_position = end_position
        self.__results = None
        self.__generate_points()

    def __generate_points(self):
        self.__points = as_tensor([random_point(self.__start_position, self.__end_position)
                                   for _ in range(self.__count)]
                                  )

    def compute(self):
        self.__results = unsqueeze(function(self.__points), 1)

    def save(self, file_name):
        torch_save(self, file_name)

    def __len__(self):
        return self.__count

    def get_batch_count(self, points_per_batch): # nr of points / size of a batch
        return self.__count // points_per_batch

    def get_batch(self, batch_index, points_per_batch):
        batch_points: Tensor = self.__points[batch_index * points_per_batch:(batch_index + 1) * points_per_batch]
        batch_results: Tensor = self.__results[batch_index * points_per_batch:(batch_index + 1) * points_per_batch]
        return batch_points, batch_results

    @property
    def points(self):
        return self.__points

    @property
    def results(self):
        return self.__results

    def __str__(self):
        s = ""
        for index in range(self.__count):
            s += "f({:.3f}, {:.3f}) = {:.3f}\n".format(self.points[index][0], self.points[index][1], self.results[index][0])
        return s
