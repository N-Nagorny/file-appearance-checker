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

void Watcher::setTrayIconActions() { // Initializing context menu of tray icon
    minimizeAction = new QAction("Minimize", this);
    restoreAction = new QAction("Restore", this);
    quitAction = new QAction("Quit", this);

    QObject::connect (minimizeAction, SIGNAL(triggered()), parentPointer, SLOT(hide()));
    QObject::connect (restoreAction, SIGNAL(triggered()), parentPointer, SLOT(showNormal()));
    QObject::connect (quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction (minimizeAction);
    trayIconMenu->addAction (restoreAction);
    trayIconMenu->addAction (quitAction);
}

void Watcher::showTrayIcon() { // Creating system tray item icon
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/images/abc.png");
    trayIcon->setIcon(trayImage);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();
}

void Watcher::changeEvent(QEvent *event) // QWidget changeEvent overriding for minimizing app to tray instead dashboard
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::WindowStateChange)
    {
        if (isMinimized())
        {
            this->hide();
        }
    }
}

void Watcher::checkChanges(const QString& path) { // Getting name of appeared file
    delete dir;
    dir = new QDir(path);
    listOfFiles = dir->entryInfoList();

    qDebug() << "Изменения в каталоге";
    qDebug() << listOfFiles.length() << oldLength << "\n";
    if (listOfFiles.length() > oldLength) {
        QFileInfoList::iterator i;
        QFileInfoList::iterator j;
        for (j = oldListOfFiles.begin(); j != oldListOfFiles.end(); ++j)
        {
            for (i = listOfFiles.begin(); i != listOfFiles.end(); ++i)
            {
                if (i->fileName().compare(j->fileName()) == 0)
                {
                    listOfFiles.erase(i);
                    break;
                }
            }
        }
        qDebug() << listOfFiles.first().fileName();
        dialog = new Dialog(listOfFiles.first(), this);
        dialog->show();
        setLabel(listOfFiles.first().fileName()); // Showing bubble notification in tray
    }
    oldListOfFiles = dir->entryInfoList();
    oldLength = oldListOfFiles.length();
}

void Watcher::setLabel(const QString& str) {
    trayIcon->showMessage("Содержимое папки изменено", str);
}

Watcher::~Watcher() {
    delete watcher;

    delete minimizeAction;
    delete restoreAction;
    delete quitAction;

    delete trayIconMenu;
    delete trayIcon;
}
