#include "dialog.h"

Dialog::Dialog(const QFileInfo &fileinfo, QWidget *parent): QDialog(parent) {
    info = fileinfo;
    lay1 = new QVBoxLayout();
    lay2 = new QHBoxLayout();
    fileNameLbl = new QLabel(info.fileName());
    closeBtn = new QPushButton("Закрыть");
    folderBtn = new QPushButton("Открыть папку");

    this->setLayout(lay1);
    lay1->addLayout(lay2);
    lay1->addWidget(fileNameLbl);
    lay2->addWidget(closeBtn);
    lay2->addWidget(folderBtn);

    QString path = info.absolutePath();
    QObject::connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));            //"Выход" button
    QObject::connect(folderBtn, SIGNAL(clicked()), this, SLOT(openExplorer()));
}

void Dialog::openExplorer() {
    desktopSrv = new QDesktopServices();
    QDesktopServices::openUrl(QUrl(info.absolutePath(), QUrl::TolerantMode));
}

Dialog::~Dialog() {
    delete lay1;
    delete lay2;
    delete fileNameLbl;
    delete closeBtn;
    delete folderBtn;
}
