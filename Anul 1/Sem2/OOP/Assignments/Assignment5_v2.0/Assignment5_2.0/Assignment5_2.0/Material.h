#pragma once
#include <string>
#include <iostream>
#include "Size.h"


class Material {
private:
	std::string ID;
	Size size;
	int radioactivityLevel;
	int quantityOfMicrofragments;
	std::string digitizedScan;

public:
	Material() = default;

	Material(std::string ID, Size size, int radioactivityLevel, int quantityOfMicrofragments, std::string digitizedScan);

	Material(const Material& material);

	std::string getID();

	Size& getSize();

	float getRadioactivityLevel();

	float getQuantityOfMicrofragments();

	std::string getDigitizedScan();

	void setID(const std::string newID);

	void setSize(const Size newSize);

	void setRadioactivityLevel(const float newRadioactivityLevel);

	void setQuantityOfMicrofragments(const float newQuantityOfMicrofragments);

	void setDigitizedScan(const std::string newDigitizedScan);

	friend std::ostream& operator<<(std::ostream& outStream, Material material);

	friend std::istream& operator>>(std::istream& inputStream, Material& material);

	void operator=(Material newMaterial);

	bool operator==(const Material compareMaterial);

	std::string toString();

	~Material() = default;
};
