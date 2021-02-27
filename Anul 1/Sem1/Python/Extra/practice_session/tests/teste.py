from domain import Plm
import unittest


class test_Plm(unittest.TestCase):
    def testAdd(self):
        p = Plm()
        self.assertEqual(p.Add(2, 0), 2)
