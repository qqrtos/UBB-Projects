#include "ActionRemove.h"

ActionRemove::ActionRemove(Repository& repo, Material removed) :
	Action{ repo },
	removedMaterial{ removed }
{}

void ActionRemove::execute() {
	this->repository.removeMaterial(this->removedMaterial);
}

void ActionRemove::revert() {
	this->repository.addMaterial(this->removedMaterial);
}
