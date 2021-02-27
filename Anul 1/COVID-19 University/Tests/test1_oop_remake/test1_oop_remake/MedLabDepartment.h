#pragma once
#include <string>

class MedLabDepartment {
protected:
	std::string department;
	int nrDoctors;

	MedLabDepartment(std::string department, int nrDoctors):
		department{department},
		nrDoctors{nrDoctors}
	{}

public:
	virtual bool isEfficient() const = 0;

	virtual std::string toString() const = 0;

	~MedLabDepartment() = default;
};