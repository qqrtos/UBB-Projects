#pragma once

#include "Action.h"

class ActionRemove : public Action {
private:
	Material removedMaterial;

public:
	ActionRemove(Repository& repo, Material removed);

	void execute() override;

	void revert() override;

	~ActionRemove() = default;
};
