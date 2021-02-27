from Domain import *


class Service:
    def __init__(self, orders, drivers):
        self._drivers = drivers
        self._orders = orders

    def addOrder(self, driverID, distance):
        '''
        Adds an order to the repository
        Input: driver's ID and the distance
        Return: -
        '''
        if self._drivers.elementWithID(driverID) is None:
            raise Exception("Driver is not in repo.")
        order = Order(driverID, distance)
        self._orders.store(order)

    def income(self, driverID):
        '''
        Returns the income for one driver.
        '''
        if self._drivers.elementWithID(driverID) is None:
            raise Exception("Driver not in repo.")
        data = driverID + ' ' + self._drivers.elementWithID(driverID).name + ' '
        s = 0
        for i in range(len(self._orders)):
            if self._orders[i].ID == driverID:
                s += (2.5 * self._orders[i].distance)
        data += str(s)
        return data
