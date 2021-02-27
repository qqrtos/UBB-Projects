from Repository import *
from Service import *


class UserInterface:
    def __init__(self, service, driversRepo, ordersRepo):
        self._service = service
        self._drivers = driversRepo
        self._orders = ordersRepo

    @staticmethod
    def printMenu():
        print("1. Add an order.")
        print("2. Display all orders.")
        print("3. Income for a driver.")
        print("x. Exit.")

    def addOrder(self):
        driverID = input("Driver ID: ")
        distance = input("Distance: ")
        self._service.addOrder(driverID, distance)

    def displayOrders(self):
        formatedOrders = ''
        for i in range(len(self._orders)):
            formatedOrders += str(self._orders[i])
        print(formatedOrders)

    def printIncome(self):
        driverID = input("Driver ID: ")
        print(self._service.income(driverID))

    def start(self):
        commands = {
            '1': self.addOrder,
            '2': self.displayOrders,
            '3': self.printIncome,
            'x': exit
        }
        self.printMenu()
        while True:
            opt = input("Command:> ")
            if opt in commands.keys():
                try:
                    commands[opt]()
                except Exception as e:
                    print(e)
            else:
                print("Invalid command!")


drivers = Repository('drivers.txt', Driver)
orders = Repository('orders.txt', Order)
service = Service(orders, drivers)
UI = UserInterface(service, drivers, orders)
UI.start()
