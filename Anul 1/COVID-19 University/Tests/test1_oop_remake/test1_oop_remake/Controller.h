#pragma once
#include "MedLabDepartment.h"
#include <vector>
#include <memory>

class Controller {
private:
	std::vector<std::shared_ptr<MedLabDepartment>> listOfUnits;

public:
	void addDepartment(MedLabDepartment* unit);

	std::vector<std::shared_ptr<MedLabDepartment>> getAlldepartments() const;

	std::vector<std::shared_ptr<MedLabDepartment>> getAllEfficientdepartments() const;

	~Controller() = default;
};

