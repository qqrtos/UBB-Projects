#include "domain.h"
#include <exception>
#include <iostream>

Material::Material(const Material& copyMaterial) {
	this->ID = copyMaterial.ID;
	this->size = copyMaterial.size;
	this->radioactivityLevel = copyMaterial.radioactivityLevel;
	this->quantityOfMicrofragments = copyMaterial.quantityOfMicrofragments;
	this->digitizedScan = copyMaterial.digitizedScan;
}

Material::Material(std::string ID, std::string size, float radioactivityLevel, float quantityOfMicrofragments, std::string digitizedScan) {
	if (ID.empty() or quantityOfMicrofragments < 0 or digitizedScan.empty() or size.empty()) {
		throw std::exception("Invalid arguments to create a material.\n");
	}

	this->ID = ID;
	this->size = size;
	this->radioactivityLevel = radioactivityLevel;
	this->quantityOfMicrofragments = quantityOfMicrofragments;
	this->digitizedScan = digitizedScan;
}

std::string Material::getID() const {
	return this->ID;
}

std::string Material::getSize() const {
	return this->size;
}

float Material::getRadioactivityLevel() const {
	return this->radioactivityLevel;
}

float Material::getQuantityOfMicrofragments() const {
	return this->quantityOfMicrofragments;
}

std::string Material::getDigitizedScan() const {
	return this->digitizedScan;
}

void Material::setID(std::string newID) {
	if (newID.empty()) {
		throw std::exception("ID can't be empty.\n");
	}

	this->ID = newID;
}

void Material::setSize(std::string newSize) {
	if (newSize.empty()) {
		throw std::exception("Size can't be empty.\n");
	}

	this->size = newSize;
}

void Material::setRadioactivityLevel(float newRadioactivityLevel) {
	this->radioactivityLevel = newRadioactivityLevel;
}

void Material::setQuantityOfMicrofragments(float newQuantityOfMicrofragments) {
	if (0 > newQuantityOfMicrofragments) {
		throw std::exception("Quantity of microfragments can't be lower than 0.\n");
	}

	this->quantityOfMicrofragments = newQuantityOfMicrofragments;
}

void Material::setDigitizedScan(std::string newDigitizedScan) {
	if (newDigitizedScan.empty()) {
		throw std::exception("Digitized scan can't be left empty.\n");
	}

	this->digitizedScan = newDigitizedScan;
}

std::ostream& operator<<(std::ostream& outStream, const Material& material) {
	std::cout << material.ID << " " << material.size << " " << material.radioactivityLevel << " " << material.quantityOfMicrofragments << "\n";
	return outStream;
}
