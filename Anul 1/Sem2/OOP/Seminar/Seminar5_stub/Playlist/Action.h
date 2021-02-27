#pragma once

class Action {
public:
	virtual void executeUndo(void) = 0;

	virtual void executeRedo(void) = 0;
};

