#include "watcher.h"

Watcher::Watcher(QDialog *parent, QString path): QWidget(parent) {
    parentPointer = parent;
    watcher = new QFileSystemWatcher(this);
    setTrayIconActions();
    showTrayIcon();
    watcher->addPath(path);

    dir = new QDir(path);
    listOfFiles = dir->entryInfoList();
    oldListOfFiles = dir->entryInfoList();
    oldLength = listOfFiles.length();

    QObject::connect(watcher, SIGNAL(directoryChanged(const QString&)), this, SLOT(checkChanges(const QString&)));
}

void Watcher::setTrayIconActions() {
    minimizeAction = new QAction("Minimize", this);
    restoreAction = new QAction("Restore", this);
    quitAction = new QAction("Quit", this);

    connect (minimizeAction, SIGNAL(triggered()), parentPointer, SLOT(hide()));
    connect (restoreAction, SIGNAL(triggered()), parentPointer, SLOT(showNormal()));
    connect (quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction (minimizeAction);
    trayIconMenu->addAction (restoreAction);
    trayIconMenu->addAction (quitAction);
}

void Watcher::showTrayIcon() {
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/images/abc.png");
    trayIcon -> setIcon(trayImage);
    trayIcon -> setContextMenu(trayIconMenu);
    trayIcon -> show();
}

void Watcher::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event -> type() == QEvent::WindowStateChange)
    {
        if (isMinimized())
        {
            this -> hide();
        }
    }
}

void Watcher::checkChanges(const QString& dirPath) {
    delete dir;
    dir = new QDir(path);
    listOfFiles = dir->entryInfoList();
    qDebug() << "Изменения в каталоге";
    qDebug() << listOfFiles.length() << oldLength << "\n";
    if (listOfFiles.length() > oldLength) {
        QFileInfoList::iterator i;
        QFileInfoList::iterator j;
        QFileInfoList::iterator k;
        for (i = listOfFiles.begin(); i != listOfFiles.end(); ++i)
            for (j = oldListOfFiles.begin(); j != oldListOfFiles.end(); ++j)
                if (i->fileName() == j->fileName()) {
                    listOfFiles.erase(i);
                    for (k = listOfFiles.begin(); k != listOfFiles.end(); ++k)
                        qDebug() << k->fileName();
                }
        setLabel(dirPath);
    }
    oldListOfFiles = dir->entryInfoList();
    oldLength = listOfFiles.length();
}

void Watcher::setLabel(const QString& str) {
    trayIcon->showMessage("Содержимое папки изменено", str);
    //QMessageBox::information(this, "MainForm", str);
}

Watcher::~Watcher() {
    delete watcher;

    delete minimizeAction;
    delete restoreAction;
    delete quitAction;

    delete trayIconMenu;
    delete trayIcon;
}
