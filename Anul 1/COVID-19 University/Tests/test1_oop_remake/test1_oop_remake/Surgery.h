#pragma once
#include <string>
#include "MedLabDepartment.h"

class Surgery : virtual public MedLabDepartment {
private:
	int nrPatients;

public:
	Surgery() = default;

	Surgery(std::string deckName, int nrDoctors, int nrPatients);

	bool isEfficient() const override;

	std::string toString() const override;
};

