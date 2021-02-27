#include "controller.h"
#define NULL ((void*)0)
#include <string.h>

Bot* createNewBot(int ID, char* state, char* specialization, int energyCapacity) {
	Bot* newBot = (Bot*)malloc(1 * sizeof(Bot));

	newBot->ID = ID;
	strcpy(newBot->state, state);
	strcpy(newBot->specialization, specialization);
	newBot->energyCapacity = energyCapacity;

	return newBot;
}

int bot_HasUniqueID(Controller* controller, int ID) {
	/*
		Check whether a the parameter ID is already in the repository.
		Return: ->ERROR_CODE - ID parameter is already present in repository.
				->SUCCESS_CODE - ID not in repository.
	*/
	for (int i = 0; i < controller->repository->vector->count; ++i) {
		Bot* currentBot = (Bot*)controller->repository->vector->elements[i];
		if (currentBot->ID == ID) {
			return ERROR_CODE;
		}
	}
	return SUCCESS_CODE;
}




/// Undo/Redo using vector of vectors (storing each change)
///////////////////////////////////////////////////////////////////////////////////////////////////



Vector* createRepositoryListCopy(Controller* controller) {
	/*
		Create a copy of the elements in the repository.
		Return: a pointer to a vector containing copies of all elements in repository.
	*/
	Vector* copyRepositoryList = vector_CreateVector();
	Vector* repositoryList = repository_GetAllElemets(controller->repository);

	for (int i = 0; i < repositoryList->count; ++i) {
		int copyID = ((Bot*)repositoryList->elements[i])->ID;
		int copyEnergyCapacity = ((Bot*)repositoryList->elements[i])->energyCapacity;
		char copyState[64], copySpecialization[64];
		strcpy(copyState, ((Bot*)repositoryList->elements[i])->state);
		strcpy(copySpecialization, ((Bot*)repositoryList->elements[i])->specialization);

		Bot* copyOfCurrentBot = createNewBot(copyID, copyState, copySpecialization, copyEnergyCapacity);

		vector_AddElement(copyRepositoryList, copyOfCurrentBot);
	}

	return copyRepositoryList;
}

UndoRedoController_HistoryOfChanges* UndoRedoCreate_HistoryOfChanges() {
	UndoRedoController_HistoryOfChanges* undoRedo_HistoryOfChanges = (UndoRedoController_HistoryOfChanges*)malloc(1 * sizeof(UndoRedoController_HistoryOfChanges));

	undoRedo_HistoryOfChanges->history = vector_CreateVector();
	undoRedo_HistoryOfChanges->index = -1;

	return undoRedo_HistoryOfChanges;
}

int controller_UndoOperation_HistoryOfChanges(Controller* controller) {
	if (-1 == controller->undoRedoController_HistoryOfChanges->index) {
		return ERROR_CODE;
	}

	repository_ReplaceRepositoryList(controller->repository, \
		controller->undoRedoController_HistoryOfChanges->history->elements[controller->undoRedoController_HistoryOfChanges->index--]);

	return SUCCESS_CODE;
}

int controller_RedoOperation_HistoryOfChanges(Controller* controller) {
	if (controller->undoRedoController_HistoryOfChanges->history->count <= controller->undoRedoController_HistoryOfChanges->index + 2) {
		return ERROR_CODE;
	}

	repository_ReplaceRepositoryList(controller->repository, \
		controller->undoRedoController_HistoryOfChanges->history->elements[2 + controller->undoRedoController_HistoryOfChanges->index]);
	
	controller->undoRedoController_HistoryOfChanges->index += 1;

	return SUCCESS_CODE;
}


void destroyUndoRedoController_HistoryOfChanges(UndoRedoController_HistoryOfChanges* controller) {
	for (int i = 0; i < controller->history->count - 1; ++i) {
		vector_DestroyVector(&controller->history->elements[i]);
	}

	free(controller->history);

	free(controller);
}



/// Undo/Redo using vector of inverse operations
///////////////////////////////////////////////////////////////////////////////////////////////////



