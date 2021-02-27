#include "SeniorService.h"
//#include "DynamicVector.h"

SeniorService::SeniorService(TextFileRepository& repository) : repository{ repository } {}

void SeniorService::changeFileLocation(const std::string newFileLocation) {
	this->repository.changeCurrentFile(newFileLocation);
}

std::string SeniorService::getFilePath() const {
	return this->repository.getFilePath();
}

std::vector<Material> SeniorService::getAllMaterials() const {
	return this->repository.getAllMaterials();
}

Material SeniorService::getElementByID(const std::string ID) const {
	return this->repository.getMaterialByID(ID);
}

void SeniorService::addMaterial(std::string ID, Size size, int radioactivityLevel, int quantityOfMicrofragments, std::string digitizedScan) {
	Material* newMaterial = new Material{ ID,size,radioactivityLevel,quantityOfMicrofragments,digitizedScan };
	this->repository.addMaterial(*newMaterial);
}

void SeniorService::removeMaterial(std::string ID) {
	Material toBeRemoved = this->repository.getMaterialByID(ID);
	this->repository.removeMaterial(toBeRemoved);
}

void SeniorService::updateMaterial(std::string ID, Size newSize, int newRadioactivityLevel, int newQuantityOfMicrofragments, std::string newDigitizedScan) {
	Material newMaterial{ ID,newSize,newRadioactivityLevel,newQuantityOfMicrofragments,newDigitizedScan };
	this->repository.updateMaterial(ID, newMaterial);
}

SeniorService::~SeniorService() {}
