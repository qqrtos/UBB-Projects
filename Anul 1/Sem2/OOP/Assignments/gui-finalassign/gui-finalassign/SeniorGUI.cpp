#include "SeniorGUI.h"
#include <qmessagebox.h>

int _createInformationWindow(std::string message) {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Error");
	msgBox.setText(QString::fromStdString(message));
	return msgBox.exec();
}

SeniorGUI::SeniorGUI(SeniorService& seniorService, AssistantService& assistantService, QWidget* parent) :
	QWidget{ parent },
	seniorService{ seniorService },
	assistantService{ assistantService }
{
	this->initGUI();
	this->connectSignalsAndSlots();
	this->populateMaterialsList();
}

void SeniorGUI::update() {
	this->populateMaterialsList();
}

void SeniorGUI::initGUI() {
	//General layout.
	QHBoxLayout* layout = new QHBoxLayout{ this };

	//Initialize the materials list.
	this->materialsList = new QListWidget{};
	layout->addWidget(this->materialsList);

	//On the right - information about the materials + buttons
	QWidget* rightSide = new QWidget{};
	QVBoxLayout* verticalBox = new QVBoxLayout{ rightSide };

	//In the vertical box on the right, add info about the material and buttons
	QWidget* materialsInfo = new QWidget{};
	QFormLayout* formLayout = new QFormLayout{ materialsInfo };

	this->IDEdit = new QLineEdit{};
	this->sizeEdit = new QLineEdit{};
	this->fragmentsEdit = new QLineEdit{};
	this->radioactivityEdit = new QLineEdit{};
	this->digitizedScanEdit = new QLineEdit{};

	//Create pairs of label - line edit rows
	QLabel* IDLabel = new QLabel{ "ID: " };
	IDLabel->setBuddy(this->IDEdit);
	QLabel* sizeLabel = new QLabel{ "Size: " };
	IDLabel->setBuddy(this->sizeEdit);
	QLabel* fragmentsLabel = new QLabel{ "Microfragments: " };
	IDLabel->setBuddy(this->fragmentsEdit);
	QLabel* radioactivityLabel = new QLabel{ "Radioactivity: " };
	IDLabel->setBuddy(this->radioactivityEdit);
	QLabel* digitizedScanLabel = new QLabel{ "Digitized Scan: " };
	IDLabel->setBuddy(this->digitizedScanEdit);

	formLayout->addRow(IDLabel, this->IDEdit);
	formLayout->addRow(sizeLabel, this->sizeEdit);
	formLayout->addRow(fragmentsLabel, this->fragmentsEdit);
	formLayout->addRow(radioactivityLabel, this->radioactivityEdit);
	formLayout->addRow(digitizedScanLabel, this->digitizedScanEdit);

	verticalBox->addWidget(materialsInfo);

	//Add buttons on the form.
	QWidget* buttonsWiddget = new QWidget{};
	QHBoxLayout* horizontalButtonBox = new QHBoxLayout{ buttonsWiddget };

	this->addMaterialButton = new QPushButton{"Add Material"};
	this->deleteMaterialButton = new QPushButton{"Delete material"};
	this->updateMaterialButton = new QPushButton{"Update material"};

	horizontalButtonBox->addWidget(this->addMaterialButton);
	horizontalButtonBox->addWidget(this->deleteMaterialButton);
	horizontalButtonBox->addWidget(this->updateMaterialButton);

	verticalBox->addWidget(buttonsWiddget);

	layout->addWidget(rightSide);
}

void SeniorGUI::populateMaterialsList() {
	std::vector<Material> materials = this->seniorService.getAllMaterials();

	if (this->materialsList->count() > 0)
		this->materialsList->clear();

	for (Material current : materials) {
		QString materialInList = QString::fromStdString(current.getID());
		QListWidgetItem* item = new QListWidgetItem{ materialInList };
		this->materialsList->addItem(item);
	}
}

