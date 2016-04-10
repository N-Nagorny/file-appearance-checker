#include "mainwindow.h"
#include "settingswindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <QDialog>

mainwindow::mainwindow(QWidget *parent): QWidget(parent) {
    lay1 = new QVBoxLayout();

    settingsBut = new QPushButton("Настройки");
    exitBut = new QPushButton("Выход");

    this->setLayout(lay1);

    lay1->addWidget(settingsBut);
    lay1->addWidget(exitBut);

    this->setMinimumSize(150, 150);
    this->setMaximumSize(150, 150);
    this->setWindowTitle("FAC");

    QObject::connect(settingsBut, SIGNAL(clicked()), this, SLOT(callSettings()));
    QObject::connect(exitBut, SIGNAL(clicked()), this, SLOT(close()));
}

void mainwindow::callSettings() {
    settingswindow *setwin = new settingswindow(this);
    setwin->exec();
}

mainwindow::~mainwindow() {
    delete lay1;
    delete settingsBut;
    delete exitBut;
}
