#include "InMemoryRepository.h"

int InMemoryRepository::getIndexOfMaterialInRepository(Material material) {
	for (int i = 0; i < this->getRepositoryCount(); ++i) {
		if (this->materials[i] == material) {
			return i;
		}
	}
	return -1;
}

int InMemoryRepository::getRepositoryCount() const {
	return this->materials.size();
}

std::vector<Material> InMemoryRepository::getAllMaterials() {
	return this->materials;
}

Material InMemoryRepository::getMaterialByID(const std::string ID) {
	for (Material& material : this->materials) {
		if (material.getID() == ID) {
			return material;
		}
	}

	return Material{};
}

void InMemoryRepository::addMaterial(Material material) {
	this->materials.push_back(material);
}

void InMemoryRepository::removeMaterial(Material material) {
	int index = this->getIndexOfMaterialInRepository(material);

	if (index == -1) {
		throw CustomException("Element not in repository.");
	}

	this->materials.erase(this->materials.begin() + index);
}

void InMemoryRepository::updateMaterial(std::string ID, Material newMaterial) {
	if (this->getMaterialByID(ID).getID() == "") {
		throw CustomException("ID not found.");
	}

	for (auto& material : this->materials)
		if (material.getID() == ID) {
			material.setSize(newMaterial.getSize());
			material.setDigitizedScan(newMaterial.getDigitizedScan());
			material.setQuantityOfMicrofragments(newMaterial.getQuantityOfMicrofragments());
			material.setRadioactivityLevel(newMaterial.getRadioactivityLevel());
		}
}