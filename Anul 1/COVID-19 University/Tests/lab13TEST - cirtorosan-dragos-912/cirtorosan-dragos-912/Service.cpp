#include "Service.h"

#include <algorithm>


Service::Service(Repository<Bots>& repo) :
	repository{ repo }
{}

std::vector<Bots> Service::getAll() {
	return this->repository.getAll();
}

std::vector<Bots> Service::getAllSorted() {
	std::vector<Bots> inRepo = this->repository.getAll();
	std::sort(inRepo.begin(), inRepo.end(), 
		[](const Bots first, const Bots second) -> bool {
			return first.getManufacturer() < second.getManufacturer();
		}
	);
	return inRepo;
}

std::vector<Bots> Service::filterByManufacturer(std::string manufacturer) {
	/*
		Filters the list, keeping only the bots which have the manufacturer equal to the parameter.
		Input: the manufacturer.
		Return: a vector of bots with the required manufacturer.
	*/

	std::vector<Bots> result{};
	std::vector<Bots> allElements = this->repository.getAll();

	std::copy_if(allElements.begin(), allElements.end(), std::back_inserter(result),
		[manufacturer](Bots current) { return current.getManufacturer() == manufacturer; }
	);

	return result;
}
