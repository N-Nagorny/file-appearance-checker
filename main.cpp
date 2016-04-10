#include "mainwindow.h"
#include <QApplication>
#include <QSizePolicy>

int main(int argc, char *argv[]) {
    QApplication *app = new QApplication(argc, argv);
    mainwindow *win = new mainwindow();

    win -> show();

    return app -> exec();
}
