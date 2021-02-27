#pragma once

#include "Action.h"
#include "ActionAdd.h"
#include "ActionRemove.h"
#include "ActionUpdate.h"

#include <vector>
#include <iterator>

class AssistantService {
private:
	Repository& seniorRepository;
	Repository& myListRepository;
	int indexOfCurrentMaterial;

	std::stack<Action*> operations;
	std::stack<Action*> undoneOperations;

public:
	AssistantService(Repository& seniorRepository, Repository& myListRepository);

	std::vector<Material> filterBySizeAndMicrofragments(Size size, float microfragments = 0);

	void saveMaterialForStudy(std::string ID);

	std::vector<Material> getAssistantMaterialsList();

	std::string getPathToRepository() const;

	void undo();

	void redo();

	Material getNext();
};