#include "mainwindow.h"
#include "mainmenu.h"
#include <QApplication>
#include <QtWidgets>
#include <QSettings>

int main(int argc, char *argv[])
{
 qputenv("QT_SCREEN_SCALE_FACTORS", "1 ");

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
