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
	this->operations.push(new ActionAdd(this->repository, *newMaterial));
	this->repository.addMaterial(*newMaterial);
}

void SeniorService::removeMaterial(std::string ID) {
	Material toBeRemoved = this->repository.getMaterialByID(ID);
	this->operations.push(new ActionRemove(this->repository, toBeRemoved));
	this->repository.removeMaterial(toBeRemoved);
}

void SeniorService::updateMaterial(std::string ID, Size newSize, int newRadioactivityLevel, int newQuantityOfMicrofragments, std::string newDigitizedScan) {
	Material newMaterial{ ID,newSize,newRadioactivityLevel,newQuantityOfMicrofragments,newDigitizedScan };
	Material oldMaterial = this->repository.getMaterialByID(ID);
	this->operations.push(new ActionUpdate(this->repository, oldMaterial, newMaterial));
	this->repository.updateMaterial(ID, newMaterial);
}

void SeniorService::undo() {
	if (this->operations.empty()) {
		throw std::exception{ "Can't perform another undo." };
	}

	Action* undoAction = this->operations.top();
	undoAction->revert();
	this->undoneOperations.push(undoAction);
	this->operations.pop();
}

void SeniorService::redo() {
	if (this->undoneOperations.empty()) {
		throw std::exception{ "Can't perform another redo." };
	}

	this->undoneOperations.top()->execute();
	this->undoneOperations.pop();
}

SeniorService::~SeniorService() {}
