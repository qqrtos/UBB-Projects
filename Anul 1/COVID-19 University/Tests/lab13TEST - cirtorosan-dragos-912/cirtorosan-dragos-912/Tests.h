#pragma once
#include "Service.h"
#include <cassert>

class Tests {
public:
	void runAllTests();

	void test_FilterByManufacturer__CorrectSize();
};

inline void Tests::runAllTests() {
	test_FilterByManufacturer__CorrectSize();
}

void Tests::test_FilterByManufacturer__CorrectSize() {
	Repository<Bots> r{ "testRepo.txt" };
	r.add(Bots{ "Okeanos", "Baker", 2512, "blue" });
	r.add(Bots{ "Okeanos", "Surveyor", 2313, "red" });
	r.add(Bots{ "Skyrim", "Baker", 1317, "black" });

	Service s{ r };

	assert(s.filterByManufacturer("Okeanos").size() == 2);

	remove("testRepo.txt");
}