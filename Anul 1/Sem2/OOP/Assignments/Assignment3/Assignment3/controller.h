#pragma once
#include "repository.h"

typedef struct {
	Vector* undoStack;
	Vector* redoStack;
}UndoRedoController_ListOfOperations;

typedef struct {
	Vector* history;
	int index;
}UndoRedoController_HistoryOfChanges;

typedef struct {
	Repository* repository;
	UndoRedoController_ListOfOperations* undoRedoController_ListOfOperations;
	UndoRedoController_HistoryOfChanges* undoRedoController_HistoryOfChanges;
}Controller;

Controller* controller_CreateController(Repository* repository);

/*
	Return a pointer to a new bot.
*/
Bot* createNewBot(int ID, char* state, char* specialization, int energyCapacity);

/*
	Store a bot in the repository.
	Return: ->ERROR_CODE - bot with this ID is already in the repository.
			->SUCCESS_CODE - bot has been added.
*/
int controller_StoreBot(Controller* controller, int ID, char* state, char* specialization, int energyCapacity);

int controller_RemoveBot(Controller* controller, int ID);

int controller_UpdateBot(Controller* controller, int ID, char* newState, char* newSpecialization, int newEnergyCapacity);

int controller_getBotsList(Controller* controller, Bot** list, int* size);

/*
	Perform an undo operation using the list of operations implementation.
	Return: ->ERROR_CODE - an undo is not possible
			->SUCCESS_CODE - repository status has returned to a previous state
*/
int controller_UndoOperation_ListOfOperations(Controller* controller);

/*
	Perform an redo operation using the list of operations implementation.
	Return: ->ERROR_CODE - an undo is not possible
			->SUCCESS_CODE - repository status has returned to a previous state
*/
int controller_RedoOperation_ListOfOperations(Controller* controller);

/*
	Perform an redo operation using the list of lists implementation.
	Return: ->ERROR_CODE - an undo is not possible
			->SUCCESS_CODE - repository status has returned to a previous state
*/
int controller_UndoOperation_HistoryOfChanges(Controller* controller);

/*
	Perform a redo operation using the list of lists implementation.
	Return: ->ERROR_CODE - an redo is not possible
			->SUCCESS_CODE - repository status has returned to a previous state
*/
int controller_RedoOperation_HistoryOfChanges(Controller* controller);

int controller_DestroyController(Controller* controller);