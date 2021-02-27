#include "AssistantTableWindow.h"

AssistantTableWindow::AssistantTableWindow(QAbstractTableModel* model, QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);

	this->ui.assistantMaterials_tableView->setModel(model);
}

AssistantTableWindow::~AssistantTableWindow() {}
