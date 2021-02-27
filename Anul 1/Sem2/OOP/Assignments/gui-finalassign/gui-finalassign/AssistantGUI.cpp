	#include "AssistantGUI.h"
#include <qpushbutton.h>
#include <QMessageBox>

#include <Windows.h>

int createInformationWindow(std::string message) {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Error");
	msgBox.setText(QString::fromStdString(message));
	return msgBox.exec();
}

//void populateMaterialsList(std::vector<Material> materials, QListWidget* list) {
//	list->clear();
//	for (Material current : materials) {
//		QString materialInList = QString::fromStdString(current.toString());
//		QListWidgetItem* item = new QListWidgetItem{ materialInList };
//		list->addItem(item);
//	}
//}

AssistantGUI::AssistantGUI(AssistantService& assistantservice, SeniorService& seniorService, QAbstractTableModel* assistantTableModel, QWidget* parent) :
	QWidget(parent),
	assistantService{ assistantservice },
	seniorService{ seniorService },
	assistantTableModel{ assistantTableModel }
{
	ui.setupUi(this);

	this->ui.currentMaterial_label->setText(QString::fromStdString(this->assistantService.getNext().toString()));

	this->connectSignalsAndSlots();
}

AssistantGUI::~AssistantGUI() {}

void AssistantGUI::connectSignalsAndSlots() {
	QShortcut* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
	QObject::connect(undoShortcut, &QShortcut::activated, this, &AssistantGUI::undoOperation);

	QShortcut* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
	QObject::connect(redoShortcut, &QShortcut::activated, this, &AssistantGUI::redoOperation);

	QObject::connect(this->ui.undo_pushButton, &QPushButton::clicked, this, &AssistantGUI::undoOperation);

	QObject::connect(this->ui.redo_pushButton, &QPushButton::clicked, this, &AssistantGUI::redoOperation);

	QObject::connect(this->ui.save_pushButton, &QPushButton::clicked , this, &AssistantGUI::saveMaterialToAssistantList);

	QObject::connect(this->ui.next_pushButton, &QPushButton::clicked, this, &AssistantGUI::showNextMaterial);

	QObject::connect(this->ui.filterMaterials_pushButton, &QPushButton::clicked, this, &AssistantGUI::filterMaterials);

	QObject::connect(this->ui.openList_pushButton, &QPushButton::clicked, this, &AssistantGUI::openAssistantListInExternalApp);

	QObject::connect(this->ui.displayAssistantList_pushButton, &QPushButton::clicked, this, &AssistantGUI::displayAssistantList);
}

void AssistantGUI::saveMaterialToAssistantList() {
	std::string materialString = this->ui.currentMaterial_label->text().toStdString();
	std::string ID = materialString.substr(0, materialString.find(','));

	std::vector<Material> inList = this->assistantService.getAssistantMaterialsList();

	if (std::find_if(inList.begin(), inList.end(),
		[ID](Material current) { return current.getID() == ID; }) == inList.end()) {
		this->assistantService.saveMaterialForStudy(ID);
		inList.push_back(this->seniorService.getElementByID(ID));
	}
}

void AssistantGUI::showNextMaterial() {
	Material material = this->assistantService.getNext();
	this->ui.currentMaterial_label->setText(QString::fromStdString(material.toString()));
}

void AssistantGUI::filterMaterials() {
	FilterMaterialsGUI* filterMaterialsWindow = new FilterMaterialsGUI{ this->assistantService };
	filterMaterialsWindow->show();
}

void AssistantGUI::openAssistantListInExternalApp() {

	std::string pathToFile = this->assistantService.getPathToRepository();

	auto dotBeforeExtension = pathToFile.rfind(".");
	std::string assistantRepositoryExtension = pathToFile.substr(dotBeforeExtension + 1);

	std::wstring temporaryString = std::wstring(pathToFile.begin(), pathToFile.end());
	LPCWSTR convertedFullPath = temporaryString.c_str();

	if (assistantRepositoryExtension == "csv")
		ShellExecuteW(NULL, L"open", convertedFullPath, L"", L"C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Excel 2016", SW_SHOW);
	else if (assistantRepositoryExtension == "html")
		ShellExecuteW(NULL, L"open", convertedFullPath, L"", L"C:\\Program Files (x86)\\BraveSoftware\\Brave-Browser\\Application\\brave.exe", SW_SHOW);
}

void AssistantGUI::displayAssistantList() {
	AssistantTableWindow* myList = new AssistantTableWindow(this->assistantTableModel);
	myList->show();
}

void AssistantGUI::undoOperation() {
	try {
		this->assistantService.undo();
	}
	catch (std::exception& e) {
		createInformationWindow(e.what());
	}
}

void AssistantGUI::redoOperation() {
	try {
		this->assistantService.redo();
	}
	catch (std::exception& e) {
		createInformationWindow(e.what());
	}
}
