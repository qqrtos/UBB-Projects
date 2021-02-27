class UndoController:
    def __init__(self):
        # History of program operations (the undoable ones)
        self._history = []
        # Index of operations to undo/redo
        self._index = 0
        self._duringUndoRedo = False

    def recordOperation(self, operation):
        '''
        Record how to undo/redo a program operation
        '''
        if self._duringUndoRedo is True:
            return
        # # How do we clear the history if an operation different than undo/redo is made?
        # if self._index < len(self._history):
        #     self._history = self._history[:self._index]  # list: add add
        #     # undo add => list: add
        #     # update

        self._history.append(operation)  # this might not be enough though
        self._index += 1

    def undo(self):
        if self._index == 0:
            raise ValueError("No more undos!")
        self._duringUndoRedo = True
        self._index -= 1
        self._history[self._index].undo()
        self._duringUndoRedo = False

    def redo(self):
        if self._index == len(self._history):
            raise ValueError("No more redos!")
        self._duringUndoRedo = True
        self._history[self._index].redo()
        self._index += 1
        self._duringUndoRedo = False


class FunctionCall:
    '''
    Remembers which functions to call and which parameters.
    '''

    # * -> all parameters are put in a tuple.
    def __init__(self, function, *parameters):
        self._function = function
        self._params = parameters

    def call(self):
        # () -> function call parameters
        self._function(
            *self._params)  # we donn't call the function with 1 parameter which is a tuple. We split them using *
        #       self._function(self._params)  ->   _function( (a,b,c) )
        #       self._function(*self._params)  ->   _function(a, b, c)


class Operation:
    '''
    Encodes an operation that happened in the program.
    '''

    def __init__(self, undoFunction, redoFunction):
        self._undo = undoFunction
        self._redo = redoFunction

    def undo(self):
        self._undo.call()

    def redo(self):
        self._redo.call()


'''
Implement undo/redo.
    1. Remember what we need to do for undo or redo.
       ^(remember = what function to call and with which parameters)
    2. Remember the order in which operations were made.
       ^(keep a list of program operations)
    3. Carry out the operations when user requests undo() or redo().
'''
