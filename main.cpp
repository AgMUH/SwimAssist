#include "mainwindow.h"
#include "mainmenu.h"
#include <QApplication>
#include <QtWidgets>
#include <QSettings>
#include <QDir>

int main(int argc, char *argv[])
{
    QDir dir = QDir::current();
    bool userDir = dir.exists("User");
    bool estDir = dir.exists("Estafeta");
    if(!userDir){
        dir.mkdir("User");
    }
    if(!estDir){
        dir.mkdir("Estafeta");
    }
    qputenv("QT_SCREEN_SCALE_FACTORS", "1 ");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
