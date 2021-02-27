#pragma once
#include <vector>
#include "Material.h"
#include <fstream>
#include "Repository.h"

class TextFileRepository : public Repository {
private:
	std::string filePath;

public:
	TextFileRepository(const std::string filePath);

	std::string getFilePath() const;

	void changeCurrentFile(const std::string newFilePath);

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

	~TextFileRepository() = default;

	//void dumpMaterialsToFile(std::vector<Material> materials) override;
};

