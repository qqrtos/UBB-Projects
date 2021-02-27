#include "service.h"

Service::Service(const Repository& repository) {
	this->repository = repository;
}

void Service::addMaterial(std::string ID, std::string size, float radioactivityLevel, float quantityOfMicrofragments, std::string digitizedScan) {
	Material* newMaterial = new Material{ ID, size, radioactivityLevel, quantityOfMicrofragments, digitizedScan };
	this->repository.addMaterial(*newMaterial);
}

void Service::removeMaterial(std::string ID) {
	this->repository.removeMaterial(ID);
}

void Service::updateMaterial(std::string ID, std::string newSize, float newRadioactivityLevel, float newQuantityOfMicrofragments, std::string newDigitizedScan) {
	Material newMaterial{ID, newSize, newRadioactivityLevel, newQuantityOfMicrofragments, newDigitizedScan};
	this->repository.updateMaterial(ID, newMaterial);
}
