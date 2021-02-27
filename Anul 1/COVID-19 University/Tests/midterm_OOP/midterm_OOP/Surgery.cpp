#include "Surgery.h"
#include <vector>
#include <iostream>
#include <sstream>

std::vector<std::string> split(std::string& input, char delimiter, bool spaceAfterDelimiterFormat = false) {
	std::vector<std::string> result{};
	std::string token;
	std::istringstream stream(input);

	while (std::getline(stream, token, delimiter)) {
		if (spaceAfterDelimiterFormat == true)
			stream.get(); //useless space after comma
		result.push_back(token);
	}

	return result;
}

Surgery::Surgery(std::string hospitalName, int nrDoctors, int nrPatiens) :
	nrOfDoctors{nrDoctors},
	hospitalName{hospitalName},
	nrPatiens{nrPatiens}
{}

bool Surgery::isEfficient() const {
	return (this->nrPatiens / this->nrOfDoctors) >= 2;
}

std::string Surgery::toString() const {
	return std::string{ this->hospitalName + ", " + std::to_string(this->nrOfDoctors) + ", " + std::to_string(this->nrPatiens) + "\n" };
}

std::ostream& operator<<(std::ostream& outStream, Surgery surgery) {
	outStream << surgery.toString();
	return outStream;
}
