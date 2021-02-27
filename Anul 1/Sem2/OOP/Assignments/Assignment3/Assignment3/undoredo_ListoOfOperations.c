#include "undoredo_ListOfOperations.h"
#include "controller.h"

Operation* createNewInverseOperation(void* functionName, Bot* newBot, Bot* oldBot) {
	Operation* newOperation = (Operation*)malloc(1 * sizeof(Operation));

	newOperation->newBot = newBot;
	newOperation->oldBot = oldBot;
	newOperation->function = functionName;

	return newOperation;
}

void executeUndoOperation(UndoRedoController_ListOfOperations* controller) {
	Operation* undoOperation = (Operation*)controller->undoStack->elements[controller->undoStack->count - 1];

	if (undoOperation->function == controller_StoreBot) {
		repository_StoreElement(controller->repository, undoOperation->newBot);
	}
	else if (undoOperation->function == controller_RemoveBot) {
		repository_RemoveElement(controller->repository, undoOperation->newBot);
	}
	else if (undoOperation->function == controller_UpdateBot) {
		repository_UpdateElement(controller->repository, undoOperation->oldBot, undoOperation->newBot);
	}

	vector_RemoveElement(controller->undoRedoController_ListOfOperations->undoStack, \
		controller->undoRedoController_ListOfOperations->undoStack->elements[controller->undoRedoController_ListOfOperations->undoStack->count - 1]);
}

void executeRedoOperation(UndoRedoController_ListOfOperations* controller) {
	Operation* redoOperation = (Operation*)controller->undoRedoController_ListOfOperations->redoStack->elements[controller->undoRedoController_ListOfOperations->redoStack->count - 1];

	if (redoOperation->function == controller_StoreBot) {
		repository_StoreElement(controller->repository, redoOperation->newBot);
	}
	else if (redoOperation->function == controller_RemoveBot) {
		repository_RemoveElement(controller->repository, redoOperation->newBot);
	}
	else if (redoOperation->function == controller_UpdateBot) {
		repository_UpdateElement(controller->repository, redoOperation->oldBot, redoOperation->newBot);
	}

	vector_RemoveElement(controller->undoRedoController_ListOfOperations->redoStack, \
		controller->undoRedoController_ListOfOperations->redoStack->elements[controller->undoRedoController_ListOfOperations->redoStack->count - 1]);
}

UndoRedoController_ListOfOperations* UndoRedoCreate_ListOfOperations()
{
	UndoRedoController_ListOfOperations* newUndoRedoController = (UndoRedoController_ListOfOperations*)malloc(1 * sizeof(UndoRedoController_ListOfOperations));
	newUndoRedoController->undoStack = vector_CreateVector();
	newUndoRedoController->redoStack = vector_CreateVector();
	return newUndoRedoController;
}

int destroyUndoRedoController_ListOfOperations(UndoRedoController_ListOfOperations* controller)
{
	vector_DestroyVector(&controller->undoStack);
	vector_DestroyVector(&controller->redoStack);
	free(controller);

	return SUCCESS_CODE;
}

int controller_UndoOperation_ListOfOperations(UndoRedoController_ListOfOperations* controller)
{
	if (0 == controller->undoRedoController_ListOfOperations->undoStack->count) {
		return ERROR_CODE;
	}

	executeUndoOperation(controller);

	return SUCCESS_CODE;
}

int controller_RedoOperation_ListOfOperations(UndoRedoController_ListOfOperations* controller)
{
	if (0 == controller->undoRedoController_ListOfOperations->redoStack->count) {
		return ERROR_CODE;
	}

	executeRedoOperation(controller);

	return SUCCESS_CODE;
}