#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>
#include <QSettings>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

#include "watcher.h"

class MainWindow: public QDialog {
    Q_OBJECT
private:
    QString path;
    QSettings *settings;
    Watcher *watcherInst;

    QVBoxLayout *lay1;
    QHBoxLayout *lay2;
    QHBoxLayout *lay3;

    QLineEdit *ed;
    QPushButton *chooseBtn;
    QPushButton *exitBtn;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void changeSettings();
private:
    void callFileDialog();
    void saveSettings();
    void loadSettings();
};

#endif // MAIN_WINDOW_H
