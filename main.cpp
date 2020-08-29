#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){ 
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
