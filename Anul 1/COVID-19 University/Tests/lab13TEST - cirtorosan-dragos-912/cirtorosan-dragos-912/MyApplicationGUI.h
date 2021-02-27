#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyApplicationGUI.h"

#include "Service.h"

class MyApplicationGUI : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MyApplicationGUIClass ui;

    Service& service;

public:
    MyApplicationGUI(Service& serv, QWidget *parent = Q_NULLPTR);

private:
    void connectSignalsAndSlots();

    int createNewInformationWindow(std::string message);

    //Element getElementAtIndex();

    void showNumberOfBotsForManufacturerButton_handler();

signals:
    void listChanged();

//SLOTS
private:
    void populateListWidget();

    //void updateSelectedItem();
};
