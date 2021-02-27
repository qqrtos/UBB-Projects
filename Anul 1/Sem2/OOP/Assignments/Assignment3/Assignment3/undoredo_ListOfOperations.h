#pragma once
#include "repository.h"

typedef struct {
	Bot* newBot;
	Bot* oldBot;
	void* function;
}Operation;

typedef struct {
	Vector* undoStack;
	Vector* redoStack;
}UndoRedoController_ListOfOperations;

int undoRedoController_UndoOperation_ListOfOperations(Controller* controller);

int controller_RedoOperation_ListOfOperations(Controller* controller);