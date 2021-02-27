#pragma once

#include "Action.h"

class ActionAdd : public Action {
private:
	Material addedMaterial;

public:
	ActionAdd(Repository& repo, Material added);

	void execute() override;

	void revert() override;

	~ActionAdd() = default;
};

