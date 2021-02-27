#pragma once

#include <fstream>
#include <vector>

template <typename TElem>
class Repository {
private:
	std::string filePath;

public:
	Repository(std::string path);

	std::vector<TElem> getAll();

	void add(TElem newElem);

	~Repository() = default;
};

template <typename TElem>
inline Repository<TElem>::Repository(std::string path) :
	filePath{ path }
{}

template <typename TElem>
inline std::vector<TElem> Repository<TElem>::getAll() {
	std::vector<TElem> elementsInRepository{};

	std::ifstream input{ this->filePath, std::ifstream::in };

	TElem current{};
	while (input >> current) {
		elementsInRepository.push_back(current);
	}

	input.close();

	return elementsInRepository;
}

template <typename TElem>
inline void Repository<TElem>::add(TElem newElem) {
	std::ofstream output{ this->filePath, std::ofstream::app };

	output << newElem << "\n";

	output.close();
}