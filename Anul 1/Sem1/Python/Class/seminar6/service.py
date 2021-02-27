import random


class GameException(Exception):
    '''
    GameException is a Python Exception.
    '''

    def __init__(self, message):
        super().__init__(message)


class Service:
    def __init__(self):
        self._guessList = []

    def _generateNumber(self):
        '''
        Generate a valid number.
        :return:
        '''
        digitsList = [0] * 10
        number = []
        n = random.randrange(1, 10)
        number.append(n)
        digitsList[n] = 1
        for i in range(3):
            n = random.randrange(0, 10)
            while digitsList[n] == 1:
                n = random.randrange(0, 10)
            number.append(n)
            digitsList[n] = 1
        return number

    def newGame(self):
        self._number = self._generateNumber()
        # print(self._number)

    def numBulls(self, guess):
        '''
        Returns the number of bulls.
        :param guess: user's guess
        :return: number of bulls
        '''
        n = 0
        for i in range(4):
            if self._number[i] == guess[i]:
                n += 1
        return n

    def numCows(self, guess):
        '''
        Returns the number of cows.
        :param guess: user's guess
        :return: number of cows
        '''
        n = 0
        for i in range(4):
            if (guess[i] in self._number) and (guess[i] != self._number[i]):
                n += 1
        return n

    def isRepeatedGuess(self, num):
        '''
        Determines whether the user gas already tried that number
        :return: yes / no
        '''
        try:
            assert num not in self._guessList
            self._guessList.append(num)
            return False
        except:
            return True

    def guess(self, userGuess):
        '''
        Validate a guess and convert it to a list.
        :param userGuess: the guess
        :return: the guess split in digits as a list
        '''
        try:
            assert len(userGuess) == 4
            guessList = [int(x) for x in userGuess]
            return guessList
        except:
            raise GameException("Introduced number isn't valid.")


'''
1. Generate 1000 numbers.
2. For each generated number:
    *number in [1023, 9876]
    *check no duplicate digits
'''


def test_generate():
    s = Service()
    for i in range(1000):
        s.newGame()
        numberAux = 0
        for i in range(4):
            numberAux = numberAux * 10 + int(s._number[i])  # transform into number from a list

        assert numberAux in range(1023, 9877)  # check the interval
        appearances = [0] * 10

        while numberAux > 0:  # check for duplicate digits
            appearances[numberAux % 10] += 1
            numberAux = numberAux // 10
        for i in range(10):
            if appearances[i] > 1:
                assert False


test_generate()
