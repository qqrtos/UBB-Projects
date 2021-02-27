from service import Service
from service import GameException


class UserInterface:
    def __init__(self, serv):
        self._serv = serv

    def _printMenu(self):
        print("\n1. Guess.\n2. New Game.\n3. Exit\n")

    def start(self):
        self._printMenu()
        self._serv.newGame()
        while True:
            opt = input("Option:> ")
            if opt == '1':
                try:
                    guess = self._serv.guess(input("Guess:> "))
                    bulls = self._serv.numBulls(guess)
                    cows = self._serv.numCows(guess)

                    if bulls == 4:
                        print("YOU WON!")
                        break
                    elif self._serv.isRepeatedGuess(guess) == True:
                        print("\nYou already tried that!!! \n\t\t GAME LOST")
                        break
                    else:
                        print('B: ' + str(bulls))
                        print('C: ' + str(cows))
                except GameException as GE:
                    print(GE)

            elif opt == '2':
                self._serv.newGame()
            elif opt == '3':
                break
            else:
                print("Bad choice")


s = Service()
UI = UserInterface(s)
UI.start()
