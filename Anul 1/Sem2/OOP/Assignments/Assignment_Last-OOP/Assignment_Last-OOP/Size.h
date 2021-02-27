#pragma once
#include <iostream>

class Size {
private:
	int width, length, height;

public:
	Size() = default;

	Size(int width, int length, int height);

	Size(std::string dimensions);

	Size(const Size& size);

	friend std::ostream& operator<<(std::ostream& outStream, Size size);

	friend std::istream& operator>>(std::istream& inputStream, Size& size);

	std::string toString() const;

	void operator=(const Size newSize);

	bool operator==(const Size other);

	~Size() = default;
};

