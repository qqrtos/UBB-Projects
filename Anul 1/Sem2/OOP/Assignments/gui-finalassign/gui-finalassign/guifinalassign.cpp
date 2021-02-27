#include "guifinalassign.h"

guifinalassign::guifinalassign(SeniorGUI& seniorgui, AssistantGUI& assistantgui, QWidget* parent) :
	QMainWindow(parent),
	seniorGUI{ seniorgui },
	assistantGUI{ assistantgui }
{
	ui.setupUi(this);
	this->connectSignalsAndSlots();
}

void guifinalassign::connectSignalsAndSlots() {
	QObject::connect(this->ui.seniorMode_pushButton, &QPushButton::clicked, this, &guifinalassign::openSeniorGUI);

	QObject::connect(this->ui.assistantMode_pushButton, &QPushButton::clicked, this, &guifinalassign::openAssistantGUI);
}

void guifinalassign::openSeniorGUI() {
	this->seniorGUI.show();
	//this->hide();
}

void guifinalassign::openAssistantGUI() {
	this->assistantGUI.show();
	//this->hide();
}
