#pragma once
#include "Repository.h"
class CSVFileRepository : public Repository {
private:
	std::string filePath;

public:
	CSVFileRepository(std::string pathToCSVFile);

	std::string getPathToRepository() const override;

	int getRepositoryCount() const override;

	std::vector<Material> getAllMaterials() override;

	Material getMaterialByID(const std::string ID) override;

	void addMaterial(Material material) override;

	void removeMaterial(Material material) override;

	void updateMaterial(std::string ID, Material newMaterial) override;

	~CSVFileRepository() = default;
};

