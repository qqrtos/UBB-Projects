#pragma once
#include "Repository.h"
//#include <vector>

class HTMLFileRepository : public Repository {
private:
	std::string filePath;
	std::vector<Material> myList;

public:
	HTMLFileRepository(std::string filePath);

	std::string getPathToRepository() const override;

	int getRepositoryCount() const override;

	std::vector<Material> getAllMaterials() override;

	Material getMaterialByID(const std::string ID) override;

	void addMaterial(Material material) override;

	void removeMaterial(Material material) override;

	void updateMaterial(std::string ID, Material newMaterial) override;

	~HTMLFileRepository() = default;

private:
	void dumpMyListToFile();
};

