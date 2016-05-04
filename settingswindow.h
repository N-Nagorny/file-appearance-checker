#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QtWidgets>

class settingswindow: public QDialog {
    Q_OBJECT

private:
    QString path;
    QSettings *settings;

    QVBoxLayout *lay1;
    QHBoxLayout *lay2;
    QHBoxLayout *lay3;

    QLineEdit *ed;
    QPushButton *chooseBtn;

    QPushButton *okBtn;
    QPushButton *closeBtn;

public:
    settingswindow(QWidget *parent = 0);
    ~settingswindow();

private slots:
    void callFileDialog();
    void loadSettings();
    void saveSettings();
};

#endif // SETTINGSWINDOW_H
