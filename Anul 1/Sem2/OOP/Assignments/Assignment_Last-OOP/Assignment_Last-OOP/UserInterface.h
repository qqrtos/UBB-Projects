#pragma once
#include <algorithm>
#include "SeniorService.h"
#include "AssistantService.h"
#include "DynamicVector.h"
#include "CSVFileRepository.h"
#include "HTMLFileRepository.h"

class UserInterface {
private:
	SeniorService& seniorService;
	AssistantService& assistantService;

public:
	UserInterface(SeniorService& seniorService, AssistantService& assistantService);

	void startSeniorUI();

	void startAssistantUI();

	~UserInterface() = default;

private:
	void changeFileLocation();

	void changeMode();

	void listAllMaterials();

	void addMaterial();

	void removeMaterial();

	void updateMaterial();

	DynamicVector<Material>::Iterator getNext(DynamicVector<Material>::Iterator current);

	void saveMaterialToAssistantList();

	void listAssistantMaterials();

	void filterMaterials();

	void openAssistantList();
};