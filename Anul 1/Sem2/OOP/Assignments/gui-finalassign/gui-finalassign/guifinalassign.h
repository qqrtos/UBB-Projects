#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_guifinalassign.h"

#include "SeniorGUI.h"
#include "AssistantGUI.h"

class guifinalassign : public QMainWindow {
	Q_OBJECT

private:
	Ui::guifinalassignClass ui;

	SeniorGUI& seniorGUI;

	AssistantGUI& assistantGUI;

public:
	guifinalassign(SeniorGUI& seniorgui, AssistantGUI& assistantgui, QWidget *parent = Q_NULLPTR);

private:

	void connectSignalsAndSlots();

	void openSeniorGUI();

	void openAssistantGUI();
};
