#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;


/// Complexity: Best - Theta(1), Worst: Theta(height), Total: O(height)
Node* SortedMultiMap::insertNode(Node* insertFrom, TElem data) {
	if (insertFrom == NULL) {
		insertFrom = new Node{ data.first, data.second };
	}
	else if (insertFrom->key == data.first) {
		insertFrom->values.push_back(data.second);
	}
	else if (this->relation(data.first, insertFrom->key)) {
		insertFrom->left = insertNode(insertFrom->left, data);
	}
	else {
		insertFrom->right = insertNode(insertFrom->right, data);
	}
	return insertFrom;
}


/// Complexity: Best - Theta(1), Worst - Theta(height), Total - O(height)
vector<TValue> SortedMultiMap::getValues(Node* current, TKey k) const {
	if (current == NULL) {
		return vector<TValue>();
	}
	else {
		if (current->key == k) {
			return current->values;
		}
		else if (not this->relation(current->key, k)) {
			return this->getValues(current->left, k);
		}
		else if (this->relation(current->key, k)) {
			return this->getValues(current->right, k);
		}
	}
}


/// Complexity: Theta(n)
void SortedMultiMap::deleteBST(Node* current) {
	if (current != NULL) {
		this->deleteBST(current->left);
		this->deleteBST(current->right);
		delete current;
	}
}

/// Complexity: O(height)
void SortedMultiMap::replaceValueRecursive(Node* current, TKey k, TValue oldValue, TValue newValue) {
	if (current == NULL) {
		return;
	}
	else {
		if (current->key == k) {
			for (int i = 0; i < current->values.size(); ++i) {
				if (current->values[i] == oldValue) {
					current->values[i] = newValue;
					return;
				}
			}
		}
		else if (not this->relation(current->key, k)) {
			return this->replaceValueRecursive(current->left, k, oldValue, newValue);
		}
		else if (this->relation(current->key, k)) {
			return this->replaceValueRecursive(current->right, k, oldValue, newValue);
		}
	}
}


/// Complexity: Best - Theta(1), Worst - Theta(height), Total - O(height)
Node* successor(Node* node) {
	Node* current = node;

	while (current and current->left != NULL) {
		current = current->left;
	}

	return current;
}


/// Complexity: Best - Theta(1), Worst - Theta(height), Total - O(height)
Node* SortedMultiMap::deleteNode(Node* current, TKey k, vector<TValue> v, bool& wasDeleted) {
	if (current == NULL) {
		return current;
	}

	if (current->key == k and current->values == v) { // Delete an entire node (key + all values)
		wasDeleted = true;
		this->count -= 1;

		if (current->left == NULL) { // Node has no left child
			Node* temp = current->right;
			delete current;
			return temp;
		}
		else if (current->right == NULL) { // Node has no right child
			Node* temp = current->left;
			delete current;
			return temp;
		}
		else { // Node has 2 children
			Node* temp = successor(current->right); // Get the inorder successor

			current->key = temp->key;
			current->values = temp->values;

			current->right = this->deleteNode(current->right, temp->key, temp->values, wasDeleted); // Delete the inorder successor
		} 
	}
	else if (current->key == k and v.size() == 1) { // Delete a value from the array of values for that key
		auto pos = find(current->values.begin(), current->values.end(), v[0]);

		if (pos != current->values.end()) {
			wasDeleted = true;
			this->count -= 1;
			current->values.erase(pos);
		}

		return this->root;
	}
	else if (not this->relation(current->key, k)) {
		return this->deleteNode(current->left, k, v, wasDeleted);
	}
	else {
		return this->deleteNode(current->right, k, v, wasDeleted);
	}

	return current;
}


SortedMultiMap::SortedMultiMap(Relation r) :
	relation{ r },
	count{ 0 },
	root{ NULL }
{}

/// Total complexity: O(height)
void SortedMultiMap::add(TKey c, TValue v) {
	this->root = this->insertNode(this->root, pair<TKey, TValue>(c, v));
	this->count += 1;
}

/// Total complexity: O(height)
vector<TValue> SortedMultiMap::search(TKey c) const {
	return this->getValues(this->root, c);
}

/// Total complexity: O(height)
bool SortedMultiMap::remove(TKey c, TValue v) {
	bool isDeleted = false;
	this->root = this->deleteNode(this->root, c, vector<TValue>(1, v), isDeleted);
    return isDeleted;
}

void SortedMultiMap::replace(TKey k, TValue oldValue, TValue newValue) {
	this->replaceValueRecursive(this->root, k, oldValue, newValue);
}

/// Complexity: Theta(1)
int SortedMultiMap::size() const {
	return this->count;
}

/// Complexity: Theta(1)
bool SortedMultiMap::isEmpty() const {
	return this->count == 0;
}

SMMIterator SortedMultiMap::iterator() const {
  	return SMMIterator(*this);
}

/// Complexity: Theta(n)
SortedMultiMap::~SortedMultiMap() {
	this->deleteBST(this->root);
}
