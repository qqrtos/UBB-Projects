#include "Map.h"
#include "MapIterator.h"
#include <exception>

using namespace std;

MapIterator::MapIterator(const Map& d) :
	map(d),
	currentEntry{ NULL_TELEM },
	currentIndex{ this->map.m }
{
	this->first();
}


void MapIterator::first() {
	for (int i = 0; i < this->map.m; ++i) {
		Entry currentEntry = this->map.elements[i];

		if (currentEntry.isDeleted == true or currentEntry.entry == NULL_TELEM)
			continue;

		this->currentEntry = currentEntry.entry;
		this->currentIndex = i;
		return;
	}

	this->currentIndex = this->map.m;
}


void MapIterator::next() {
	if (!this->valid()) {
		throw std::exception{ "Invalid iterator." };
	}

	for (int i = this->currentIndex + 1; i < this->map.m; ++i) {
		Entry currentEntry = this->map.elements[i];

		if (currentEntry.isDeleted == true or currentEntry.entry == NULL_TELEM)
			continue;

		this->currentEntry = currentEntry.entry;
		this->currentIndex = i;
		return;
	}

	this->currentIndex = this->map.m;
}


TElem MapIterator::getCurrent() {
	if (!this->valid()) {
		throw std::exception{ "Invalid iterator." };
	}

	return this->currentEntry;
}


bool MapIterator::valid() const {
	return this->currentIndex < this->map.m;
}



