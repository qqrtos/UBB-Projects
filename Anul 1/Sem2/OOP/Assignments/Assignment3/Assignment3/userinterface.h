#pragma once
#include "controller.h"

typedef struct {
	Controller* controller;
}UserInterface;

UserInterface* userinterface_createUI(Controller* controller);

void userinterface_start(UserInterface* UI);

void userinterface_destroyUI(UserInterface* ui);