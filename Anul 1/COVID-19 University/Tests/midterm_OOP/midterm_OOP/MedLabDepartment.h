#pragma once
#include <string>

class MedLabDepartment {
public:
	virtual bool isEfficient() const = 0;

	virtual std::string toString() const = 0;
};