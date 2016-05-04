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
public:
    Watcher(QDialog *parent = 0, QString path = "");
    ~Watcher();
private slots:
    void setLabel(const QString&);
private:
    void setTrayIconActions();
    void showTrayIcon();
    void changeEvent(QEvent *event);
};

#endif // WATCHER_H
