#include "main_window.h"

MainWindow::MainWindow(QWidget *parent): QDialog(parent) { //Main window initialization

    path = "";
    settings = new QSettings("N-Nagorny", "FAC");

    lay1 = new QVBoxLayout();
    lay2 = new QHBoxLayout();
    lay3 = new QHBoxLayout();

    ed = new QLineEdit();
    ed->setReadOnly(true);
    chooseBtn = new QPushButton("Обзор…");
    exitBtn = new QPushButton("Выход");

    loadSettings(); // Loading tracked path from "./config"
    watcherInst = new Watcher(this, path);

    this->setLayout(lay1);
    lay1->addLayout(lay2);
    lay1->addLayout(lay3);

    lay2->addWidget(ed);
    lay2->addWidget(chooseBtn);
    lay3->addWidget(exitBtn);

    this->setMinimumSize(500, 150);
    this->setMaximumSize(500, 150);
    this->setWindowTitle("FAC");

    QObject::connect(chooseBtn, SIGNAL(clicked()), this, SLOT(changeSettings())); //"Обзор..." button
    QObject::connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));            //"Выход" button
}

void MainWindow::callFileDialog() { // Calling change directory dialog
    QString result;
    result = QFileDialog::getExistingDirectory(this, "Выберите папку для отслеживания", path);
    if (result.length())
        path = result;
}

void MainWindow::saveSettings() { // Saving tracked path in "./config" and reloading Watcher instance
    ed->setText(path);
    if (watcherInst != nullptr)
        delete watcherInst;
    watcherInst = new Watcher(this, path);
    settings->setValue("Path", path);
    settings->sync();
    QMessageBox::information(this, "FAC", "Настройки сохранены");
}

void MainWindow::changeSettings() {
    callFileDialog();
    saveSettings();
}

void MainWindow::loadSettings() { // Loading tracked path from "./config"
    path = settings->value("Path").toString();
    qDebug() << path;
    if (path.length() == 0) {
        changeSettings();
    }
    else
        ed->setText(path);
}


MainWindow::~MainWindow() {
    delete watcherInst;
    delete settings;

    delete lay1;
    delete lay2;
    delete lay3;

    delete ed;
    delete chooseBtn;
    delete exitBtn;
}
