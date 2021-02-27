#pragma once
#include "MedLabDepartment.h"

class Surgery : public MedLabDepartment {
private:
	std::string hospitalName;
	int nrPatiens;
	int nrOfDoctors;

public:
	Surgery(std::string hospitalName, int nrDoctors, int nrPatiens);

	friend std::ostream& operator<<(std::ostream& outStream, Surgery surgery);

	bool isEfficient() const override;

	std::string toString() const override;

	~Surgery() = default;
};

