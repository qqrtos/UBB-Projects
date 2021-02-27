#pragma once

#include "Domain.h"
#include "Repository.h"

class Service {
private:
	Repository<Bots>& repository;

public:
	Service(Repository<Bots>& repo);

	std::vector<Bots> getAll();

	std::vector<Bots> getAllSorted();

	std::vector<Bots> filterByManufacturer(std::string manufacturer);

	~Service() = default;
};

