#include "QStandardItemModel"
#include "QStandardItem"
#include <vector>
#include <string>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QAxObject>
#include <QFileDialog>
#include <QMessageBox>
#include <mainmenu.h>
#include <mainwindow.h>
#include "createform.h"
#include "ui_createform.h"
using namespace std;
CreateForm::CreateForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateForm)
{
    ui->setupUi(this);

}

CreateForm::~CreateForm()
{
    delete ui;
}
static bool checkButtonSave = false;
static bool checkButtonAddPerson = false;
void CreateForm::on_pushButton_AddPerson_clicked()
{
    checkButtonAddPerson = true;
    QString comboBoxPriority = "";
    if(ui->lineEdit_dst->text() == "" || ui->lineEdit_city->text() == ""||ui->lineEdit_school->text() == ""||ui->lineEdit_FIO_Create_Form->text() == ""
            ||ui->lineEdit_Coach_CreateForm->text() == ""){
        QMessageBox::critical(this,"Помилка введення", "Заповніть необхідні поля!");
    }
    else
    {
        bool teamContainsed = false;
        int rowOfTeam;
        if(ui->comboBox_meter->currentText().contains("4x")){

            QString teamName = "("+ui->lineEdit_customTeam->text().simplified()+")";
            QString teamDistance = ui->comboBox_meter->currentText()+","+ui->comboBox_style->currentText()+","+ui->comboBox_sex->currentText();
            for (int i = 0;i<ui->tableWidget->rowCount();i++) {
                if(ui->tableWidget->item(i,5)->text().contains(teamName)
                        && ui->tableWidget->item(i,6)->text().contains(teamDistance)){
                    teamContainsed=true;
                    rowOfTeam=i;
                    break;
                }
            }
        }
        if((!ui->comboBox_meter->currentText().contains("4x") && !teamContainsed)||(ui->comboBox_meter->currentText().contains("4x") && !teamContainsed)){
            if((ui->comboBox_meter->currentText().contains("4x")
                && ui->checkBox_personalOrTeam->isChecked()
                && ui->lineEdit_customTeam->text().length()!=0)
               || (!ui->comboBox_meter->currentText().contains("4x")
                   && ui->checkBox_personalOrTeam->isChecked()
                   && ui->lineEdit_customTeam->text().length()!=0)
               ||
                  (!ui->comboBox_meter->currentText().contains("4x")
                   && !ui->checkBox_personalOrTeam->isChecked()))
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,  new QTableWidgetItem(ui->lineEdit_FIO_Create_Form->text().simplified()));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,  new QTableWidgetItem(ui->spinBox_Year->text()));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,  new QTableWidgetItem(ui->comboBox_rank->currentText()));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,  new QTableWidgetItem(ui->lineEdit_dst->text()));
                if(ui->checkBox_personalOrTeam->isChecked() && !ui->checkBox_outOfCompetition->isChecked()){
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,5,  new QTableWidgetItem(ui->lineEdit_school->text().simplified()+"("+ui->lineEdit_customTeam->text().simplified()+")"));
                }
                else ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,5,  new QTableWidgetItem(ui->lineEdit_school->text().simplified()));

                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,7,  new QTableWidgetItem(ui->comboBox_minutes->currentText()+":"+ui->comboBox_seconds->currentText()+ "." +ui->comboBox_miliseconds->currentText()));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,8,  new QTableWidgetItem(ui->lineEdit_Coach_CreateForm->text()));

                if(ui->checkBox_outOfCompetition->isChecked()){ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,6,  new QTableWidgetItem(ui->comboBox_meter->currentText()+
                                                                                                                                                                              ","+ui->comboBox_style->currentText()+","+ui->comboBox_sex->currentText()+"(ПК)"));}
                else if(ui->checkBox_personalOrTeam->isChecked() && ui->checkBox_manyFights->isChecked())
                {
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,6,  new QTableWidgetItem(ui->comboBox_meter->currentText()+","+ui->comboBox_style->currentText()+","+ui->comboBox_sex->currentText()+"(КБ)"));
                }
                else if(ui->checkBox_personalOrTeam->isChecked() && !ui->checkBox_manyFights->isChecked())
                {
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,6,  new QTableWidgetItem(ui->comboBox_meter->currentText()+","+ui->comboBox_style->currentText()+","+ui->comboBox_sex->currentText()+"(К)"));
                }
                else if(ui->checkBox_manyFights->isChecked()){
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,6,  new QTableWidgetItem(ui->comboBox_meter->currentText()+","+ui->comboBox_style->currentText()+","+ui->comboBox_sex->currentText()+"(Б)"));
                }
                else ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,6,  new QTableWidgetItem(ui->comboBox_meter->currentText()+","+ui->comboBox_style->currentText()+","+ui->comboBox_sex->currentText()));




                if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() != "" && ui->lineEdit_country->text()!=""){
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,  new QTableWidgetItem(ui->lineEdit_city->text()+",\n"+ui->lineEdit_region->text()+" обл.,\n"+ui->lineEdit_country->text()));
                }

                else if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() != "" && ui->lineEdit_country->text()==""){
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,  new QTableWidgetItem(ui->lineEdit_city->text()+",\n"+ui->lineEdit_region->text()+" обл."));
                }
                else if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() == "" && ui->lineEdit_country->text() ==""){
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,  new QTableWidgetItem(ui->lineEdit_city->text()));
                }
                else if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() == "" && ui->lineEdit_country->text() !=""){
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(ui->lineEdit_city->text()+",\n"+ui->lineEdit_country->text()));
                }

                ui->tableWidget->resizeRowsToContents();
                ui->tableWidget->resizeColumnsToContents();
                ui->tableWidget->scrollToBottom();
            }
            else{
                QMessageBox::critical(this,"Помилка введення", "Введіть команду");
            }
        }
        else{
            if(ui->checkBox_personalOrTeam->isChecked() && ui->lineEdit_customTeam->text().length()!=0){
                QString previousPeopleName = ui->tableWidget->item(rowOfTeam,0)->text();
                QString previousPeopleYear = ui->tableWidget->item(rowOfTeam,1)->text();
                QString previousPeopleRank = ui->tableWidget->item(rowOfTeam,2)->text();
                QString previousPeopleLocation = ui->tableWidget->item(rowOfTeam,3)->text();
                QString previousPeopleDST = ui->tableWidget->item(rowOfTeam,4)->text();
                QString previousPeopleSchoolAndTeam = ui->tableWidget->item(rowOfTeam,5)->text();
                QString previousPeopleCoach = ui->tableWidget->item(rowOfTeam,8)->text();
                ui->tableWidget->setItem(rowOfTeam,0,  new QTableWidgetItem(previousPeopleName+'\n'+ ui->lineEdit_FIO_Create_Form->text().simplified()));
                ui->tableWidget->setItem(rowOfTeam,1,  new QTableWidgetItem(previousPeopleYear+'\n'+ ui->spinBox_Year->text()));
                ui->tableWidget->setItem(rowOfTeam,2,  new QTableWidgetItem(previousPeopleRank+'\n'+ui->comboBox_rank->currentText()));
                ui->tableWidget->setItem(rowOfTeam,4,  new QTableWidgetItem(previousPeopleDST+'\n'+ui->lineEdit_dst->text()));
                ui->tableWidget->setItem(rowOfTeam,5,  new QTableWidgetItem(previousPeopleSchoolAndTeam+'\n'+ui->lineEdit_school->text().simplified()+"("+ui->lineEdit_customTeam->text().simplified()+")"));

                ui->tableWidget->setItem(rowOfTeam,8,  new QTableWidgetItem(previousPeopleCoach +'\n'+ui->lineEdit_Coach_CreateForm->text()));


                if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() != "" && ui->lineEdit_country->text()!=""){
                    ui->tableWidget->setItem(rowOfTeam,3,  new QTableWidgetItem(previousPeopleLocation+'\n'+ui->lineEdit_city->text()+",\n"+ui->lineEdit_region->text()+" обл.,\n"+ui->lineEdit_country->text()));
                }

                else if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() != "" && ui->lineEdit_country->text()==""){
                    ui->tableWidget->setItem(rowOfTeam,3,  new QTableWidgetItem(previousPeopleLocation+'\n'+ui->lineEdit_city->text()+",\n"+ui->lineEdit_region->text()+" обл."));
                }
                else if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() == "" && ui->lineEdit_country->text() ==""){
                    ui->tableWidget->setItem(rowOfTeam,3,  new QTableWidgetItem(previousPeopleLocation+'\n'+ui->lineEdit_city->text()));
                }
                else if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() == "" && ui->lineEdit_country->text() !=""){
                    ui->tableWidget->setItem(rowOfTeam,3,new QTableWidgetItem(previousPeopleLocation+'\n'+ui->lineEdit_city->text()+",\n"+ui->lineEdit_country->text()));
                }
