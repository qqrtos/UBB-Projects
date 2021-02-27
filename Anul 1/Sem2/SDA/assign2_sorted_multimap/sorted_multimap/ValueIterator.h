#pragma once

#include "SortedMultiMap.h"


class ValueIterator {
	friend class SortedMultiMap;

private:
	const SortedMultiMap& map;
	TKey key;
	NODE* current;

public:
	ValueIterator(const SortedMultiMap& map, const TKey k);
	void first();
	void next();
	bool valid() const;
	TValue getCurrent() const;
};

