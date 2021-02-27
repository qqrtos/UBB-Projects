#include "ActionRemove.h"

ActionRemove::ActionRemove(Repository& workingRepository, Song removedSong) :
	repository{ workingRepository },
	removedSong{ removedSong }
{}

void ActionRemove::executeUndo() {
	this->repository.addSong(removedSong);
}

void ActionRemove::executeRedo() {
	this->repository.removeSong(removedSong);
}
