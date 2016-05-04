<<<<<<< HEAD
#include <QtWidgets/QApplication>

#include "main_window.h"

int main(int argc, char *argv[]) {
    QApplication *app = new QApplication(argc, argv);
    MainWindow *win = new MainWindow();

    win->show();

    return app->exec();
=======
#include "mainwindow.h"
#include <QApplication>
#include <QSizePolicy>

int main(int argc, char *argv[]) {
    QApplication *app = new QApplication(argc, argv);
    mainwindow *win = new mainwindow();

    win -> show();

    return app -> exec();
>>>>>>> 0a18310b6324abb8a41b95a3e8d5cfbc49ee3f18
}
