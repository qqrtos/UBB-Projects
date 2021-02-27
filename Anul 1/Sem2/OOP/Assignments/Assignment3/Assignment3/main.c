#include "userinterface.h"
#include "repository.h"
#include "tests.h"

#include <crtdbg.h>

int main() {
	test_repository();
	test_controller();

	Repository* repository = repository_CreateRepository();

	Controller* controller = controller_CreateController(repository);

	UserInterface* UI = userinterface_createUI(controller);
	
	userinterface_start(UI);

	repository_DestroyRepository(repository);
	controller_DestroyController(controller);
	userinterface_destroyUI(UI);

	_CrtDumpMemoryLeaks();

	return 0;
}