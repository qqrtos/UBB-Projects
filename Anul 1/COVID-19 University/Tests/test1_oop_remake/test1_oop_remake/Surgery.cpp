#include "Surgery.h"

Surgery::Surgery(std::string deckName, int nrDoctors, int nrPatients) :
	MedLabDepartment{ deckName,nrDoctors },
	nrPatients{ nrPatients }
{}

bool Surgery::isEfficient() const {
	return float(this->nrDoctors) / float(this->nrPatients) >= 2;
}

std::string Surgery::toString() const {
	return std::string(this->department + ", " + "Surgery, " + std::to_string(this->nrDoctors) + ", " + std::to_string(this->nrPatients) + "\n");
}
