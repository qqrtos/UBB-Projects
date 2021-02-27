#pragma once

#include <QWidget>
#include "ui_AssistantGUI.h"
#include "AssistantService.h"
#include <ui_AssistantGUI.h>
#include <QShortcut>

#include "SeniorService.h"
#include "FilterMaterialsGUI.h"
#include "AssistantTableWindow.h"

class AssistantGUI : public QWidget {
	Q_OBJECT

private:
	Ui::AssistantGUI ui;

	AssistantService& assistantService;
	
	SeniorService& seniorService;

	QAbstractTableModel* assistantTableModel;

public:
	AssistantGUI(AssistantService& assistantservice, SeniorService& seniorService, QAbstractTableModel* assistantTableModel, QWidget *parent = Q_NULLPTR);
	~AssistantGUI();

private:
	void connectSignalsAndSlots();

	void saveMaterialToAssistantList();

	void showNextMaterial();

	void filterMaterials();

	void openAssistantListInExternalApp();

	void displayAssistantList();

	void undoOperation();
	
	void redoOperation();
};
