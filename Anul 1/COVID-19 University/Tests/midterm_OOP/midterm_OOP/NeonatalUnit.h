#pragma once
#include "MedLabDepartment.h"
class NeonatalUnit : public MedLabDepartment {
private:
	std::string hospitalName;
	int nrOfDoctors;
	int nrMothers;
	int nrBabies;
	float averageGrade;

public:
	NeonatalUnit(std::string hospName, int nrDoctors, int nrMothers, int nrBabies, float averageGrade);

	friend std::ostream& operator<<(std::ostream& outStream, NeonatalUnit neoNatal);

	friend std::istream& operator>>(std::istream& inputStream, NeonatalUnit& neoNatal);

	bool isEfficient() const override;

	std::string toString() const override;
};

