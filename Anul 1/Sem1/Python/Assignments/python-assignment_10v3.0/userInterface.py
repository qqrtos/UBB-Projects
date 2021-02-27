from domain import *


class UserInterface:
    def __init__(self, game):
        self._game = game

    @property
    def game(self):
        return self._game

    def start(self):
        pass