#include "ActionAdd.h"

ActionAdd::ActionAdd(Repository& workingRepository, Song addedSong) :
	repository{ workingRepository },
	addedSong{ addedSong }
{}

void ActionAdd::executeUndo() {
	this->repository.removeSong(addedSong);
}

void ActionAdd::executeRedo() {
	this->repository.addSong(addedSong);
}
