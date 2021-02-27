#pragma once
#include "Action.h"
#include "Song.h"
#include "Repository.h"

class ActionRemove : public Action {
private:
	Song removedSong;
	Repository& repository;

public:
	ActionRemove(Repository& workingRepository, Song removedSong);

	void executeUndo(void) override;

	void executeRedo(void) override;
};

