from domain import *


class SaveLoadFileException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class UserInterface:
    def __init__(self, game):
        self._game = game

    @property
    def game(self):
        return self._game

    def _saveGame(self):
        self.game.saveGame()

    def _loadGame(self):
        self.game.loadGame()

    def getInput(self):
        option = input('> ')
        if option == "save game":
            self._saveGame()
        if option == "load game":
            self._loadGame()
            raise SaveLoadFileException("Game was loaded.")

        option = option.strip().split(' ')
        if len(option) != 3:
            raise GameError("Input has 3 parameters.")

        try:
            row = int(option[0])
            col = int(option[1])
            symbol = option[2].capitalize()
            assert symbol in ['X', 'O']
        except:
            raise GameError("Invalid input!")

        return (row, col, symbol)

    def start(self):
        print("\nTo save the game to file, input command 'save game'.")
        print("To load a game, input command 'load game'.\n")
        print(self.game.board)
        gameOver = False
        winner = None

        while not gameOver:
            try:
                row, col, symbol = self.getInput()
                self.game.playerMove(row, col, symbol)
                self.game.computerMove()

                gameOver, winner = self.game.won()

                print(self.game.board)
            except GameError as GE:
                print(GE)
            except SaveLoadFileException as SLFE:
                print(SLFE)
                print(self.game.board)

        print("\n\t\tGame over!\n\t\tWinner: " + winner)


board = Board()
computer = Computer(board)
game = Game(board, computer)
UI = UserInterface(game)
UI.start()