Operation* createNewInverseOperation(void* functionName, Bot* newBot, Bot* oldBot) {
	Operation* newOperation = (Operation*)malloc(1 * sizeof(Operation));

	newOperation->newBot = newBot;
	newOperation->oldBot = oldBot;
	newOperation->function = functionName;

	return newOperation;
}

void executeUndoOperation(Controller* controller) {
	Operation* undoOperation = (Operation*)controller->undoRedoController_ListOfOperations->undoStack->elements[controller->undoRedoController_ListOfOperations->undoStack->count - 1];

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

void executeRedoOperation(Controller* controller) {
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

UndoRedoController_ListOfOperations* UndoRedoCreate_ListOfOperations() {
	/*
		Create an undo controller for the list of lists implementation.
	*/
	UndoRedoController_ListOfOperations* newUndoRedoController = (UndoRedoController_ListOfOperations*)malloc(1 * sizeof(UndoRedoController_ListOfOperations));

	newUndoRedoController->undoStack = vector_CreateVector();
	newUndoRedoController->redoStack = vector_CreateVector();

	return newUndoRedoController;
}

int destroyUndoRedoController_ListOfOperations(UndoRedoController_ListOfOperations* controller) {
	/*
		Free up momemory used by the undo controller (list of lists implementation).
	*/
	vector_DestroyVector(&controller->undoStack);
	vector_DestroyVector(&controller->redoStack);
	free(controller);

	return SUCCESS_CODE;
}

int controller_UndoOperation_ListOfOperations(Controller* controller) {
	/*
		Perform an undo operation.
		Return: ->ERROR_CODE - no more undo's left
				->SUCCESS_CODE - operation performed succesfully
	*/
	if (0 == controller->undoRedoController_ListOfOperations->undoStack->count) {
		return ERROR_CODE;
	}

	executeUndoOperation(controller);

	return SUCCESS_CODE;
}

int controller_RedoOperation_ListOfOperations(Controller* controller) {
	/*
		Perform an uredo operation.
		Return: ->ERROR_CODE - no more redo's left
				->SUCCESS_CODE - operation performed succesfully
	*/
	if (0 == controller->undoRedoController_ListOfOperations->redoStack->count) {
		return ERROR_CODE;
	}

	executeRedoOperation(controller);

	return SUCCESS_CODE;
}



///Controller functions.
////////////////////////////////////////////////////////////////////////////////////////////////////////


void addUndoRedoOperationInTheStack(Vector* stack, void* inverseFunction, Bot* beforeBot, Bot* afterBot) {
	Operation* newOperation = createNewInverseOperation(inverseFunction, beforeBot, afterBot);
	vector_AddElement(stack, newOperation);
}

Controller* controller_CreateController(Repository* repository) {
	Controller* controller = (Controller*)malloc(1 * sizeof(Controller));

	controller->repository = repository;
	controller->undoRedoController_ListOfOperations = UndoRedoCreate_ListOfOperations();
	controller->undoRedoController_HistoryOfChanges = UndoRedoCreate_HistoryOfChanges();

	vector_AddElement(controller->undoRedoController_HistoryOfChanges->history, createRepositoryListCopy(controller));

	return controller;
}

int controller_StoreBot(Controller* controller, int ID, char* state, char* specialization, int energyCapacity) {
	/*
		Store a bot in the repository.
		Return: ->ERROR_CODE - bot with the same ID is already in the repository.
				->SUCCESS_CODE - bot has been stored.
	*/
	if (ERROR_CODE == bot_HasUniqueID(controller, ID)) {
		return ERROR_CODE;
	}

	Bot* newBot = createNewBot(ID, state, specialization, energyCapacity);
	Bot* newRedoStoreBot = createNewBot(ID, state, specialization, energyCapacity);

	///operations list undo/redo
	addUndoRedoOperationInTheStack(controller->undoRedoController_ListOfOperations->undoStack, controller_RemoveBot, newBot, NULL);
	addUndoRedoOperationInTheStack(controller->undoRedoController_ListOfOperations->redoStack, controller_StoreBot, newRedoStoreBot, NULL);

	int returnValue = repository_StoreElement(controller->repository, newBot);

	if (SUCCESS_CODE == returnValue) {
		///history of changes list undo/redo
		vector_AddElement(controller->undoRedoController_HistoryOfChanges->history, createRepositoryListCopy(controller));
		controller->undoRedoController_HistoryOfChanges->index += 1;
	}

	return returnValue;
}

int controller_RemoveBot(Controller* controller, int ID) {
	/*
		Remove a bot from the repository.
		Return: ->ERROR_CODE - bot ID not in repository.
				->SUCCESS_CODE - bot has been deleted.
	*/
	Bot* toBeRemoved = NULL;

	for (int i = 0; i < controller->repository->vector->count; ++i) {
		Bot* currentElement = (Bot*)controller->repository->vector->elements[i];

		if (currentElement->ID == ID) {
			toBeRemoved = currentElement;
			break;
		}
	}

	if (NULL == toBeRemoved) {
		return ERROR_CODE;
	}

	Bot* undoRemoveBot = createNewBot(toBeRemoved->ID, toBeRemoved->state, toBeRemoved->specialization, toBeRemoved->energyCapacity);

	addUndoRedoOperationInTheStack(controller->undoRedoController_ListOfOperations->undoStack, controller_StoreBot, undoRemoveBot, NULL);
	addUndoRedoOperationInTheStack(controller->undoRedoController_ListOfOperations->redoStack, controller_RemoveBot, undoRemoveBot, NULL);

	int returnValue = repository_RemoveElement(controller->repository, toBeRemoved);

	if (SUCCESS_CODE == returnValue) {
		///history of changes list undo/redo
		vector_AddElement(controller->undoRedoController_HistoryOfChanges->history, createRepositoryListCopy(controller));
		controller->undoRedoController_HistoryOfChanges->index += 1;
	}

	return returnValue;
}

int controller_UpdateBot(Controller* controller, int ID, char* newState, char* newSpecialization, int newEnergyCapacity) {
	/*
		Update the bot with the given ID.
		Return: ->ERROR_CODE - bot is not stored in the repository.
				->SUCCESS_CODE - bot has been updated.
	*/
	Bot* newBot = createNewBot(ID, newState, newSpecialization, newEnergyCapacity);
	Bot* toBeReplaced = NULL;

	for (int i = 0; i < controller->repository->vector->count; ++i) {
		Bot* currentElement = (Bot*)controller->repository->vector->elements[i];

		if (currentElement->ID == ID) {
			toBeReplaced = currentElement;
			break;
		}
	}

	if (NULL == toBeReplaced) {
		return ERROR_CODE;
	}

	///list of operations undo/redo
	Bot* oldBot = createNewBot(toBeReplaced->ID, toBeReplaced->state, toBeReplaced->specialization, toBeReplaced->energyCapacity);

	addUndoRedoOperationInTheStack(controller->undoRedoController_ListOfOperations->undoStack, controller_UpdateBot, oldBot, newBot);
	addUndoRedoOperationInTheStack(controller->undoRedoController_ListOfOperations->redoStack, controller_UpdateBot, newBot, oldBot);

	int returnCode = repository_UpdateElement(controller->repository, toBeReplaced, newBot);
	free(toBeReplaced);

	if (SUCCESS_CODE == returnCode) {
		///history of changes list undo/redo
		vector_AddElement(controller->undoRedoController_HistoryOfChanges->history, createRepositoryListCopy(controller));
		controller->undoRedoController_HistoryOfChanges->index += 1;
	}

	return returnCode;
}

int controller_getBotsList(Controller* controller, Bot** list, int* size) {
	/*
		Return through the parameter list the vector of bots in the repository.
	*/
	*size = 0;

	for (int index = 0; index < controller->repository->vector->count; ++index) {
		list[*size] = (Bot*)controller->repository->vector->elements[index];
		++(*size);
	}

	return SUCCESS_CODE;
}

int controller_DestroyController(Controller* controller) {
	destroyUndoRedoController_ListOfOperations(controller->undoRedoController_ListOfOperations);
	destroyUndoRedoController_HistoryOfChanges(controller->undoRedoController_HistoryOfChanges);
	free(controller);
	return SUCCESS_CODE;
}
