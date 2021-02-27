from repository.Repository import *
from domain.Car import Car


class CarTextRepository(Repository):
    '''
    A text file backed repository for cars
    What do we want?
        *works the same as Repository
            -the program can change between CarTextRepository and Repository
               without changes to the source code
            =>modules are interchangable and independent
            =>this class has the same methods as Repository
        *load the cars from the text file when we build the Repo
        *save all car changes to a text file
    '''

    def __init__(self, fileName):
        super().__init__()
        self._fileName = fileName
        self._loadFile()  # load car data from a given file

    def store(self, object):
        '''
        Do the same thing as Repository.store
        Also save the cars to the file
        :return: -
        '''
        Repository.store(self, object)
        '''
        2 options:
            #1 - Repo.store worked => new car is stored => save it to file
            #2 - Repo.store failed => RepositoryException in Repo.store => car is not saved
        '''
        self._saveFile()

    # Private method
    def _loadFile(self):
        '''
        1. Open self._fileName fro text file reading
        2. For each line in input file:
            -> separate into tokens (by commas)
            -> build the car from the input
            -> store the car in the Repo
        3. Close input file
        :return: -
        '''
        with open(self._fileName, "r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                tokens = line.split(',')
                newCar = Car(*tokens)
                self.store(newCar)
            f.close()
