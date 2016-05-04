#include "watcher.h"

Watcher::Watcher(QDialog *parent, QString path): QWidget(parent) {
    parentPointer = parent;
    watcher = new QFileSystemWatcher(this);
    setTrayIconActions();
    showTrayIcon();
    watcher->addPath(path);

    QObject::connect(watcher, SIGNAL(directoryChanged(const QString&)), this, SLOT(setLabel(const QString&)));
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

void Watcher::setLabel(const QString& str) {
    trayIcon->showMessage("Содержимое папки изменено", str);
}

Watcher::~Watcher() {
    delete parentPointer;
    delete watcher;

    delete minimizeAction;
    delete restoreAction;
    delete quitAction;

    delete trayIconMenu;
    delete trayIcon;
}
