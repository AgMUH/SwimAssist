#include "startingprotocol.h"
#include "ui_startingprotocol.h"
#include <QFileDialog>
#include <stdlib.h>
#include <QSize>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QMimeData>
#include <QDebug>
#include <QClipboard>
#include <ranksettings.h>
#include <settingsrecords.h>
#include <string>
#include <math.h>
#include <QMessageBox>
#include <QVariant>
#include <QDirIterator>
#include <QDir>


StartingProtocol::StartingProtocol(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartingProtocol)
{
    ui->setupUi(this);
    ui->tableWidget_startSwim->verticalHeader()->setVisible(false);
    ui->tableWidget_startSwim_2->verticalHeader()->setVisible(false);
    ui->tableWidget_lastProtocol->verticalHeader()->setVisible(false);
    ui->tableWidget_lastProtocol_2->verticalHeader()->setVisible(false);
    ui->tableWidget_teams->verticalHeader()->setVisible(false);
    ui->tableWidget_manyFights->verticalHeader()->setVisible(false);
    ui->tableWidget_startSwim->resizeRowsToContents();
    ui->tableWidget_startSwim->resizeColumnsToContents();
    ui->lineEdit_inputTime->setInputMask("00:00.00");
    ui->lineEdit_inputTime->setCursorPosition(0);
    ui->lineEdit_inputTime_2->setInputMask("00:00.00");
    ui->lineEdit_firstSportsmen->setInputMask("00:00.00");
    ui->pushButton_update->setVisible(false);
    ui->pushButton_update_2->setVisible(false);
    ui->pushButton_openFileProtocol->setVisible(false);
    ui->pushButton_openFileProtocol_2->setVisible(false);
    ui->pushButton_updateByYears_2->setVisible(false);
    ui->tableWidget_sortYears_2->verticalHeader()->setVisible(false);
    ui->pushButton_updateByYears->setVisible(false);
    ui->tableWidget_sortYears->verticalHeader()->setVisible(false);
    ui->pushButton_updateByYears_3->setVisible(false);
    ui->tableWidget_sortYears_3->verticalHeader()->setVisible(false);
    //    ui->tableWidget_startSwim->setEditTriggers(0);
    ui->tableWidget_sortYears->setEditTriggers(0);
    ui->tableWidget_sortYears_4->verticalHeader()->setVisible(false);
    ui->tableWidget_sortYears_2->setEditTriggers(0);
    ui->tableWidget_sortYears_3->setEditTriggers(0);
    //    ui->tableWidget_startSwim_2->setEditTriggers(0);
    ui->tableWidget_sortYears_4->setEditTriggers(0);
    ui->widget->hide();
    ui->pushButton_addParticipant->clicked(true);
    QDirIterator iTR("User/", QDir::Files);

    while(iTR.hasNext()){
        QFile file(iTR.next());
        if (file.open(QIODevice::ReadOnly))
        {
            if(!file.fileName().contains("4x") && !file.fileName().contains("test")){
                ui->comboBox_protocolFiles->addItem(file.fileName() ,QVariant::Int);
            }
            else if(file.fileName().contains("4x")){
                ui->comboBox_protocolFiles_2->addItem(file.fileName() ,QVariant::Int);
            }
            file.close();
            ui->tableWidget_lastProtocol->verticalHeader()->hide();
            ui->tableWidget_lastProtocol_2->verticalHeader()->hide();
        }
    }
    QDirIterator iTRa("Estafeta/", QDir::Files);

    while(iTRa.hasNext()){
        QFile file(iTRa.next());
        if (file.open(QIODevice::ReadOnly))
        {
            if(!file.fileName().contains("test")){
                ui->comboBox_protocolFiles_2->addItem(file.fileName() ,QVariant::Int);
            }
            file.close();
            ui->tableWidget_lastProtocol_2->verticalHeader()->hide();
        }
    }
}

StartingProtocol::~StartingProtocol()
{
    delete ui;
}

void StartingProtocol::on_pushButton_back_clicked()
{
    this->close();
    emit protocolWindow();
}
static int count1 = 0;
void StartingProtocol::on_pushButton_openFile_clicked()
{
    QStringList fileName = QFileDialog::getOpenFileNames(this,
                                                    tr("Open"), "",
                                                    tr("(*.zay);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else
    {
        for(int i=0;i<fileName.count();i++){
            QFile file(fileName[i]);
            if (file.open(QIODevice::ReadOnly))
            {
                QDataStream stream(&file);
                qint32 row, column;
                stream >> row >> column;
                int countRow = ui->tableWidget_startReiting->rowCount();
                ui->tableWidget_startReiting->setRowCount(row+countRow);
                ui->tableWidget_startReiting->setColumnCount(column+1);

                for (int i = countRow; i < row+countRow; ++i){
                    count1++;
                    ui->tableWidget_startReiting->setItem(i,0, new QTableWidgetItem);
                    ui->tableWidget_startReiting->item(i,0)->setText(QString::number(count1));

                    for (int j = 1; j < 10; j++)
                    {

                        ui->tableWidget_startReiting->setItem(i,j,new QTableWidgetItem);
                        ui->tableWidget_startReiting->item(i,j)->read(stream);
                    }
                }
                file.close();
                ui->tableWidget_startReiting->verticalHeader()->hide();
            }
        }

        bool flag = false;

        for (int i = 0; i < ui->tableWidget_startReiting->rowCount(); ++i) {
            for (int j = 0; j < ui->comboBox_category->count(); ++j) {
                if(ui->tableWidget_startReiting->item(i,7)->text().contains("(ПК)")){
                    if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(ПК)").join("")){
                        flag=true;
                    }
                }
                else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(Б)")){
                    if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(Б)").join("")){
                        flag=true;
                    }
                }
                else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(К)")){
                    if(ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЧ(К)")
                            || ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЖ(К)")){
                        if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("Ч(К)").join("")){
                            flag=true;
                        }
                        else if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("Ж(К)").join("")){
                            flag=true;
                        }
                        else if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join("")){
                            flag=true;
                        }
                    }
                    else {
                        if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join("")){
                            flag=true;
                        }
                    }
                }
                else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(КБ)")){
                    if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(КБ)").join("")){
                        flag=true;
                    }
                }
                else if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text())
                {
                    flag=true;
                }
            }
            if(!flag){
                if(ui->tableWidget_startReiting->item(i,7)->text().contains("(ПК)")){
                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(ПК)").join(""),QVariant::Int);
                }
                else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(К)")){
                    if(ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЧ(К)")){

                        ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("Ч(К)").join(""),QVariant::Int);
                    }
                    else if(ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЖ(К)")){

                        ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("Ж(К)").join(""),QVariant::Int);
                    }
                    else {

                        ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join(""),QVariant::Int);
                    }
                }
                else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(Б)")){

                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(Б)").join(""),QVariant::Int);
                }
                else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(КБ)")){

                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(КБ)").join(""),QVariant::Int);
                }
                else{

                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text(),QVariant::Int);
                }
            }
            flag=false;
        }
    }
    ui->tableWidget_startReiting->sortByColumn(8,Qt::AscendingOrder);
    setRowsNumbering(ui->tableWidget_startReiting);

    bool flag = false;
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    bool flag4 = false;
    for (int i = 0; i < ui->tableWidget_startReiting->rowCount(); i++) {
        if(ui->tableWidget_startReiting->item(i,2)->text().length()==4){
            for (int j = 0;j<ui->comboBox_sortYear_4->count();j++) {
                if(ui->comboBox_sortYear_4->itemText(j)==ui->tableWidget_startReiting->item(i,2)->text().mid(0,4)){
                    flag=true;
                }
            }
            if(!flag)
                ui->comboBox_sortYear_4->addItem(ui->tableWidget_startReiting->item(i,2)->text().mid(0,4),QVariant::Int);
            flag=false;
        }
        else{
            for (int j = 0;j<ui->comboBox_sortYear_4->count();j++) {
                if(ui->comboBox_sortYear_4->itemText(j)==ui->tableWidget_startReiting->item(i,2)->text().mid(0,4)){
                    flag1=true;
                }
            }
            if(!flag1)
                ui->comboBox_sortYear_4->addItem(ui->tableWidget_startReiting->item(i,2)->text().mid(0,4),QVariant::Int);
            for (int j = 0;j<ui->comboBox_sortYear_4->count();j++) {
                if(ui->comboBox_sortYear_4->itemText(j)==ui->tableWidget_startReiting->item(i,2)->text().mid(5,4)){
                    flag2=true;
                }
            }
            if(!flag2)
                ui->comboBox_sortYear_4->addItem(ui->tableWidget_startReiting->item(i,2)->text().mid(5,4),QVariant::Int);
            for (int j = 0;j<ui->comboBox_sortYear_4->count();j++) {
                if(ui->comboBox_sortYear_4->itemText(j)==ui->tableWidget_startReiting->item(i,2)->text().mid(10,4)){
                    flag3=true;
                }
            }
            if(!flag3)
                ui->comboBox_sortYear_4->addItem(ui->tableWidget_startReiting->item(i,2)->text().mid(10,4),QVariant::Int);
            for (int j = 0;j<ui->comboBox_sortYear_4->count();j++) {
                if(ui->comboBox_sortYear_4->itemText(j)==ui->tableWidget_startReiting->item(i,2)->text().mid(15,4)){
                    flag4=true;
                }
            }
            if(!flag4)
                ui->comboBox_sortYear_4->addItem(ui->tableWidget_startReiting->item(i,2)->text().mid(15,4),QVariant::Int);
            flag1=false;
            flag2=false;
            flag3=false;
            flag4=false;
        }
    }
    ui->comboBox_sortYear_4->model()->sort(0, Qt::AscendingOrder);



    ui->tableWidget_startReiting->resizeRowsToContents();
    ui->tableWidget_startReiting->resizeColumnsToContents();
}



//---------------------------createSwim--------------------------------

