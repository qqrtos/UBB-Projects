#include "NeonatalUnit.h"

NeonatalUnit::NeonatalUnit(std::string deckName, int nrDoctors, int nrMothers, int nrBabies, float averageGrade) :
	MedLabDepartment{ deckName,nrDoctors },
	nrMothers{ nrMothers },
	nrBabies{ nrBabies },
	averageGrade{ averageGrade }
{}

bool NeonatalUnit::isEfficient() const {
	return this->averageGrade > 8.5 and this->nrBabies >= this->nrMothers;
}

std::string NeonatalUnit::toString() const {
	return std::string(this->department + ", " + "Neonatal Unit, " + std::to_string(this->nrDoctors) + ", " + std::to_string(this->nrMothers) + \
		", " + std::to_string(this->nrBabies) + ", " + std::to_string(this->averageGrade) + +"\n");
}
