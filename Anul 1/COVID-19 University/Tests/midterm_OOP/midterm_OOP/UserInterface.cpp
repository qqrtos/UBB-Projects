#include "UserInterface.h"
#include <iostream>
#include "Surgery.h"
#include "NeonatalUnit.h"
#include <iostream>
#include <vector>
#include <sstream>

void UserInterface::startUI() {
	std::string command, arguments;

	while (true) {
		std::cout << ">";
		std::cin >> command;

		try {
			if (command == "add") {
				std::string deckName;
				int nrDoctors;
				std::cin >> deckName;
				std::cin.get();
				std::cin >> nrDoctors;
				deckName.erase(deckName.end() - 1);
				this->addUI(deckName, nrDoctors);
			}
			else if (command == "exit") {
				break;
			}
		}
		catch (std::exception& error) {
			std::cout << error.what() << "\n";
		}
	}
}

void UserInterface::addUI(std::string deckName, int nrDoctors) {
	if (deckName == "surgery") {
		int nrPatients;
		std::cin >> nrPatients;
		Surgery s{ deckName,nrDoctors,nrPatients };
	}
	else {
		int nrMothers;
		int nrBabies;
		float averageGrade;
		std::string line;
		std::getline(std::cin, line);
		std::vector<std::string> result{};
		std::string token;
		std::istringstream stream(line);

		while (std::getline(stream, token, ',')) {
			stream.get(); //useless space after comma
			result.push_back(token);
		}

		NeonatalUnit n{ deckName,nrDoctors,std::stoi(result[0]),std::stoi(result[1]),std::stof(result[2]) };
	}
}
