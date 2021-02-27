import random


class Sentence:
    def __init__(self, file):
        self._score = 0
        self._loadSentence(file)

    @property
    def sentence(self):
        return self._sentence

    @property
    def score(self):
        return self._score

    def _loadSentence(self, file):
        self._sentence = ""

        with open(file, 'r') as f:
            sentences = f.readlines()

            selectedSentence = random.choice(sentences).strip()

            for character in selectedSentence:
                self._sentence += character
                if character != ' ':
                    self._score += 1

            self._sentence = list(self._scrambleSentence(self._sentence))

            f.close()

    def _scrambleSentence(self, text):
        words = text.split(' ')
        scrambledSentence = ""

        for word in words:
            scrambledWord = '' + word[0]
            letters = list(word[1:-1])

            while len(letters) != 0:
                randomIndex = random.randint(0, len(letters) - 1)
                scrambledWord += letters[randomIndex]
                letters.pop(randomIndex)

            scrambledWord += word[-1]
            scrambledSentence += scrambledWord + ' '

        return scrambledSentence

    def __str__(self):
        sentenceString = ""
        for letter in self.sentence:
            sentenceString += letter
        return sentenceString
