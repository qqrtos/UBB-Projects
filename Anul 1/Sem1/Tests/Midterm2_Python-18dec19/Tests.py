from Repository import *
from Service import *
import unittest


class TestDomain(unittest.TestCase):
    def driver(self):
        d = Driver('1', 'John')
        self.assertEqual(d.ID, '1')
        self.assertEqual(d.name, 'John')
        self.assertNotEqual(d.ID, 1)

    def order(self):
        o = Order('1', '23')
        self.assertEqual(o.ID, '1')
        self.assertEqual(o.distance, 23)
        with self.assertRaises(Exception):
            self.distance = '0'


class TestService(unittest.TestCase):
    def __init__(self):
        super().__init__()
        self.ordersRepo = Repository('orders.txt', Order)
        self.driversRepo = Repository('drivers.txt', Driver)
        self.serv = Service(self.ordersRepo, self.driversRepo)

    def addOrder(self):
        driver = '1'
        distance = '25'
        l1 = len(self.ordersRepo)
        self.serv.addOrder(driver, distance)
        self.assertEqual(l1 + 1, len(self.ordersRepo))
        distance = '0zc'
        with self.assertRaises(Exception):
            self.serv.addOrder(driver, distance)
