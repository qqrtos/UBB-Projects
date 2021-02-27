#pragma once
#include <string>
#include "MedLabDepartment.h"

class NeonatalUnit : virtual public MedLabDepartment{
private:
	int nrMothers;
	int nrBabies;
	float averageGrade;

public:
	NeonatalUnit() = default;

	NeonatalUnit(std::string deckName, int nrDoctors, int nrMothers, int nrBabies, float averageGrade);

	bool isEfficient() const override;

	std::string toString() const override;
};

