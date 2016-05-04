#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>

class mainwindow: public QWidget {

    Q_OBJECT

private:
    QVBoxLayout *lay1;
    QPushButton *settingsBut, *exitBut;

public:
    mainwindow(QWidget *parent = 0);
    ~mainwindow();

private slots:
    void callSettings();
};

#endif // MAINWINDOW_H
