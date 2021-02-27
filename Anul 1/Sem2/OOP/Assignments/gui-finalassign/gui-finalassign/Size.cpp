#include "Size.h"
#include <string>
#include "DynamicVector.h"
#include <vector>


Size::Size(int width, int length, int height) {
	if (width <= 0 || length <= 0 || height <= 0)
		throw std::exception("Invalid size");
	this->width = width;
	this->height = height;
	this->length = length;
}

Size::Size(std::string dimensions) {
	dimensions.append("X"); ///formatting purposes.

	std::string delimiter = "X";
	int position = 0;
	std::vector<std::string> arguments;

	///Split string using the 'x' delimiter.
	while ((position = dimensions.find(delimiter)) != std::string::npos) {
		arguments.push_back(dimensions.substr(0, position));
		dimensions.erase(0, position + delimiter.length());
	}

	///Convert arguments to float using stod and instantiate size.
	this->width = std::stoi(arguments[0]);
	this->length = std::stoi(arguments[1]);
	this->height = std::stoi(arguments[2]);
}

Size::Size(const Size& size) {
	this->height = size.height;
	this->width = size.width;
	this->length = size.length;
}

std::string Size::toString() const {
	return std::to_string(this->width) + "X" + std::to_string(this->length) + "X" + std::to_string(this->height);
}

void Size::operator=(const Size newSize) {
	this->height = newSize.height;
	this->width = newSize.width;
	this->length = newSize.length;
}

bool Size::operator==(const Size other) {
	return this->height == other.height && this->length == other.length && this->width == other.width;
}

std::ostream& operator<<(std::ostream& outStream, Size size) {
	outStream << size.width << "X" << size.length << "X" << size.height;
	return outStream;
}

std::istream& operator>>(std::istream& inputStream, Size& size) {
	std::string input;

	inputStream >> input;
	/*input.append("X"); ///formatting purposes.

	std::string delimiter = "X";
	int position = 0;
	DynamicVector<std::string> arguments;

	///Split string using the 'x' delimiter.
	while ((position = input.find(delimiter)) != std::string::npos) {
		arguments.append(input.substr(0, position));
		input.erase(0, position + delimiter.length());
	}

	///Convert arguments to float using stod and instantiate size.
	size.width = std::stod(arguments[0]);
	size.length = std::stod(arguments[1]);
	size.height = std::stod(arguments[2]);*/

	Size sizeFromInput{ input };
	size = sizeFromInput;

	return inputStream;
}