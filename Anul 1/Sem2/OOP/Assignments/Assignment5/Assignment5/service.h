#pragma once
#include "repository.h"

class Service {
private:
	Repository repository;

public:
	Service() = default;

	Service(const Repository& repository);

	void addMaterial(std::string ID, std::string size, float radioactivityLevel, float quantityOfMicrofragments, std::string digitizedScan);

	void removeMaterial(std::string ID);

	void updateMaterial(std::string ID, std::string newSize, float newRadioactivityLevel, float newQuantityOfMicrofragments, std::string newDigitizedScan);

	~Service() = default;
};

