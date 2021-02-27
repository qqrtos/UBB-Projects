from domain import *


class UserInterface:
    def __init__(self, game):
        self.game = game

    def start(self):
        pass


s = Sentence("repository/sentences.txt")
print(s)
