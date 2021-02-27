#include "MyApplicationGUI.h"
#include <QtWidgets/QApplication>

#include <qdebug.h>
#include <memory>

#include "MyApplicationGUI.h"
#include "Tests.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Tests tests{};
    tests.runAllTests();

    std::string path = "repository.txt";
    std::auto_ptr<Repository<Bots>> repo{ new Repository<Bots>{path} };
    Service serv{ *repo };

    MyApplicationGUI mainWindow{ serv };
    mainWindow.show();

    return a.exec();
}
