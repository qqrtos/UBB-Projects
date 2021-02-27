#include "SeniorGUI.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	/// H:\\\\Informatique\\Anul 1\\Sem2\\OOP\\Assignments\\Assignment_Last-OOP\\Assignment_Last-OOP\\repository.txt
	std::string assistantRepositoryLocation{ "H:\\\\Informatique\\Anul 1\\Sem2\\OOP\\Assignments\\Assignment_Last - OOP\\Assignment_Last - OOP\\assistant.html" };
	std::string seniorRepositoryLocation{ "H:\\\\Informatique\\Anul 1\\Sem2\\OOP\\Assignments\\Assignment_Last-OOP\\Assignment_Last-OOP\\repository.txt" };
	//assistantRepositoryLocation.replace(assistantRepositoryLocation.find("\\"), 1, "\\\\");
	//seniorRepositoryLocation.replace(seniorRepositoryLocation.find("\\"), 1, "\\\\");

	Repository* assistantRepository = new HTMLFileRepository{ assistantRepositoryLocation };
	TextFileRepository seniorRepository{ seniorRepositoryLocation };

	AssistantService assistantService{ seniorRepository,*assistantRepository };
	SeniorService seniorService{ seniorRepository };

	SeniorGUI seniorGraphicalUI{ seniorService,assistantService };
	seniorGraphicalUI.show();

	//delete assistantRepository;

	return a.exec();
}
