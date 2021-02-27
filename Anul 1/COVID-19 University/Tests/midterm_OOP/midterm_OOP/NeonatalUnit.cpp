#include "NeonatalUnit.h"

NeonatalUnit::NeonatalUnit(std::string hospName, int nrDoctors, int nrMothers, int nrBabies, float averageGrade) :
	hospitalName{ hospName },
	nrOfDoctors{ nrDoctors },
	nrBabies{ nrBabies },
	averageGrade{ averageGrade }
{}

bool NeonatalUnit::isEfficient() const {
	return this->nrBabies >= this->nrMothers and this->averageGrade > 8.5;
}

std::string NeonatalUnit::toString() const {
	return std::string{ this->hospitalName + ", " + std::to_string(this->nrOfDoctors) + ", " + std::to_string(this->nrMothers) + ", " + std::to_string(this->nrBabies) + ", " + std::to_string(this->averageGrade) + "\n" };
}

std::ostream& operator<<(std::ostream& outStream, NeonatalUnit neoNatal) {
	outStream << neoNatal.toString();
}
