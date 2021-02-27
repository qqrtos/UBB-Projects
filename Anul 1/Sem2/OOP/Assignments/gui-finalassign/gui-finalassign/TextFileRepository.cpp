#include "TextFileRepository.h"
#include <ios>
#include <algorithm>

TextFileRepository::TextFileRepository(const std::string filePath) :
	filePath{ filePath }
{}

std::string TextFileRepository::getFilePath() const {
	return this->filePath;
}

void TextFileRepository::changeCurrentFile(const std::string newFilePath) {
	std::ifstream testStream(newFilePath, std::ios::trunc | std::ios::out);
	testStream.close();
	
	this->filePath = newFilePath;
}

int TextFileRepository::getRepositoryCount() const {
	std::ifstream inputStream(this->filePath, std::ios::app | std::ios::out);

	return std::count(std::istreambuf_iterator<char>(inputStream),
		std::istreambuf_iterator<char>(), '\n');
}

std::vector<Material> TextFileRepository::getAllMaterials() {
	std::vector<Material> materialsList;
	Material currentMaterial;

	std::ifstream inputStream(this->filePath);

	while (!inputStream.eof()) {
		try {
			inputStream >> currentMaterial;
			inputStream.get(); //endline
			materialsList.push_back(currentMaterial);
		}
		catch (...) {} //read until eof raises an error.
	}

	inputStream.close();

	return materialsList;
}

Material TextFileRepository::getMaterialByID(const std::string ID) {
	std::ifstream inputStream(this->filePath);

	Material currentMaterial;

	while (!inputStream.eof()) {
		try {
			inputStream >> currentMaterial;
			if (currentMaterial.getID() == ID) {
				inputStream.close();
				return currentMaterial;
			}
		}
		catch (...) {} //read until eof raises an error.
	}

	inputStream.close();

	throw CustomException("No material with given ID found.");
}

void TextFileRepository::addMaterial(Material material) {
	std::ofstream inputStream(this->filePath, std::ios::app | std::ios::out);

	inputStream << material << "\n";

	inputStream.close();

	this->notify();
}

void TextFileRepository::removeMaterial(Material material) {
	std::ifstream inputStream(this->filePath, std::ios::app | std::ios::out);

	std::string lines, line;
	while (std::getline(inputStream, line)) {
		std::string ID = line.substr(0, line.find(","));

		if (ID != material.getID())
			lines.append(line + "\n");
	}

	inputStream.close();

	std::ofstream outputStream(this->filePath, std::ios::trunc | std::ios::out);
	outputStream << lines;

	outputStream.close();

	this->notify();
}

void TextFileRepository::updateMaterial(std::string ID, Material newMaterial) {
	std::ifstream inputStream(this->filePath);

	std::string lines, line;
	while (std::getline(inputStream, line)) {
		std::string currentElementID = line.substr(0, line.find(","));

		if (currentElementID != ID)
			lines.append(line + "\n");
		else
			lines.append(newMaterial.toString() + "\n");
	}

	inputStream.close();

	std::ofstream outputStream(this->filePath);
	outputStream << lines;
	outputStream.close();
}
