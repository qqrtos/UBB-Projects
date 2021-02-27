#include "SMMIterator.h"
#include "SortedMultiMap.h"

void SMMIterator::putNodesOnStack(Node* root) {
	if (root != NULL) {
		this->putNodesOnStack(root->left);

		TKey k = root->key;
		std::vector<TValue> v = root->values;

		nodes.push_back(std::pair<TKey, std::vector<TValue>>(k, v));

		this->putNodesOnStack(root->right);
	}
}


/// Complexity: Theta(n)
SMMIterator::SMMIterator(const SortedMultiMap& d) :
	map(d),
	nodes{ std::vector<pair<TKey, std::vector<TValue>>>{} }
{
	this->putNodesOnStack(this->map.root);
	this->first();
}


/// Complexity: Theta(1)
void SMMIterator::first() {
	currentNodeINDX = 0;
	currentValueINDX = 0;
}


/// Complexity: Theta(1)
void SMMIterator::next() {
	if (not this->valid()) {
		throw std::exception{ "Invalid iterator." };
	}

	if (this->currentValueINDX == this->nodes[currentNodeINDX].second.size() - 1) {
		currentNodeINDX += 1;
		currentValueINDX = 0;
	}
	else {
		currentValueINDX += 1;
	}
}


/// Complexity: Theta(1)
bool SMMIterator::valid() const {
	if (this->nodes.size() == 0) return false;

	return this->currentNodeINDX < this->nodes.size() - 1 or
		(this->currentNodeINDX == this->nodes.size() - 1 and
			this->currentValueINDX < this->nodes[this->currentNodeINDX].second.size());
}


/// Complexity: Theta(1)
TElem SMMIterator::getCurrent() const {
	if (not this->valid()) {
		throw std::exception{ "Invalid iterator." };
	}

	return std::pair<TKey, TValue>(
		this->nodes[currentNodeINDX].first,
		this->nodes[currentNodeINDX].second[currentValueINDX]
		);
}
