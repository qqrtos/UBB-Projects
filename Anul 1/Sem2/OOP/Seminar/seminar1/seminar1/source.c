#include <stdio.h>
#include "planet.h"
#include "repository.h"
#include <crtdbg.h>

int main() {
	testPlanet();
	testRepo();

	_CrtDumpMemoryLeaks();
	return 0;
}