#include "ActionUpdate.h"

ActionUpdate::ActionUpdate(Repository& repo, Material oldMat, Material newMat) :
	Action{ repo },
	newMaterial{ newMat },
	oldMaterial{ oldMat }
{}

void ActionUpdate::execute() {
	this->repository.updateMaterial(this->oldMaterial.getID(), this->newMaterial);
}

void ActionUpdate::revert() {
	this->repository.updateMaterial(this->newMaterial.getID(), this->oldMaterial);
}
