#include "userinterface.h"
#include <iostream>
#include <string.h>

UserInterface::UserInterface(const Service& service) {
	this->service = service;
}

void UserInterface::StartUI(std::string mode) const {
	if (mode == "SENIOR") {
		std::cout << "Merge modul.";
	}
}

UserInterface::~UserInterface() {}
