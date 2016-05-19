#include <QtWidgets/QApplication>

#include "main_window.h"

int main(int argc, char *argv[]) {
    QApplication *app = new QApplication(argc, argv);
    MainWindow *win = new MainWindow();
    QIcon icon(":/images/abc.png");
    app->setWindowIcon(icon);

    win->show();

    return app->exec();
}
