#pragma once
#include <string>

class Material {
private:
	std::string ID;
	std::string size;
	float radioactivityLevel;
	float quantityOfMicrofragments;
	std::string digitizedScan;

public:
	Material() = default;

	Material(std::string ID, std::string size, float radioactivityLevel, float quantityOfMicrofragments, std::string digitizedScan);

	Material(const Material& copyMaterial);
	
	~Material() = default;

	std::string getID() const;

	std::string getSize() const;

	float getRadioactivityLevel() const;

	float getQuantityOfMicrofragments() const;

	std::string getDigitizedScan() const;

	void setID(std::string newID);

	void setSize(std::string newSize);

	void setRadioactivityLevel(float newRadioactivityLevel);

	void setQuantityOfMicrofragments(float newQuantityOfMicrofragments);

	void setDigitizedScan(std::string newDigitizedScan);

	friend std::ostream& operator<<(std::ostream& outStream, const Material& material);
};

