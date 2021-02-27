#include <iostream>
#include "Tests.h"
#include "UserInterface.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main() {
	/*Tests testAssignment5;
	testAssignment5.runTests();*/

	/// H:\Informatique\Anul 1\Sem2\OOP\Assignments\Assignment5_v2.0\Assignment5_2.0\Assignment5_2.0\repository.txt
	/// H:\Informatique\Anul 1\Sem2\OOP\Assignments\Assignment5_v2.0\Assignment5_2.0\Assignment5_2.0\assistant.csv
	/// H:\Informatique\Anul 1\Sem2\OOP\Assignments\Assignment5_v2.0\Assignment5_2.0\Assignment5_2.0\assistant.html
	std::string seniorRepositoryLocation, assistantRepositoryLocation;
	std::string commandFileLocation;

	std::cin >> commandFileLocation;
	std::cin.get(); //read empty space between the 2 strings
	std::getline(std::cin, seniorRepositoryLocation);
	seniorRepositoryLocation.replace(seniorRepositoryLocation.find("\\"), 1, "\\\\");

	std::cin >> commandFileLocation;
	std::cin.get(); //read empty space between the 2 strings
	std::getline(std::cin, assistantRepositoryLocation);
	assistantRepositoryLocation.replace(assistantRepositoryLocation.find("\\"), 1, "\\\\");

	std::string modeCommand, modeName;
	std::cin >> modeCommand >> modeName;
	std::cin.get(); //endline

	auto dotBeforeExtension = assistantRepositoryLocation.rfind(".");
	std::string assistantRepositoryExtension = assistantRepositoryLocation.substr(dotBeforeExtension + 1);

	Repository* assistantRepository;
	if (assistantRepositoryExtension == "csv") {
		assistantRepository = new CSVFileRepository{ assistantRepositoryLocation };
	}
	else if (assistantRepositoryExtension == "html") {
		assistantRepository = new HTMLFileRepository{ assistantRepositoryLocation };
	}
	else {
		throw std::exception("Wrong file extension.");
	}

	TextFileRepository seniorRepository{ seniorRepositoryLocation };
	AssistantService assistantService{ seniorRepository,*assistantRepository };
	SeniorService seniorService{ seniorRepository };
	UserInterface userInterface{ seniorService,assistantService };

	if (modeName == "A") {
		userInterface.startSeniorUI();
	}
	else if (modeName == "B") {
		userInterface.startAssistantUI();
	}
	else {
		std::cout << "Wrong mode!\n";
		return -1;
	}

	delete assistantRepository;

	return 0;
}