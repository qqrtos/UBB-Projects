#include "MyApplicationGUI.h"
#include <qmessagebox.h>

#include <qcolor.h>

int MyApplicationGUI::createNewInformationWindow(std::string message) {
    QMessageBox confirmartion;
    confirmartion.setWindowTitle("Information");
    confirmartion.setText(QString::fromStdString(message));
    confirmartion.setStandardButtons(QMessageBox::Ok);
    confirmartion.setDefaultButton(QMessageBox::Ok);
    return confirmartion.exec();
}

void MyApplicationGUI::showNumberOfBotsForManufacturerButton_handler() {
    /*
        This function sets the text for the nrBots_output_label to the actual number of bots for thar manufacturer in the repository.
        Input: -
        Output: sets the text of nrBots_output_label
    */

    std::string manuf = this->ui.manufacturerInput_lineEdit->text().toStdString();

    if (manuf != "") {
        int count = this->service.filterByManufacturer(manuf).size();

        this->ui.nrBots_output_label->setText(QString::fromStdString(std::to_string(count)));
    }
}


MyApplicationGUI::MyApplicationGUI(Service& serv, QWidget* parent) :
    QMainWindow(parent),
    service{ serv }
{
    ui.setupUi(this);
    this->connectSignalsAndSlots();
    this->populateListWidget();
}

void MyApplicationGUI::connectSignalsAndSlots() {
    QObject::connect(this, &MyApplicationGUI::listChanged, this, &MyApplicationGUI::populateListWidget);
    QObject::connect(this->ui.showNrOfBotsForManufacturer_pushButton, &QPushButton::clicked, this, &MyApplicationGUI::showNumberOfBotsForManufacturerButton_handler);
}


void MyApplicationGUI::populateListWidget() {
    if (this->ui.listWidget->count() > 0)
        this->ui.listWidget->clear();

    std::vector<Bots> repoList = this->service.getAllSorted();

   for (auto current : repoList) {
       QString materialInList = QString::fromStdString(current.toString());
       QListWidgetItem* item = new QListWidgetItem{ materialInList };
       item->setTextColor(QColor(QString::fromStdString(current.getColor())));

       this->ui.listWidget->addItem(item);
    }
}