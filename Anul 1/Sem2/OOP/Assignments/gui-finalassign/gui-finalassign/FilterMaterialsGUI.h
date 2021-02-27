#pragma once

#include <QWidget>
#include "ui_FilterMaterialsGUI.h"

#include "AssistantService.h"

class FilterMaterialsGUI : public QWidget
{
	Q_OBJECT

private:
	AssistantService& assistantService;

	Ui::FilterMaterialsGUI ui;

public:
	FilterMaterialsGUI(AssistantService& assistantservice, QWidget *parent = Q_NULLPTR);
	~FilterMaterialsGUI();

private:
	void connectSignalsAndSlots();

	void filterMaterials();

	static void populateList(std::vector<Material> materials, QListWidget* list);
};
