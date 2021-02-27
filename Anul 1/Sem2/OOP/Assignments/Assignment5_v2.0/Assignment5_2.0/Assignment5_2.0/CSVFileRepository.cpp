#include "CSVFileRepository.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>

Material transform_CSV_line_to_material(const std::string CSVline) {
	std::vector<std::string> materialTokens{};
	std::stringstream stream{ CSVline };
	std::string token;

	while (std::getline(stream, token, ',')) {
		materialTokens.push_back(token);
	}

	Size sizeFromStringToken{ materialTokens[1] };

	return Material{
		materialTokens[0], //ID
		sizeFromStringToken, //Size
		std::stoi(materialTokens[2]), //Radioactivity
		std::stoi(materialTokens[3]), //Microfragments
		materialTokens[4] //Digitized scan
	};
}

std::string material_to_csv_format(Material material) {
	return material.getID() + "," + material.getSize().toString() + "," + std::to_string(material.getRadioactivityLevel()) \
		+ "," + std::to_string(material.getQuantityOfMicrofragments()) + "," + material.getDigitizedScan();
}

CSVFileRepository::CSVFileRepository(std::string pathToCSVFile) :
	filePath{ pathToCSVFile }
{}

std::string CSVFileRepository::getPathToRepository() const {
	return this->filePath;
}

int CSVFileRepository::getRepositoryCount() const {
	std::ifstream inputStream(this->filePath);

	int count = std::count(std::istreambuf_iterator<char>(inputStream),
		std::istreambuf_iterator<char>(), '\n');
	
	inputStream.close();

	return count;
}

std::vector<Material> CSVFileRepository::getAllMaterials() {
	std::vector<Material> materialsList{};
	std::ifstream CSVInputStream{ this->filePath };

	std::string line;
	while (std::getline(CSVInputStream, line)) {
		Material materialFromLine = transform_CSV_line_to_material(line);
		materialsList.push_back(materialFromLine);
	}

	CSVInputStream.close();

	return materialsList;
}

Material CSVFileRepository::getMaterialByID(const std::string ID) {
	std::ifstream CSVInputStream{ this->filePath };

	std::string line;
	while (std::getline(CSVInputStream, line)) {
		Material materialFromLine = transform_CSV_line_to_material(line);
		if (materialFromLine.getID() == ID) {
			return materialFromLine;
		}
	}

	CSVInputStream.close();

	throw RepositoryException("Material with given ID not found.");
}

void CSVFileRepository::addMaterial(Material material) {
	std::ofstream CSVOutputStream{ this->filePath, std::ios::app | std::ios::out };
	try {
		/*Material already in repository.*/
		Material found = this->getMaterialByID(material.getID());
	}
	catch (...) {  
		CSVOutputStream << material_to_csv_format(material) << "\n";
	}

	CSVOutputStream.close();
}

void CSVFileRepository::removeMaterial(Material material) {
	std::ifstream CSVInputStream{ this->filePath };
	std::ofstream CSVOutputStream{ this->filePath, std::ios::trunc | std::ios::out };
	std::string lines;

	std::string line;
	while (std::getline(CSVInputStream, line)) {
		Material materialFromLine = transform_CSV_line_to_material(line);
		if (materialFromLine.getID() != "ID") {
			lines.append(material_to_csv_format(materialFromLine) + "\n");
		}
	}

	CSVInputStream.close();

	CSVOutputStream << lines;

	CSVOutputStream.close();
}

void CSVFileRepository::updateMaterial(std::string ID, Material newMaterial) {
	std::ifstream CSVInputStream{ this->filePath };
	std::ofstream CSVOutputStream{ this->filePath, std::ios::trunc | std::ios::out };
	std::string lines;

	std::string line;
	while (std::getline(CSVInputStream, line)) {
		Material currentMaterial = transform_CSV_line_to_material(line);
		if (currentMaterial.getID() != "ID") {
			lines.append(material_to_csv_format(currentMaterial) + "\n");
		}
		else {
			lines.append(material_to_csv_format(newMaterial) + "\n");
		}
	}

	CSVInputStream.close();

	CSVOutputStream << lines;

	CSVOutputStream.close();
}
