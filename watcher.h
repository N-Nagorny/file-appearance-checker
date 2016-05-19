#ifndef WATCHER_H
#define WATCHER_H

#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QFileSystemWatcher>
#include <QDialog>
#include <QDir>
#include <QDebug>

class Watcher: public QWidget {
    Q_OBJECT
private:
    QDialog *parentPointer;
    QString path;
    QFileSystemWatcher *watcher;

    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QMenu *trayIconMenu;
    QSystemTrayIcon *trayIcon;

    QDir *dir;
    QFileInfoList listOfFiles;
    QFileInfoList oldListOfFiles;
    int oldLength;
public:
    Watcher(QDialog *parent = 0, QString path = "");
    ~Watcher();
private slots:
    void checkChanges(const QString& dirPath);
private:
    void setTrayIconActions();
    void showTrayIcon();
    void changeEvent(QEvent *event);
    void setLabel(const QString&);
};

#endif // WATCHER_H
