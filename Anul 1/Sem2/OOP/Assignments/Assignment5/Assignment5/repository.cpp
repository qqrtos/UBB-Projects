#include "repository.h"

int Repository::getMaterialsCount() {
	return this->materialsList.getCount();
}

void Repository::addMaterial(Material& material) {
	this->materialsList.add(material);
}

void Repository::removeMaterial(std::string ID) {
	Material toBeRemoved{};
	for (int i = 0; i < this->materialsList.getCount(); ++i) {
		if (this->materialsList[i].getID() == ID) {
			toBeRemoved = this->materialsList[i];
			break;
		}
	}
	this->materialsList.remove(toBeRemoved);
}

void Repository::updateMaterial(std::string ID, Material& newMaterial) {
	Material toBeUpdated{};
	for (int i = 0; i < this->materialsList.getCount(); ++i) {
		if (this->materialsList[i].getID() == ID) {
			toBeUpdated = this->materialsList[i];
			break;
		}
	}
	this->materialsList.update(toBeUpdated, newMaterial);
}