//                QTableWidgetItem * item = ui->tableWidget->item(ui->tableWidget->rowCount()-1,0);

                ui->tableWidget->resizeRowsToContents();
                ui->tableWidget->resizeColumnsToContents();
                ui->tableWidget->scrollToBottom();
//                ui->tableWidget->scrollToItem(item);

            }
            else{
                QMessageBox::critical(this,"Помилка введення", "Введіть команду");
            }
        }
    }

}



void CreateForm::on_pushButton_OpenMsWord_clicked()
{

    QAxObject* WordApplication = new QAxObject("Word.Application",this);
    QAxObject* WordDocuments = WordApplication->querySubObject( "Documents()" );
    QAxObject* NewDoc = WordDocuments->querySubObject( "Add()" );
    QAxObject* ActiveDocument = WordApplication->querySubObject("ActiveDocument()");

    QAxObject* Orientation = NewDoc->querySubObject("PageSetup()");
    Orientation->setProperty("Orientation","wdOrientLandscape");

    // создание таблицы
    QAxObject* Tables = ActiveDocument->querySubObject("Tables()");
    QAxObject* NewTable = Tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", ActiveDocument->dynamicCall("Range()"), ui->tableWidget->rowCount()+1, 10, 1, 1);
    // запись текста в ячейку
    QAxObject* Cell = NewTable->querySubObject("Cell(Row, Column)", 1,1);
    QAxObject* CellRange = Cell->querySubObject("Range()");
    CellRange->dynamicCall("InsertAfter(Text)","№");
    for(int i = 2;i<=ui->tableWidget->columnCount()+1;i++){

        QAxObject* Cell = NewTable->querySubObject("Cell(Row, Column)", 1,i);
        QAxObject* CellRange = Cell->querySubObject("Range()");

        CellRange->setProperty("VerticalAlignment","wdCellAlignVerticalCenter");
        CellRange->dynamicCall("InsertAfter(Text)", ui->tableWidget->horizontalHeaderItem(i-2)->text());
    }
    int count = 0;
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        count++;
        QAxObject* Cell = NewTable->querySubObject("Cell(Row, Column)", i+2,1);
        QAxObject* CellRange = Cell->querySubObject("Range()");
        CellRange->dynamicCall("InsertAfter(Text)", count);
        for(int j=0;j<ui->tableWidget->columnCount();j++){
            QAxObject* Cell = NewTable->querySubObject("Cell(Row, Column)", i+2,j+2);
            QAxObject* CellRange = Cell->querySubObject("Range()");
            CellRange->dynamicCall("InsertAfter(Text)", ui->tableWidget->item(i,j)->text());
        }
    }

    WordApplication->setProperty("Visible" , true);
    delete WordApplication;

}
void CreateForm::on_pushButton_Save_clicked()
{
    checkButtonAddPerson = false;
    QString fr = QFileDialog::getSaveFileName(this,tr("Save"),"c:/",tr("(*.zay)"));
    QFile file(fr);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        qint32 row(ui->tableWidget->rowCount()), column(ui->tableWidget->columnCount());
        stream << row << column;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; j++){
                ui->tableWidget->item(i,j)->write(stream);}
        file.close();
    }
    checkButtonSave = true;
}


