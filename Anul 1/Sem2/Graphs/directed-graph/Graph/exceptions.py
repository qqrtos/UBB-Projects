class DuplicateKeyError(Exception):
    def __init__(self, message):
        super().__init__(message)


class NotFoundError(Exception):
    def __init__(self, message):
        super().__init__(message)


class AlgorithmFailed(Exception):
    def __init__(self, message):
        super().__init__(message)
