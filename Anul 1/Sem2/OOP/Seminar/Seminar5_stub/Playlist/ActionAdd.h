#pragma once
#include "Action.h"
#include "Song.h"
#include "Repository.h"

class ActionAdd : public Action {
private:
	Song addedSong;
	Repository& repository;

public:
	ActionAdd(Repository& workingRepository, Song addedSong);

	void executeUndo(void) override;

	void executeRedo(void) override;
};

