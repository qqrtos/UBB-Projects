#include "FilterMaterialsGUI.h"

FilterMaterialsGUI::FilterMaterialsGUI(AssistantService& assistantservice, QWidget* parent) :
	QWidget(parent),
	assistantService{ assistantservice }
{
	ui.setupUi(this);
	this->connectSignalsAndSlots();
}

FilterMaterialsGUI::~FilterMaterialsGUI() {}

void FilterMaterialsGUI::connectSignalsAndSlots() {
	QObject::connect(this->ui.filter_pushButton, &QPushButton::clicked, this, &FilterMaterialsGUI::filterMaterials);
}

void FilterMaterialsGUI::filterMaterials() {
	int microfragmentsFilter;
	Size sizeFilter = Size(this->ui.size_lineEdit->text().toStdString());
	
	if (this->ui.microfragments_lineEdit->text().toStdString() != "") {
		microfragmentsFilter = this->ui.microfragments_lineEdit->text().toInt();
	}
	else microfragmentsFilter = 0;


	std::vector<Material> filteredMaterials = this->assistantService.filterBySizeAndMicrofragments(sizeFilter, microfragmentsFilter);

	populateList(filteredMaterials, this->ui.filteredMaterials_listWidget);
}

void FilterMaterialsGUI::populateList(std::vector<Material> materials, QListWidget* list) {
	list->clear();
	for (Material current : materials) {
		QString materialInList = QString::fromStdString(current.toString());
		QListWidgetItem* item = new QListWidgetItem{ materialInList };
		list->addItem(item);
	}
}
