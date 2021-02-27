#pragma once

#include "Action.h"

class ActionUpdate : public Action {
private:
	Material newMaterial;
	Material oldMaterial;

public:
	ActionUpdate(Repository& repo, Material oldMat, Material newMat);

	void execute() override;

	void revert() override;

	~ActionUpdate() = default;
};

