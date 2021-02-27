#pragma once
#include "InMemoryRepository.h"
#include "TextFileRepository.h"
//#include "DynamicVector.h"
#include <vector>

class SeniorService {
private:
	TextFileRepository& repository;

public:
	SeniorService(TextFileRepository& repository);

	void changeFileLocation(const std::string newFileLocation);

	std::string getFilePath() const;

	std::vector<Material> getAllMaterials() const;

	Material getElementByID(const std::string ID) const;

	void addMaterial(std::string ID, Size size, int radioactivityLevel, int quantityOfMicrofragments, std::string digitizedScan);

	void removeMaterial(std::string ID);

	void updateMaterial(std::string ID, Size newSize, int newRadioactivityLevel, int newQuantityOfMicrofragments, std::string newDigitizedScan);

	~SeniorService();
};