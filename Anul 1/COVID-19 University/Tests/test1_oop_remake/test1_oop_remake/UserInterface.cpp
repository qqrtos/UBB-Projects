#include "UserInterface.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> split(std::string& input, char delimiter, bool spaceAfterDelimiterFormat = false) {
	std::vector<std::string> result{};
	std::string token;
	std::istringstream stream(input);

	while (std::getline(stream, token, delimiter)) {
		if (spaceAfterDelimiterFormat == true)
			stream.get(); //useless space after comma
		result.push_back(token);
	}

	return result;
}

UserInterface::UserInterface(Controller& controller) :
	controller{ controller }
{}

void UserInterface::startUI() {
	std::string command, arguments;

	while (true) {
		std::cout << ">";
		std::cin >> command;

		if (command == "add") {
			this->UI_add();
		}
		else if (command == "list") {
			std::string line;
			std::getline(std::cin, line);

			if (line == " efficient")
				for (auto each : this->controller.getAllEfficientdepartments()){
					std::cout << each->toString();
				}
			else
				for (auto each : this->controller.getAlldepartments()) {
					std::cout << each->toString();
				}
		}
		else if (command == "exit") {
			break;
		}
	}
}

void UserInterface::UI_add() {
	std::string line;
	std::getline(std::cin, line);

	std::vector<std::string> tokens = split(line, ',', true);
	
	if (tokens[1] == "Surgery") {
		//(std::string deckName, int nrDoctors, int nrPatients)
		this->controller.addDepartment(new Surgery{ tokens[0],std::stoi(tokens[2]),std::stoi(tokens[3]) });
	}
	else {
		//(std::string deckName, int nrDoctors, int nrMothers, int nrBabies, float averageGrade)
		this->controller.addDepartment(new NeonatalUnit{ tokens[0],std::stoi(tokens[2]),std::stoi(tokens[3]),std::stoi(tokens[4]),std::stof(tokens[5]) });
	}
}
