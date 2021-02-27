#pragma once
#include "Repository.h"
//#include "DynamicVector.h"
#include <vector>

class AssistantService {
private:
	Repository& seniorRepository;
	//std::vector<Material> assistantList;
	Repository& myListRepository;

public:
	AssistantService(Repository& seniorRepository, Repository& myListRepository);

	std::vector<Material> filterBySizeAndMicrofragments(Size size, float microfragments = 0);

	void saveMaterialForStudy(std::string ID);

	std::vector<Material> getAssistantMaterialsList();

	std::string getPathToRepository() const;
};