void SeniorGUI::connectSignalsAndSlots() {
	QShortcut* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
	QObject::connect(undoShortcut, &QShortcut::activated, this, &SeniorGUI::undoOperation);

	QObject::connect(undoShortcut, &QShortcut::activated, this, &SeniorGUI::updateSelectedItem);

	QShortcut* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
	QObject::connect(redoShortcut, &QShortcut::activated, this, &SeniorGUI::redoOperation);

	QObject::connect(redoShortcut, &QShortcut::activated, this, &SeniorGUI::updateSelectedItem);

	///Every time materials changed signal is emited => populate materials list again
	QObject::connect(this, &SeniorGUI::materialsListChanged, this, &SeniorGUI::populateMaterialsList);

	///Connect add button click to the button handler.
	QObject::connect(this->addMaterialButton, &QPushButton::clicked, this, &SeniorGUI::addMaterial_ButtonHandlerGUI);

	///Connect delete button click to delete button handler.
	QObject::connect(this->deleteMaterialButton, &QPushButton::clicked, this, &SeniorGUI::deleteMaterial_ButtonHandlerGUI);

	///Connect update button click to update button handler.
	QObject::connect(this->updateMaterialButton, &QPushButton::clicked, this, &SeniorGUI::updateMaterial_ButtonHandlerGUI);

	///Whenever selected item in materials list changes, update the info.
	QObject::connect(this->materialsList, &QListWidget::itemSelectionChanged, this, &SeniorGUI::updateSelectedItem);
}

Material SeniorGUI::getMaterialAtIndex() {
	QModelIndex index = this->materialsList->currentIndex();
	std::string ID = index.data(Qt::DisplayRole).toString().toStdString();

	Material selectedMaterial = this->seniorService.getElementByID(ID);

	return selectedMaterial;
}

int SeniorGUI::getSelectedIndexInList() {
	if (this->materialsList->count() == 0)
		return -1;

	// get selected index
	QModelIndexList index = this->materialsList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
	{
		this->IDEdit->clear();
		this->fragmentsEdit->clear();
		this->radioactivityEdit->clear();
		this->sizeEdit->clear();
		this->digitizedScanEdit->clear();
		return -1;
	}

	int idx = index.at(0).row();
	return idx;
}

void SeniorGUI::updateSelectedItem() {
	//Get the material at the selected index.
	if (this->getSelectedIndexInList() == -1) {
		return;
	}

	Material selectedMaterial = this->getMaterialAtIndex();

	this->IDEdit->setText(QString::fromStdString(selectedMaterial.getID()));
	this->fragmentsEdit->setText(QString::fromStdString(std::to_string(selectedMaterial.getQuantityOfMicrofragments())));
	this->radioactivityEdit->setText(QString::fromStdString(std::to_string(selectedMaterial.getRadioactivityLevel())));
	this->sizeEdit->setText(QString::fromStdString(selectedMaterial.getSize().toString()));
	this->digitizedScanEdit->setText(QString::fromStdString(selectedMaterial.getDigitizedScan()));
}

void SeniorGUI::addMaterial_ButtonHandlerGUI() {
	std::string ID = this->IDEdit->text().toStdString();
	QString size = this->sizeEdit->text();
	QString radioactivity = this->radioactivityEdit->text();
	QString microfragments = this->radioactivityEdit->text();
	std::string digitizedScan = this->digitizedScanEdit->text().toStdString();

	this->seniorService.addMaterial(ID, Size{ size.toStdString() }, std::stoi(radioactivity.toStdString()), std::stoi(microfragments.toStdString()), digitizedScan);

	emit materialsListChanged();
}

void SeniorGUI::deleteMaterial_ButtonHandlerGUI() {
	Material atIndex = this->getMaterialAtIndex();

	this->seniorService.removeMaterial(atIndex.getID());

	emit materialsListChanged();
}

void SeniorGUI::updateMaterial_ButtonHandlerGUI() {
	std::string ID = this->IDEdit->text().toStdString();
	std::string newSize = this->sizeEdit->text().toStdString();
	int newRadioactivity = std::stoi(this->radioactivityEdit->text().toStdString());
	int newMicrofragments = std::stoi(this->radioactivityEdit->text().toStdString());
	std::string newDigitizedScan = this->digitizedScanEdit->text().toStdString();

	this->seniorService.updateMaterial(ID, Size{ newSize }, newRadioactivity, newMicrofragments, newDigitizedScan);
}

void SeniorGUI::undoOperation() {
	try {
		this->seniorService.undo();
	}
	catch (std::exception& e) {
		_createInformationWindow(e.what());
	}
}

void SeniorGUI::redoOperation() {
	try {
		this->seniorService.redo();
	}
	catch (std::exception& e) {
		_createInformationWindow(e.what());
	}
}