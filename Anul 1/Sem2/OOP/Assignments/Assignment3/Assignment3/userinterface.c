#include "userinterface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void swapBots(Bot* first, Bot* second) {
	Bot auxiliary;
	auxiliary.energyCapacity = first->energyCapacity;
	auxiliary.ID = first->ID;
	strcpy(auxiliary.state, first->state);
	strcpy(auxiliary.specialization, first->specialization);

	first->energyCapacity = second->energyCapacity;
	first->ID = second->ID;
	strcpy(first->state, second->state);
	strcpy(first->specialization, second->specialization);

	second->energyCapacity = auxiliary.energyCapacity;
	first->ID = auxiliary.ID;
	strcpy(first->state, auxiliary.state);
	strcpy(first->specialization, auxiliary.specialization);
}

void formatArgument(char* argument) {
	///Left-Trims argument and adds comma to the end.
	int stringLength = strlen(argument);
	for (int i = 0; i < stringLength - 1; ++i) {
		argument[i] = argument[i + 1];
	}
	argument[stringLength - 2] = ',';
	argument[stringLength - 1] = '\0';
}

int transformStringToInteger(char* string) {
	int number = 0;
	int length = strlen(string);
	formatArgument(string);
	string[length - 2] = '\0';
	length -= 2;

	for (int i = 0; i < length; ++i) {
		if (isdigit(string[i])) {
			number = number * 10 + (string[i] - '0');
		}
		else {
			return ERROR_CODE;
		}
	}

	return number;
}

void sortBotsByState(Vector* bots) {
	for (int i = 0; i < bots->count; ++i) {
		Bot* currentBot = (Bot*)bots->elements[i];
		for (int j = i + 1; j < bots->count; ++j) {
			Bot* comparisonBot = (Bot*)bots->elements[j];
			if (strcmp(currentBot->state, comparisonBot->state) > 0) {
				swapBots(currentBot, comparisonBot);
			}
		}
	}
}

void listAllElements(UserInterface* UI) {
	Bot* bots[50];
	int numberOfBots;

	controller_getBotsList(UI->controller, bots, &numberOfBots);

	for (int index = 0; index < numberOfBots; ++index) {
		printf("%d %s %s %d\n", (*bots[index]).ID, (*bots[index]).state, (*bots[index]).specialization, (*bots[index]).energyCapacity);
	}
}

void listElementsWithSpecialization(UserInterface* UI, char* specialization) {
	Bot* bots[50];
	int numberOfBots;

	controller_getBotsList(UI->controller, bots, &numberOfBots);

	for (int index = 0; index < numberOfBots; ++index) {
		if (strcmp(bots[index]->specialization, specialization) == 0) {
			printf("%d %s %s %d\n", bots[index]->ID, bots[index]->state, bots[index]->specialization, bots[index]->energyCapacity);
		}
	}
}

void listElementsBoundedByCapacity(UserInterface* UI, int maximumCapacity) {
	Bot* bots[50];
	int numberOfBots;

	controller_getBotsList(UI->controller, bots, &numberOfBots);
	Vector* botsBoundedByCapacity = vector_CreateVector();

	for (int i = 0; i < numberOfBots; ++i) {
		if (bots[i]->energyCapacity <= maximumCapacity) {
			vector_AddElement(botsBoundedByCapacity, bots[i]);
		}
	}
	sortBotsByState(botsBoundedByCapacity);

	for (int index = 0; index < botsBoundedByCapacity->count; ++index) {
		Bot* currentBot = (Bot*)botsBoundedByCapacity->elements[index];
		printf("%d %s %s %d\n", currentBot->ID, currentBot->state, currentBot->specialization, currentBot->energyCapacity);
	}
}

void addElement(UserInterface* UI) {
	char uselessCommaFormat;

	int ID, energy;
	char state[64], specialization[64];
	scanf("%d%c %s %s %d", &ID, &uselessCommaFormat, state, specialization, &energy);

	if (ERROR_CODE == controller_StoreBot(UI->controller, ID, state, specialization, energy)) {
		printf("No!\n");
	}
}

void deleteElement(UserInterface* UI) {
	int ID;

	scanf("%d", &ID);

	if (ERROR_CODE == controller_RemoveBot(UI->controller, ID)) {
		printf("No!\n");
	}
}

void updateElement(UserInterface* UI, Bot* newElement) {
	char uselessCommaFormat;

	int ID, newEnergyCapacity;
	char newState[64], newSpecialization[64];
	scanf("%d%c %s %s %d", &ID, &uselessCommaFormat, newState, newSpecialization, &newEnergyCapacity);

	if (ERROR_CODE == controller_UpdateBot(UI->controller, ID, newState, newSpecialization, newEnergyCapacity)) {
		printf("No!\n");
	}
}

void undo_ListOfOperations(UserInterface* UI) {
	if (ERROR_CODE == controller_UndoOperation_ListOfOperations(UI->controller)) {
		printf("No!\n");
	}
}

void redo_ListOfOperations(UserInterface* UI) {
	if (ERROR_CODE == controller_RedoOperation_ListOfOperations(UI->controller)) {
		printf("No!\n");
	}
}

void undo_HistoryOfChanges(UserInterface* UI) {
	if (ERROR_CODE == controller_UndoOperation_HistoryOfChanges(UI->controller)) {
		printf("No!\n");
	}
}

void redo_HistoryOfChanges(UserInterface* UI) {
	if (ERROR_CODE == controller_RedoOperation_HistoryOfChanges(UI->controller)) {
		printf("No!\n");
	}
}

UserInterface* userinterface_createUI(Controller* controller) {
	UserInterface* ui = (UserInterface*)malloc(1 * sizeof(UserInterface));
	ui->controller = controller;
	return ui;
}

void userinterface_start(UserInterface* UI) {
	while (1) {
		printf(">");
		char command[20];
		scanf("%s", command);

		if (strcmp(command, "exit") == 0) {
			break;
		}
		else if (strcmp(command, "add") == 0) {
			Bot bot;
			addElement(UI, &bot);
		}
		else if (strcmp(command, "delete") == 0) {
			deleteElement(UI);
		}
		else if (strcmp(command, "update") == 0) {
			Bot newBot;
			updateElement(UI, &newBot);
		}
		else if (strcmp(command, "list") == 0) {
			char argument[20];
			int maximumCapacity;
			fgets(argument, sizeof(argument), stdin);
			if (argument[0] == '\n') {
				listAllElements(UI);
			}
			else if ((maximumCapacity = transformStringToInteger(argument)) != ERROR_CODE) {
				listElementsBoundedByCapacity(UI, maximumCapacity);
			}
			else {
				formatArgument(argument);
				listElementsWithSpecialization(UI, argument);
			}
		}
		else if (strcmp(command, "undo") == 0) {
			undo_ListOfOperations(UI);
			//undo_HistoryOfChanges(UI);
		}
		else if (strcmp(command, "redo") == 0) {
			redo_ListOfOperations(UI);
			//redo_HistoryOfChanges(UI);
		}

	}
}

void userinterface_destroyUI(UserInterface* ui)
{
	free(ui);
}
