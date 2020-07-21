#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "createform.h"
#include "settingsrecords.h"
#include <calculatorfinn.h>
#include <QSettings>
MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    newCreateForm = new CreateForm();
    connect(newCreateForm, &CreateForm::firstWindow, this, &MainMenu::show);
    startingProtocol = new StartingProtocol();
    connect(startingProtocol, &StartingProtocol::protocolWindow,this,&MainMenu::show);
//    rankSettings = new RankSettings();
//    connect(rankSettings, &RankSettings::rankMenu,this, &MainMenu::show);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_pushButton_CreateForm_clicked()
{
    newCreateForm->show();
    this->close();
}
void MainMenu::on_pushButton_calculatorFin_clicked()
{
    CalculatorFinn * calculatorFinn = new CalculatorFinn();
    calculatorFinn->show();
}
void MainMenu::on_pushButton_SettingsRecords_clicked()
{
    SettingsRecords * settingsrecords = new SettingsRecords();
    settingsrecords->show();
}
void MainMenu::on_pushButton_startingProtocol_clicked()
{
    startingProtocol->show();
    this->close();
}
void MainMenu::on_pushButton_sportRank_clicked()
{
    RankSettings * rank = new RankSettings();
    rank->show();

}
