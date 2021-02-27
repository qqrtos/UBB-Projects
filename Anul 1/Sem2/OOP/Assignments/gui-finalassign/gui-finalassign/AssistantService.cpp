#include "AssistantService.h"
#include <algorithm>

AssistantService::AssistantService(Repository& seniorRepository, Repository& myListRepository) :
	seniorRepository{ seniorRepository },
	myListRepository{ myListRepository },
	indexOfCurrentMaterial{ 0 }
{}

std::vector<Material> AssistantService::filterBySizeAndMicrofragments(Size size, float microfragments) {
	std::vector<Material> filteredMaterials{};
	std::vector<Material> allMaterials = this->seniorRepository.getAllMaterials();

	std::copy_if(allMaterials.begin(), allMaterials.end(), std::back_inserter(filteredMaterials),
		[=](auto& material) {
			return material.getSize() == size && material.getQuantityOfMicrofragments() >= microfragments;
		}
	);

	return filteredMaterials;
}

void AssistantService::saveMaterialForStudy(std::string ID) {
	Material toStudy = this->seniorRepository.getMaterialByID(ID);
	try {
		Material alreadyInRepo = this->myListRepository.getMaterialByID(ID);
		throw std::exception("Material already in repository.");
	}
	catch (std::exception& e) {
		if (toStudy.getID() != "") { //only save valid materials
			this->myListRepository.addMaterial(toStudy);
			this->operations.push(new ActionAdd(this->myListRepository, toStudy));
		}
	}
}

std::vector<Material> AssistantService::getAssistantMaterialsList() {
	return this->myListRepository.getAllMaterials();
}

std::string AssistantService::getPathToRepository() const {
	return this->myListRepository.getPathToRepository();
}

void AssistantService::undo() {
	if (this->operations.empty()) {
		throw std::exception{ "Can't perform another undo." };
	}

	Action* currentAction = this->operations.top();
	currentAction->revert();
	this->undoneOperations.push(currentAction);
	this->operations.pop();
}

void AssistantService::redo() {
	if (this->undoneOperations.empty()) {
		throw std::exception{ "Can't perform another redo." };
	}

	this->undoneOperations.top()->execute();
	this->undoneOperations.pop();
}

Material AssistantService::getNext() {
	std::vector<Material> materialsInSeniorRepository = this->seniorRepository.getAllMaterials();
	if (this->indexOfCurrentMaterial == materialsInSeniorRepository.size()) {
		this->indexOfCurrentMaterial = 0;
	}
	Material next = materialsInSeniorRepository[this->indexOfCurrentMaterial++];
	return next;
}
