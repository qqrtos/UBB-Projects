#include "Controller.h"
//#include <iterator>
#include <algorithm>

void Controller::addDepartment(MedLabDepartment* unit) {
	this->listOfUnits.push_back(std::shared_ptr<MedLabDepartment>(unit));
}

std::vector<std::shared_ptr<MedLabDepartment>> Controller::getAlldepartments() const {
	return this->listOfUnits;
}

std::vector<std::shared_ptr<MedLabDepartment>> Controller::getAllEfficientdepartments() const {
	std::vector<std::shared_ptr<MedLabDepartment>> result{};

	std::copy_if(this->listOfUnits.begin(), this->listOfUnits.end(), std::back_inserter(result),
		[](std::shared_ptr<MedLabDepartment> element) {
			return element->isEfficient() == true;
		}
	);

	return result;
}
