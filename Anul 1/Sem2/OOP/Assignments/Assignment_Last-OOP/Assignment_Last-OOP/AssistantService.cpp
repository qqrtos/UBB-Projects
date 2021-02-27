#include "AssistantService.h"
#include <algorithm>

AssistantService::AssistantService(Repository& seniorRepository, Repository& myListRepository) :
	seniorRepository{ seniorRepository },
	myListRepository{ myListRepository }
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
	if (toStudy.getID() != "") //only save valid materials
		this->myListRepository.addMaterial(toStudy);
}

std::vector<Material> AssistantService::getAssistantMaterialsList() {
	return this->myListRepository.getAllMaterials();
}

std::string AssistantService::getPathToRepository() const {
	return this->myListRepository.getPathToRepository();
}

