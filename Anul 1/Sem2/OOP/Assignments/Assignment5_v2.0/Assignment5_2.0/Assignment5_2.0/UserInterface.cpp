#include "UserInterface.h"
#include "DynamicVector.h"
#include <Windows.h>

UserInterface::UserInterface(SeniorService& seniorService, AssistantService& assistantService) :
	seniorService{ seniorService },
	assistantService{ assistantService }
{}

void UserInterface::changeFileLocation() {
	std::string newFileLocation;
	std::getline(std::cin, newFileLocation);
	std::cout << "\n\n" << newFileLocation << "\n\n";
	this->seniorService.changeFileLocation(newFileLocation);
}

void UserInterface::changeMode() {
	std::string newMode;
	std::cin >> newMode;

	if (newMode == "A") {
		this->startSeniorUI();
	}
	else if (newMode == "B") {
		this->startAssistantUI();
	}
	else {
		std::cout << "Invalid mode!\n";
		return;
	}
}

void UserInterface::listAllMaterials() {
	std::vector<Material> materials = this->seniorService.getAllMaterials();

	for (auto material : materials) {
		std::cout << "\t" << material << "\n";
	}
}

void UserInterface::addMaterial() {
	std::string ID;
	Size size;
	float radioactivity;
	float microfragments;
	std::string scan;

	char commaFormat;

	std::cin >> ID >> size >> radioactivity >> commaFormat >> microfragments >> commaFormat >> scan;
	ID.erase(std::remove(ID.begin(), ID.end(), ','), ID.end());
	scan.erase(std::remove(scan.begin(), scan.end(), ','), scan.end());

	this->seniorService.addMaterial(ID, size, radioactivity, microfragments, scan);
}

void UserInterface::removeMaterial() {
	std::string ID;
	std::cin >> ID;
	ID.erase(std::remove(ID.begin(), ID.end(), ','), ID.end());

	this->seniorService.removeMaterial(ID);
}

void UserInterface::updateMaterial() {
	std::string ID;
	Size newSize;
	float newRadioactivity;
	float newMicrofragments;
	std::string newScan;

	char commaFormat;

	std::cin >> ID >> newSize >> newRadioactivity >> commaFormat >> newMicrofragments >> commaFormat >> newScan;
	ID.erase(std::remove(ID.begin(), ID.end(), ','), ID.end());
	newScan.erase(std::remove(newScan.begin(), newScan.end(), ','), newScan.end());

	this->seniorService.updateMaterial(ID, newSize, newRadioactivity, newMicrofragments, newScan);
}

void UserInterface::startSeniorUI() {
	std::string command, arguments;
	bool newMode = false;

	while (true) {
		std::cout << ">";
		std::cin >> command;

		try {
			if (command == "add") {
				this->addMaterial();
			}
			else if (command == "delete") {
				this->removeMaterial();
			}
			else if (command == "update") {
				this->updateMaterial();
			}
			else if (command == "list") {
				this->listAllMaterials();
			}
			else if (command == "mode") {
				newMode = true;
				break;
			}
			else if (command == "fileLocation") {
				this->changeFileLocation();
			}
			else if (command == "exit") {
				break;
			}
		}
		catch (std::exception& error) {
			std::cout << error.what() << "\n";
		}
	}

	if (newMode == true) {
		this->changeMode();
	}
}

DynamicVector<Material>::Iterator UserInterface::getNext(DynamicVector<Material>::Iterator current) {
	return DynamicVector<Material>::Iterator(++current);
}

void UserInterface::saveMaterialToAssistantList() {
	std::string ID;
	std::cin >> ID;
	this->assistantService.saveMaterialForStudy(ID);
}

void UserInterface::listAssistantMaterials() {
	for (auto material : this->assistantService.getAssistantMaterialsList()) {
		std::cout << "\t" << material << "\n";
	}
}

void UserInterface::filterMaterials() {
	Size size;
	float microfragments;

	std::cin >> size >> microfragments;

	for (auto material : this->assistantService.filterBySizeAndMicrofragments(size, microfragments)) {
		std::cout << "\t" << material << "\n";
	}
}

void UserInterface::openAssistantList() {
	std::string pathToFile = this->assistantService.getPathToRepository();

	auto dotBeforeExtension = pathToFile.rfind(".");
	std::string assistantRepositoryExtension = pathToFile.substr(dotBeforeExtension + 1);

	std::wstring temporaryString = std::wstring(pathToFile.begin(), pathToFile.end());
	LPCWSTR convertedFullPath = temporaryString.c_str();

	if (assistantRepositoryExtension == "csv")
		ShellExecuteW(NULL, L"open", convertedFullPath, L"",  L"C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Excel 2016", SW_SHOW);
	else
		ShellExecuteW(NULL, L"open", convertedFullPath, L"", L"C:\\Program Files (x86)\\BraveSoftware\\Brave-Browser\\Application\\brave.exe", SW_SHOW);
}

void UserInterface::startAssistantUI() {
	std::vector<Material> materials = this->seniorService.getAllMaterials();
	std::string mode = "B";
	bool newMode = false;

	if (materials.size() != 0) {
		//DynamicVector<Material>::Iterator iterator = materials.begin();
		auto iterator = materials.begin();
		std::cout << "\tCurrent material: " << *iterator << "\n\n>";

		while (true) {
			std::string command;
			std::cin >> command;

			try {
				if (command == "next") {
					//this->getNext(iterator);
					++iterator;
					if (iterator == materials.end()) {
						iterator = materials.begin();
					}
					std::cout << "\tCurrent material: " << *iterator << "\n\n>";
				}
				else if (command == "save") {
					this->saveMaterialToAssistantList();
				}
				else if (command == "mylist") {
					this->listAssistantMaterials();
				}
				else if (command == "list") {
					this->filterMaterials();
				}
				else if (command == "mode") {
					newMode = true;
					break;
				}
				else if (command == "open") {
					this->openAssistantList();
				}
				else if (command == "exit") {
					break;
				}
			}
			catch (std::exception& error) {
				std::cout << error.what() << "\n";
			}
		}

		if (newMode == true) {
			this->changeMode();
		}
	}
}
