#pragma once

#include "SortedMultiMap.h"

#include <stack>


class SMMIterator{
	friend class SortedMultiMap;
private:
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	std::vector<std::pair<TKey, std::vector<TValue>>> nodes;
	int currentNodeINDX;
	int currentValueINDX;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;

private:
	void putNodesOnStack(Node* root);
};

