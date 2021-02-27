#pragma once

#include <QtWidgets/QMainWindow>
#include <qwidget.h>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QShortcut>

#include "AssistantService.h"
#include "SeniorService.h"
#include "CSVFileRepository.h"
#include "HTMLFileRepository.h"

class SeniorGUI : public QWidget, public Observer {
	Q_OBJECT

private:
	AssistantService& assistantService;
	SeniorService& seniorService;

public:
	SeniorGUI(SeniorService& seniorService, AssistantService& assistantService, QWidget* parent = 0);

	~SeniorGUI() = default;

private:
	QListWidget* materialsList;
	QLineEdit* IDEdit;
	QLineEdit* sizeEdit;
	QLineEdit* fragmentsEdit;
	QLineEdit* radioactivityEdit;
	QLineEdit* digitizedScanEdit;

	QPushButton* addMaterialButton;
	QPushButton* deleteMaterialButton;
	QPushButton* updateMaterialButton;

	void update() override;

	void initGUI();
	void populateMaterialsList();
	void connectSignalsAndSlots();

	Material getMaterialAtIndex();
	int getSelectedIndexInList();
	void updateSelectedItem();

	void addMaterial_ButtonHandlerGUI();
	void deleteMaterial_ButtonHandlerGUI();
	void updateMaterial_ButtonHandlerGUI();
	void undoOperation();
	void redoOperation();

signals:
	void materialsListChanged();
};