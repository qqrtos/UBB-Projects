#pragma once

#include "Repository.h"
#include "Material.h"

class Action {
protected:
    Repository& repository;
    Action(Repository& repo) : repository{ repo } {}

public:
    virtual void execute() = 0;

    virtual void revert() = 0;
    
    virtual ~Action() = default;
};
