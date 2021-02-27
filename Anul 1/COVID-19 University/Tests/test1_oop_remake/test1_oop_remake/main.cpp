#include "NeonatalUnit.h"
#include "Surgery.h"
#include "UserInterface.h"

int main() {
	{
		Controller controller;
		UserInterface UI{ controller };

		UI.startUI();
	}
	return 0;
}