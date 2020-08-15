#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenu.h"
#include <QMessageBox>
#include <Qt>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    mainMenu = new MainMenu();
    connect(mainMenu, &MainMenu::AuthorizationMenu, this, &MainWindow::show);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_SignIn_clicked()
{
    QString login = ui->lineEdit_LogIn->text();
    QString password = ui->lineEdit_Password->text();
    if((login == "Urri" && password == "Urri9")|| (login == "swim" && password == "0505387397"))
    {
        mainMenu->ui->pushButton_startingProtocol->setEnabled(true);
        mainMenu->ui->pushButton_sportRank->setEnabled(true);
        mainMenu->ui->pushButton_SettingsRecords->setEnabled(true);
        mainMenu->ui->pushButton_calculatorFin->setEnabled(true);
        mainMenu->show();
        this->close();
    }
    else
    {
        QMessageBox::warning(this,"Авторизація","Невірний логін або пароль");
    }
}

void MainWindow::on_pushButton_SignInGuest_clicked()
{
//    mainMenu->ui->pushButton_startingProtocol->setEnabled(false);
    mainMenu->ui->pushButton_sportRank->setEnabled(false);
    mainMenu->ui->pushButton_SettingsRecords->setEnabled(false);
    mainMenu->ui->pushButton_calculatorFin->setEnabled(false);
    mainMenu->show();
    this->close();
}
