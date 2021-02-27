from repository.CarTextRepository import *


carRepo = CarTextRepository("cars.txt")
clientRepo = ClientTextRepository("client.txt")
RentalRepo = RentalTextRepository("rental.txt", carRepo, clientRepo)

'''
    When loading a rental from the file:
        read cliendID and carID
        client=clientRepo.find(clientID)
        car=carRepo.find(carID)
'''

'''
    Inheritance :)
        -> important in OOP
        -> only used when using classes
        -> allows us to reuse code
        -> makes modules interchangeable
        
    By default, a class that doesn't inherit any other class, it inherits
    the class object (which has some basic functions)
                * it has __str__
                * no __len__
'''
