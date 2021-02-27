#pragma once
#include "Surgery.h"
#include "NeonatalUnit.h"
#include "MedLabDepartment.h"
#include "Controller.h"

class UserInterface {
private:
	Controller controller;
public:
	UserInterface(Controller& controller);

	void startUI();

private:
	void UI_add();
};

