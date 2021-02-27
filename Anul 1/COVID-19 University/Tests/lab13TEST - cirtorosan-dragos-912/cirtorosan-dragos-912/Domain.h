#pragma once

#include <string>
#include <exception>
#include <iostream>
#include <vector>

class Bots {
private: 
	std::string manufacturer;
	std::string model;
	int yearOfFabrication;
	std::string color;

public:
	Bots() = default;

	Bots(std::string manuf, std::string model, int yearOfFabr, std::string color);

	Bots(const Bots& copyElement);

	std::string getManufacturer() const;
	/*std::string getModel() const;
	int getYearOfFabrication() const;*/
	std::string getColor() const;

	std::string toString() const;

	friend std::istream& operator>>(std::istream& input, Bots& target);

	friend std::ostream& operator<<(std::ostream& output, const Bots target);

	~Bots() = default;
};

