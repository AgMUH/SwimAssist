#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainmenu.h>
#include <ui_mainmenu.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_SignIn_clicked();
    void on_pushButton_SignInGuest_clicked();

private:
    MainMenu * mainMenu;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
