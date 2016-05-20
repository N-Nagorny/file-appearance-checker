#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDesktopServices>
#include <QFileInfo>
#include <QUrl>
#include <QDir>
class Dialog : public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout *lay1;
    QHBoxLayout *lay2;
    QLabel      *fileNameLbl;
    QPushButton *closeBtn;
    QPushButton *folderBtn;
    QDesktopServices *desktopSrv;
    QFileInfo info;
public:
    explicit Dialog(const QFileInfo &fileinfo, QWidget *parent = 0);
    ~Dialog();
signals:

public slots:
    void openExplorer();

};

#endif // DIALOG_H