static int numb_sportsmen = -1;
static int numb_swim = 1;
static int countPeopleInCategory=0;
void StartingProtocol::on_pushButton_createSwim_clicked()
{
    if(!ui->comboBox_category->currentText().contains("4x")){
        countPeopleInCategory=0;
        numb_sportsmen=-1;
        numb_swim=1;
        if(true){
            countPeopleInCategory=0;
            for (int i=0;i<ui->tableWidget_startReiting->rowCount();i++) {
                if(!ui->tableWidget_startReiting->isRowHidden(i)
                        && (ui->comboBox_category->currentText()==ui->tableWidget_startReiting->item(i,7)->text()
                            || ui->comboBox_category->currentText()==ui->tableWidget_startReiting->item(i,7)->text().split("(ПК)").join("")
                            || ui->comboBox_category->currentText()==ui->tableWidget_startReiting->item(i,7)->text().split("(Б)").join("")
                            || ui->comboBox_category->currentText()==ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join("")
                            || ui->comboBox_category->currentText()==ui->tableWidget_startReiting->item(i,7)->text().split("(КБ)").join(""))){
                    countPeopleInCategory++;
                }
            }
            ui->tableWidget_startSwim->clearContents();
            ui->tableWidget_startSwim->setRowCount(0);
            int tableRow = ui->tableWidget_startReiting->rowCount()-1;
            int tableColumn = 1;
            int countSwims;
            if(countPeopleInCategory % ui->comboBox_countWays->currentText().toInt() == 0)
            {
                countSwims = countPeopleInCategory / ui->comboBox_countWays->currentText().toInt();
            }
            else
                countSwims = countPeopleInCategory / ui->comboBox_countWays->currentText().toInt() + 1;

            ui->tableWidget_startSwim->setRowCount(countSwims+ countPeopleInCategory);
            ui->tableWidget_startSwim->setColumnCount(12);
            int ostacha = countPeopleInCategory % ui->comboBox_countWays->currentText().toInt();
            int flagint = 0;
            int index=0;
            int flagind = 0;
            QFont font;
            font.setBold(true);
            bool checkZapliv=false;
            for (int i = 0; i < countSwims+countPeopleInCategory;i++) {
                numb_sportsmen++;
                if(ostacha==1){

                    if(flagind==0 && numb_sportsmen==1){
                        index=ui->comboBox_countWays->currentText().toInt()/2;
                        flagind++;
                    }
                    else if(flagind==1 && numb_sportsmen==1){
                        index=1;
                    }
                    else index++;

                }
                else if (ostacha!=0 && ostacha !=1)
                {
                    if(flagind==0 && numb_sportsmen==1){
                        index = qRound(double(ui->comboBox_countWays->currentText().toDouble()/ostacha));
                        flagind++;
                    }
                    else if(flagind==1){
                        if(numb_sportsmen==1){index=0;}
                        index++;
                    }
                }
                else if (ostacha==0){
                    if(numb_sportsmen==1){index=0;}
                    index++;
                }

                for (int j = 0; j < 12; j++)
                {
                    ui->tableWidget_startSwim->setItem(i,j,new QTableWidgetItem);
                }
                if(numb_sportsmen==0){
                    ui->tableWidget_startSwim->setSpan(i,0,1,12);
                    if(!checkZapliv){
                        ui->tableWidget_startSwim->item(i,0)->setText(ui->comboBox_category->currentText() + "\nЗаплив "+ QString::number(numb_swim));
                        checkZapliv=true;}
                    else if(checkZapliv){
                        ui->tableWidget_startSwim->item(i,0)->setText("Заплив "+ QString::number(numb_swim));
                    }
                    QTableWidgetItem *item = ui->tableWidget_startSwim->item(i, 0);
                    item->setTextAlignment(Qt::AlignHCenter);

                    numb_swim++;

                    continue;

                }
                ui->tableWidget_startSwim->item(i,0)->setText(QString::number(index));
                for(int j = 1; j<12;j++){

                    for(;;){
                        if(!ui->tableWidget_startReiting->isRowHidden(tableRow)){
                            if(ui->tableWidget_startReiting->item(tableRow,7)->text().contains("(ПК)")){
                                if(ui->tableWidget_startReiting->item(tableRow,7)->text().split("(ПК)").join("") != ui->comboBox_category->currentText()){
                                    tableRow--;
                                }
                                else break;


                            }
                            else if(ui->tableWidget_startReiting->item(tableRow,7)->text().contains("(Б)")){
                                if(ui->tableWidget_startReiting->item(tableRow,7)->text().split("(Б)").join("") != ui->comboBox_category->currentText()){
                                    tableRow--;
                                }
                                else break;

                            }

                            else if(ui->tableWidget_startReiting->item(tableRow,7)->text().contains("(К)")){
                                if(ui->tableWidget_startReiting->item(tableRow,7)->text().split("(К)").join("") != ui->comboBox_category->currentText()){
                                    tableRow--;
                                }
                                else break;

                            }
                            else if(ui->tableWidget_startReiting->item(tableRow,7)->text().contains("(КБ)")){
                                if(ui->tableWidget_startReiting->item(tableRow,7)->text().split("(КБ)").join("") != ui->comboBox_category->currentText()){
                                    tableRow--;
                                }
                                else break;

                            }

                            else if(ui->tableWidget_startReiting->item(tableRow,7)->text() != ui->comboBox_category->currentText()){tableRow--;}
                            else break;
                        }
                        else tableRow--;
                    }
                    if(j==10 || j==9){
                        ui->tableWidget_startSwim->item(i,j)->setText("-");
                        continue;}
                    else if(j==8){
                        ui->tableWidget_startSwim->item(i,8)->setFont(font);
                    }
                    else{
                        ui->tableWidget_startSwim->item(i,j)->setText(ui->tableWidget_startReiting->item(tableRow,tableColumn)->text());
                        tableColumn++;
                        if(tableColumn==8){
                            tableColumn++;
                        }
                    }
                }
                for (int j = 1; j<12;j++) {

                }
                tableColumn=1;
                tableRow--;
                if(ostacha==1){
                    if(flagint == 1){
                        if(numb_sportsmen==ui->comboBox_countWays->currentText().toInt()-1){
                            numb_sportsmen=-1;
                            flagint=2;
                        }
                    }
                    if(numb_sportsmen==2 && ostacha == 1 && flagint==0){
                        numb_sportsmen=-1;
                        flagint = 1;
                    }

                    if(numb_sportsmen == ui->comboBox_countWays->currentText().toInt()){
                        numb_sportsmen=-1;
                    }

                }
                else
                {
                    if(numb_sportsmen==ostacha && flagint!=1){
                        numb_sportsmen=-1;
                        flagint=1;
                    }
                    else if(numb_sportsmen == ui->comboBox_countWays->currentText().toInt()){
                        numb_sportsmen=-1;
                    }
                }


            }
            int countPeopleInSwim=0;
            int allRows = 1;
            QString rowInfo;
            for (int i = 0; i < countSwims ;i++) {
                for (;allRows!=countSwims+countPeopleInCategory;) {
                    if(!ui->tableWidget_startSwim->item(allRows,0)->text().contains("Заплив")){
                        countPeopleInSwim++;
                        allRows++;
                    }
                    else break;
                }
                if(countPeopleInSwim==2){}
                else if(countPeopleInSwim==3){
                    for (int j = 1;j<12;j++) {
                        if(j==10 || j==9){continue;}
                        rowInfo = ui->tableWidget_startSwim->item(allRows-2,j)->text();
                        ui->tableWidget_startSwim->item(allRows-2,j)->setText(ui->tableWidget_startSwim->item(allRows-1,j)->text());
                        ui->tableWidget_startSwim->item(allRows-1,j)->setText(rowInfo);
                    }

                }
                else if(countPeopleInSwim==4){
                    for (int j=1;j<12;j++) {
                        if(j==10 || j==9){continue;}
                        rowInfo = ui->tableWidget_startSwim->item(allRows-3,j)->text();
                        ui->tableWidget_startSwim->item(allRows-3,j)->setText(ui->tableWidget_startSwim->item(allRows-1,j)->text());
                        ui->tableWidget_startSwim->item(allRows-1,j)->setText(rowInfo);
                    }
                }
                else if(countPeopleInSwim==5){
                    for (int j=1;j<12;j++) {
                        if(j==10 || j==9){continue;}
                        rowInfo = ui->tableWidget_startSwim->item(allRows-3,j)->text();
                        ui->tableWidget_startSwim->item(allRows-3,j)->setText(ui->tableWidget_startSwim->item(allRows-4,j)->text());
                        ui->tableWidget_startSwim->item(allRows-4,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim->item(allRows-3,j)->text();
                        ui->tableWidget_startSwim->item(allRows-3,j)->setText(ui->tableWidget_startSwim->item(allRows-1,j)->text());
                        ui->tableWidget_startSwim->item(allRows-1,j)->setText(rowInfo);
                    }
                }
                else if(countPeopleInSwim==6){
                    for (int j=1;j<12;j++) {
                        if(j==10 || j==9){continue;}
                        rowInfo = ui->tableWidget_startSwim->item(allRows-5,j)->text();
                        ui->tableWidget_startSwim->item(allRows-5,j)->setText(ui->tableWidget_startSwim->item(allRows-4,j)->text());
                        ui->tableWidget_startSwim->item(allRows-4,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim->item(allRows-3,j)->text();
                        ui->tableWidget_startSwim->item(allRows-3,j)->setText(ui->tableWidget_startSwim->item(allRows-2,j)->text());
                        ui->tableWidget_startSwim->item(allRows-2,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim->item(allRows-4,j)->text();
                        ui->tableWidget_startSwim->item(allRows-4,j)->setText(ui->tableWidget_startSwim->item(allRows-1,j)->text());
                        ui->tableWidget_startSwim->item(allRows-1,j)->setText(rowInfo);
                    }
                }
                else if(countPeopleInSwim==7){
                    for (int j=1;j<12;j++) {
                        if(j==10 || j==9){continue;}
                        rowInfo = ui->tableWidget_startSwim->item(allRows-5,j)->text();
                        ui->tableWidget_startSwim->item(allRows-5,j)->setText(ui->tableWidget_startSwim->item(allRows-6,j)->text());
                        ui->tableWidget_startSwim->item(allRows-6,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim->item(allRows-4,j)->text();
                        ui->tableWidget_startSwim->item(allRows-4,j)->setText(ui->tableWidget_startSwim->item(allRows-2,j)->text());
                        ui->tableWidget_startSwim->item(allRows-2,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim->item(allRows-4,j)->text();
                        ui->tableWidget_startSwim->item(allRows-4,j)->setText(ui->tableWidget_startSwim->item(allRows-5,j)->text());
                        ui->tableWidget_startSwim->item(allRows-5,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim->item(allRows-4,j)->text();
                        ui->tableWidget_startSwim->item(allRows-4,j)->setText(ui->tableWidget_startSwim->item(allRows-1,j)->text());
                        ui->tableWidget_startSwim->item(allRows-1,j)->setText(rowInfo);
                    }
                }
                else if(countPeopleInSwim==8){
                    for (int j=1;j<12;j++) {
                        if(j==10 || j==9){continue;}
                        rowInfo = ui->tableWidget_startSwim->item(allRows-6,j)->text();
                        ui->tableWidget_startSwim->item(allRows-6,j)->setText(ui->tableWidget_startSwim->item(allRows-7,j)->text());
                        ui->tableWidget_startSwim->item(allRows-7,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim->item(allRows-4,j)->text();
                        ui->tableWidget_startSwim->item(allRows-4,j)->setText(ui->tableWidget_startSwim->item(allRows-6,j)->text());
                        ui->tableWidget_startSwim->item(allRows-6,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim->item(allRows-5,j)->text();
                        ui->tableWidget_startSwim->item(allRows-5,j)->setText(ui->tableWidget_startSwim->item(allRows-2,j)->text());
                        ui->tableWidget_startSwim->item(allRows-2,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim->item(allRows-4,j)->text();
                        ui->tableWidget_startSwim->item(allRows-4,j)->setText(ui->tableWidget_startSwim->item(allRows-1,j)->text());
                        ui->tableWidget_startSwim->item(allRows-1,j)->setText(rowInfo);
                    }
                }

                countPeopleInSwim=0;
                allRows++;
            }
            ui->tableWidget_startSwim->resizeColumnsToContents();
            numb_swim = 1;

        }
    }
    else{
        //-----------------------------------
        countPeopleInCategory=0;
        numb_sportsmen=-1;
        numb_swim=1;
        if(true){
            countPeopleInCategory=0;
            for (int i=0;i<ui->tableWidget_startReiting->rowCount();i++) {
                if(!ui->tableWidget_startReiting->isRowHidden(i) && (ui->comboBox_category->currentText()==ui->tableWidget_startReiting->item(i,7)->text()
                                                                     || ui->comboBox_category->currentText()==ui->tableWidget_startReiting->item(i,7)->text().split("(ПК)").join("")
                                                                     || ui->comboBox_category->currentText()==ui->tableWidget_startReiting->item(i,7)->text().split("(Б)").join("")
                                                                     || ui->comboBox_category->currentText()==ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join("")
                                                                     || ui->comboBox_category->currentText()==ui->tableWidget_startReiting->item(i,7)->text().split("(КБ)").join("")
                                                                     || ui->comboBox_category->currentText()==ui->tableWidget_startReiting->item(i,7)->text().split("Ч(К)").join("")
                                                                     || ui->comboBox_category->currentText()==ui->tableWidget_startReiting->item(i,7)->text().split("Ж(К)").join(""))){
                    countPeopleInCategory++;
                }
            }
            ui->tableWidget_startSwim_2->clearContents();
            ui->tableWidget_startSwim_2->setRowCount(0);
            int tableRow = ui->tableWidget_startReiting->rowCount()-1;
            int tableColumn = 1;
            int countSwims;
            if(countPeopleInCategory % ui->comboBox_countWays->currentText().toInt() == 0)
            {
                countSwims = countPeopleInCategory / ui->comboBox_countWays->currentText().toInt();
            }
            else
                countSwims = countPeopleInCategory / ui->comboBox_countWays->currentText().toInt() + 1;

            ui->tableWidget_startSwim_2->setRowCount(countSwims+ countPeopleInCategory);
            ui->tableWidget_startSwim_2->setColumnCount(12);
            int ostacha = countPeopleInCategory % ui->comboBox_countWays->currentText().toInt();
            int flagint = 0;
            int index=0;
            int flagind = 0;
            QFont font;
            font.setBold(true);
            bool checkZapliv = false;
            for (int i = 0; i < countSwims+countPeopleInCategory;i++) {
                numb_sportsmen++;
                if(ostacha==1){

                    if(flagind==0 && numb_sportsmen==1){
                        index=ui->comboBox_countWays->currentText().toInt()/2;
                        flagind++;
                    }
                    else if(flagind==1 && numb_sportsmen==1){
                        index=1;
                    }
                    else index++;

                }
                else if (ostacha!=0 && ostacha !=1)
                {
                    if(flagind==0 && numb_sportsmen==1){
                        index = qRound(double(ui->comboBox_countWays->currentText().toDouble()/ostacha));
                        flagind++;
                    }
                    else if(flagind==1){
                        if(numb_sportsmen==1){index=0;}
                        index++;
                    }
                }
                else if (ostacha==0){
                    if(numb_sportsmen==1){index=0;}
                    index++;
                }

                for (int j = 0; j < 12; j++)
                {
                    ui->tableWidget_startSwim_2->setItem(i,j,new QTableWidgetItem);
                }
                if(numb_sportsmen==0){
                    ui->tableWidget_startSwim_2->setSpan(i,0,1,12);
                    if(!checkZapliv){
                        ui->tableWidget_startSwim_2->item(i,0)->setText(ui->comboBox_category->currentText() + "\nЗаплив "+ QString::number(numb_swim));
                        checkZapliv=true;
                    }
                    else if(checkZapliv){
                        ui->tableWidget_startSwim_2->item(i,0)->setText("Заплив "+ QString::number(numb_swim));
                    }
                    QTableWidgetItem *item = ui->tableWidget_startSwim_2->item(i, 0);
                    item->setTextAlignment(Qt::AlignHCenter);
                    numb_swim++;

                    continue;

                }
                ui->tableWidget_startSwim_2->item(i,0)->setText(QString::number(index));
                for(int j = 1; j<12;j++){

                    for(;;){
                        if(!ui->tableWidget_startReiting->isRowHidden(tableRow)){
                            if(ui->tableWidget_startReiting->item(tableRow,7)->text().contains("(ПК)")){
                                if(ui->tableWidget_startReiting->item(tableRow,7)->text().split("(ПК)").join("") != ui->comboBox_category->currentText()){
                                    tableRow--;
                                }
                                else break;


                            }
                            else if(ui->tableWidget_startReiting->item(tableRow,7)->text().contains("(Б)")){
                                if(ui->tableWidget_startReiting->item(tableRow,7)->text().split("(Б)").join("") != ui->comboBox_category->currentText()){
                                    tableRow--;
                                }
                                else break;

                            }
                            else if(ui->tableWidget_startReiting->item(tableRow,7)->text().contains("ЗмЧ(К)")){
                                if(ui->tableWidget_startReiting->item(tableRow,7)->text().split("Ч(К)").join("") != ui->comboBox_category->currentText()){
                                    tableRow--;
                                }
                                else break;
                            }
                            else if(ui->tableWidget_startReiting->item(tableRow,7)->text().contains("ЗмЖ(К)")){
                                if(ui->tableWidget_startReiting->item(tableRow,7)->text().split("Ж(К)").join("") != ui->comboBox_category->currentText()){
                                    tableRow--;
                                }
                                else break;
                            }
                            else if(ui->tableWidget_startReiting->item(tableRow,7)->text().contains("(К)")){
                                if(ui->tableWidget_startReiting->item(tableRow,7)->text().split("(К)").join("") != ui->comboBox_category->currentText()){
                                    tableRow--;
                                }
                                else break;

                            }
                            else if(ui->tableWidget_startReiting->item(tableRow,7)->text().contains("(КБ)")){
                                if(ui->tableWidget_startReiting->item(tableRow,7)->text().split("(КБ)").join("") != ui->comboBox_category->currentText()){
                                    tableRow--;
                                }
                                else break;

                            }

                            else if(ui->tableWidget_startReiting->item(tableRow,7)->text() != ui->comboBox_category->currentText()){tableRow--;}
                            else break;
                        }
                        else tableRow--;
                    }
                    if(j==10 || j==9){continue;}
                    else if(j==8){
                        ui->tableWidget_startSwim_2->item(i,8)->setFont(font);
                    }
                    else{
                        ui->tableWidget_startSwim_2->item(i,j)->setText(ui->tableWidget_startReiting->item(tableRow,tableColumn)->text());
                        tableColumn++;
                        if(tableColumn==8){
                            tableColumn++;
                        }
                    }
                }
                ui->tableWidget_startSwim_2->item(i,8)->setTextAlignment(Qt::AlignTop);
                for (int j = 1; j<12;j++) {

                }
                tableColumn=1;
                tableRow--;
                if(ostacha==1){
                    if(flagint == 1){
                        if(numb_sportsmen==ui->comboBox_countWays->currentText().toInt()-1){
                            numb_sportsmen=-1;
                            flagint=2;
                        }
                    }
                    if(numb_sportsmen==2 && ostacha == 1 && flagint==0){
                        numb_sportsmen=-1;
                        flagint = 1;
                    }

                    if(numb_sportsmen == ui->comboBox_countWays->currentText().toInt()){
                        numb_sportsmen=-1;
                    }

                }
                else
                {
                    if(numb_sportsmen==ostacha && flagint!=1){
                        numb_sportsmen=-1;
                        flagint=1;
                    }
                    else if(numb_sportsmen == ui->comboBox_countWays->currentText().toInt()){
                        numb_sportsmen=-1;
                    }
                }


            }
            int countPeopleInSwim=0;
            int allRows = 1;
            QString rowInfo;
            for (int i = 0; i < countSwims ;i++) {
                for (;allRows!=countSwims+countPeopleInCategory;) {
                    if(!ui->tableWidget_startSwim_2->item(allRows,0)->text().contains("Заплив")){
                        countPeopleInSwim++;
                        allRows++;
                    }
                    else break;
                }
                if(countPeopleInSwim==2){}
                else if(countPeopleInSwim==3){
                    for (int j = 1;j<12;j++) {
                        if(j==10 || j==9){continue;}
                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-2,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-2,j)->setText(ui->tableWidget_startSwim_2->item(allRows-1,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-1,j)->setText(rowInfo);
                    }

                }
                else if(countPeopleInSwim==4){
                    for (int j=1;j<12;j++) {
                        if(j==10 || j==9){continue;}
                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-3,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-3,j)->setText(ui->tableWidget_startSwim_2->item(allRows-1,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-1,j)->setText(rowInfo);
                    }
                }
                else if(countPeopleInSwim==5){
                    for (int j=1;j<12;j++) {
                        if(j==10 || j==9){continue;}
                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-3,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-3,j)->setText(ui->tableWidget_startSwim_2->item(allRows-4,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-4,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-3,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-3,j)->setText(ui->tableWidget_startSwim_2->item(allRows-1,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-1,j)->setText(rowInfo);
                    }
                }
                else if(countPeopleInSwim==6){
                    for (int j=1;j<12;j++) {
                        if(j==10 || j==9){continue;}
                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-5,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-5,j)->setText(ui->tableWidget_startSwim_2->item(allRows-4,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-4,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-3,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-3,j)->setText(ui->tableWidget_startSwim_2->item(allRows-2,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-2,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-4,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-4,j)->setText(ui->tableWidget_startSwim_2->item(allRows-1,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-1,j)->setText(rowInfo);
                    }
                }
                else if(countPeopleInSwim==7){
                    for (int j=1;j<12;j++) {
                        if(j==10 || j==9){continue;}
                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-5,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-5,j)->setText(ui->tableWidget_startSwim_2->item(allRows-6,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-6,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-4,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-4,j)->setText(ui->tableWidget_startSwim_2->item(allRows-2,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-2,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-4,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-4,j)->setText(ui->tableWidget_startSwim_2->item(allRows-5,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-5,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-4,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-4,j)->setText(ui->tableWidget_startSwim_2->item(allRows-1,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-1,j)->setText(rowInfo);
                    }
                }
                else if(countPeopleInSwim==8){
                    for (int j=1;j<12;j++) {
                        if(j==10 || j==9){continue;}
                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-6,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-6,j)->setText(ui->tableWidget_startSwim_2->item(allRows-7,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-7,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-4,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-4,j)->setText(ui->tableWidget_startSwim_2->item(allRows-6,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-6,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-5,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-5,j)->setText(ui->tableWidget_startSwim_2->item(allRows-2,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-2,j)->setText(rowInfo);

                        rowInfo = ui->tableWidget_startSwim_2->item(allRows-4,j)->text();
                        ui->tableWidget_startSwim_2->item(allRows-4,j)->setText(ui->tableWidget_startSwim_2->item(allRows-1,j)->text());
                        ui->tableWidget_startSwim_2->item(allRows-1,j)->setText(rowInfo);
                    }
                }

                countPeopleInSwim=0;
                allRows++;
            }
            ui->tableWidget_startSwim_2->resizeColumnsToContents();
            numb_swim = 1;
        }
    }
    int countSp2=0;
    int firstIndex2=0,lastIndex2=0;
    int way2=0;
    for (int i=0;i<ui->tableWidget_startSwim_2->rowCount();i++) {
        firstIndex2=i;
        for (int j=i+1;j<ui->tableWidget_startSwim_2->rowCount();j++) {
            if(ui->tableWidget_startSwim_2->item(j,0)->text().contains("Заплив")){
                lastIndex2=j;break;
            }
            else {
                countSp2++;
                lastIndex2=j+1;
            }
        }
        if(countSp2!=ui->comboBox_countWays->count()){
            way2 = (ui->comboBox_countWays->currentText().toInt()-countSp2)/2 +1;
        }
        else way2 = (ui->comboBox_countWays->currentText().toInt()-countSp2 + 1)/2 +1;
        for (int j = firstIndex2+1;j<lastIndex2;j++) {
            ui->tableWidget_startSwim_2->item(j,0)->setText(QString::number(way2));
            way2++;
        }
        i+=countSp2;
        countSp2=0;
    }
    int countSp=0;
    int firstIndex=0,lastIndex=0;
    int way=0;
    for (int i=0;i<ui->tableWidget_startSwim->rowCount();i++) {
        firstIndex=i;
        for (int j=i+1;j<ui->tableWidget_startSwim->rowCount();j++) {
            if(ui->tableWidget_startSwim->item(j,0)->text().contains("Заплив")){
                lastIndex=j;break;
            }
            else {
                countSp++;
                lastIndex=j+1;
            }
        }
        if(countSp!=ui->comboBox_countWays->count()){
            way = (ui->comboBox_countWays->currentText().toInt()-countSp)/2 +1;
        }
        else way = (ui->comboBox_countWays->currentText().toInt()-countSp + 1)/2 +1;
        for (int j = firstIndex+1;j<lastIndex;j++) {
            ui->tableWidget_startSwim->item(j,0)->setText(QString::number(way));
            way++;
        }
        i+=countSp;
        countSp=0;
    }
    ui->tableWidget_startSwim->resizeRowsToContents();
    ui->tableWidget_startSwim->resizeColumnsToContents();
    ui->tableWidget_startSwim_2->resizeRowsToContents();
    ui->tableWidget_startSwim_2->resizeColumnsToContents();
}


void StartingProtocol::on_pushButton_copyTableSwim_clicked()
{
    QString selected_text_as_html;
    QString selected_text;
    QTableWidget *table = ui->tableWidget_startSwim;
    selected_text_as_html.prepend("<html><style>br{mso-data-placement:same-cell;}</style><table><tr><td>");

    for (int rowIndex = 0; rowIndex <table->rowCount(); rowIndex++) {
        for (int columnIndex = 0; columnIndex < 12; columnIndex++) {
            if(columnIndex==7)continue;
            QString text = table->item(rowIndex,columnIndex)->text();
            selected_text.append(text);
            text.replace("\n","<br>");
            selected_text_as_html.append(text);
            selected_text_as_html.append("</td><td>");
            selected_text.append(QLatin1Char('\t'));
        }
        selected_text_as_html.append("</td></tr><tr><td>");
        selected_text.append(QLatin1Char('\n'));
    }
    selected_text_as_html.append("</td></tr>");
    QMimeData * md = new QMimeData;
    md->setHtml(selected_text_as_html);
    qDebug() << selected_text;
    md->setText(selected_text);
    qApp->clipboard()->setMimeData(md);
}

void StartingProtocol::on_pushButton_copyTableReitings_clicked()
{
    QString selected_text_as_html;
    QString selected_text;
    QTableWidget *table = ui->tableWidget_startReiting;
    selected_text_as_html.prepend("<html><style>br{mso-data-placement:same-cell;}</style><table><tr><td>");
    for (int columnIndex = 0; columnIndex < 10; columnIndex++) {
        QString text = table->horizontalHeaderItem(columnIndex)->text();
        selected_text.append(text);
        text.replace("\n","<br>");
        selected_text_as_html.append(text);
        selected_text_as_html.append("</td><td>");
        selected_text.append(QLatin1Char('\t'));
    }
    selected_text_as_html.append("</td></tr><tr><td>");
    selected_text.append(QLatin1Char('\n'));

    for (int rowIndex = 0; rowIndex <table->rowCount(); rowIndex++) {
        if(!ui->tableWidget_startReiting->isRowHidden(rowIndex)){
            for (int columnIndex = 0; columnIndex < 10; columnIndex++) {
                QString text = table->item(rowIndex,columnIndex)->text();
                selected_text.append(text);
                text.replace("\n","<br>");
                selected_text_as_html.append(text);
                selected_text_as_html.append("</td><td>");
                selected_text.append(QLatin1Char('\t'));
            }
            selected_text_as_html.append("</td></tr><tr><td>");
            selected_text.append(QLatin1Char('\n'));
        }
    }
    selected_text_as_html.append("</td></tr>");
    QMimeData * md = new QMimeData;
    md->setHtml(selected_text_as_html);
    qDebug() << selected_text;
    md->setText(selected_text);
    qApp->clipboard()->setMimeData(md);
}


void StartingProtocol::on_pushButton_update_clicked()
{
    RankSettings * rank = new RankSettings();
    for(int i=0;i<ui->tableWidget_startSwim->rowCount();i++){
        if((ui->tableWidget_startSwim->item(i,8)->text()!=""
            && ui->tableWidget_startSwim->item(i,8)->text().length()==8
            && ui->tableWidget_startSwim->item(i,8)->text().contains(":")==true
            && ui->tableWidget_startSwim->item(i,8)->text().contains(".")==true)){
            if(ui->comboBox_swimPool->currentText() == "50м"){
                if(ui->comboBox_category->currentText().contains("50,В.ст.,Ч")){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(0,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(0,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(0,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(0,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,В.ст.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(1,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(1,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(1,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(1,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,В.ст.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(2,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(2,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(2,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(2,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="400,В.ст.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(3,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(3,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(3,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(3,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="800,В.ст.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-2;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(4,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(4,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(4,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(4,5)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="1500,В.ст.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-2;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(5,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(5,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(5,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(5,5)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="50,На спині,Ч"){
                    for(int j = 3; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(6,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(6,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(6,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(6,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,На спині,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(7,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(7,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(7,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(7,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,На спині,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(8,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(8,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(8,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(8,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="50,Брас,Ч"){
                    for(int j = 3; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(9,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(9,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(9,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(9,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,Брас,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(10,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(10,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(10,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(10,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,Брас,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(11,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(11,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(11,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(11,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="50,Бат,Ч"){
                    for(int j = 3; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(12,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(12,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(12,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(12,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,Бат,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(13,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(13,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(13,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(13,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,Бат,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(14,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(14,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(14,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(14,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,Комп.,Ч"){
                    ui->tableWidget_startSwim->item(0,9)->setText("Помилка");
                }
                else if(ui->comboBox_category->currentText()=="200,Комп.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(16,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(16,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(16,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(16,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="400,Комп.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-2;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(17,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(17,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Men->item(17,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Men->item(17,5)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                //-----------------------------------------Women-----------------------------------
                else if(ui->comboBox_category->currentText()=="50,В.ст.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(0,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(0,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(0,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(0,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,В.ст.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(1,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(1,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(1,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(1,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,В.ст.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(2,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(2,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(2,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(2,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="400,В.ст.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(3,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(3,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(3,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(3,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="800,В.ст.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-2;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(4,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(4,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(4,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(4,5)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="1500,В.ст.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-2;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(5,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(5,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(5,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(5,5)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="50,На спині,Ж"){
                    for(int j = 3; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(6,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(6,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(6,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(6,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,На спині,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(7,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(7,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(7,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(7,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,На спині,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(8,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(8,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(8,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(8,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="50,Брас,Ж"){
                    for(int j = 3; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(9,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(9,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(9,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(9,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,Брас,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(10,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(10,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(10,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(10,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,Брас,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(11,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(11,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(11,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(11,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="50,Бат,Ж"){
                    for(int j = 3; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(12,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(12,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(12,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(12,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,Бат,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(13,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(13,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(13,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(13,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,Бат,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(14,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(14,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(14,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(14,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,Комп.,Ж"){
                    ui->tableWidget_startSwim->item(0,9)->setText("-");
                }
                else if(ui->comboBox_category->currentText()=="200,Комп.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(16,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(16,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(16,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(16,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="400,Комп.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-2;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(17,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(17,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_50Women->item(17,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_50Women->item(17,5)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                ui->tableWidget_startSwim->item(i,8)->setBackgroundColor(Qt::white);
            }
            //------------------------25m----------------------------
            else {
                if(ui->comboBox_category->currentText()=="50,В.ст.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(0,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(0,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(0,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(0,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,В.ст.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(1,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(1,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(1,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(1,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,В.ст.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(2,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(2,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(2,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(2,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="400,В.ст.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(3,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(3,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(3,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(3,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="800,В.ст.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-2;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(4,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(4,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(4,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(4,5)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="1500,В.ст.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-2;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(5,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(5,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(5,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(5,5)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="50,На спині,Ч"){
                    for(int j = 3; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(6,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(6,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(6,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(6,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,На спині,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(7,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(7,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(7,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(7,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,На спині,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(8,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(8,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(8,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(8,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="50,Брас,Ч"){
                    for(int j = 3; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(9,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(9,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(9,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(9,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,Брас,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(10,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(10,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(10,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(10,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,Брас,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(11,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(11,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(11,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(11,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="50,Бат,Ч"){
                    for(int j = 3; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(12,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(12,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(12,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(12,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,Бат,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(13,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(13,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(13,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(13,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,Бат,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(14,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(14,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(14,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(14,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,Комп.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(15,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(15,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(15,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(15,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,Комп.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(16,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(16,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(16,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(16,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="400,Комп.,Ч"){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-2;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(17,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(17,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Men->item(17,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Men->item(17,5)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                //-----------------------Women25-----------------
                else if(ui->comboBox_category->currentText()=="50,В.ст.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(0,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(0,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(0,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(0,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,В.ст.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(1,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(1,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(1,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(1,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,В.ст.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(2,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(2,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(2,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(2,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="400,В.ст.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(3,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(3,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(3,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(3,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="800,В.ст.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-2;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(4,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(4,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(4,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(4,5)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="1500,В.ст.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-2;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(5,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(5,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(5,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(5,5)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="50,На спині,Ж"){
                    for(int j = 3; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(6,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(6,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(6,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(6,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,На спині,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(7,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(7,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(7,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(7,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,На спині,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(8,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(8,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(8,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(8,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="50,Брас,Ж"){
                    for(int j = 3; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(9,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(9,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(9,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(9,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,Брас,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(10,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(10,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(10,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(10,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,Брас,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(11,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(11,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(11,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(11,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="50,Бат,Ж"){
                    for(int j = 3; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(12,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(12,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(12,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(12,7)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,Бат,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(13,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(13,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(13,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(13,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,Бат,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(14,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(14,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(14,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(14,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="100,Комп.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(15,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(15,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(15,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(15,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="200,Комп.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(16,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(16,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(16,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(16,6)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->comboBox_category->currentText()=="400,Комп.,Ж"){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-2;j++){
                        if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(17,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(17,j)->text())
                        {
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() <= rank->ui->tableWidget_25Women->item(17,j-1)->text()){
                            ui->tableWidget_startSwim->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim->item(i,8)->text() > rank->ui->tableWidget_25Women->item(17,5)->text() ){
                            ui->tableWidget_startSwim->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                ui->tableWidget_startSwim->item(i,8)->setBackgroundColor(Qt::white);

            }

        }
        else{
            ui->tableWidget_startSwim->item(i,8)->setBackgroundColor(Qt::red);
            ui->tableWidget_startSwim->item(i,9)->setText("-");
            ui->tableWidget_startSwim->item(i,10)->setText("-");
        }
        if(ui->tableWidget_startSwim->item(i,7)->text().contains("(ПК)")){
            ui->tableWidget_startSwim->item(i,10)->setText("~");
        }
        if(ui->tableWidget_startSwim->item(i,8)->text().contains("ДК")){
            ui->tableWidget_startSwim->item(i,8)->setBackgroundColor(Qt::white);
            ui->tableWidget_startSwim->item(i,9)->setText("-");
            ui->tableWidget_startSwim->item(i,10)->setText("-");
        }
    }


    SettingsRecords * finn = new SettingsRecords();
    int points;
    QString miliseconds;
    double second;
    double minute,recSeconds;
    for(int i = 0; i< ui->tableWidget_startSwim->rowCount();i++){
        if(ui->tableWidget_startSwim->item(i,8)->text()!=""
                && ui->tableWidget_startSwim->item(i,8)->text().length()==8
                && ui->tableWidget_startSwim->item(i,8)->text().contains(":")==true
                && ui->tableWidget_startSwim->item(i,8)->text().contains(".")==true
                && ui->tableWidget_startSwim->item(i,8)->text() != "ДК"
                && !ui->tableWidget_startSwim->item(i,7)->text().contains("ПК")
                && ui->tableWidget_startSwim->item(i,8)->text() != "00:00.00"){
            if(ui->comboBox_swimPool->currentText()=="50м"){
                if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men50->text().mid(3,7).toDouble() + recSeconds) / second),3);


                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("400,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men400->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men400->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("800,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men800->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men800->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("1500,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men1500->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men1500->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,Бат,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_but_men50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_men50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,Бат,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_but_men100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_men100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,Бат,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_but_men200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_men200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,На спині,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_back_men50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_back_men50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,На спині,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_back_men100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_back_men100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,На спині,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_back_men200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_back_men200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,Брас,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_bras_men50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_bras_men50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,Брас,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_bras_men100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_bras_men100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,Брас,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_bras_men200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_bras_men200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,Комп.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_complex_men200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_men200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("400,Комп.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_complex_men400->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_men400->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("400,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women400->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women400->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("800,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women800->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women800->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("1500,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women1500->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women1500->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,Бат,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_but_women50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_women50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,Бат,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_but_women100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_women100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,Бат,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_but_women200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_women200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,На спині,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_back_women50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_back_women50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,На спині,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_back_women100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_back_women100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,На спині,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_back_women200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_back_women200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,Брас,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_bras_women50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_bras_women50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,Брас,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_bras_women100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_bras_women100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,Брас,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_bras_women200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_bras_women200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,Комп.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_complex_women200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_women200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("400,Комп.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_complex_women400->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_women400->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,Комп.,Ж")){
                    ui->tableWidget_startSwim->item(i,10)->setText("-");
                }
                else ui->tableWidget_startSwim->item(i,10)->setText("-");
            }
            else{

                if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("400,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men400->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men400->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("800,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men800->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men800->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("1500,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men1500->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men1500->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,Бат,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_but_men50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_but_men50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,Бат,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_but_men100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_but_men100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,Бат,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_but_men200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_but_men200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,На спині,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_back_men50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_back_men50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,На спині,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_back_men100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_back_men100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,На спині,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_back_men200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_back_men200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,Брас,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_bras_men50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_bras_men50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,Брас,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_bras_men100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_bras_men100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,Брас,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_bras_men200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_bras_men200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,Комп.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_complex_men200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_men200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("400,Комп.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_complex_men400->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_men400->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,Комп.,Ч")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_complex_men100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_men100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("400,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women400->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women400->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("800,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women800->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women800->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("1500,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women1500->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women1500->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,Бат,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_but_women50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_but_women50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,Бат,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_but_women100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_but_women100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,Бат,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_but_women200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_but_women200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,На спині,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_back_women50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_back_women50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,На спині,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_back_women100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_back_women100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,На спині,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_back_women200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_back_women200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("50,Брас,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_bras_women50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_bras_women50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,Брас,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_bras_women100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_bras_women100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,Брас,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_bras_women200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_bras_women200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("200,Комп.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_complex_women200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_women200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("400,Комп.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_complex_women400->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_women400->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim->item(i,7)->text().contains("100,Комп.,Ж")){
                    minute = ui->tableWidget_startSwim->item(i,8)->text().mid(0,2).toDouble();
                    second = ui->tableWidget_startSwim->item(i,8)->text().mid(3,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_complex_women100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_women100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim->item(i,10)->setText(QString::number(points));
                }
                else ui->tableWidget_startSwim->item(i,10)->setText("-");
            }
        }
    }



}

void StartingProtocol::on_pushButton_createNewReiting_clicked()
{
    if(ui->tableWidget_startSwim->rowCount()!=0 && !ui->tableWidget_startSwim->item(1,7)->text().contains(ui->lineEdit_styleProtocol->text())){
        ui->tableWidget_lastProtocol->clearContents();
        ui->tableWidget_lastProtocol->setRowCount(0);
    }
    int indDistance = ui->tableWidget_startSwim->item(1,7)->text().indexOf("(");
    if(ui->tableWidget_startSwim->item(1,7)->text().contains("(")){
        ui->lineEdit_styleProtocol->setText(ui->tableWidget_startSwim->item(1,7)->text().mid(0,indDistance));
    }
    else ui->lineEdit_styleProtocol->setText(ui->tableWidget_startSwim->item(1,7)->text());


    ui->comboBox_protocolFiles->setCurrentText("User/"+ui->lineEdit_styleProtocol->text()+".prot");

    int countUpdatedPeople=0;


    bool flagRepeatPerson =false;
    for (int i=0;i<ui->tableWidget_startSwim->rowCount();i++) {
        if(ui->tableWidget_startSwim->item(i,8)->text()!=""
                && ui->tableWidget_startSwim->item(i,9)->text()!=""
                && ui->tableWidget_startSwim->item(i,10)->text()!=""
                && ui->tableWidget_startSwim->item(i,8)->text()!=":."){
            countUpdatedPeople++;
            flagRepeatPerson = true;
        }
        for (int j=0;j<ui->tableWidget_lastProtocol->rowCount();j++) {
            if(ui->tableWidget_lastProtocol->item(j,1)->text().contains(ui->tableWidget_startSwim->item(i,1)->text())
                    && ui->tableWidget_lastProtocol->item(j,6)->text().contains(ui->tableWidget_startSwim->item(i,7)->text())
                    && ui->tableWidget_lastProtocol->item(j,2)->text().contains(ui->tableWidget_startSwim->item(i,2)->text())
                    && ui->tableWidget_lastProtocol->item(j,5)->text().contains(ui->tableWidget_startSwim->item(i,6)->text())
                    && flagRepeatPerson){
                ui->tableWidget_lastProtocol->removeRow(j);
                break;
            }
        }
        flagRepeatPerson=false;
    }

    int previousCountPeople = ui->tableWidget_lastProtocol->rowCount();
    int tableRow = ui->tableWidget_lastProtocol->rowCount();
    QString beforePoints="";
    ui->tableWidget_lastProtocol->setRowCount(countUpdatedPeople+previousCountPeople);

    int tableColumn = -1;
    bool flag = false;
    for(int i=0;i < ui->tableWidget_startSwim->rowCount();i++){
        for(int j = 1; j < 12; j++){
            if(ui->tableWidget_startSwim->item(i,j)->text()==""){
                flag = true;
                break;
            }
        }
        for(int j = 0; j < 11;j++){
            if(flag)break;
            ui->tableWidget_lastProtocol->setItem(tableRow,j, new QTableWidgetItem);
        }
        for(int j = 0;j<11;j++){
            if(flag){break;}
            tableColumn++;
            if(tableColumn==3) {
                tableColumn++;
            }
            if(j==9){
                for (int k=0;k<6-ui->tableWidget_startSwim->item(i, tableColumn)->text().length();k++) {
                    beforePoints+=" ";
                }
            }
            ui->tableWidget_lastProtocol->item(tableRow,j)->setText(beforePoints+ui->tableWidget_startSwim->item(i, tableColumn)->text());
            beforePoints="";
        }
        if(!flag) tableRow++;
        tableColumn = -1;
        flag= false;
    }
    ui->tableWidget_lastProtocol->sortByColumn(7,Qt::AscendingOrder);
    ui->tableWidget_lastProtocol->sortByColumn(9,Qt::DescendingOrder);
    QString afterPoits="";
    for (int i=0;i<ui->tableWidget_lastProtocol->rowCount();i++) {
        afterPoits = ui->tableWidget_lastProtocol->item(i,9)->text();
        ui->tableWidget_lastProtocol->item(i,9)->setText(afterPoits.trimmed());
    }


    bool flag2 = false;

    for (int i = 0; i < ui->tableWidget_lastProtocol->rowCount(); i++) {
        for (int j = 0;j<ui->comboBox_sortYear->count();j++) {
            if(ui->comboBox_sortYear->itemText(j)==ui->tableWidget_lastProtocol->item(i,2)->text().mid(0,4)){
                flag2=true;
            }
        }
        if(!flag2)
            ui->comboBox_sortYear->addItem(ui->tableWidget_lastProtocol->item(i,2)->text().mid(0,4),QVariant::Int);
        flag2=false;
    }

    int countOfTableProtocol = 1;
    for (int i = 0;i<ui->tableWidget_lastProtocol->rowCount();i++) {
        if(!ui->tableWidget_lastProtocol->isRowHidden(i)){

            ui->tableWidget_lastProtocol->item(i,0)->setText(QString::number(countOfTableProtocol));
            countOfTableProtocol++;
        }
    }


    QString fr = "User\\"+ui->lineEdit_styleProtocol->text()+".prot";
    QFile file(fr);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        qint32 row(ui->tableWidget_lastProtocol->rowCount()), column(ui->tableWidget_lastProtocol->columnCount());
        stream << row << column;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; j++){
                ui->tableWidget_lastProtocol->item(i,j)->write(stream);}
        file.close();
    }

    ui->comboBox_protocolFiles->clear();
    QDirIterator iTR("User/", QDir::Files);

    while(iTR.hasNext()){
        QFile file(iTR.next());
        if (file.open(QIODevice::ReadOnly))
        {
            ui->comboBox_protocolFiles->addItem(file.fileName() ,QVariant::Int);
            file.close();
            ui->tableWidget_lastProtocol->verticalHeader()->hide();
        }
    }

    QString summ="";
    QString beforePointT="";
    for (int i=0;i<ui->tableWidget_lastProtocol->rowCount();i++) {
        summ=ui->tableWidget_lastProtocol->item(i,9)->text();
        for (int k=0;k<6-ui->tableWidget_lastProtocol->item(i, 9)->text().length();k++) {
            beforePointT+=" ";
        }
        ui->tableWidget_lastProtocol->item(i,9)->setText(beforePointT+summ);
        beforePointT="";
    }

    ui->tableWidget_lastProtocol->sortByColumn(9,Qt::DescendingOrder);
    QString afterPoitsT="";
    for (int i=0;i<ui->tableWidget_lastProtocol->rowCount();i++) {
        afterPoitsT = ui->tableWidget_lastProtocol->item(i,9)->text();
        ui->tableWidget_lastProtocol->item(i,9)->setText(afterPoitsT.trimmed());
    }
    setRowsNumbering(ui->tableWidget_lastProtocol);
    ui->comboBox_sortYear->model()->sort(Qt::AscendingOrder);
    //    bool flag1 = false;
    //    ui->lineEdit_styleProtocol->clear();
    //    ui->lineEdit_styleProtocol->setText(ui->comboBox_category->currentText());
    //    for (int i=0;i<ui->comboBox_protocolFiles->count();i++) {
    //        if(ui->comboBox_protocolFiles->itemText(i).contains(ui->lineEdit_styleProtocol->text())){
    //            ui->comboBox_protocolFiles->setCurrentIndex(i);
    //            break;
    //        }
    //    }
    ui->lineEdit_styleProtocol->setText(ui->comboBox_category->currentText());


    ui->comboBox_protocolFiles->setCurrentText("User/"+ui->lineEdit_styleProtocol->text()+".prot");
    ui->tableWidget_lastProtocol->resizeColumnsToContents();
    ui->tableWidget_lastProtocol->resizeRowsToContents();
}

void StartingProtocol::on_pushButton_clearTableReiting_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Очистити таблицю?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Ok)
    {
        ui->tableWidget_startReiting->clearContents();
        ui->tableWidget_startReiting->setRowCount(0);
    }
    else
        msgBox.close();
    ui->comboBox_category->clear();
    ui->comboBox_category->addItem("",QVariant::Int);
    ui->comboBox_category->addItem("Ч",QVariant::Int);
    ui->comboBox_category->addItem("Ж",QVariant::Int);
    bool flag = false;
    for (int i = 0; i < ui->tableWidget_startReiting->rowCount(); ++i) {
        for (int j = 0; j < ui->comboBox_category->count(); ++j) {
            if(ui->tableWidget_startReiting->item(i,7)->text().contains("(ПК)")){
                if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(ПК)").join("")){
                    flag=true;
                }
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(Б)")){
                if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(Б)").join("")){
                    flag=true;
                }
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(К)")){
                if(ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЧ(К)")
                        || ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЖ(К)")){
                    if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("Ч(К)").join("")){
                        flag=true;
                    }
                    else if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("Ж(К)").join("")){
                        flag=true;
                    }
                    else if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join("")){
                        flag=true;
                    }
                }
                else {
                    if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join("")){
                        flag=true;
                    }
                }
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(КБ)")){
                if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(КБ)").join("")){
                    flag=true;
                }
            }
            else if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text())
            {
                flag=true;
            }
        }
        if(!flag){
            if(ui->tableWidget_startReiting->item(i,7)->text().contains("(ПК)")){

                ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(ПК)").join(""),QVariant::Int);
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(К)")){
                if(ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЧ(К)")){

                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("Ч(К)").join(""),QVariant::Int);
                }
                else if(ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЖ(К)")){

                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("Ж(К)").join(""),QVariant::Int);
                }
                else {

                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join(""),QVariant::Int);
                }
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(Б)")){

                ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(Б)").join(""),QVariant::Int);
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(КБ)")){

                ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(КБ)").join(""),QVariant::Int);
            }
            else{

                ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text(),QVariant::Int);
            }
        }
        flag=false;
    }
}

void StartingProtocol::on_pushButton_deleteRow_clicked()
{
    QString distance = ui->comboBox_category->currentText();
    int rowCount=0;
    for(int i=0;i<ui->tableWidget_startReiting->rowCount();i++){
        if(!ui->tableWidget_startReiting->isRowHidden(i)){
            rowCount++;
        }
    }
    if(ui->spinBox_deleteRow->value()!=0 && ui->spinBox_deleteRow->value() <= rowCount){
        QMessageBox msgBox;

        msgBox.setText("Видалити рядок " + ui->spinBox_deleteRow->text()+" ?");

        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

        msgBox.setDefaultButton(QMessageBox::Ok);

        int ret = msgBox.exec();

        if(ret==QMessageBox::Ok)
        {
            int rowIndex=-1;
            for(int i=0;i<ui->tableWidget_startReiting->rowCount();i++){
                if(!ui->tableWidget_startReiting->isRowHidden(i) && ui->tableWidget_startReiting->item(i,0)->text()==ui->spinBox_deleteRow->text()){
                    rowIndex=i;
                }
            }
            ui->tableWidget_startReiting->removeRow(rowIndex);
            QString summ;
            QString beforePointT="";
            for (int i=0;i<ui->tableWidget_startReiting->rowCount();i++) {
                summ=ui->tableWidget_startReiting->item(i,9)->text();
                for (int k=0;k<6-ui->tableWidget_startReiting->item(i, 9)->text().length();k++) {
                    beforePointT+=" ";
                }
                ui->tableWidget_startReiting->item(i,9)->setText(beforePointT+summ);
                beforePointT="";
            }

            ui->tableWidget_startReiting->sortByColumn(9,Qt::DescendingOrder);
            QString afterPoitsT="";
            for (int i=0;i<ui->tableWidget_startReiting->rowCount();i++) {
                afterPoitsT = ui->tableWidget_startReiting->item(i,9)->text();
                ui->tableWidget_startReiting->item(i,9)->setText(afterPoitsT.trimmed());
            }
            setRowsNumbering(ui->tableWidget_startReiting);
            ui->tableWidget_startReiting->resizeColumnsToContents();
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
    setRowsNumbering(ui->tableWidget_lastProtocol);
    ui->comboBox_category->clear();
    ui->comboBox_category->addItem("",QVariant::Int);
    ui->comboBox_category->addItem("Ч",QVariant::Int);
    ui->comboBox_category->addItem("Ж",QVariant::Int);

    bool flag = false;
    for (int i = 0; i < ui->tableWidget_startReiting->rowCount(); ++i) {
        for (int j = 0; j < ui->comboBox_category->count(); ++j) {
            if(ui->tableWidget_startReiting->item(i,7)->text().contains("(ПК)")){
                if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(ПК)").join("")){
                    flag=true;
                }
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(Б)")){
                if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(Б)").join("")){
                    flag=true;
                }
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(К)")){
                if(ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЧ(К)")
                        || ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЖ(К)")){
                    if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("Ч(К)").join("")){
                        flag=true;
                    }
                    else if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("Ж(К)").join("")){
                        flag=true;
                    }
                    else if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join("")){
                        flag=true;
                    }
                }
                else {
                    if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join("")){
                        flag=true;
                    }
                }
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(КБ)")){
                if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(КБ)").join("")){
                    flag=true;
                }
            }
            else if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text())
            {
                flag=true;
            }
        }
        if(!flag){
            if(ui->tableWidget_startReiting->item(i,7)->text().contains("(ПК)")){

                ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(ПК)").join(""),QVariant::Int);
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(К)")){
                if(ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЧ(К)")){

                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("Ч(К)").join(""),QVariant::Int);
                }
                else if(ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЖ(К)")){

                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("Ж(К)").join(""),QVariant::Int);
                }
                else {

                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join(""),QVariant::Int);
                }
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(Б)")){

                ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(Б)").join(""),QVariant::Int);
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(КБ)")){

                ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(КБ)").join(""),QVariant::Int);
            }
            else{

                ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text(),QVariant::Int);
            }
        }
        flag=false;
    }
    for (int i=0;i<ui->comboBox_category->count();i++) {
        if(ui->comboBox_category->itemText(i)==distance){
            ui->comboBox_category->setCurrentIndex(i);
            break;
        }
    }
}



void StartingProtocol::on_pushButton_addParticipant_clicked()
{

    ui->widget->setGeometry(ui->widget->x()-541,ui->widget->y(),541,471);
    ui->widget->show();
}



void StartingProtocol::on_pushButton_sortByYears_clicked()
{

    for (int i = 0; i < ui->tableWidget_lastProtocol->rowCount(); ++i) {
        ui->tableWidget_lastProtocol->setRowHidden(i,false);
    }
    QString summ="";
    ui->tableWidget_lastProtocol->resizeRowsToContents();
    QString beforePointT="";
    for (int i=0;i<ui->tableWidget_lastProtocol->rowCount();i++) {
        summ=ui->tableWidget_lastProtocol->item(i,9)->text();
        for (int k=0;k<6-ui->tableWidget_lastProtocol->item(i, 9)->text().length();k++) {
            beforePointT+=" ";
        }
        ui->tableWidget_lastProtocol->item(i,9)->setText(beforePointT+summ);
        beforePointT="";
    }

    ui->tableWidget_lastProtocol->sortByColumn(9,Qt::DescendingOrder);
    QString afterPoitsT="";
    for (int i=0;i<ui->tableWidget_lastProtocol->rowCount();i++) {
        afterPoitsT = ui->tableWidget_lastProtocol->item(i,9)->text();
        ui->tableWidget_lastProtocol->item(i,9)->setText(afterPoitsT.trimmed());
    }
    setRowsNumbering(ui->tableWidget_lastProtocol);
    ui->tableWidget_lastProtocol->resizeColumnsToContents();
}
int index=0;
void StartingProtocol::on_pushButton_OK_timeInput_clicked()
{
    if(ui->tab_startingProtocol->isVisible()){
        ui->tableWidget_startSwim->item(index,8)->setText(ui->lineEdit_inputTime->text());}
    ui->tableWidget_startSwim->resizeRowsToContents();
    ui->tableWidget_startSwim->resizeColumnsToContents();
    QFont font;
    font.setBold(false);
    ui->tableWidget_startSwim->item(index,1)->setFont(font);
    ui->pushButton_update->clicked(true);
    if(ui->tableWidget_startSwim->rowCount()-1!=index){
        if(ui->tableWidget_startSwim->item(index+1,1)->text()==""){
            index = index+2;
        }
        else index++;
        QTableWidgetItem * itemNext =  ui->tableWidget_startSwim->item(index,1);
        on_tableWidget_startSwim_itemPressed(itemNext);
    }


}

void StartingProtocol::on_tableWidget_startSwim_itemPressed(QTableWidgetItem *item)
{
    ui->lineEdit_inputTime->clear();
    ui->lineEdit_inputTime->setFocus();
    ui->lineEdit_nameForTime->setText(item->text());
    QFont font;
    font.setBold(false);
    for(int i=0;i<ui->tableWidget_startSwim->rowCount();i++){
        ui->tableWidget_startSwim->item(i,1)->setFont(font);
    }
    font.setBold(true);
    ui->tableWidget_startSwim->item(item->row(),1)->setFont(font);
    ui->tableWidget_startSwim->scrollToItem(item);
    index = item->row();
}

void StartingProtocol::on_pushButton_closeWidgetAddPerson_clicked()
{
    ui->widget->hide();
    ui->pushButton_addParticipant->clicked(true);
}



void StartingProtocol::on_pushButton_copyTableProtocol_clicked()
{
    QString selected_text_as_html;
    QString selected_text;
    QTableWidget *table = ui->tableWidget_lastProtocol;
    selected_text_as_html.prepend("<html><style>br{mso-data-placement:same-cell;}</style><table><tr><td>");
    for (int columnIndex = 0; columnIndex < 11; columnIndex++) {
        QString text = table->horizontalHeaderItem(columnIndex)->text();
        selected_text.append(text);
        text.replace("\n","<br>");
        selected_text_as_html.append(text);
        selected_text_as_html.append("</td><td>");
        selected_text.append(QLatin1Char('\t'));
    }
    selected_text_as_html.append("</td></tr><tr><td>");
    selected_text.append(QLatin1Char('\n'));

    for (int rowIndex = 0; rowIndex <table->rowCount(); rowIndex++) {
        if(ui->tableWidget_lastProtocol->item(rowIndex,8)->text()!=""
                && !ui->tableWidget_lastProtocol->isRowHidden(rowIndex)){
            for (int columnIndex = 0; columnIndex < 11; columnIndex++) {
                QString text = table->item(rowIndex,columnIndex)->text();
                selected_text.append(text);
                text.replace("\n","<br>");
                selected_text_as_html.append(text);
                selected_text_as_html.append("</td><td>");
                selected_text.append(QLatin1Char('\t'));
            }
            selected_text_as_html.append("</td></tr><tr><td>");
            selected_text.append(QLatin1Char('\n'));
        }
    }
    selected_text_as_html.append("</td></tr>");
    QMimeData * md = new QMimeData;
    md->setHtml(selected_text_as_html);
    qDebug() << selected_text;
    md->setText(selected_text);
    qApp->clipboard()->setMimeData(md);
}

void StartingProtocol::on_pushButton_DK_clicked()
{
    if(ui->tab_startingProtocol->isVisible()){
        ui->tableWidget_startSwim->item(index,8)->setText("ДК");
        ui->tableWidget_startSwim->item(index,8)->setBackgroundColor(Qt::white);
        //        ui->tableWidget_startSwim->item(index,9)->setText("-");
        //        ui->tableWidget_startSwim->item(index,10)->setText("-");
        QFont font;
        font.setBold(false);
        ui->tableWidget_startSwim->item(index,1)->setFont(font);
        if(ui->tableWidget_startSwim->rowCount()-1!=index){
            if(ui->tableWidget_startSwim->item(index+1,1)->text()==""){
                index = index+2;
            }
            else index++;
            QTableWidgetItem * itemNext =  ui->tableWidget_startSwim->item(index,1);
            on_tableWidget_startSwim_itemPressed(itemNext);
        }
    }
}

void StartingProtocol::on_comboBox_swimPool_currentTextChanged(const QString &arg1)
{
    ui->pushButton_update->clicked(true);
}

void StartingProtocol::on_pushButton_saveStartSwim_clicked()
{

}

//void StartingProtocol::on_comboBox_firstYear_currentTextChanged(const QString &arg1)
//{
//    if(arg1!=""){
//        ui->comboBox_secondYear->setEnabled(true);
//    }
//    else  {
//        ui->comboBox_fifthYear->setCurrentIndex(0);
//        ui->comboBox_secondYear->setCurrentIndex(0);
//        ui->comboBox_fourthYear->setCurrentIndex(0);
//        ui->comboBox_thirdYear->setCurrentIndex(0);
//        ui->comboBox_fifthYear->setEnabled(false);
//        ui->comboBox_secondYear->setEnabled(false);
//        ui->comboBox_fourthYear->setEnabled(false);
//        ui->comboBox_thirdYear->setEnabled(false);
//    }
//}

//void StartingProtocol::on_comboBox_secondYear_currentTextChanged(const QString &arg1)
//{
//    if(arg1!=""){
//        ui->comboBox_thirdYear->setEnabled(true);
//    }
//    else  {
//        ui->comboBox_fifthYear->setCurrentIndex(0);
//        ui->comboBox_fourthYear->setCurrentIndex(0);
//        ui->comboBox_thirdYear->setCurrentIndex(0);
//        ui->comboBox_thirdYear->setEnabled(false);
//        ui->comboBox_fourthYear->setEnabled(false);
//        ui->comboBox_fifthYear->setEnabled(false);
//    }
//}

//void StartingProtocol::on_comboBox_thirdYear_currentTextChanged(const QString &arg1)
//{
//    if(arg1!=""){
//        ui->comboBox_fourthYear->setEnabled(true);
//    }
//    else  {
//        ui->comboBox_fifthYear->setCurrentIndex(0);
//        ui->comboBox_fourthYear->setCurrentIndex(0);
//        ui->comboBox_fourthYear->setEnabled(false);
//        ui->comboBox_fifthYear->setEnabled(false);
//    }
//}

//void StartingProtocol::on_comboBox_fourthYear_currentTextChanged(const QString &arg1)
//{
//    if(arg1!=""){
//        ui->comboBox_fifthYear->setEnabled(true);
//    }
//    else  {
//        ui->comboBox_fifthYear->setCurrentIndex(0);
//        ui->comboBox_fifthYear->setEnabled(false);
//    }
//}

//void StartingProtocol::on_comboBox_fifthYear_currentTextChanged(const QString &arg1)
//{

//}



void StartingProtocol::on_pushButton_clicked()
{
    QString selected_text_as_html;
    QString selected_text;
    QTableWidget *table = ui->tableWidget_teams;
    selected_text_as_html.prepend("<html><style>br{mso-data-placement:same-cell;}</style><table><tr><td>");
    for (int columnIndex = 0; columnIndex < 10; columnIndex++) {
        QString text = table->horizontalHeaderItem(columnIndex)->text();
        selected_text.append(text);
        text.replace("\n","<br>");
        selected_text_as_html.append(text);
        selected_text_as_html.append("</td><td>");
        selected_text.append(QLatin1Char('\t'));
    }
    selected_text_as_html.append("</td></tr><tr><td>");
    selected_text.append(QLatin1Char('\n'));

    for (int rowIndex = 0; rowIndex <table->rowCount(); rowIndex++) {
        if(ui->tableWidget_teams->item(rowIndex,8)->text()!=""){
            for (int columnIndex = 0; columnIndex < 11; columnIndex++) {
                QString text = table->item(rowIndex,columnIndex)->text();
                selected_text.append(text);
                text.replace("\n","<br>");
                selected_text_as_html.append(text);
                selected_text_as_html.append("</td><td>");
                selected_text.append(QLatin1Char('\t'));
            }
            selected_text_as_html.append("</td></tr><tr><td>");
            selected_text.append(QLatin1Char('\n'));
        }
    }
    selected_text_as_html.append("</td></tr>");
    QMimeData * md = new QMimeData;
    md->setHtml(selected_text_as_html);
    qDebug() << selected_text;
    md->setText(selected_text);
    qApp->clipboard()->setMimeData(md);
}

void StartingProtocol::on_pushButton_copyManyFights_clicked()
{
    QString selected_text_as_html;
    QString selected_text;
    QTableWidget *table = ui->tableWidget_manyFights;
    selected_text_as_html.prepend("<html><style>br{mso-data-placement:same-cell;}</style><table><tr><td>");
    for (int columnIndex = 0; columnIndex < 11; columnIndex++) {
        QString text = table->horizontalHeaderItem(columnIndex)->text();
        selected_text.append(text);
        text.replace("\n","<br>");
        selected_text_as_html.append(text);
        selected_text_as_html.append("</td><td>");
        selected_text.append(QLatin1Char('\t'));
    }
    selected_text_as_html.append("</td></tr><tr><td>");
    selected_text.append(QLatin1Char('\n'));

    for (int rowIndex = 0; rowIndex <table->rowCount(); rowIndex++) {
        if(ui->tableWidget_manyFights->item(rowIndex,8)->text()!="" &&
                !ui->tableWidget_manyFights->isRowHidden(rowIndex)){
            for (int columnIndex = 0; columnIndex < 11; columnIndex++) {
                QString text = table->item(rowIndex,columnIndex)->text();
                selected_text.append(text);
                text.replace("\n","<br>");
                selected_text_as_html.append(text);
                selected_text_as_html.append("</td><td>");
                selected_text.append(QLatin1Char('\t'));
            }
            selected_text_as_html.append("</td></tr><tr><td>");
            selected_text.append(QLatin1Char('\n'));
        }
    }
    selected_text_as_html.append("</td></tr>");
    QMimeData * md = new QMimeData;
    md->setHtml(selected_text_as_html);
    qDebug() << selected_text;
    md->setText(selected_text);
    qApp->clipboard()->setMimeData(md);
}

void StartingProtocol::on_pushButton_clearTableTeams_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Очистити таблицю?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Ok)
    {
        ui->tableWidget_teams->clearContents();
        ui->tableWidget_teams->setRowCount(0);
    }
    else
        msgBox.close();
}

void StartingProtocol::on_pushButton_goToManyFights_clicked()
{
    int summOfPoints=0;
    bool flag1 = false;
    int countPeopleManyFights=0;
    int flagCountMF=false;
    for (int i = 0; i < ui->tableWidget_lastProtocol->rowCount(); i++) {
        if(ui->tableWidget_lastProtocol->item(i,6)->text().contains("Б)")){
            for (int j=0;j<ui->tableWidget_manyFights->rowCount();j++) {
                if(ui->tableWidget_manyFights->item(j,1)->text().contains(ui->tableWidget_lastProtocol->item(i,1)->text())
                        && ui->tableWidget_manyFights->item(j,2)->text().contains(ui->tableWidget_lastProtocol->item(i,2)->text())){
                    flagCountMF=true;break;
                }
            }
            if(!flagCountMF){
                countPeopleManyFights++;
            }
        }
        flagCountMF=false;
    }

    int previousRowCountMF=ui->tableWidget_manyFights->rowCount();
    int tableRowMF = ui->tableWidget_manyFights->rowCount();
    int tableColumnMF = 0;
    bool flagMF = false;
    QString distanceMF,resultMF,pointsMF;


    ui->tableWidget_manyFights->setRowCount(countPeopleManyFights+previousRowCountMF);
    for (int i=previousRowCountMF;i<ui->tableWidget_manyFights->rowCount();i++) {
        for (int j=0 ;j<11;j++) {
            ui->tableWidget_manyFights->setItem(i,j,new QTableWidgetItem);
        }
    }

    for (int i=0;i<ui->tableWidget_lastProtocol->rowCount();i++) {

        if(ui->tableWidget_lastProtocol->item(i,6)->text().contains("Б)")){
            for (int j=0;j<ui->tableWidget_manyFights->rowCount();j++) {
                if(ui->tableWidget_manyFights->item(j,1)->text().contains(ui->tableWidget_lastProtocol->item(i,1)->text())){
                    flagMF=true;
                    if(!ui->tableWidget_manyFights->item(j,6)->text().contains(ui->tableWidget_lastProtocol->item(i,6)->text())){
                        distanceMF=ui->tableWidget_manyFights->item(j,6)->text();
                        resultMF=ui->tableWidget_manyFights->item(j,7)->text();
                        pointsMF=ui->tableWidget_manyFights->item(j,8)->text();
                        summOfPoints=ui->tableWidget_manyFights->item(j,9)->text().toInt();
                        ui->tableWidget_manyFights->item(j,6)->setText(distanceMF+'\n'+ui->tableWidget_lastProtocol->item(i,6)->text());
                        ui->tableWidget_manyFights->item(j,7)->setText(resultMF+'\n'+ui->tableWidget_lastProtocol->item(i,7)->text());
                        ui->tableWidget_manyFights->item(j,8)->setText(pointsMF+'\n'+ui->tableWidget_lastProtocol->item(i,9)->text());
                        ui->tableWidget_manyFights->item(j,9)->setText(QString::number(summOfPoints+ui->tableWidget_lastProtocol->item(i,9)->text().toInt()));
                        break;
                    }
                }
            }
            if(!flagMF){
                for (int j=0;j<11;j++) {
                    if(j==8){
                        ui->tableWidget_manyFights->item(tableRowMF,8)->setText(ui->tableWidget_lastProtocol->item(i,9)->text());
                        continue;
                    }

                    ui->tableWidget_manyFights->item(tableRowMF,j)->setText(ui->tableWidget_lastProtocol->item(i,j)->text());
                }

                tableRowMF++;
            }
        }
        flagMF=false;

    }
    //    for (int i = ui->tableWidget_manyFights->rowCount()-1;i!=-1;i--) {
    //        if(ui->tableWidget_manyFights->item(i,1)->text()==""){
    //            ui->tableWidget_manyFights->removeRow(i);
    //        }
    //    }
    //    for (int i = 0; i < ui->tableWidget_lastProtocol->rowCount(); ++i) {
    //        for (int j = 0; j < ui->comboBox_firstYearM->count(); ++j) {
    //            if(ui->comboBox_firstYearM->itemText(j)==ui->tableWidget_lastProtocol->item(i,2)->text()){
    //                flag1=true;
    //            }
    //        }
    //        if(!flag1){
    //            ui->comboBox_firstYearM->addItem(ui->tableWidget_lastProtocol->item(i,2)->text(),QVariant::Int);
    //            ui->comboBox_secondYearM->addItem(ui->tableWidget_lastProtocol->item(i,2)->text(),QVariant::Int);
    //            ui->comboBox_thirdYearM->addItem(ui->tableWidget_lastProtocol->item(i,2)->text(),QVariant::Int);
    //            ui->comboBox_fourthYearM->addItem(ui->tableWidget_lastProtocol->item(i,2)->text(),QVariant::Int);
    //            ui->comboBox_fifthYearM->addItem(ui->tableWidget_lastProtocol->item(i,2)->text(),QVariant::Int);
    //        }
    //        flag1=false;
    //    }
    bool flag2 = false;

    for (int i = 0; i < ui->tableWidget_manyFights->rowCount(); i++) {
        for (int j = 0;j<ui->comboBox_sortYear_3->count();j++) {
            if(ui->comboBox_sortYear_3->itemText(j)==ui->tableWidget_manyFights->item(i,2)->text().mid(0,4)){
                flag2=true;
            }
        }
        if(!flag2)
            ui->comboBox_sortYear_3->addItem(ui->tableWidget_manyFights->item(i,2)->text().mid(0,4),QVariant::Int);
        flag2=false;
    }
    setRowsNumbering(ui->tableWidget_manyFights);
    ui->tableWidget_manyFights->resizeRowsToContents();


    QString fr = "User\\Bagatoborstvo.mf";
    QFile file(fr);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        qint32 row(ui->tableWidget_manyFights->rowCount()), column(ui->tableWidget_manyFights->columnCount());
        stream << row << column;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; j++){
                ui->tableWidget_manyFights->item(i,j)->write(stream);}
        file.close();
    }
    bool flagMFUser = false;
    if (file.open(QIODevice::ReadOnly))
    {
        for (int i=0;i<ui->comboBox_protocolFiles->count();i++) {
            if(ui->comboBox_protocolFiles->itemText(i).contains(file.fileName())){
                flagMFUser=true;
            }
        }
        if(!flagMFUser) ui->comboBox_protocolFiles->addItem(file.fileName() ,QVariant::Int);
        file.close();
        ui->tableWidget_lastProtocol->verticalHeader()->hide();
    }
    QString summ="";
    ui->tableWidget_manyFights->resizeRowsToContents();
    QString beforePointT="";
    for (int i=0;i<ui->tableWidget_manyFights->rowCount();i++) {
        summ=ui->tableWidget_manyFights->item(i,9)->text();
        for (int k=0;k<6-ui->tableWidget_manyFights->item(i, 9)->text().length();k++) {
            beforePointT+=" ";
        }
        ui->tableWidget_manyFights->item(i,9)->setText(beforePointT+summ);
        beforePointT="";
    }

    ui->tableWidget_manyFights->sortByColumn(9,Qt::DescendingOrder);
    QString afterPoitsT="";
    for (int i=0;i<ui->tableWidget_manyFights->rowCount();i++) {
        afterPoitsT = ui->tableWidget_manyFights->item(i,9)->text();
        ui->tableWidget_manyFights->item(i,9)->setText(afterPoitsT.trimmed());
    }
    setRowsNumbering(ui->tableWidget_manyFights);
    ui->comboBox_sortYear_3->model()->sort(Qt::AscendingOrder);
    ui->tableWidget_manyFights->resizeColumnsToContents();
}

void StartingProtocol::on_pushButton_goToTeams_clicked()
{

    int summOfPoints=0;
    bool flagTeams = false;
    int countPeopleTeams=0;
    bool flagCountTeams=false;
    int symb1 = 0;
    int symb2 =0;
    QString team="";
    bool repeatTeammate=false;
    for (int i = 0; i < ui->tableWidget_lastProtocol->rowCount(); i++) {
        symb1 = ui->tableWidget_lastProtocol->item(i,5)->text().indexOf("(");
        symb2 = ui->tableWidget_lastProtocol->item(i,5)->text().indexOf(")",symb1);
        team = ui->tableWidget_lastProtocol->item(i,5)->text().mid(symb1+1, symb2-symb1-1);
        if(ui->tableWidget_lastProtocol->item(i,6)->text().contains("(К)") ||
                ui->tableWidget_lastProtocol->item(i,6)->text().contains("(КБ)")){
            for (int j=0;j<ui->tableWidget_teams->rowCount();j++) {
                if(ui->tableWidget_teams->item(j,2)->text().contains(ui->tableWidget_lastProtocol->item(i,1)->text())
                        && ui->tableWidget_teams->item(j,7)->text().contains("("+team+")")){
                    flagCountTeams=true;
                }
            }
            if(!flagCountTeams){
                countPeopleTeams++;
            }
        }
        flagCountTeams=false;
    }

    int previousRowCountTeams=ui->tableWidget_teams->rowCount();
    int tableRowTeams = ui->tableWidget_teams->rowCount();

    bool flagTeams1 = false;
    QString distanceTeams,resultTeams,pointsTeams, nameTeams, yearBR, schoolTeams;


    ui->tableWidget_teams->setRowCount(countPeopleTeams+previousRowCountTeams);
    for (int i=previousRowCountTeams;i<countPeopleTeams+previousRowCountTeams;i++) {
        for (int j=0 ;j<11;j++) {
            ui->tableWidget_teams->setItem(i,j,new QTableWidgetItem);
        }
    }

    for (int i=0;i<ui->tableWidget_lastProtocol->rowCount();i++) {
        symb1 = ui->tableWidget_lastProtocol->item(i,5)->text().indexOf("(");
        symb2 = ui->tableWidget_lastProtocol->item(i,5)->text().indexOf(")",symb1);
        team = ui->tableWidget_lastProtocol->item(i,5)->text().mid(symb1+1, symb2-symb1-1);
        if(ui->tableWidget_lastProtocol->item(i,6)->text().contains("(К")){
            for (int j=0;j<ui->tableWidget_teams->rowCount();j++) {

                if(ui->tableWidget_teams->item(j,2)->text().contains(ui->tableWidget_lastProtocol->item(i,1)->text()) &&
                        ui->tableWidget_teams->item(j,7)->text().contains(ui->tableWidget_lastProtocol->item(i,6)->text()) &&
                        ui->tableWidget_teams->item(j,8)->text().contains(ui->tableWidget_lastProtocol->item(i,7)->text())){repeatTeammate = true;continue;}
                if(ui->tableWidget_teams->item(j,1)->text()!=""&& ui->tableWidget_teams->item(j,1)->text()==team){
                    flagTeams1=true;
                    distanceTeams=ui->tableWidget_teams->item(j,7)->text();
                    resultTeams=ui->tableWidget_teams->item(j,8)->text();
                    pointsTeams=ui->tableWidget_teams->item(j,9)->text();
                    nameTeams=ui->tableWidget_teams->item(j,2)->text();
                    yearBR = ui->tableWidget_teams->item(j,3)->text();
                    summOfPoints=ui->tableWidget_teams->item(j,10)->text().toInt();
                    schoolTeams=ui->tableWidget_teams->item(j,6)->text();
                    ui->tableWidget_teams->item(j,6)->setText(schoolTeams+'\n'+ui->tableWidget_lastProtocol->item(i,5)->text());
                    ui->tableWidget_teams->item(j,7)->setText(distanceTeams+'\n'+ui->tableWidget_lastProtocol->item(i,6)->text());
                    ui->tableWidget_teams->item(j,3)->setText(yearBR+'\n'+ui->tableWidget_lastProtocol->item(i,2)->text());
                    ui->tableWidget_teams->item(j,8)->setText(resultTeams+'\n'+ui->tableWidget_lastProtocol->item(i,7)->text());
                    ui->tableWidget_teams->item(j,9)->setText(pointsTeams+'\n'+ui->tableWidget_lastProtocol->item(i,9)->text());
                    ui->tableWidget_teams->item(j,10)->setText(QString::number(summOfPoints+ui->tableWidget_lastProtocol->item(i,9)->text().toInt()));
                    ui->tableWidget_teams->item(j,2)->setText(nameTeams+'\n'+ui->tableWidget_lastProtocol->item(i,1)->text());
                    break;
                }
            }
            if(!flagTeams1 && !repeatTeammate){
                for (int j=1;j<11;j++) {
                    if(j==10){
                        ui->tableWidget_teams->item(tableRowTeams,10)->setText(ui->tableWidget_lastProtocol->item(i,9)->text());
                        continue;
                    }
                    if(j==1){
                        ui->tableWidget_teams->item(tableRowTeams,1)->setText(ui->tableWidget_lastProtocol->item(i,5)->text().mid(symb1+1, symb2-symb1-1));
                        continue;
                    }
                    if(j==9){
                        ui->tableWidget_teams->item(tableRowTeams,9)->setText(ui->tableWidget_lastProtocol->item(i,9)->text());
                        continue;
                    }
                    ui->tableWidget_teams->item(tableRowTeams,j)->setText(ui->tableWidget_lastProtocol->item(i,j-1)->text());
                }

                tableRowTeams++;
            }
        }
        repeatTeammate=false;
        flagTeams1=false;

    }
    for (int i = ui->tableWidget_teams->rowCount()-1;i!=-1;i--) {
        if(ui->tableWidget_teams->item(i,1)->text()==""){
            ui->tableWidget_teams->removeRow(i);
        }
    }
    QString summ="";
    ui->tableWidget_teams->resizeRowsToContents();
    QString beforePointT="";
    for (int i=0;i<ui->tableWidget_teams->rowCount();i++) {
        summ=ui->tableWidget_teams->item(i,10)->text();
        for (int k=0;k<6-ui->tableWidget_teams->item(i, 10)->text().length();k++) {
            beforePointT+=" ";
        }
        ui->tableWidget_teams->item(i,10)->setText(beforePointT+summ);
        beforePointT="";
    }

    ui->tableWidget_teams->sortByColumn(10,Qt::DescendingOrder);
    QString afterPoitsT="";
    for (int i=0;i<ui->tableWidget_teams->rowCount();i++) {
        afterPoitsT = ui->tableWidget_teams->item(i,10)->text();
        ui->tableWidget_teams->item(i,10)->setText(afterPoitsT.trimmed());
    }
    setRowsNumbering(ui->tableWidget_teams);


    QString fr = "User\\Teams.tm";
    QFile file(fr);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        qint32 row(ui->tableWidget_teams->rowCount()), column(ui->tableWidget_teams->columnCount());
        stream << row << column;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; j++){
                ui->tableWidget_teams->item(i,j)->write(stream);}
        file.close();
    }
    bool flagTeam=false;
    if (file.open(QIODevice::ReadOnly))
    {
        for (int i=0;i<ui->comboBox_protocolFiles->count();i++) {
            if(ui->comboBox_protocolFiles->itemText(i).contains(file.fileName())){
                flagTeam=true;
            }
        }
        if(!flagTeam) ui->comboBox_protocolFiles->addItem(file.fileName() ,QVariant::Int);
        file.close();
        ui->tableWidget_lastProtocol->verticalHeader()->hide();
    }



}

void StartingProtocol::on_pushButton_openFileFights_clicked()
{
    QStringList fileName = QFileDialog::getOpenFileNames(this,
                                                    tr("Open"), "",
                                                    tr("(*prot);;(*.mf);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else
    {
        for(int i=0; i<fileName.count();i++){
            QFile file(fileName[i]);
            if(fileName[i].contains(".mf")){
                if (file.open(QIODevice::ReadOnly))
                {
                    QDataStream stream(&file);
                    qint32 row, column;
                    stream >> row >> column;
                    int countRow = ui->tableWidget_manyFights->rowCount();
                    ui->tableWidget_manyFights->setRowCount(row+countRow);
                    ui->tableWidget_manyFights->setColumnCount(11);

                    for (int i = countRow; i < row+countRow; ++i){
                        for (int j = 0; j < 11; j++)
                        {

                            ui->tableWidget_manyFights->setItem(i,j,new QTableWidgetItem);
                            ui->tableWidget_manyFights->item(i,j)->read(stream);
                        }
                    }
                    file.close();
                    ui->tableWidget_manyFights->verticalHeader()->hide();
                }
            }
            else if(fileName[i].contains(".prot")){
                ui->tableWidget_lastProtocol->clearContents();
                ui->tableWidget_lastProtocol->setRowCount(0);
                if (file.open(QIODevice::ReadOnly))
                {
                    QDataStream stream(&file);
                    qint32 row, column;
                    stream >> row >> column;
                    int countRow = ui->tableWidget_lastProtocol->rowCount();
                    ui->tableWidget_lastProtocol->setRowCount(row+countRow);
                    ui->tableWidget_lastProtocol->setColumnCount(column);

                    for (int i = countRow; i < row+countRow; ++i){
                        for (int j = 0; j < 11; j++)
                        {

                            ui->tableWidget_lastProtocol->setItem(i,j,new QTableWidgetItem);
                            ui->tableWidget_lastProtocol->item(i,j)->read(stream);
                        }
                    }
                    file.close();
                    ui->tableWidget_lastProtocol->verticalHeader()->hide();
                }
                ui->pushButton_goToManyFights->clicked(true);
            }
        }
        ui->pushButton_openFileProtocol->clicked(true);
    }
    bool flag2 = false;

    for (int i = 0; i < ui->tableWidget_manyFights->rowCount(); i++) {
        for (int j = 0;j<ui->comboBox_sortYear_3->count();j++) {
            if(ui->comboBox_sortYear_3->itemText(j)==ui->tableWidget_manyFights->item(i,2)->text().mid(0,4)){
                flag2=true;
            }
        }
        if(!flag2)
            ui->comboBox_sortYear_3->addItem(ui->tableWidget_manyFights->item(i,2)->text().mid(0,4),QVariant::Int);
        flag2=false;
    }
    ui->comboBox_sortYear_3->model()->sort(Qt::AscendingOrder);
    setRowsNumbering(ui->tableWidget_manyFights);
    ui->tableWidget_manyFights->resizeRowsToContents();
}

void StartingProtocol::on_pushButton_saveFileFights_clicked()
{
    QString fr = QFileDialog::getSaveFileName(this,tr("Save"),"c:/",tr("(*.mf)"));
    QFile file(fr);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        qint32 row(ui->tableWidget_manyFights->rowCount()), column(ui->tableWidget_manyFights->columnCount());
        stream << row << column;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; j++){
                ui->tableWidget_manyFights->item(i,j)->write(stream);}
        file.close();
    }
}
static int count3=0;
void StartingProtocol::on_pushButton_saveFileTeam_clicked()
{
    QString fr = QFileDialog::getSaveFileName(this,tr("Save"),"c:/",tr("(*.tm)"));
    QFile file(fr);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        qint32 row(ui->tableWidget_teams->rowCount()), column(ui->tableWidget_teams->columnCount());
        stream << row << column;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; j++){
                ui->tableWidget_teams->item(i,j)->write(stream);}
        file.close();
    }



}

void StartingProtocol::on_pushButton_openFileTeam_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open"), "",
                                                    tr("(*.tm);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream stream(&file);
            qint32 row, column;
            stream >> row >> column;
            int countRow = ui->tableWidget_teams->rowCount();
            ui->tableWidget_teams->setRowCount(row+countRow);
            ui->tableWidget_teams->setColumnCount(column);

            for (int i = countRow; i < row+countRow; ++i){
                count3++;
                ui->tableWidget_teams->setItem(i,0, new QTableWidgetItem);
                ui->tableWidget_teams->item(i,0)->setText(QString::number(count3));

                for (int j = 0; j < 11; j++)
                {

                    ui->tableWidget_teams->setItem(i,j,new QTableWidgetItem);
                    ui->tableWidget_teams->item(i,j)->read(stream);
                }
            }
            file.close();
            ui->tableWidget_teams->verticalHeader()->hide();
        }
    }
}


void StartingProtocol::on_pushButton_openFileProtocol_clicked()
{
    ui->tableWidget_lastProtocol->clearContents();
    ui->tableWidget_lastProtocol->setRowCount(0);
    QString fileName = ui->comboBox_protocolFiles->currentText();
    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        QFileInfo fileInfo(file.fileName());
        QString filename(fileInfo.fileName());
        ui->lineEdit_styleProtocol->setText(filename.remove(".prot").remove(".tm").remove(".mf").remove("User\\"));
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream stream(&file);
            qint32 row, column;
            stream >> row >> column;
            int countRow = ui->tableWidget_lastProtocol->rowCount();
            ui->tableWidget_lastProtocol->setRowCount(row+countRow);
            ui->tableWidget_lastProtocol->setColumnCount(column);

            for (int i = countRow; i < row+countRow; ++i){
                for (int j = 0; j < 11; j++)
                {

                    ui->tableWidget_lastProtocol->setItem(i,j,new QTableWidgetItem);
                    ui->tableWidget_lastProtocol->item(i,j)->read(stream);
                }
            }
            file.close();
            ui->tableWidget_lastProtocol->verticalHeader()->hide();
        }
    }
    //    bool flag1 = false;
    //    for (int i = 0; i < ui->tableWidget_lastProtocol->rowCount(); ++i) {
    //        for (int j = 0; j < ui->comboBox_firstYear->count(); ++j) {
    //            if(ui->comboBox_firstYear->itemText(j)==ui->tableWidget_lastProtocol->item(i,2)->text()){
    //                flag1=true;
    //            }
    //        }
    //        if(!flag1){
    //            ui->comboBox_firstYear->addItem(ui->tableWidget_lastProtocol->item(i,2)->text(),QVariant::Int);
    //            ui->comboBox_secondYear->addItem(ui->tableWidget_lastProtocol->item(i,2)->text(),QVariant::Int);
    //            ui->comboBox_thirdYear->addItem(ui->tableWidget_lastProtocol->item(i,2)->text(),QVariant::Int);
    //            ui->comboBox_fourthYear->addItem(ui->tableWidget_lastProtocol->item(i,2)->text(),QVariant::Int);
    //            ui->comboBox_fifthYear->addItem(ui->tableWidget_lastProtocol->item(i,2)->text(),QVariant::Int);
    //        }
    //        flag1=false;
    //    }
    bool flag2 = false;

    for (int i = 0; i < ui->tableWidget_lastProtocol->rowCount(); i++) {
        for (int j = 0;j<ui->comboBox_sortYear->count();j++) {
            if(ui->comboBox_sortYear->itemText(j)==ui->tableWidget_lastProtocol->item(i,2)->text().mid(0,4)){
                flag2=true;
            }
        }
        if(!flag2)
            ui->comboBox_sortYear->addItem(ui->tableWidget_lastProtocol->item(i,2)->text().mid(0,4),QVariant::Int);
        flag2=false;
    }
    QString summ="";
    ui->tableWidget_lastProtocol->resizeRowsToContents();
    QString beforePointT="";
    for (int i=0;i<ui->tableWidget_lastProtocol->rowCount();i++) {
        summ=ui->tableWidget_lastProtocol->item(i,9)->text();
        for (int k=0;k<6-ui->tableWidget_lastProtocol->item(i, 9)->text().length();k++) {
            beforePointT+=" ";
        }
        ui->tableWidget_lastProtocol->item(i,9)->setText(beforePointT+summ);
        beforePointT="";
    }

    ui->tableWidget_lastProtocol->sortByColumn(9,Qt::DescendingOrder);
    QString afterPoitsT="";
    for (int i=0;i<ui->tableWidget_lastProtocol->rowCount();i++) {
        afterPoitsT = ui->tableWidget_lastProtocol->item(i,9)->text();
        ui->tableWidget_lastProtocol->item(i,9)->setText(afterPoitsT.trimmed());
    }
    ui->comboBox_sortYear->model()->sort(Qt::AscendingOrder);
    setRowsNumbering(ui->tableWidget_lastProtocol);
}

void StartingProtocol::on_pushButton_cleanFightTable_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Очистити таблицю?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Ok)
    {
        ui->tableWidget_manyFights->clearContents();
        ui->tableWidget_manyFights->setRowCount(0);
    }
    else
        msgBox.close();
}

void StartingProtocol::on_pushButton_cleanProtocol_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Очистити таблицю?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Ok)
    {
        ui->tableWidget_lastProtocol->clearContents();
        ui->tableWidget_lastProtocol->setRowCount(0);
    }
    else
        msgBox.close();
}

void StartingProtocol::on_pushButton_copyStartProtocolEstafet_clicked()
{

}

void StartingProtocol::on_comboBox_protocolFiles_currentIndexChanged(const QString &arg1)
{
    ui->pushButton_openFileProtocol->clicked(true);
}

int index1=0;
void StartingProtocol::on_pushButton_OK_timeInput_2_clicked()
{

    if(ui->tab_3->isVisible()){
        ui->tableWidget_startSwim_2->item(index1,8)->setText(ui->lineEdit_firstSportsmen->text()+'\n'+ui->lineEdit_inputTime_2->text());
    }
    ui->tableWidget_startSwim_2->resizeRowsToContents();
    ui->tableWidget_startSwim_2->resizeColumnsToContents();

    ui->pushButton_update_2->clicked(true);
    QFont font;
    font.setBold(false);
    ui->tableWidget_startSwim_2->item(index1,1)->setFont(font);
    if(ui->tableWidget_startSwim_2->rowCount()-1!=index1){
        if(ui->tableWidget_startSwim_2->item(index1+1,1)->text()==""){
            index1 = index1+2;
        }
        else index1++;
        QTableWidgetItem * itemNext =  ui->tableWidget_startSwim_2->item(index1,1);
        on_tableWidget_startSwim_2_itemPressed(itemNext);
    }
}

void StartingProtocol::on_pushButton_DK_2_clicked()
{
    if(ui->tab_3->isVisible()){
        ui->tableWidget_startSwim_2->item(index1,8)->setText(ui->lineEdit_firstSportsmen->text()+'\n'+"ДК");
        ui->pushButton_update_2->clicked(true);
        ui->tableWidget_startSwim_2->item(index1,10)->setText("-");
        ui->pushButton_update_2->clicked(true);
        QFont font;
        font.setBold(false);
        ui->tableWidget_startSwim_2->item(index1,1)->setFont(font);
        if(ui->tableWidget_startSwim_2->rowCount()-1!=index1){
            if(ui->tableWidget_startSwim_2->item(index1+1,1)->text()==""){
                index1 = index1+2;
            }
            else index1++;
            QTableWidgetItem * itemNext =  ui->tableWidget_startSwim_2->item(index1,1);
            on_tableWidget_startSwim_2_itemPressed(itemNext);
        }
    }
}

void StartingProtocol::on_pushButton_cleanProtocol_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Очистити таблицю?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Ok)
    {
        ui->tableWidget_lastProtocol_2->clearContents();
        ui->tableWidget_lastProtocol_2->setRowCount(0);
    }
    else
        msgBox.close();
}

void StartingProtocol::on_pushButton_createNewReiting_2_clicked()
{
    if(!ui->tableWidget_startSwim_2->item(1,7)->text().contains(ui->lineEdit_styleProtocol_2->text())){
        ui->tableWidget_lastProtocol_2->clearContents();
        ui->tableWidget_lastProtocol_2->setRowCount(0);
    }


    ui->lineEdit_styleProtocol_2->setText(ui->tableWidget_startSwim_2->item(1,7)->text().split("(К)").join(""));
    ui->comboBox_protocolFiles_2->setCurrentText("Estafeta/"+ui->lineEdit_styleProtocol->text()+".prot");
    int countUpdatedPeople=0;


    bool flagRepeatPerson =false;
    for (int i=0;i<ui->tableWidget_startSwim_2->rowCount();i++) {
        if(ui->tableWidget_startSwim_2->item(i,8)->text()!=""
                && ui->tableWidget_startSwim_2->item(i,9)->text()!=""
                && ui->tableWidget_startSwim_2->item(i,10)->text()!=""){
            countUpdatedPeople++;
            flagRepeatPerson = true;
        }
        for (int j=0;j<ui->tableWidget_lastProtocol_2->rowCount();j++) {
            if(ui->tableWidget_lastProtocol_2->item(j,1)->text().contains(ui->tableWidget_startSwim_2->item(i,1)->text())
                    && ui->tableWidget_lastProtocol_2->item(j,6)->text().contains(ui->tableWidget_startSwim_2->item(i,7)->text())
                    && ui->tableWidget_lastProtocol_2->item(j,2)->text().contains(ui->tableWidget_startSwim_2->item(i,2)->text())
                    && ui->tableWidget_lastProtocol_2->item(j,5)->text().contains(ui->tableWidget_startSwim_2->item(i,6)->text())
                    && flagRepeatPerson){
                ui->tableWidget_lastProtocol_2->removeRow(j);
                break;
            }
        }
        flagRepeatPerson=false;
    }
    int previousCountPeople = ui->tableWidget_lastProtocol_2->rowCount();
    int tableRow = ui->tableWidget_lastProtocol_2->rowCount();
    QString beforePoints="";
    ui->tableWidget_lastProtocol_2->setRowCount(countUpdatedPeople+previousCountPeople);

    int tableColumn = -1;
    bool flag = false;
    for(int i=0;i < ui->tableWidget_startSwim_2->rowCount();i++){
        for(int j = 1; j < 12; j++){
            if(ui->tableWidget_startSwim_2->item(i,j)->text()==""){
                flag = true;
                break;
            }
        }
        for(int j = 0; j < 11;j++){
            if(flag)break;
            ui->tableWidget_lastProtocol_2->setItem(tableRow,j, new QTableWidgetItem);
        }
        for(int j = 0;j<11;j++){
            if(flag){break;}
            tableColumn++;
            if(tableColumn==3) {
                tableColumn++;
            }
            if(j==9){
                for (int k=0;k<6-ui->tableWidget_startSwim_2->item(i, tableColumn)->text().length();k++) {
                    beforePoints+=" ";
                }
            }
            ui->tableWidget_lastProtocol_2->item(tableRow,j)->setText(beforePoints+ui->tableWidget_startSwim_2->item(i, tableColumn)->text());
            beforePoints="";
        }
        if(!flag) tableRow++;
        tableColumn = -1;
        flag= false;
    }
    ui->tableWidget_lastProtocol_2->sortByColumn(7,Qt::AscendingOrder);
    ui->tableWidget_lastProtocol_2->sortByColumn(9,Qt::DescendingOrder);
    QString afterPoits="";
    for (int i=0;i<ui->tableWidget_lastProtocol_2->rowCount();i++) {
        afterPoits = ui->tableWidget_lastProtocol_2->item(i,9)->text();
        ui->tableWidget_lastProtocol_2->item(i,9)->setText(afterPoits.trimmed());
    }
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    bool flag4 = false;

    for (int i = 0; i < ui->tableWidget_lastProtocol_2->rowCount(); i++) {
        for (int j = 0;j<ui->comboBox_sortYear_2->count();j++) {
            if(ui->comboBox_sortYear_2->itemText(j)==ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(0,4)){
                flag1=true;
            }
        }
        if(!flag1)
            ui->comboBox_sortYear_2->addItem(ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(0,4),QVariant::Int);
        for (int j = 0;j<ui->comboBox_sortYear_2->count();j++) {
            if(ui->comboBox_sortYear_2->itemText(j)==ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(5,4)){
                flag2=true;
            }
        }
        if(!flag2)
            ui->comboBox_sortYear_2->addItem(ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(5,4),QVariant::Int);
        for (int j = 0;j<ui->comboBox_sortYear_2->count();j++) {
            if(ui->comboBox_sortYear_2->itemText(j)==ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(10,4)){
                flag3=true;
            }
        }
        if(!flag3)
            ui->comboBox_sortYear_2->addItem(ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(10,4),QVariant::Int);
        for (int j = 0;j<ui->comboBox_sortYear_2->count();j++) {
            if(ui->comboBox_sortYear_2->itemText(j)==ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(15,4)){
                flag4=true;
            }
        }
        if(!flag4)
            ui->comboBox_sortYear_2->addItem(ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(15,4),QVariant::Int);
        flag1=false;
        flag2=false;
        flag3=false;
        flag4=false;
    }
    ui->comboBox_sortYear_2->model()->sort(Qt::AscendingOrder);
    setRowsNumbering(ui->tableWidget_lastProtocol_2);
    QString fr = "Estafeta\\"+ui->lineEdit_styleProtocol_2->text()+".prot";
    QFile file(fr);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        qint32 row(ui->tableWidget_lastProtocol_2->rowCount()), column(ui->tableWidget_lastProtocol_2->columnCount());
        stream << row << column;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; j++){
                ui->tableWidget_lastProtocol_2->item(i,j)->write(stream);}
        file.close();
    }

    ui->comboBox_protocolFiles_2->clear();
    QDirIterator iTR("Estafeta/", QDir::Files);

    while(iTR.hasNext()){
        QFile file(iTR.next());
        if (file.open(QIODevice::ReadOnly))
        {
            ui->comboBox_protocolFiles_2->addItem(file.fileName() ,QVariant::Int);
            file.close();
            ui->tableWidget_lastProtocol_2->verticalHeader()->hide();
        }
    }
    QString summ="";
    QString beforePointT="";
    for (int i=0;i<ui->tableWidget_lastProtocol_2->rowCount();i++) {
        summ=ui->tableWidget_lastProtocol_2->item(i,9)->text();
        for (int k=0;k<6-ui->tableWidget_lastProtocol_2->item(i, 9)->text().length();k++) {
            beforePointT+=" ";
        }
        ui->tableWidget_lastProtocol_2->item(i,9)->setText(beforePointT+summ);
        beforePointT="";
    }

    ui->tableWidget_lastProtocol_2->sortByColumn(9,Qt::DescendingOrder);
    QString afterPoitsT="";
    for (int i=0;i<ui->tableWidget_lastProtocol_2->rowCount();i++) {
        afterPoitsT = ui->tableWidget_lastProtocol_2->item(i,9)->text();
        ui->tableWidget_lastProtocol_2->item(i,9)->setText(afterPoitsT.trimmed());
    }
    setRowsNumbering(ui->tableWidget_lastProtocol_2);

    ui->tableWidget_lastProtocol_2->resizeRowsToContents();
    ui->tableWidget_lastProtocol_2->resizeColumnsToContents();
    //    ui->pushButton_updateByYears_2->clicked(true);
}

void StartingProtocol::on_pushButton_copyTableSwim_2_clicked()
{
    QString selected_text_as_html;
    QString selected_text;
    QTableWidget *table = ui->tableWidget_startSwim_2;
    selected_text_as_html.prepend("<html><style>br{mso-data-placement:same-cell;}</style><table><tr><td>");

    for (int rowIndex = 0; rowIndex <table->rowCount(); rowIndex++) {
        if(!ui->tableWidget_startSwim_2->isRowHidden(rowIndex)){
            for (int columnIndex = 0; columnIndex < 12; columnIndex++) {

                if(columnIndex==7)continue;
                QString text = table->item(rowIndex,columnIndex)->text();
                selected_text.append(text);
                text.replace("\n","<br>");
                selected_text_as_html.append(text);
                selected_text_as_html.append("</td><td>");
                selected_text.append(QLatin1Char('\t'));
            }
            selected_text_as_html.append("</td></tr><tr><td>");
            selected_text.append(QLatin1Char('\n'));
        }
    }
    selected_text_as_html.append("</td></tr>");
    QMimeData * md = new QMimeData;
    md->setHtml(selected_text_as_html);
    qDebug() << selected_text;
    md->setText(selected_text);
    qApp->clipboard()->setMimeData(md);
}

void StartingProtocol::on_pushButton_update_2_clicked()
{
    RankSettings * rank = new RankSettings();
    for(int i=0;i<ui->tableWidget_startSwim_2->rowCount();i++){
        if(ui->tableWidget_startSwim_2->item(i,8)->text().contains(":")==true
                && ui->tableWidget_startSwim_2->item(i,8)->text().contains(".")==true){
            if(ui->comboBox_swimPool_2->currentText() == "50м"){
                if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,В.ст.,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,В.ст.,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(0,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(0,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(0,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(0,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,Ч")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(1,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(1,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(1,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(1,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,В.ст.,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,В.ст.,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(2,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(2,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(2,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(2,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,На спині,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,На спині,ЗмЧ")){
                    for(int j = 3; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(6,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(6,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(6,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(6,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,На спині,Ч")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,На спині,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(7,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(7,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(7,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(7,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,На спині,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,На спині,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(8,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(8,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(8,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(8,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Брас,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Брас,ЗмЧ")){
                    for(int j = 3; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(9,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(9,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(9,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(9,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Брас,Ч")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Брас,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(10,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(10,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(10,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(10,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Брас,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Брас,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(11,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(11,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(11,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(11,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Бат,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Бат,ЗмЧ")){
                    for(int j = 3; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(12,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(12,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(12,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(12,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Бат,Ч")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Бат,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(13,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(13,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(13,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(13,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Бат,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Бат,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(14,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(14,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(14,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(14,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }

                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Комб.,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Комб.,ЗмЧ")){
                    for(int j = 3; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(6,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(6,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(6,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(6,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }

                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,Ч")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(7,j-1)->text() &&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(7,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(7,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(7,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Комб.,Ч")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Комб.,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(8,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(8,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Men->item(8,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Men->item(8,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }

                //-----------------------------------------Women-----------------------------------
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,В.ст.,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,В.ст.,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(0,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(0,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(0,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(0,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(1,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(1,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(1,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(1,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,В.ст.,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,В.ст.,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(2,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(2,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(2,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(2,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,На спині,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,На спині,ЗмЖ")){
                    for(int j = 3; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(6,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(6,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(6,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(6,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,На спині,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,На спині,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(7,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(7,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(7,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(7,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,На спині,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,На спині,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(8,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(8,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(8,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(8,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Брас,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Брас,ЗмЖ")){
                    for(int j = 3; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(9,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(9,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(9,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(9,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Брас,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Брас,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(10,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(10,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(10,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(10,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Брас,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Брас,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(11,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(11,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(11,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(11,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Бат,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Бат,ЗмЖ")){
                    for(int j = 3; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(12,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(12,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(12,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(12,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Бат,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Бат,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(13,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(13,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(13,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(13,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Бат,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Бат,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(14,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(14,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(14,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(14,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Комб.,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Комб.,ЗмЖ")){
                    for(int j = 3; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(6,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(6,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(6,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(6,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(7,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(7,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(7,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(7,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Комб.,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Комб.,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_50Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(8,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(8,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_50Women->item(8,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_50Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_50Women->item(8,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else ui->tableWidget_startSwim_2->item(i,9)->setText("-");
                //                ui->tableWidget_startSwim->item(i,8)->setBackgroundColor(Qt::white);
            }
            //------------------------25m----------------------------
            else{
                if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,В.ст.,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,В.ст.,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(0,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(0,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(0,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(0,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,Ч")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(1,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(1,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(1,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(1,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,В.ст.,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,В.ст.,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(2,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(2,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(2,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(2,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,На спині,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,На спині,ЗмЧ")){
                    for(int j = 3; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(6,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(6,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(6,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(6,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,На спині,Ч")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,На спині,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(7,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(7,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(7,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(7,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,На спині,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,На спині,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(8,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(8,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(8,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(8,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Брас,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Брас,ЗмЧ")){
                    for(int j = 3; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(9,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(9,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(9,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(9,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Брас,Ч")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Брас,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(10,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(10,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(10,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(10,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Брас,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Брас,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(11,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(11,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(11,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(11,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Бат,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Бат,ЗмЧ")){
                    for(int j = 3; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(12,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(12,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(12,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(12,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Бат,Ч")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Бат,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(13,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(13,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(13,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(13,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Бат,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Бат,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(14,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(14,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(14,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(14,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }

                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Комб.,Ч") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Комб.,ЗмЧ")){
                    for(int j = 3; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(6,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(6,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(6,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(6,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }

                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,Ч")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(7,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(7,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(7,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(7,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Комб.,Ч")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Комб.,ЗмЧ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Men->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(8,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(8,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Men->item(8,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Men->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Men->item(8,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                //                //-----------------------Women25-----------------
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,В.ст.,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,В.ст.,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(0,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(0,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(0,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(0,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(1,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(1,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(1,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(1,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }

                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,В.ст.,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,В.ст.,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(2,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(2,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(2,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(2,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,На спині,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,На спині,ЗмЖ")){
                    for(int j = 3; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(6,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(6,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(6,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(6,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,На спині,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,На спині,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(7,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(7,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(7,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(7,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,На спині,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,На спині,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(8,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(8,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(8,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(8,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Брас,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Брас,ЗмЖ")){
                    for(int j = 3; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(9,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(9,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(9,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(9,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Брас,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Брас,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(10,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(10,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(10,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(10,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Брас,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Брас,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(11,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(11,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(11,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(11,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Бат,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Бат,ЗмЖ")){
                    for(int j = 3; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(12,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(12,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(12,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(12,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Бат,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Бат,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(13,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(13,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(13,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(13,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Бат,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Бат,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(14,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(14,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(14,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(14,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Комб.,Ж") ||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Комб.,ЗмЖ")){
                    for(int j = 3; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(6,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(6,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(6,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(6,7)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount();j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(7,j-1)->text()&&
                                ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(7,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(7,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(7,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Комб.,Ж")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,Комб.,ЗмЖ")){
                    for(int j = 2; j < rank->ui->tableWidget_25Women->columnCount()-1;j++){
                        if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(8,j-1)->text()&&
                                ui->tableWidget_startSwim->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(8,j)->text())
                        {
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) <= rank->ui->tableWidget_25Women->item(8,j-1)->text()){
                            ui->tableWidget_startSwim_2->item(i,9)->setText(rank->ui->tableWidget_25Women->horizontalHeaderItem(j-1)->text());
                            break;
                        }
                        else if(ui->tableWidget_startSwim_2->item(i,8)->text().mid(0,8) > rank->ui->tableWidget_25Women->item(8,6)->text() ){
                            ui->tableWidget_startSwim_2->item(i,9)->setText("б/р");
                            break;
                        }
                        else continue;
                    }
                }
                else ui->tableWidget_startSwim_2->item(i,9)->setText("-");
                //        else{
                //            ui->tableWidget_startSwim->item(i,8)->setBackgroundColor(Qt::red);
                //        }
                //        if(ui->tableWidget_startSwim->item(i,7)->text().contains("(ПК)")){
                //            ui->tableWidget_startSwim->item(i,10)->setText("~");
                //        }
                //        if(ui->tableWidget_startSwim->item(i,8)->text()=="ДК"){
                //            ui->tableWidget_startSwim->item(i,8)->setBackgroundColor(Qt::white);
                //            ui->tableWidget_startSwim->item(i,9)->setText("-");
                //            ui->tableWidget_startSwim->item(i,10)->setText("-");
                //        }
            }

        }
    }
    SettingsRecords * finn = new SettingsRecords();
    int points;
    QString miliseconds;
    double second;
    double minute,recSeconds;
    for(int i = 0; i< ui->tableWidget_startSwim_2->rowCount();i++){
        if(ui->tableWidget_startSwim_2->item(i,8)->text()!=""
                && ui->tableWidget_startSwim_2->item(i,8)->text().contains(":")
                && ui->tableWidget_startSwim_2->item(i,8)->text().contains(".")
                && ui->tableWidget_startSwim_2->item(i,8)->text().length()>=8
                && !ui->tableWidget_startSwim_2->item(i,8)->text().contains("ДК")
                && !ui->tableWidget_startSwim_2->item(i,10)->text().contains("ПК")){
            if(ui->comboBox_swimPool_2->currentText()=="50м"){
                if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,В.ст.,Ч")){
                    ui->tableWidget_startSwim_2->item(i,10)->setText("-");
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men4x100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men4x100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,Зм")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_Freestyle_Mixed_4x100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_Freestyle_Mixed_4x100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men4x200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men4x200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,Ч")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_complex_men4x100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_men4x100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,ЗмЧ")
                        || ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,ЗмЖ")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_complex_Mixed_4x100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_Mixed_4x100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,Ж")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_complex_women4x100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_women4x100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women4x100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women4x100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women4x200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women4x200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }

            }
            else{
                //-------------------25m
                if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men4x50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men4x50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men4x100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men4x100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,ЗмЧ")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_Freestyle_Mixed_4x100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_Freestyle_Mixed_4x100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,В.ст.,ЗмЧ")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_Freestyle_Mixed_4x50m->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_Freestyle_Mixed_4x50m->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,В.ст.,Ч")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men4x200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men4x200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Комб.,Ч")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_complex_men4x50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_men4x50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,ЗмЖ")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,Комб.,ЗмЧ")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_Complex_Mixed_4x100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_Complex_Mixed_4x100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Комб.,ЗмЖ")||
                        ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,Комб.,ЗмЧ")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_Complex_Mixed_4x50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_Complex_Mixed_4x50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("50,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women4x50->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women4x50->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("100,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women4x100->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women4x100->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }
                else if(ui->tableWidget_startSwim_2->item(i,7)->text().contains("200,В.ст.,Ж")){
                    minute = ui->tableWidget_startSwim_2->item(i,8)->text().mid(9,2).toDouble();
                    second = ui->tableWidget_startSwim_2->item(i,8)->text().mid(12,7).toDouble();
                    if(minute!=0){
                        second=second+(minute*60);
                    }
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women4x200->text().mid(0,2).toDouble()*60;
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women4x200->text().mid(3,7).toDouble() + recSeconds) / second),3);
                    ui->tableWidget_startSwim_2->item(i,10)->setText(QString::number(points));
                }

            }
        }
        else if(!ui->tableWidget_startSwim_2->item(i,10)->text().contains("ПК"))ui->tableWidget_startSwim_2->item(i,10)->setText("-");
    }
    for (int i=0;i<ui->tableWidget_startSwim_2->rowCount();i++) {
        if(ui->tableWidget_startSwim_2->item(i,1)->text()!=""
                && ui->tableWidget_startSwim_2->item(i,10)->text()==""){
            ui->tableWidget_startSwim_2->item(i,10)->setText("-");
        }
        if(ui->tableWidget_startSwim_2->item(i,1)->text()!=""
                && ui->tableWidget_startSwim_2->item(i,9)->text()==""){
            ui->tableWidget_startSwim_2->item(i,9)->setText("-");
        }

    }

}

void StartingProtocol::on_comboBox_swimPool_2_currentIndexChanged(const QString &arg1)
{

}

void StartingProtocol::on_pushButton_sortByYears_2_clicked()
{

}

void StartingProtocol::on_pushButton_openFileProtocol_2_clicked()
{
    ui->tableWidget_lastProtocol_2->clearContents();
    ui->tableWidget_lastProtocol_2->setRowCount(0);
    QString fileName = ui->comboBox_protocolFiles_2->currentText();
    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        QFileInfo fileInfo(file.fileName());
        QString filename(fileInfo.fileName());
        ui->lineEdit_styleProtocol_2->setText(filename.remove(".prot").remove(".tm").remove(".mf").remove("Estafeta\\"));
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream stream(&file);
            qint32 row, column;
            stream >> row >> column;
            int countRow = ui->tableWidget_lastProtocol_2->rowCount();
            ui->tableWidget_lastProtocol_2->setRowCount(row+countRow);
            ui->tableWidget_lastProtocol_2->setColumnCount(column);

            for (int i = countRow; i < row+countRow; ++i){
                for (int j = 0; j < 11; j++)
                {

                    ui->tableWidget_lastProtocol_2->setItem(i,j,new QTableWidgetItem);
                    ui->tableWidget_lastProtocol_2->item(i,j)->read(stream);
                }
            }
            file.close();
            ui->tableWidget_lastProtocol_2->verticalHeader()->hide();
        }
    }

    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    bool flag4 = false;

    for (int i = 0; i < ui->tableWidget_lastProtocol_2->rowCount(); i++) {
        for (int j = 0;j<ui->comboBox_sortYear_2->count();j++) {
            if(ui->comboBox_sortYear_2->itemText(j)==ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(0,4)){
                flag1=true;
            }
        }
        if(!flag1)
            ui->comboBox_sortYear_2->addItem(ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(0,4),QVariant::Int);
        for (int j = 0;j<ui->comboBox_sortYear_2->count();j++) {
            if(ui->comboBox_sortYear_2->itemText(j)==ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(5,4)){
                flag2=true;
            }
        }
        if(!flag2)
            ui->comboBox_sortYear_2->addItem(ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(5,4),QVariant::Int);
        for (int j = 0;j<ui->comboBox_sortYear_2->count();j++) {
            if(ui->comboBox_sortYear_2->itemText(j)==ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(10,4)){
                flag3=true;
            }
        }
        if(!flag3)
            ui->comboBox_sortYear_2->addItem(ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(10,4),QVariant::Int);
        for (int j = 0;j<ui->comboBox_sortYear_2->count();j++) {
            if(ui->comboBox_sortYear_2->itemText(j)==ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(15,4)){
                flag4=true;
            }
        }
        if(!flag4)
            ui->comboBox_sortYear_2->addItem(ui->tableWidget_lastProtocol_2->item(i,2)->text().mid(15,4),QVariant::Int);
        flag1=false;
        flag2=false;
        flag3=false;
        flag4=false;
    }

    setRowsNumbering(ui->tableWidget_lastProtocol_2);
    ui->comboBox_sortYear_2->model()->sort(Qt::AscendingOrder);
    ui->tableWidget_lastProtocol_2->resizeRowsToContents();
    ui->tableWidget_lastProtocol_2->resizeColumnsToContents();
}

void StartingProtocol::on_comboBox_protocolFiles_2_currentTextChanged(const QString &arg1)
{
    ui->pushButton_openFileProtocol_2->clicked(true);
}

void StartingProtocol::on_comboBox_swimPool_2_currentTextChanged(const QString &arg1)
{
    ui->pushButton_update_2->clicked(true);
}

void StartingProtocol::on_pushButton_goToTeams_2_clicked()
{
    int summOfPoints=0;
    bool flagTeams = false;
    int countPeopleTeams=0;
    bool flagCountTeams=false;
    int symb11 = 0;
    int symb22 =0;
    bool repeatTeammate1=false;
    QString team="";
    for (int i = 0; i < ui->tableWidget_lastProtocol_2->rowCount(); i++) {
        symb11 = ui->tableWidget_lastProtocol_2->item(i,5)->text().indexOf("(");
        symb22 = ui->tableWidget_lastProtocol_2->item(i,5)->text().indexOf(")",symb11);
        team = ui->tableWidget_lastProtocol_2->item(i,5)->text().mid(symb11+1, symb22-symb11-1);
        if(ui->tableWidget_lastProtocol_2->item(i,6)->text().contains("(К)") ||
                ui->tableWidget_lastProtocol_2->item(i,6)->text().contains("(КБ)")){
            for (int j=0;j<ui->tableWidget_teams->rowCount();j++) {
                if(ui->tableWidget_teams->item(j,2)->text().contains(ui->tableWidget_lastProtocol_2->item(i,1)->text())
                        && ui->tableWidget_teams->item(j,7)->text().contains(team)){
                    flagCountTeams=true;
                }
            }
            if(!flagCountTeams){
                countPeopleTeams++;
            }
        }
        flagCountTeams=false;
    }

    int previousRowCountTeams=ui->tableWidget_teams->rowCount();
    int tableRowTeams = ui->tableWidget_teams->rowCount();

    bool flagTeams1 = false;
    QString distanceTeams,resultTeams,pointsTeams, nameTeams, yearBR, schoolTeams;


    ui->tableWidget_teams->setRowCount(countPeopleTeams+previousRowCountTeams);
    for (int i=previousRowCountTeams;i<countPeopleTeams+previousRowCountTeams;i++) {
        for (int j=0 ;j<11;j++) {
            ui->tableWidget_teams->setItem(i,j,new QTableWidgetItem);
        }
    }
    int symb1 = 0;
    int symb2 =0;
    bool repeatTeammate=false;
    for (int i=0;i<ui->tableWidget_lastProtocol_2->rowCount();i++) {
        symb1 = ui->tableWidget_lastProtocol_2->item(i,5)->text().indexOf("(");
        symb2 = ui->tableWidget_lastProtocol_2->item(i,5)->text().indexOf(")",symb1);
        if(ui->tableWidget_lastProtocol_2->item(i,6)->text().contains("(К")){
            for (int j=0;j<ui->tableWidget_teams->rowCount();j++) {

                if(ui->tableWidget_teams->item(j,2)->text().contains(ui->tableWidget_lastProtocol_2->item(i,1)->text()) &&
                        ui->tableWidget_teams->item(j,7)->text().contains(ui->tableWidget_lastProtocol_2->item(i,6)->text()) &&
                        ui->tableWidget_teams->item(j,8)->text().contains(ui->tableWidget_lastProtocol_2->item(i,7)->text())){repeatTeammate = true;continue;}
                if(ui->tableWidget_lastProtocol_2->item(i,5)->text().contains("("+ui->tableWidget_teams->item(j,1)->text()+")")){
                    flagTeams1=true;
                    distanceTeams=ui->tableWidget_teams->item(j,7)->text();
                    resultTeams=ui->tableWidget_teams->item(j,8)->text();
                    pointsTeams=ui->tableWidget_teams->item(j,9)->text();
                    nameTeams=ui->tableWidget_teams->item(j,2)->text();
                    yearBR = ui->tableWidget_teams->item(j,3)->text();
                    summOfPoints=ui->tableWidget_teams->item(j,10)->text().toInt();
                    schoolTeams=ui->tableWidget_teams->item(j,6)->text();
                    ui->tableWidget_teams->item(j,6)->setText(schoolTeams+'\n'+ui->tableWidget_lastProtocol_2->item(i,5)->text());
                    ui->tableWidget_teams->item(j,7)->setText(distanceTeams+'\n'+ui->tableWidget_lastProtocol_2->item(i,6)->text());

                    ui->tableWidget_teams->item(j,3)->setText(yearBR+'\n'+ui->tableWidget_lastProtocol_2->item(i,2)->text());
                    ui->tableWidget_teams->item(j,8)->setText(resultTeams+'\n'+ui->tableWidget_lastProtocol_2->item(i,7)->text());
                    ui->tableWidget_teams->item(j,9)->setText(pointsTeams+'\n'+ui->tableWidget_lastProtocol_2->item(i,9)->text());
                    ui->tableWidget_teams->item(j,10)->setText(QString::number(summOfPoints+ui->tableWidget_lastProtocol_2->item(i,9)->text().toInt()));
                    ui->tableWidget_teams->item(j,2)->setText(nameTeams+'\n'+ui->tableWidget_lastProtocol_2->item(i,1)->text());
                    break;
                }
            }
            if(!flagTeams1 && !repeatTeammate){
                for (int j=1;j<11;j++) {
                    if(j==10){
                        ui->tableWidget_teams->item(tableRowTeams,10)->setText(ui->tableWidget_lastProtocol_2->item(i,9)->text());
                        continue;
                    }
                    if(j==1){
                        ui->tableWidget_teams->item(tableRowTeams,1)->setText(ui->tableWidget_lastProtocol_2->item(i,5)->text().mid(symb1+1, symb2-symb1-1));
                        continue;
                    }
                    if(j==9){
                        ui->tableWidget_teams->item(tableRowTeams,9)->setText(ui->tableWidget_lastProtocol_2->item(i,9)->text());
                        continue;
                    }
                    ui->tableWidget_teams->item(tableRowTeams,j)->setText(ui->tableWidget_lastProtocol_2->item(i,j-1)->text());
                }

                tableRowTeams++;
            }
        }
        repeatTeammate=false;
        flagTeams1=false;

    }
    for (int i = ui->tableWidget_teams->rowCount()-1;i!=-1;i--) {
        if(ui->tableWidget_teams->item(i,1)->text()==""){
            ui->tableWidget_teams->removeRow(i);
        }
    }
    QString summ="";
    ui->tableWidget_teams->resizeRowsToContents();
    QString beforePointT="";
    for (int i=0;i<ui->tableWidget_teams->rowCount();i++) {
        summ=ui->tableWidget_teams->item(i,10)->text();
        for (int k=0;k<6-ui->tableWidget_teams->item(i, 10)->text().length();k++) {
            beforePointT+=" ";
        }
        ui->tableWidget_teams->item(i,10)->setText(beforePointT+summ);
        beforePointT="";
    }

    ui->tableWidget_teams->sortByColumn(10,Qt::DescendingOrder);
    QString afterPoitsT="";
    for (int i=0;i<ui->tableWidget_teams->rowCount();i++) {
        afterPoitsT = ui->tableWidget_teams->item(i,10)->text();
        ui->tableWidget_teams->item(i,10)->setText(afterPoitsT.trimmed());
    }
    setRowsNumbering(ui->tableWidget_teams);


    QString fr = "User\\Teams.tm";
    QFile file(fr);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        qint32 row(ui->tableWidget_teams->rowCount()), column(ui->tableWidget_teams->columnCount());
        stream << row << column;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; j++){
                ui->tableWidget_teams->item(i,j)->write(stream);}
        file.close();
    }
    bool flagTeam=false;
    if (file.open(QIODevice::ReadOnly))
    {
        for (int i=0;i<ui->comboBox_protocolFiles_2->count();i++) {
            if(ui->comboBox_protocolFiles_2->itemText(i).contains(file.fileName())){
                flagTeam=true;
            }
        }
        if(!flagTeam) ui->comboBox_protocolFiles_2->addItem(file.fileName() ,QVariant::Int);
        file.close();
        ui->tableWidget_lastProtocol_2->verticalHeader()->hide();
    }
}

void StartingProtocol::on_pushButton_copyTableProtocol_2_clicked()
{
    QString selected_text_as_html;
    QString selected_text;
    QTableWidget *table = ui->tableWidget_lastProtocol_2;
    selected_text_as_html.prepend("<html><style>br{mso-data-placement:same-cell;}</style><table><tr><td>");
    for (int columnIndex = 0; columnIndex < 11; columnIndex++) {
        QString text = table->horizontalHeaderItem(columnIndex)->text();
        selected_text.append(text);
        text.replace("\n","<br>");
        selected_text_as_html.append(text);
        selected_text_as_html.append("</td><td>");
        selected_text.append(QLatin1Char('\t'));
    }
    selected_text_as_html.append("</td></tr><tr><td>");
    selected_text.append(QLatin1Char('\n'));

    for (int rowIndex = 0; rowIndex <table->rowCount(); rowIndex++) {
        if(ui->tableWidget_lastProtocol_2->item(rowIndex,8)->text()!=""
                && !ui->tableWidget_lastProtocol_2->isRowHidden(rowIndex)){
            for (int columnIndex = 0; columnIndex < 11; columnIndex++) {
                QString text = table->item(rowIndex,columnIndex)->text();
                selected_text.append(text);
                text.replace("\n","<br>");
                selected_text_as_html.append(text);
                selected_text_as_html.append("</td><td>");
                selected_text.append(QLatin1Char('\t'));
            }
            selected_text_as_html.append("</td></tr><tr><td>");
            selected_text.append(QLatin1Char('\n'));
        }
    }
    selected_text_as_html.append("</td></tr>");
    QMimeData * md = new QMimeData;
    md->setHtml(selected_text_as_html);
    qDebug() << selected_text;
    md->setText(selected_text);
    qApp->clipboard()->setMimeData(md);
}

void StartingProtocol::on_pushButton_goToManyFights_2_clicked()
{

}

void StartingProtocol::on_tableWidget_startSwim_2_itemPressed(QTableWidgetItem *item)
{
    int rowItem = item->row();
    if(ui->tableWidget_startSwim_2->item(rowItem,8)->text() == ""){
        ui->lineEdit_firstSportsmen->clear();
        ui->lineEdit_inputTime_2->clear();
        ui->lineEdit_firstSportsmen->setFocus();
        ui->lineEdit_firstSportsmen->setCursorPosition(0);
    }
    else if(ui->tableWidget_startSwim_2->item(rowItem,8)->text().mid(0,2) == ":."
            && ui->tableWidget_startSwim_2->item(rowItem,8)->text().mid(3,2) == ":."){
        ui->lineEdit_firstSportsmen->clear();
        ui->lineEdit_inputTime_2->clear();
        ui->lineEdit_firstSportsmen->setFocus();
        ui->lineEdit_firstSportsmen->setCursorPosition(0);
    }
    else if(ui->tableWidget_startSwim_2->item(rowItem,8)->text().mid(0,2) == ":."
            && ui->tableWidget_startSwim_2->item(rowItem,8)->text().mid(5,1) == ":"){
        ui->lineEdit_firstSportsmen->clear();
        ui->lineEdit_firstSportsmen->setFocus();
        ui->lineEdit_firstSportsmen->setCursorPosition(0);
        ui->lineEdit_inputTime_2->setText(ui->tableWidget_startSwim_2->item(rowItem,8)->text().mid(3,8));
    }

    else if(ui->tableWidget_startSwim_2->item(rowItem,8)->text().mid(2,1) == ":"
            && ui->tableWidget_startSwim_2->item(rowItem,8)->text().mid(9,1) == ":"){
        ui->lineEdit_inputTime_2->clear();
        ui->lineEdit_inputTime_2->setFocus();
        ui->lineEdit_inputTime_2->setCursorPosition(0);
        ui->lineEdit_firstSportsmen->setText(ui->tableWidget_startSwim_2->item(rowItem,8)->text().mid(0,8));
    }
    else {
        ui->lineEdit_firstSportsmen->setText(ui->tableWidget_startSwim_2->item(rowItem,8)->text().mid(0,8));
        ui->lineEdit_inputTime_2->setText(ui->tableWidget_startSwim_2->item(rowItem,8)->text().mid(9,8));
    }
    ui->lineEdit_nameForTime_2->setText(item->text());
    index1 = item->row();
    QFont font;
    font.setBold(true);
    ui->tableWidget_startSwim_2->item(item->row(),1)->setFont(font);
}


void StartingProtocol::on_lineEdit_firstSportsmen_textChanged(const QString &arg1)
{
    if(ui->lineEdit_firstSportsmen->cursorPosition()==8){
        ui->lineEdit_inputTime_2->setFocus();
        ui->lineEdit_inputTime_2->setCursorPosition(0);
    }
}

void StartingProtocol::on_comboBox_category_currentTextChanged(const QString &arg1)
{
    updateRatingTable();
    ui->tableWidget_startReiting->resizeColumnsToContents();
}


void StartingProtocol::on_pushButton_addSortYear_2_clicked()
{

    //    ui->tableWidget_sortYears->setRowCount(ui->tableWidget_sortYears->rowCount());
    bool flag = false;
    for (int i = 0; i < ui->tableWidget_sortYears_2->rowCount(); i++) {
        if(ui->tableWidget_sortYears_2->item(i,0)->text()==ui->comboBox_sortYear_2->currentText()) flag = true;
    }
    if(!flag){
        ui->tableWidget_sortYears_2->insertRow(ui->tableWidget_sortYears_2->rowCount());
        ui->tableWidget_sortYears_2->setItem(ui->tableWidget_sortYears_2->rowCount()-1,0, new QTableWidgetItem);
        ui->tableWidget_sortYears_2->item(ui->tableWidget_sortYears_2->rowCount()-1,0)->setText(ui->comboBox_sortYear_2->currentText());
        ui->tableWidget_sortYears_2->item(ui->tableWidget_sortYears_2->rowCount()-1,0)->setTextAlignment(Qt::AlignHCenter);
    }
    ui->pushButton_updateByYears_2->clicked(true);
}


void StartingProtocol::on_pushButton_removeSortYear_2_clicked()
{
    bool flag = false;
    int indexRemovingRow=0;
    for (int i=0; i<ui->tableWidget_sortYears_2->rowCount();i++) {
        if(ui->comboBox_sortYear_2->currentText()==ui->tableWidget_sortYears_2->item(i,0)->text()){
            flag = true;
            indexRemovingRow=i;
            break;
        }
    }
    if(flag){
        ui->tableWidget_sortYears_2->removeRow(indexRemovingRow);
    }
    else {
        QMessageBox::warning(this,"Помилка","Рік "+ ui->comboBox_sortYear_2->currentText() +" відсутній у таблиці!");
    }
    ui->comboBox_sortYear_2->model()->sort(Qt::AscendingOrder);
    ui->pushButton_updateByYears_2->clicked(true);
}

void StartingProtocol::on_pushButton_updateByYears_2_clicked()
{
    for (int i=0; i<ui->tableWidget_lastProtocol_2->rowCount();i++) {
        ui->tableWidget_lastProtocol_2->setRowHidden(i,false);
    }
    bool flag=false;
    for (int i=0; i < ui->tableWidget_lastProtocol_2->rowCount(); i++) {
        for (int j=0; j < ui->tableWidget_sortYears_2->rowCount(); j++) {
            if(ui->tableWidget_lastProtocol_2->item(i,2)->text().contains(ui->tableWidget_sortYears_2->item(j,0)->text())){
                flag=true;
                break;
            }
        }

        if(!flag){
            ui->tableWidget_lastProtocol_2->setRowHidden(i,true);
        }
        flag=false;
    }
    setRowsNumbering(ui->tableWidget_lastProtocol_2);
    if(ui->tableWidget_sortYears_2->rowCount()==0){
        for (int i=0; i<ui->tableWidget_lastProtocol_2->rowCount();i++) {
            ui->tableWidget_lastProtocol_2->setRowHidden(i,false);
        }
    }
}

void StartingProtocol::on_pushButton_clearSortTable_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Очистити всі роки?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Ok)
    {
        ui->tableWidget_sortYears_2->clearContents();
        ui->tableWidget_sortYears_2->setRowCount(0);
    }
    else
        msgBox.close();
    ui->pushButton_updateByYears_2->clicked(true);
}

void StartingProtocol::on_pushButton_addSortYear_clicked()
{
    bool flag = false;
    for (int i = 0; i < ui->tableWidget_sortYears->rowCount(); i++) {
        if(ui->tableWidget_sortYears->item(i,0)->text()==ui->comboBox_sortYear->currentText()) flag = true;
    }
    if(!flag){
        ui->tableWidget_sortYears->insertRow(ui->tableWidget_sortYears->rowCount());
        ui->tableWidget_sortYears->setItem(ui->tableWidget_sortYears->rowCount()-1,0, new QTableWidgetItem);
        ui->tableWidget_sortYears->item(ui->tableWidget_sortYears->rowCount()-1,0)->setText(ui->comboBox_sortYear->currentText());
        ui->tableWidget_sortYears->item(ui->tableWidget_sortYears->rowCount()-1,0)->setTextAlignment(Qt::AlignHCenter);
    }

    ui->pushButton_updateByYears->clicked(true);
}

void StartingProtocol::on_pushButton_removeSortYear_clicked()
{
    bool flag = false;
    int indexRemovingRow=0;
    for (int i=0; i<ui->tableWidget_sortYears->rowCount();i++) {
        if(ui->comboBox_sortYear->currentText()==ui->tableWidget_sortYears->item(i,0)->text()){
            flag = true;
            indexRemovingRow=i;
            break;
        }
    }
    if(flag){
        ui->tableWidget_sortYears->removeRow(indexRemovingRow);
    }
    else {
        QMessageBox::warning(this,"Помилка","Рік "+ ui->comboBox_sortYear->currentText() +" відсутній у таблиці!");
    }
    ui->pushButton_updateByYears->clicked(true);
}

void StartingProtocol::on_pushButton_clearSortTable_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Очистити всі роки?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Ok)
    {
        ui->tableWidget_sortYears->clearContents();
        ui->tableWidget_sortYears->setRowCount(0);
    }
    else
        msgBox.close();
    ui->pushButton_updateByYears->clicked(true);
}


void StartingProtocol::on_pushButton_updateByYears_clicked()
{
    for (int i=0; i<ui->tableWidget_lastProtocol->rowCount();i++) {
        ui->tableWidget_lastProtocol->setRowHidden(i,false);
    }
    bool flag=false;
    for (int i=0; i < ui->tableWidget_lastProtocol->rowCount(); i++) {
        for (int j=0; j < ui->tableWidget_sortYears->rowCount(); j++) {
            if(ui->tableWidget_lastProtocol->item(i,2)->text().contains(ui->tableWidget_sortYears->item(j,0)->text())){
                flag=true;
                break;
            }
        }

        if(!flag){
            ui->tableWidget_lastProtocol->setRowHidden(i,true);
        }
        flag=false;
    }

    if(ui->tableWidget_sortYears->rowCount()==0){
        for (int i=0; i<ui->tableWidget_lastProtocol->rowCount();i++) {
            ui->tableWidget_lastProtocol->setRowHidden(i,false);
        }
    }
    QString summ="";
    ui->tableWidget_lastProtocol->resizeRowsToContents();
    QString beforePointT="";
    for (int i=0;i<ui->tableWidget_lastProtocol->rowCount();i++) {
        summ=ui->tableWidget_lastProtocol->item(i,9)->text();
        for (int k=0;k<6-ui->tableWidget_lastProtocol->item(i, 9)->text().length();k++) {
            beforePointT+=" ";
        }
        ui->tableWidget_lastProtocol->item(i,9)->setText(beforePointT+summ);
        beforePointT="";
    }

    ui->tableWidget_lastProtocol->sortByColumn(9,Qt::DescendingOrder);
    QString afterPoitsT="";
    for (int i=0;i<ui->tableWidget_lastProtocol->rowCount();i++) {
        afterPoitsT = ui->tableWidget_lastProtocol->item(i,9)->text();
        ui->tableWidget_lastProtocol->item(i,9)->setText(afterPoitsT.trimmed());
    }
    setRowsNumbering(ui->tableWidget_lastProtocol);
}

void StartingProtocol::on_pushButton_PK_2_clicked()
{
    if(ui->tab_3->isVisible()){
        ui->tableWidget_startSwim_2->item(index1,8)->setText(ui->lineEdit_firstSportsmen->text()+'\n'+ui->lineEdit_inputTime_2->text());
        ui->pushButton_update_2->clicked(true);
        ui->tableWidget_startSwim_2->item(index1,10)->setText("ПК");
        QFont font;
        font.setBold(false);
        ui->tableWidget_startSwim_2->item(index1,1)->setFont(font);
        if(ui->tableWidget_startSwim_2->rowCount()-1!=index1){
            if(ui->tableWidget_startSwim_2->item(index1+1,1)->text()==""){
                index1 = index1+2;
            }
            else index1++;
            QTableWidgetItem * itemNext =  ui->tableWidget_startSwim_2->item(index1,1);
            on_tableWidget_startSwim_2_itemPressed(itemNext);
        }
    }
}

void StartingProtocol::on_pushButton_addSortYear_3_clicked()
{
    bool flag = false;
    for (int i = 0; i < ui->tableWidget_sortYears_3->rowCount(); i++) {
        if(ui->tableWidget_sortYears_3->item(i,0)->text()==ui->comboBox_sortYear_3->currentText()) flag = true;
    }
    if(!flag){
        ui->tableWidget_sortYears_3->insertRow(ui->tableWidget_sortYears_3->rowCount());
        ui->tableWidget_sortYears_3->setItem(ui->tableWidget_sortYears_3->rowCount()-1,0, new QTableWidgetItem);
        ui->tableWidget_sortYears_3->item(ui->tableWidget_sortYears_3->rowCount()-1,0)->setText(ui->comboBox_sortYear_3->currentText());
        ui->tableWidget_sortYears_3->item(ui->tableWidget_sortYears_3->rowCount()-1,0)->setTextAlignment(Qt::AlignHCenter);
    }
    ui->comboBox_sortYear_3->model()->sort(Qt::AscendingOrder);
    ui->pushButton_updateByYears_3->clicked(true);

}

void StartingProtocol::on_pushButton_removeSortYear_3_clicked()
{
    bool flag = false;
    int indexRemovingRow=0;
    for (int i=0; i<ui->tableWidget_sortYears_3->rowCount();i++) {
        if(ui->comboBox_sortYear_3->currentText()==ui->tableWidget_sortYears_3->item(i,0)->text()){
            flag = true;
            indexRemovingRow=i;
            break;
        }
    }
    if(flag){
        ui->tableWidget_sortYears_3->removeRow(indexRemovingRow);
    }
    else {
        QMessageBox::warning(this,"Помилка","Рік "+ ui->comboBox_sortYear_3->currentText() +" відсутній у таблиці!");
    }
    ui->pushButton_updateByYears_3->clicked(true);
}

void StartingProtocol::on_pushButton_updateByYears_3_clicked()
{
    for (int i=0; i<ui->tableWidget_manyFights->rowCount();i++) {
        ui->tableWidget_manyFights->setRowHidden(i,false);
    }
    bool flag=false;
    for (int i=0; i < ui->tableWidget_manyFights->rowCount(); i++) {
        for (int j=0; j < ui->tableWidget_sortYears_3->rowCount(); j++) {
            if(ui->tableWidget_manyFights->item(i,2)->text().contains(ui->tableWidget_sortYears_3->item(j,0)->text())){
                flag=true;
                break;
            }
        }

        if(!flag){
            ui->tableWidget_manyFights->setRowHidden(i,true);
        }
        flag=false;
    }
    QString summ="";
    ui->tableWidget_manyFights->resizeRowsToContents();
    QString beforePointT="";
    for (int i=0;i<ui->tableWidget_manyFights->rowCount();i++) {
        summ=ui->tableWidget_manyFights->item(i,9)->text();
        for (int k=0;k<6-ui->tableWidget_manyFights->item(i, 9)->text().length();k++) {
            beforePointT+=" ";
        }
        ui->tableWidget_manyFights->item(i,9)->setText(beforePointT+summ);
        beforePointT="";
    }

    ui->tableWidget_manyFights->sortByColumn(9,Qt::DescendingOrder);
    QString afterPoitsT="";
    for (int i=0;i<ui->tableWidget_manyFights->rowCount();i++) {
        afterPoitsT = ui->tableWidget_manyFights->item(i,9)->text();
        ui->tableWidget_manyFights->item(i,9)->setText(afterPoitsT.trimmed());
    }
    setRowsNumbering(ui->tableWidget_manyFights);
    if(ui->tableWidget_sortYears_3->rowCount()==0){
        for (int i=0; i<ui->tableWidget_manyFights->rowCount();i++) {
            ui->tableWidget_manyFights->setRowHidden(i,false);
        }
    }
}

void StartingProtocol::on_pushButton_clearSortTable_3_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Очистити всі роки?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Ok)
    {
        ui->tableWidget_sortYears_3->clearContents();
        ui->tableWidget_sortYears_3->setRowCount(0);
    }
    else
        msgBox.close();
    ui->pushButton_updateByYears_3->clicked(true);
}

void StartingProtocol::on_pushButton_addSortYear_4_clicked()
{
    bool flag = false;
    for (int i = 0; i < ui->tableWidget_sortYears_4->rowCount(); i++) {
        if(ui->tableWidget_sortYears_4->item(i,0)->text()==ui->comboBox_sortYear_4->currentText()) flag = true;
    }
    if(!flag){
        ui->tableWidget_sortYears_4->insertRow(ui->tableWidget_sortYears_4->rowCount());
        ui->tableWidget_sortYears_4->setItem(ui->tableWidget_sortYears_4->rowCount()-1,0, new QTableWidgetItem);
        ui->tableWidget_sortYears_4->item(ui->tableWidget_sortYears_4->rowCount()-1,0)->setText(ui->comboBox_sortYear_4->currentText());
        ui->tableWidget_sortYears_4->item(ui->tableWidget_sortYears_4->rowCount()-1,0)->setTextAlignment(Qt::AlignHCenter);
    }
    ui->comboBox_sortYear_4->model()->sort(Qt::AscendingOrder);
    updateRatingTable();
}

void StartingProtocol::on_pushButton_removeSortYear_4_clicked()
{
    bool flag = false;
    int indexRemovingRow=0;
    for (int i=0; i<ui->tableWidget_sortYears_4->rowCount();i++) {
        if(ui->comboBox_sortYear_4->currentText()==ui->tableWidget_sortYears_4->item(i,0)->text()){
            flag = true;
            indexRemovingRow=i;
            break;
        }
    }
    if(flag){
        ui->tableWidget_sortYears_4->removeRow(indexRemovingRow);
    }
    else {
        QMessageBox::warning(this,"Помилка","Рік "+ ui->comboBox_sortYear_4->currentText() +" відсутній у таблиці!");
    }
    updateRatingTable();
}

void StartingProtocol::on_pushButton_clearSortTable_4_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Очистити всі роки?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Ok)
    {
        ui->tableWidget_sortYears_4->clearContents();
        ui->tableWidget_sortYears_4->setRowCount(0);
    }
    else
        msgBox.close();
    updateRatingTable();
}

void StartingProtocol::on_pushButton_updateByYears_4_clicked()
{
    if(ui->comboBox_category->currentText() != "Ч"
            && ui->comboBox_category->currentText() != "Ж"){
        for (int i=0; i<ui->tableWidget_startReiting->rowCount();i++) {
            ui->tableWidget_startReiting->setRowHidden(i,false);
        }
    }
    bool flag=false;
    for (int i=0; i < ui->tableWidget_startReiting->rowCount(); i++) {
        for (int j=0; j < ui->tableWidget_sortYears_4->rowCount(); j++) {
            if(ui->tableWidget_startReiting->item(i,2)->text().contains(ui->tableWidget_sortYears_4->item(j,0)->text())){
                flag=true;
                break;
            }
        }

        if(!flag){
            ui->tableWidget_startReiting->setRowHidden(i,true);
        }
        flag=false;
    }

    ui->tableWidget_startReiting->sortByColumn(8,Qt::AscendingOrder);

    setRowsNumbering(ui->tableWidget_startReiting);
    if(ui->tableWidget_sortYears_4->rowCount()==0){
        for (int i=0; i<ui->tableWidget_startReiting->rowCount();i++) {
            ui->tableWidget_startReiting->setRowHidden(i,false);
        }
    }
    if(ui->comboBox_category->currentText() != ""){
        for (int i = 0; i < ui->tableWidget_startReiting->rowCount(); ++i) {
            if(ui->tableWidget_startReiting->item(i,7)->text().contains("4x")){
                if(!ui->tableWidget_startReiting->item(i,7)->text().contains(ui->comboBox_category->currentText())
                        || !ui->comboBox_category->currentText().contains("4x")){
                    ui->tableWidget_startReiting->verticalHeader()->hideSection(i);
                }
            }
            else {
                if(!ui->tableWidget_startReiting->item(i,7)->text().contains(ui->comboBox_category->currentText())){
                    ui->tableWidget_startReiting->verticalHeader()->hideSection(i);
                }
            }
        }

        ui->tableWidget_startReiting->sortByColumn(8,Qt::AscendingOrder);
        setRowsNumbering(ui->tableWidget_startReiting);
    }
    QString comboBox_category= ui->comboBox_category->currentText();
    ui->comboBox_category->setCurrentText(comboBox_category);
    ui->tableWidget_startReiting->resizeRowsToContents();
    ui->tableWidget_startReiting->resizeColumnsToContents();
}

void StartingProtocol::on_pushButton_AddOnePerson_clicked()
{
    if(ui->lineEdit_dst->text() == "" || ui->lineEdit_city->text() == ""||ui->lineEdit_school->text() == ""||ui->lineEdit_FIO_Create_Form->text() == ""
            ||ui->lineEdit_Coach_CreateForm->text() == ""){
        QMessageBox::critical(this,"Помилка введення", "Заповніть необхідні поля!");
        ui->widget->setHidden(false);
    }
    else{
        bool teamContainsed = false;
        int rowOfTeam;
        if(ui->comboBox_meter->currentText().contains("4x")){

            QString teamSwim = ui->comboBox_meter->currentText()+","+ui->comboBox_style->currentText()+","+ui->comboBox_sex->currentText()+"(К)";
            QString teamName = "("+ui->lineEdit_customTeam->text().simplified()+")";
            for (int i = 0;i<ui->tableWidget_startReiting->rowCount();i++) {
                if(ui->tableWidget_startReiting->item(i,6)->text().contains(teamName)
                        && ui->tableWidget_startReiting->item(i,7)->text()==teamSwim){
                    teamContainsed=true;
                    rowOfTeam=i;
                    break;
                }
            }
        }
        if((!ui->comboBox_meter->currentText().contains("4x") && !teamContainsed)||(ui->comboBox_meter->currentText().contains("4x") && !teamContainsed)){
            if((ui->comboBox_meter->currentText().contains("4x") && ui->checkBox_personalOrTeam->isChecked()
                && ui->lineEdit_customTeam->text().length()!=0)
                    || (!ui->comboBox_meter->currentText().contains("4x")
                        && ui->checkBox_personalOrTeam->isChecked()
                        && ui->lineEdit_customTeam->text().length()!=0)
                    ||
                    (!ui->comboBox_meter->currentText().contains("4x")
                     && !ui->checkBox_personalOrTeam->isChecked())){
                /*Заносим данные в таблицу*/
                ui->tableWidget_startReiting->insertRow(ui->tableWidget_startReiting->rowCount());

                ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,0,  new QTableWidgetItem(QString::number(ui->tableWidget_startReiting->rowCount())));
                ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,1,  new QTableWidgetItem(ui->lineEdit_FIO_Create_Form->text().simplified()));
                ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,2,  new QTableWidgetItem(ui->spinBox_Year->text()));
                ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,3,  new QTableWidgetItem(ui->comboBox_rank->currentText()));
                ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,5,  new QTableWidgetItem(ui->lineEdit_dst->text()));
                if(ui->checkBox_personalOrTeam->isChecked() && !ui->checkBox_outOfCompetition->isChecked()){
                    ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,6,  new QTableWidgetItem(ui->lineEdit_school->text()+"("+ui->lineEdit_customTeam->text().simplified()+")"));
                }
                else ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,6,  new QTableWidgetItem(ui->lineEdit_school->text()));
                ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,8,  new QTableWidgetItem(ui->comboBox_minutes->currentText()+":"+ui->comboBox_seconds->currentText()+ "." +ui->comboBox_miliseconds->currentText()));
                ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,9,  new QTableWidgetItem(ui->lineEdit_Coach_CreateForm->text()));

                /*Чек-боксы*/


                if(ui->checkBox_outOfCompetition->isChecked()){ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,7,  new QTableWidgetItem(ui->comboBox_meter->currentText()+
                                                                                                                                                                         ","+ui->comboBox_style->currentText()+","+ui->comboBox_sex->currentText()+"(ПК)"));}
                else if(ui->checkBox_personalOrTeam->isChecked() && ui->checkBox_manyFights->isChecked())
                {
                    ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,7,  new QTableWidgetItem(ui->comboBox_meter->currentText()+","+ui->comboBox_style->currentText()+","+ui->comboBox_sex->currentText()+"(КБ)"));
                }
                else if(ui->checkBox_personalOrTeam->isChecked() && !ui->checkBox_manyFights->isChecked())
                {
                    ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,7,  new QTableWidgetItem(ui->comboBox_meter->currentText()+","+ui->comboBox_style->currentText()+","+ui->comboBox_sex->currentText()+"(К)"));
                }
                else if(ui->checkBox_manyFights->isChecked()){
                    ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,7,  new QTableWidgetItem(ui->comboBox_meter->currentText()+","+ui->comboBox_style->currentText()+","+ui->comboBox_sex->currentText()+"(Б)"));
                }
                else ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,7,  new QTableWidgetItem(ui->comboBox_meter->currentText()+","+ui->comboBox_style->currentText()+","+ui->comboBox_sex->currentText()));

                /*Проверка на город/страну/область*/

                if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() != "" && ui->lineEdit_country->text()!=""){
                    ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,4,  new QTableWidgetItem(ui->lineEdit_city->text()+",\n"+ui->lineEdit_region->text()+" обл.,\n"+ui->lineEdit_country->text()));
                }

                else if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() != "" && ui->lineEdit_country->text()==""){
                    ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,4,  new QTableWidgetItem(ui->lineEdit_city->text()+",\n"+ui->lineEdit_region->text()+" обл."));
                }

                else if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() == "" && ui->lineEdit_country->text() ==""){
                    ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,4,  new QTableWidgetItem(ui->lineEdit_city->text()));
                }
                else if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() == "" && ui->lineEdit_country->text() !=""){
                    ui->tableWidget_startReiting->setItem(ui->tableWidget_startReiting->rowCount()-1,4,new QTableWidgetItem(ui->lineEdit_city->text()+",\n"+ui->lineEdit_country->text()));
                }
                ui->tableWidget_startReiting->resizeRowsToContents();
                ui->tableWidget_startReiting->resizeColumnsToContents();
                ui->tableWidget_startReiting->scrollToBottom();
                ui->widget->hide();
                ui->pushButton_addParticipant->clicked(true);
            }
            else{
                QMessageBox::critical(this,"Помилка введення", "Введіть команду");
            }
        }
        else{
            if(ui->checkBox_personalOrTeam->isChecked() && ui->lineEdit_customTeam->text().length()!=0){
                QString previousPeopleName = ui->tableWidget_startReiting->item(rowOfTeam,1)->text();
                QString previousPeopleYear = ui->tableWidget_startReiting->item(rowOfTeam,2)->text();
                QString previousPeopleRank = ui->tableWidget_startReiting->item(rowOfTeam,3)->text();
                QString previousPeopleLocation = ui->tableWidget_startReiting->item(rowOfTeam,4)->text();
                QString previousPeopleDST = ui->tableWidget_startReiting->item(rowOfTeam,5)->text();
                QString previousPeopleSchoolAndTeam = ui->tableWidget_startReiting->item(rowOfTeam,6)->text();
                QString previousPeopleCoach = ui->tableWidget_startReiting->item(rowOfTeam,9)->text();
                ui->tableWidget_startReiting->setItem(rowOfTeam,1,  new QTableWidgetItem(previousPeopleName+'\n'+ ui->lineEdit_FIO_Create_Form->text().simplified()));
                ui->tableWidget_startReiting->setItem(rowOfTeam,2,  new QTableWidgetItem(previousPeopleYear+'\n'+ ui->spinBox_Year->text()));
                ui->tableWidget_startReiting->setItem(rowOfTeam,3,  new QTableWidgetItem(previousPeopleRank+'\n'+ui->comboBox_rank->currentText()));
                ui->tableWidget_startReiting->setItem(rowOfTeam,5,  new QTableWidgetItem(previousPeopleDST+'\n'+ui->lineEdit_dst->text()));
                ui->tableWidget_startReiting->setItem(rowOfTeam,6,  new QTableWidgetItem(previousPeopleSchoolAndTeam+'\n'+ui->lineEdit_school->text().simplified()+"("+ui->lineEdit_customTeam->text().simplified()+")"));

                ui->tableWidget_startReiting->setItem(rowOfTeam,9,  new QTableWidgetItem(previousPeopleCoach +'\n'+ui->lineEdit_Coach_CreateForm->text()));


                if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() != "" && ui->lineEdit_country->text()!=""){
                    ui->tableWidget_startReiting->setItem(rowOfTeam,4,  new QTableWidgetItem(previousPeopleLocation+'\n'+ui->lineEdit_city->text()+",\n"+ui->lineEdit_region->text()+" обл.,\n"+ui->lineEdit_country->text()));
                }

                else if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() != "" && ui->lineEdit_country->text()==""){
                    ui->tableWidget_startReiting->setItem(rowOfTeam,4,  new QTableWidgetItem(previousPeopleLocation+'\n'+ui->lineEdit_city->text()+",\n"+ui->lineEdit_region->text()+" обл."));
                }
                else if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() == "" && ui->lineEdit_country->text() ==""){
                    ui->tableWidget_startReiting->setItem(rowOfTeam,4,  new QTableWidgetItem(previousPeopleLocation+'\n'+ui->lineEdit_city->text()));
                }
                else if(ui->lineEdit_city->text()!="" && ui->lineEdit_region->text() == "" && ui->lineEdit_country->text() !=""){
                    ui->tableWidget_startReiting->setItem(rowOfTeam,4,new QTableWidgetItem(previousPeopleLocation+'\n'+ui->lineEdit_city->text()+",\n"+ui->lineEdit_country->text()));
                }

                ui->tableWidget_startReiting->resizeRowsToContents();
                ui->tableWidget_startReiting->resizeColumnsToContents();
                ui->tableWidget_startReiting->scrollToBottom();
                ui->widget->hide();
                ui->pushButton_addParticipant->clicked(true);
            }
            else{
                QMessageBox::critical(this,"Помилка введення", "Введіть команду");
            }
        }

    }
    ui->tableWidget_startReiting->verticalHeader()->hide();
    ui->tableWidget_startReiting->sortByColumn(8,Qt::AscendingOrder);
    setRowsNumbering(ui->tableWidget_startReiting);

    bool flag = false;
    for (int i = 0; i < ui->tableWidget_startReiting->rowCount(); ++i) {
        for (int j = 0; j < ui->comboBox_category->count(); ++j) {
            if(ui->tableWidget_startReiting->item(i,7)->text().contains("(ПК)")){
                if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(ПК)").join("")){
                    flag=true;
                }
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(Б)")){
                if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(Б)").join("")){
                    flag=true;
                }
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(К)")){
                if(ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЧ(К)")
                        || ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЖ(К)")){
                    if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("Ч(К)").join("")){
                        flag=true;
                    }
                    else if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("Ж(К)").join("")){
                        flag=true;
                    }
                    else if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join("")){
                        flag=true;
                    }
                }
                else {
                    if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join("")){
                        flag=true;
                    }
                }
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(КБ)")){
                if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text().split("(КБ)").join("")){
                    flag=true;
                }
            }
            else if(ui->comboBox_category->itemText(j)==ui->tableWidget_startReiting->item(i,7)->text())
            {
                flag=true;
            }
        }
        if(!flag){
            if(ui->tableWidget_startReiting->item(i,7)->text().contains("(ПК)")){

                ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(ПК)").join(""),QVariant::Int);
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(К)")){
                if(ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЧ(К)")){

                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("Ч(К)").join(""),QVariant::Int);
                }
                else if(ui->tableWidget_startReiting->item(i,7)->text().contains("ЗмЖ(К)")){

                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("Ж(К)").join(""),QVariant::Int);
                }
                else {

                    ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(К)").join(""),QVariant::Int);
                }
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(Б)")){

                ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(Б)").join(""),QVariant::Int);
            }
            else if(ui->tableWidget_startReiting->item(i,7)->text().contains("(КБ)")){

                ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text().split("(КБ)").join(""),QVariant::Int);
            }
            else{

                ui->comboBox_category->addItem(ui->tableWidget_startReiting->item(i,7)->text(),QVariant::Int);
            }
        }
        flag=false;
    }
    bool flag0 = false;
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    bool flag4 = false;
    for (int i = 0; i < ui->tableWidget_startReiting->rowCount(); i++) {
        if(ui->tableWidget_startReiting->item(i,2)->text().length()==4){
            for (int j = 0;j<ui->comboBox_sortYear_4->count();j++) {
                if(ui->comboBox_sortYear_4->itemText(j)==ui->tableWidget_startReiting->item(i,2)->text().mid(0,4)){
                    flag0=true;
                }
            }
            if(!flag0)
                ui->comboBox_sortYear_4->addItem(ui->tableWidget_startReiting->item(i,2)->text().mid(0,4),QVariant::Int);
            flag0=false;
        }
        else{
            for (int j = 0;j<ui->comboBox_sortYear_4->count();j++) {
                if(ui->comboBox_sortYear_4->itemText(j)==ui->tableWidget_startReiting->item(i,2)->text().mid(0,4)){
                    flag1=true;
                }
            }
            if(!flag1)
                ui->comboBox_sortYear_4->addItem(ui->tableWidget_startReiting->item(i,2)->text().mid(0,4),QVariant::Int);
            for (int j = 0;j<ui->comboBox_sortYear_4->count();j++) {
                if(ui->comboBox_sortYear_4->itemText(j)==ui->tableWidget_startReiting->item(i,2)->text().mid(5,4)){
                    flag2=true;
                }
            }
            if(!flag2)
                ui->comboBox_sortYear_4->addItem(ui->tableWidget_startReiting->item(i,2)->text().mid(5,4),QVariant::Int);
            for (int j = 0;j<ui->comboBox_sortYear_4->count();j++) {
                if(ui->comboBox_sortYear_4->itemText(j)==ui->tableWidget_startReiting->item(i,2)->text().mid(10,4)){
                    flag3=true;
                }
            }
            if(!flag3)
                ui->comboBox_sortYear_4->addItem(ui->tableWidget_startReiting->item(i,2)->text().mid(10,4),QVariant::Int);
            for (int j = 0;j<ui->comboBox_sortYear_4->count();j++) {
                if(ui->comboBox_sortYear_4->itemText(j)==ui->tableWidget_startReiting->item(i,2)->text().mid(15,4)){
                    flag4=true;
                }
            }
            if(!flag4)
                ui->comboBox_sortYear_4->addItem(ui->tableWidget_startReiting->item(i,2)->text().mid(15,4),QVariant::Int);
            flag1=false;
            flag2=false;
            flag3=false;
            flag4=false;
        }
    }
    if(ui->comboBox_category->currentText()=="Ч" || ui->comboBox_category->currentText()=="Ж"){
        for (int i=0; i<ui->tableWidget_startReiting->rowCount();i++) {
            if(!ui->tableWidget_startReiting->isRowHidden(i)){
                for (int j=ui->tableWidget_startReiting->rowCount()-1; j>i;j--) {
                    if(!ui->tableWidget_startReiting->isRowHidden(j)){
                        if(ui->tableWidget_startReiting->item(i,1)->text() == ui->tableWidget_startReiting->item(j,1)->text()){
                            ui->tableWidget_startReiting->setRowHidden(j,true);
                        }
                    }
                }
            }
        }
        ui->tableWidget_startReiting->sortByColumn(8,Qt::AscendingOrder);
        setRowsNumbering(ui->tableWidget_startReiting);
    }
    ui->comboBox_sortYear_4->model()->sort(0, Qt::AscendingOrder);
    ui->tableWidget_startReiting->resizeColumnsToContents();
}

void StartingProtocol::on_checkBox_personalOrTeam_clicked(bool checked)
{
    if(checked){
        ui->lineEdit_customTeam->setEnabled(true);
    }
    else ui->lineEdit_customTeam->setEnabled(false);
}

void StartingProtocol::on_lineEdit_findHuman_textChanged(const QString &arg1)
{
    for(int i=0;i<ui->tableWidget_startReiting->rowCount();i++){
        if(!ui->tableWidget_startReiting->isRowHidden(i) && ui->tableWidget_startReiting->item(i,1)->text().toLower().contains(arg1.toLower())
                && arg1 !=""){
            ui->tableWidget_startReiting->item(i,1)->setBackground(Qt::darkGray);
        }
        else ui->tableWidget_startReiting->item(i,1)->setBackground(Qt::white);
    }
}

void StartingProtocol::updateRatingTable(){

    QTableWidget * tableRating = ui->tableWidget_startReiting;
    QComboBox * comboBoxCategory = ui->comboBox_category;
    setTableRowsHidden(tableRating, false);

    if(comboBoxCategory->currentText()!="")
    {
        for (int i = 0; i < tableRating->rowCount(); ++i) {
            if(tableRating->item(i,7)->text().contains("4x")){
                if(!tableRating->item(i,7)->text().contains(comboBoxCategory->currentText())
                        || !comboBoxCategory->currentText().contains("4x")){
                    tableRating->verticalHeader()->hideSection(i);
                }
            }
            else {
                if(!tableRating->item(i,7)->text().contains(comboBoxCategory->currentText())){
                    tableRating->verticalHeader()->hideSection(i);
                }
            }
        }
    }

    if(comboBoxCategory->currentText()=="Ч" ||
            comboBoxCategory->currentText()=="Ж")
    {
        for (int i = 0; i < tableRating->rowCount(); i++) {
            if(!tableRating->isRowHidden(i)){
                for (int j = tableRating->rowCount()-1; j > i; j--) {
                    if(!tableRating->isRowHidden(j)){
                        if(tableRating->item(i,1)->text() == tableRating->item(j,1)->text()){
                            tableRating->setRowHidden(j,true);
                        }
                    }
                }
            }
        }
    }
    if(ui->tableWidget_sortYears_4->rowCount()!=0){
        bool isYearSuitable = false;
        for (int i = 0; i < tableRating->rowCount(); i++) {
            if(!tableRating->isRowHidden(i)){
                for (int j = 0; j < ui->tableWidget_sortYears_4->rowCount(); j++) {
                    if(tableRating->item(i,2)->text().contains(ui->tableWidget_sortYears_4->item(j,0)->text())){
                        isYearSuitable=true;
                        break;
                    }
                }

                if(!isYearSuitable){
                    tableRating->setRowHidden(i,true);
                }
                isYearSuitable=false;
            }
        }
    }
    tableRating->sortByColumn(8,Qt::AscendingOrder);
    setRowsNumbering(tableRating);
}
void StartingProtocol::setTableRowsHidden(QTableWidget * table, bool setHidden){   //function makes all rows visible in table
    for (int i = 0;i < table->rowCount();i++) {
        table->setRowHidden(i, setHidden);
    }
}
void StartingProtocol::setRowsNumbering(QTableWidget * table){ // function assings numbers to visible table rows
    int rowNumbering=0;
    for (int i = 0; i < table->rowCount(); ++i) {
        if(!table->isRowHidden(i)){
            rowNumbering++;
            table->item(i,0)->setText(QString::number(rowNumbering));
        }
    }
}

void StartingProtocol::on_comboBox_sortBagatoborstvoGender_currentIndexChanged(const QString &arg1)
{
    QString sortStr = ui->comboBox_sortBagatoborstvoGender->currentText();
    if(sortStr==""){
        setTableRowsHidden(ui->tableWidget_manyFights, false);
    }
    else if(sortStr=="Ч"){
        setTableRowsHidden(ui->tableWidget_manyFights, false);
        for (int i=0; i<ui->tableWidget_manyFights->rowCount();i++) {
            if(!ui->tableWidget_manyFights->item(i,6)->text().contains("Ч")){
                ui->tableWidget_manyFights->setRowHidden(i,true);
            }
        }
        setRowsNumbering(ui->tableWidget_manyFights);
    }
    else if(sortStr=="Ж"){
        setTableRowsHidden(ui->tableWidget_manyFights, false);
        for (int i=0; i<ui->tableWidget_manyFights->rowCount();i++) {
            if(!ui->tableWidget_manyFights->item(i,6)->text().contains("Ж")){
                ui->tableWidget_manyFights->setRowHidden(i,true);
            }
        }
        setRowsNumbering(ui->tableWidget_manyFights);
    }
}
