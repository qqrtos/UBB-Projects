class Repository:
    def __init__(self, file, entity):
        self._data = []
        self._file = file
        self._entity = entity
        self._loadFile()

    def __len__(self):
        return len(self._data)

    def __getitem__(self, index):
        return self._data[index]

    def _loadFile(self):
        '''
        Imports data from a file to the repo list
        '''
        with open(self._file, 'r') as f:
            lines = f.readlines()
            for line in lines:
                tokens = line.strip().split(',')
                self._data.append(self._entity(*tokens))
            f.close()

    def _saveFile(self):
        '''
        Saves data inside a file
        '''
        with open(self._file, 'w') as f:
            for element in self._data:
                f.write(str(element))
            f.close()

    def elementWithID(self, ID):
        '''
        Searches for an element with the given ID.
        Returns the element if it is found and None otherwise.
        '''
        for elem in self._data:
            if elem.ID == ID:
                return elem
        return None

    def store(self, element):
        '''
        Adds an element into repo.
        '''
        self._data.append(element)
        self._saveFile()
