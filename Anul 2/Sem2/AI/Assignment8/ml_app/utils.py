import numpy
from typing import Final

PI: Final[float] = numpy.pi


def random_float(start_inclusive: int, end_exclusive: int) -> float:
    return numpy.random.random() * (end_exclusive - start_inclusive) + start_inclusive


def random_point(start: int, end: int) -> (float, float):
    return random_float(start, end), random_float(start, end)
