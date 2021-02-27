class Driver:
    '''
    Attributes of a driver
    '''

    def __init__(self, ID, name):
        self._ID = ID
        self.name = name

    @property
    def ID(self):
        return self._ID

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, newName):
        self._name = newName

    def __str__(self):
        return self.ID + ',' + self.name + '\n'


class Order:
    '''
    Attributes of an order
    '''

    def __init__(self, driverID, distance):
        self._ID = driverID
        self.distance = distance

    @property
    def ID(self):
        return self._ID

    @property
    def distance(self):
        return self._distance

    @distance.setter
    def distance(self, newDist):
        try:
            newDist = int(newDist)
            assert newDist > 1
        except:
            raise Exception("Wrong distance.")
        self._distance = newDist

    def __str__(self):
        return self.ID + ',' + str(self.distance) + '\n'
