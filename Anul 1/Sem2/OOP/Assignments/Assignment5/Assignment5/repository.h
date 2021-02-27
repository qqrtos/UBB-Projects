#pragma once
#include "dynamicvector.h"
#include "domain.h"

class Repository {
private:
	DynamicVector<Material> materialsList;

public:
	Repository() = default;

	int getMaterialsCount();

	void addMaterial(Material& material);

	void removeMaterial(std::string ID);

	void updateMaterial(std::string ID, Material& newMaterial);

	~Repository() = default;
};

