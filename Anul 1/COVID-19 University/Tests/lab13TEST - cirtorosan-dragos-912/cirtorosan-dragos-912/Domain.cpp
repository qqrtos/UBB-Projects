#include "Domain.h"
#include <algorithm>
#include <sstream>

std::vector<std::string> splitArguments(std::string line) {
    std::string delimiter = " | ";
    std::vector<std::string> result{};
    size_t pos = 0;
    std::string token;

    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        result.push_back(token);
        line.erase(0, pos + delimiter.length());
    }

    result.push_back(line);

    return result;
}


Bots::Bots(std::string manuf, std::string model, int yearOfFabr, std::string color) :
    manufacturer{ manuf },
    model{ model },
    yearOfFabrication{ yearOfFabr },
    color{ color }
{}

Bots::Bots(const Bots & copyElement) {
    this->manufacturer = copyElement.manufacturer;
    this->model = copyElement.model;
    this->yearOfFabrication = copyElement.yearOfFabrication;
    this->color = copyElement.color;
}

std::string Bots::getManufacturer() const {
    return this->manufacturer;
}

std::string Bots::getColor() const {
    return this->color;
}

std::string Bots::toString() const {
    return std::string{ this->manufacturer + " - " + this->model };
}

std::istream& operator>>(std::istream& input, Bots& target) {
    std::string line = "";

    std::getline(input, line);
    
    if (line != "") {
        std::vector<std::string> tokens = splitArguments(line);
        target.manufacturer = tokens[0];
        target.model = tokens[1];
        target.yearOfFabrication = std::stoi(tokens[2]);
        target.color = tokens[3];
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const Bots target) {
    output << target.manufacturer << " | " << target.model << " | " << target.yearOfFabrication << " | " << target.color;
    return output;
}
