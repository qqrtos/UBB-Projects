#include "userinterface.h"
#include <iostream>

int main() {
	Repository repository{};
	Service service{ repository };
	UserInterface UI{ service };

	std::string mode;
	std::cout << "Choose mode:> ";
	std::getline(std::cin, mode);

	UI.StartUI(mode);
	return 0;
}