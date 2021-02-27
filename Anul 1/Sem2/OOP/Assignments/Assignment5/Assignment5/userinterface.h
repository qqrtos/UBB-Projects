#pragma once
#include "service.h"

class UserInterface {
private:
	Service service;

public:
	UserInterface() = default;

	UserInterface(const Service& service);

	void StartUI(std::string mode) const;

	~UserInterface();
};

