#include "guifinalassign.h"
#include <QtWidgets/QApplication>
#include <memory>
#include <qdebug.h>

#include <iostream>

#include "InMemoryRepository.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	/*
		TEST UNDO / REDO
	*/

	//TextFileRepository* r = new TextFileRepository("testundoredo.txt");
	//SeniorService s{ *r };
	//s.addMaterial("12", Size{ 1,1,1 }, 3, 3, "aaa");
	//s.addMaterial("123", Size{ 1,1,1 }, 33, 33, "bbb");
	//s.addMaterial("1234", Size{ 1,1,1 }, 333, 333, "ccc");

	//s.undo();
	//s.undo();
	////s.undo();
	////s.undo();
	//s.redo();

	//s.updateMaterial("12", Size{ 2,2,2 }, 5, 5, "ddd");

	//s.undo();
	//s.redo();

	//delete r;

	/*
		END TEST
	*/

	std::ifstream fileInput{ "config.txt" };
	std::string line; 
	fileInput >> line;
	std::string repositoryConfiguration = line.substr(line.find('=') + 1);

	TextFileRepository seniorRepository("H:\\Informatique\\Anul 1\\Sem2\\OOP\\Assignments\\gui-finalassign\\gui-finalassign\\repository.txt");
	std::auto_ptr<Repository> assistantRepository;
	if (repositoryConfiguration == "html") {
		assistantRepository = std::auto_ptr<Repository>(new HTMLFileRepository{ \
			"H:\\Informatique\\Anul 1\\Sem2\\OOP\\Assignments\\gui-finalassign\\gui-finalassign\\assistant.html" });
	}
	else if (repositoryConfiguration == "in_memory") {
		assistantRepository = std::auto_ptr<Repository>(new InMemoryRepository{});
	}
	else if (repositoryConfiguration == "csv") {
		assistantRepository = std::auto_ptr<Repository>(new CSVFileRepository{ \
			"H:\\Informatique\\Anul 1\\Sem2\\OOP\\Assignments\\gui-finalassign\\gui-finalassign\\assistant.csv" });
	}

	SeniorService seniorService{ seniorRepository };
	AssistantService assistantService{ seniorRepository,*assistantRepository };

	Assistant_TableModel model{ *assistantRepository };
	SeniorGUI seniorgui{ seniorService,assistantService };
	AssistantGUI assistantgui{ assistantService,seniorService,&model };
	guifinalassign mainWindow{ seniorgui,assistantgui };

	seniorRepository.addObserver(&seniorgui);
	assistantRepository->addObserver(&model);

	mainWindow.show();
	
	return a.exec();
}
