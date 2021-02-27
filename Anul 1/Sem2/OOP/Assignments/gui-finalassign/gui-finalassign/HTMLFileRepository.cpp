#include "HTMLFileRepository.h"
#include <fstream>
#include <iostream>

std::string material_to_HTML_tableRow(Material material) {
	std::string row{ "" };
	row += "\t\t<tr>\n";

	row += "\t\t<td>\n"; row += "\t\t\t"; row += material.getID(); row += "\n\t\t</td>\n";
	row += "\t\t<td>\n"; row += "\t\t\t"; row += material.getSize().toString(); row += "\n\t\t</td>\n";
	row += "\t\t<td>\n"; row += "\t\t\t"; row += std::to_string(material.getRadioactivityLevel()); row += "\n\t\t</td>\n";
	row += "\t\t<td>\n"; row += "\t\t\t"; row += std::to_string(material.getQuantityOfMicrofragments()); row += "\n\t\t</td>\n";
	row += "\t\t<td>\n"; row += "\t\t\t"; row += material.getDigitizedScan(); row += "\n\t\t</td>\n";

	row += "\t\t</tr>\n";

	return row;
}

void HTMLFileRepository::dumpMyListToFile() {
	std::ofstream outputStream{ this->filePath, std::ios::out | std::ios::trunc };

	outputStream << "<!DOCTYPE html>\n";
	outputStream << "<html>\n";
	outputStream << "<head>\n";
	outputStream << "\t<title>Assistant Materials</title>\n";
	outputStream << "</head>\n";

	outputStream << "<body>\n";
	outputStream << "\t<table border=\"1\">\n";

	std::string row{ "" };
	row += "\t\t<tr>\n";

	row += "\t\t<td>\n"; row += "\t\t\t"; row += "ID"; row += "\n\t\t</td>\n";
	row += "\t\t<td>\n"; row += "\t\t\t"; row += "Size"; row += "\n\t\t</td>\n";
	row += "\t\t<td>\n"; row += "\t\t\t"; row += "Radioactivity Level"; row += "\n\t\t</td>\n";
	row += "\t\t<td>\n"; row += "\t\t\t"; row += "Quantity of Microfragments"; row += "\n\t\t</td>\n";
	row += "\t\t<td>\n"; row += "\t\t\t"; row += "Digitized Scan"; row += "\n\t\t</td>\n";

	row += "\t\t</tr>\n";

	outputStream << row;

	for (auto material : this->myList) {
		outputStream << material_to_HTML_tableRow(material);
	}

	outputStream << "\t</table>\n";
	outputStream << "</body>\n";
	outputStream << "</html>";
}

HTMLFileRepository::HTMLFileRepository(std::string filePath) :
	filePath{ filePath }
{}

std::string HTMLFileRepository::getPathToRepository() const {
	return this->filePath;
}

int HTMLFileRepository::getRepositoryCount() const {
	return this->myList.size();
}

std::vector<Material> HTMLFileRepository::getAllMaterials() {
	return this->myList;
}

Material HTMLFileRepository::getMaterialByID(const std::string ID) {
	auto materialFound = std::find_if(this->myList.begin(), this->myList.end(),
		[ID](Material current) {return current.getID() == ID; }
	);

	if (materialFound == this->myList.end()) {
		throw std::exception("Material with given ID not found.");
	}

	return *materialFound;
}

void HTMLFileRepository::addMaterial(Material material) {
	this->myList.push_back(material);

	this->dumpMyListToFile();

	this->notify();
}

void HTMLFileRepository::removeMaterial(Material material) {
	this->myList.erase(
		std::find(this->myList.begin(), this->myList.end(), material)
	);

	this->dumpMyListToFile();

	this->notify();
}

void HTMLFileRepository::updateMaterial(std::string ID, Material newMaterial) {
	auto materialFound = std::find_if(this->myList.begin(), this->myList.end(),
		[ID](Material current) {return current.getID() == ID; }
	);

	if (materialFound == this->myList.end()) {
		throw std::exception("Material with given ID not found.");
	}

	*materialFound = newMaterial;

	this->dumpMyListToFile();
}
