#include "ActionAdd.h"

ActionAdd::ActionAdd(Repository& repo, Material added) :
	Action{repo},
	addedMaterial{ added }
{}

void ActionAdd::execute() {
	this->repository.addMaterial(this->addedMaterial);
}

void ActionAdd::revert() {
	this->repository.removeMaterial(this->addedMaterial);
}
