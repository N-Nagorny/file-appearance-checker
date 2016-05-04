#include "settingswindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

settingswindow::settingswindow(QWidget *parent): QDialog(parent) {
    path = "";
    qDebug() << path.length();

    settings = new QSettings("N-Nagorny", "FAC");

    lay1 = new QVBoxLayout();
    lay2 = new QHBoxLayout();
    lay3 = new QHBoxLayout();

    ed = new QLineEdit();
    ed->setReadOnly(true); // Желательно избавиться
    chooseBtn = new QPushButton("Обзор…");

    okBtn = new QPushButton("OK");
    closeBtn = new QPushButton("Закрыть");

    loadSettings();

    this->setLayout(lay1);
    lay1->addLayout(lay2);
    lay1->addLayout(lay3);

    lay2->addWidget(ed);
    lay2->addWidget(chooseBtn);

    lay3->addWidget(okBtn);
    lay3->addWidget(closeBtn);

    this->setMinimumSize(500, 150);
    this->setMaximumSize(500, 150);
    this->setWindowTitle("Настройки");

    QObject::connect(chooseBtn, SIGNAL(clicked()), this, SLOT(callFileDialog()));

    QObject::connect(okBtn, SIGNAL(clicked()), this, SLOT(saveSettings()));
    QObject::connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void settingswindow::callFileDialog() {
    QString result;
    result = QFileDialog::getExistingDirectory(this, "Выберите папку для отслеживания", path);
    if (result.length())
        path = result;
    ed->setText(path);
}

void settingswindow::loadSettings() {
    path = settings->value("Path").toString();
    qDebug() << path;
    ed->setText(path);
}

void settingswindow::saveSettings() {
    qDebug() << settings->fileName();
    settings->setValue("Path", path);
    settings->sync();
    this->close();
}

settingswindow::~settingswindow() {
    delete lay1;
    delete lay2;
    delete lay3;
}
