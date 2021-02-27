#pragma once
#include <vector>
#include "Material.h"
#include "CustomException.h"

class Repository {
public:
	Repository() = default;

	virtual int getRepositoryCount() const = 0;

	///Return the vector of all materials.
	virtual std::vector<Material> getAllMaterials() = 0;

	///Return the element with the specified ID.
	virtual Material getMaterialByID(const std::string ID) = 0;

	///Add a material to the repository.
	virtual void addMaterial(Material material) = 0;

	///Remove a material from the repository.
	virtual void removeMaterial(Material material) = 0;

	///Update a material.
	virtual void updateMaterial(std::string ID, Material newMaterial) = 0;

	virtual std::string getPathToRepository() const { return std::string{ "" }; }

	~Repository() = default;
};

