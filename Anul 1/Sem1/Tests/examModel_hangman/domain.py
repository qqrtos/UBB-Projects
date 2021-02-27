from random import choice


class Letter:
    def __init__(self, char):
        self._isHidden = True
        self._letter = char

    @property
    def isHidden(self):
        return self._isHidden

    @isHidden.setter
    def isHidden(self, value):
        if value not in [True, False]:
            raise IOError("Bad code!")
        self._isHidden = value

    @property
    def letter(self):
        return self._letter


class Sentence:
    def __init__(self, file):
        self._sentence = []
        self._loadFile(file)

    def _loadFile(self, file):
        with open(file, "r", ) as openFile:
            lines = openFile.readlines()

            # choose random sentence from text file
            text = choice(lines).strip()

            # format sentence
            for c in text:
                self._sentence.append(Letter(c))

            # print first letters and spaces
            self._prepareSentence()

            openFile.close()

    def showLetter(self, char):
        for j in range(len(self._sentence)):
            if char == self._sentence[j].letter:
                self._sentence[j].isHidden = False

    def _prepareSentence(self):
        self._sentence[0].isHidden = False

        # show first and last letter of each word
        # also show spaces
        for i in range(1, len(self._sentence) - 1):
            if self._sentence[i + 1].letter == ' ':
                self._sentence[i].isHidden = False
            elif self._sentence[i - 1].letter == ' ':
                self._sentence[i].isHidden = False
            elif self._sentence[i].letter == ' ':
                self._sentence[i].isHidden = False

        # show letters currently hidden, but which appear in word's end/beginning
        for i in range(len(self._sentence)):
            if not self._sentence[i].isHidden:
                self.showLetter(self._sentence[i].letter)

        self._sentence[-1].isHidden = False

    @property
    def sentence(self):
        return self._sentence

    def __str__(self):
        sentence = ""
        for c in self.sentence:
            if c.isHidden is True:
                sentence += '-'
            else:
                sentence += c.letter
        return sentence


class Computer:
    def __init__(self):
        self._hangman = []
        for c in 'hangman':
            self._hangman.append(Letter(c))

    def move(self):
        indx = 0
        while not self._hangman[indx].isHidden:
            indx += 1
        self._hangman[indx].isHidden = False

    def __str__(self):
        sentence = ""
        for c in self._hangman:
            if c.isHidden is True:
                sentence += '-'
            else:
                sentence += c.letter
        return sentence


class Game:
    def __init__(self, sentence, computer):
        self._sentence = sentence
        self._computer = computer

    @property
    def sentence(self):
        return self._sentence

    @property
    def computer(self):
        return self._computer

    def playerMove(self, char):
        if Letter(char) not in self.sentence:
            self.computer.move()
        else:
            for letter in self.sentence:
                if letter.isHidden == False and char == letter.letter:
                    self.computer.move()
                    return
            self.sentence.showLetter(char)
