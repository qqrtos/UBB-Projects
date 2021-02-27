#include "Material.h"
#include "DynamicVector.h"
#include <sstream>

Material::Material(std::string ID, Size size, int radioactivityLevel, int quantityOfMicrofragments, std::string digitizedScan) {
	if (ID == "" or radioactivityLevel < 0 or quantityOfMicrofragments < 0 or digitizedScan == "")
		throw std::exception("Invalid data to initialize material.");
	this->ID = ID;
	this->size = size;
	this->radioactivityLevel = radioactivityLevel;
	this->quantityOfMicrofragments = quantityOfMicrofragments;
	this->digitizedScan = digitizedScan;
}

Material::Material(const Material& material) {
	this->ID = material.ID;
	this->size = material.size;
	this->digitizedScan = material.digitizedScan;
	this->quantityOfMicrofragments = material.quantityOfMicrofragments;
	this->radioactivityLevel = material.radioactivityLevel;
}

std::string Material::getID() {
	return this->ID;
}

Size& Material::getSize() {
	return this->size;
}

float Material::getRadioactivityLevel() {
	return this->radioactivityLevel;
}

float Material::getQuantityOfMicrofragments() {
	return this->quantityOfMicrofragments;
}

void Material::setID(const std::string newID) {
	if (newID.empty()) {
		throw std::exception{ "New ID can't be empty." };
	}
	this->ID = newID;
}

void Material::setSize(const Size newSize) {
	this->size = newSize;
}

void Material::setRadioactivityLevel(const float newRadioactivityLevel) {
	this->radioactivityLevel = newRadioactivityLevel;
}

void Material::setQuantityOfMicrofragments(const float newQuantityOfMicrofragments) {
	if (newQuantityOfMicrofragments < 0) {
		throw std::exception{ "Quantity of microfragments can't be negative." };
	}
	this->quantityOfMicrofragments = newQuantityOfMicrofragments;
}

void Material::setDigitizedScan(const std::string newDigitizedScan) {
	if (newDigitizedScan.empty()) {
		throw std::exception{ "Digitized scan can't be empty." };
	}
	this->digitizedScan = newDigitizedScan;
}

std::string Material::getDigitizedScan() {
	return this->digitizedScan;
}

void Material::operator=(Material newMaterial) {
	this->ID = newMaterial.ID;
	this->size = newMaterial.size;
	this->digitizedScan = newMaterial.digitizedScan;
	this->quantityOfMicrofragments = newMaterial.quantityOfMicrofragments;
	this->radioactivityLevel = newMaterial.radioactivityLevel;
}

bool Material::operator==(const Material compareMaterial) {
	return this->ID == compareMaterial.ID;
}

std::string Material::toString() {
	std::ostringstream ss;
	ss << *this;
	return ss.str();
}

std::ostream& operator<<(std::ostream& outStream, Material material) {
	outStream << material.ID << ", " << material.size << ", " << material.radioactivityLevel << ", " << material.quantityOfMicrofragments << ", " << material.digitizedScan;
	return outStream;
}

std::istream& operator>>(std::istream& inputStream, Material& material) {
	char uselessCommaFormat;

	inputStream >> material.ID;
	material.ID.pop_back(); //get rid of comma from end of ID
	
	inputStream >> material.size >> material.radioactivityLevel >> uselessCommaFormat >> material.quantityOfMicrofragments >> uselessCommaFormat >> material.digitizedScan;
	
	return inputStream;
}
