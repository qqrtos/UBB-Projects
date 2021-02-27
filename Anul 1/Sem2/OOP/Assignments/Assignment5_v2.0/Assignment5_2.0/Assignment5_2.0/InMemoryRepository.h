#pragma once
//#include "DynamicVector.h"
#include "Material.h"
#include <vector>
#include "Repository.h"

class InMemoryRepository : public Repository {
private:
	std::vector<Material> materials;

public:
	InMemoryRepository() = default;

	int getRepositoryCount() const override;

	///Return the vector of all materials.
	std::vector<Material> getAllMaterials() override;

	///Return the element with the specified ID.
	Material getMaterialByID(const std::string ID) override;

	///Add a material to the repository.
	void addMaterial(Material material) override;

	///Remove a material from the repository.
	void removeMaterial(Material material) override;

	///Update a material.
	void updateMaterial(std::string ID, Material newMaterial) override;

	~InMemoryRepository() = default;

private:
	int getIndexOfMaterialInRepository(Material material);
};

