#pragma once

#include <QWidget>
#include "ui_AssistantTableWindow.h"

#include "Assistant_TableModel.h"

class AssistantTableWindow : public QWidget {
	Q_OBJECT

public:
	AssistantTableWindow(QAbstractTableModel* model, QWidget *parent = Q_NULLPTR);
	~AssistantTableWindow();

private:
	Ui::AssistantTableWindow ui;
};