void CreateForm::on_pushButton_openForm_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open"), "",
                                                    tr("(*.zay);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream stream(&file);
            qint32 row, column;
            stream >> row >> column;
            int countRow = ui->tableWidget->rowCount();
            ui->tableWidget->setRowCount(row+countRow);
            ui->tableWidget->setColumnCount(column);

            for (int i = countRow; i < row+countRow; ++i)
                for (int j = 0; j < column; j++)
                {
                    ui->tableWidget->setItem(i,j,new QTableWidgetItem);
                    ui->tableWidget->item(i,j)->read(stream);
                }
            file.close();
        }
    }
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
}

void CreateForm::on_pushButton_Return_clicked()
{
    this->close();
    emit firstWindow();
}

void CreateForm::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Очистити таблицю?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Ok)
    {
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
    }
    else
        msgBox.close();

}

void CreateForm::on_pushButton_deleteRow_clicked()
{
    if(ui->spinBox_deleteRow->value()!=0 && ui->spinBox_deleteRow->value() <= ui->tableWidget->rowCount()){
        QMessageBox msgBox;
        msgBox.setText("Видалити рядок " + ui->spinBox_deleteRow->text()+" ?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret==QMessageBox::Ok)
        {
            ui->tableWidget->removeRow(ui->spinBox_deleteRow->value()-1);
        }
        else
            msgBox.close();
    }
    else {
        QMessageBox msgBox1;
        msgBox1.setText("Помилка видалення!");
        msgBox1.setInformativeText("Рядок "+ ui->spinBox_deleteRow->text()+" не існує!");
        msgBox1.setStandardButtons(QMessageBox::Ok);
        msgBox1.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox1.exec();
        if(ret==QMessageBox::Ok)
        {
            msgBox1.close();
        }
    }
}

void CreateForm::on_checkBox_personalOrTeam_clicked(bool checked)
{
    if(checked){
        ui->lineEdit_customTeam->setEnabled(true);
    }
    else ui->lineEdit_customTeam->setEnabled(false);
}

void CreateForm::on_lineEdit_findHuman_textChanged(const QString &arg1)
{
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        if(!ui->tableWidget->isRowHidden(i) && ui->tableWidget->item(i,0)->text().toLower().contains(ui->lineEdit_findHuman->text().toLower())
                && ui->lineEdit_findHuman->text()!=""){
            ui->tableWidget->item(i,0)->setBackgroundColor(Qt::darkGray);
        }
        else ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
    }
}
