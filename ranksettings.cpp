#include "ranksettings.h"
#include "ui_ranksettings.h"
#include <QSettings>
#include <QFile>
#include <qdesktopservices.h>
#include <qurl.h>
RankSettings::RankSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RankSettings)
{

    ui->setupUi(this);
    QString fileName1 = "ranks25men.sav";
    if (fileName1.isEmpty())
        return;
    else {
        QFile file(fileName1);
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream stream(&file);
            qint32 row, column;
            stream >> row >> column;
            int countRow = ui->tableWidget_25Men->rowCount();
            int countColumn = ui->tableWidget_25Men->columnCount();

            for (int i = 0; i < countRow; ++i)
                for (int j = 0; j < countColumn; j++)
                {
                    ui->tableWidget_25Men->setItem(i,j,new QTableWidgetItem);
                    ui->tableWidget_25Men->item(i,j)->read(stream);
                }
            file.close();
        }
    }
    QString fileName2 = "ranks50men.sav";
    if (fileName2.isEmpty())
        return;
    else {
        QFile file(fileName2);
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream stream(&file);
            qint32 row, column;
            stream >> row >> column;
            int countRow = ui->tableWidget_50Men->rowCount();
            int countColumn = ui->tableWidget_50Men->columnCount();

            for (int i = 0; i < countRow; ++i)
                for (int j = 0; j < countColumn; j++)
                {
                    ui->tableWidget_50Men->setItem(i,j,new QTableWidgetItem);
                    ui->tableWidget_50Men->item(i,j)->read(stream);
                }
            file.close();
        }
    }
    QString fileName3 = "ranks25women.sav";
    if (fileName3.isEmpty())
        return;
    else {
        QFile file(fileName3);
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream stream(&file);
            qint32 row, column;
            stream >> row >> column;
            int countRow = ui->tableWidget_25Women->rowCount();
            int countColumn = ui->tableWidget_25Women->columnCount();

            for (int i = 0; i < countRow; ++i)
                for (int j = 0; j < countColumn; j++)
                {
                    ui->tableWidget_25Women->setItem(i,j,new QTableWidgetItem);
                    ui->tableWidget_25Women->item(i,j)->read(stream);
                }
            file.close();
        }
    }
    QString fileName4 = "ranks50women.sav";
    if (fileName4.isEmpty())
        return;
    else {
        QFile file(fileName4);
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream stream(&file);
            qint32 row, column;
            stream >> row >> column;
            int countRow = ui->tableWidget_50Women->rowCount();
            int countColumn = ui->tableWidget_50Women->columnCount();

            for (int i = 0; i < countRow; ++i)
                for (int j = 0; j < countColumn; j++)
                {
                    ui->tableWidget_50Women->setItem(i,j,new QTableWidgetItem);
                    ui->tableWidget_50Women->item(i,j)->read(stream);
                }
            file.close();
        }
    }
//    QSettings settings( "settingsRank.conf", QSettings::IniFormat );

//    settings.beginGroup( "Rank_25Men" );
//    QString Men25_00 = settings.value( "Men25_00", ui->tableWidget_25Men->item(0,0)->text()).toString();
//    QString Men25_01 = settings.value( "Men25_01", ui->tableWidget_25Men->item(0,1)->text()).toString();
//    QString Men25_02 = settings.value( "Men25_02", ui->tableWidget_25Men->item(0,2)->text()).toString();
//    QString Men25_03 = settings.value( "Men25_03", ui->tableWidget_25Men->item(0,3)->text()).toString();
//    QString Men25_04 = settings.value( "Men25_04", ui->tableWidget_25Men->item(0,4)->text()).toString();
//    QString Men25_05 = settings.value( "Men25_05", ui->tableWidget_25Men->item(0,5)->text()).toString();
//    QString Men25_06 = settings.value( "Men25_06", ui->tableWidget_25Men->item(0,6)->text()).toString();
//    QString Men25_07 = settings.value( "Men25_07", ui->tableWidget_25Men->item(0,7)->text()).toString();
//    QString Men25_10 = settings.value( "Men25_10", ui->tableWidget_25Men->item(1,0)->text()).toString();
//    QString Men25_11 = settings.value( "Men25_11", ui->tableWidget_25Men->item(1,1)->text()).toString();
//    QString Men25_12 = settings.value( "Men25_12", ui->tableWidget_25Men->item(1,2)->text()).toString();
//    QString Men25_13 = settings.value( "Men25_13", ui->tableWidget_25Men->item(1,3)->text()).toString();
//    QString Men25_14 = settings.value( "Men25_14", ui->tableWidget_25Men->item(1,4)->text()).toString();
//    QString Men25_15 = settings.value( "Men25_15", ui->tableWidget_25Men->item(1,5)->text()).toString();
//    QString Men25_16 = settings.value( "Men25_16", ui->tableWidget_25Men->item(1,6)->text()).toString();
//    QString Men25_17 = settings.value( "Men25_17", ui->tableWidget_25Men->item(1,7)->text()).toString();


 //   settings.endGroup();

//    settings.beginGroup( "Rank_50Men" );

//    QString Men50_00 = settings.value( "Men50_00", -1).toString();
//    QString Men50_01 = settings.value( "Men50_01", -1).toString();
//    QString Men50_02 = settings.value( "Men50_02", -1).toString();
//    QString Men50_03 = settings.value( "Men50_03", -1).toString();
//    QString Men50_04 = settings.value( "Men50_04", -1).toString();
//    QString Men50_05 = settings.value( "Men50_05", -1).toString();
//    QString Men50_06 = settings.value( "Men50_06", -1).toString();
//    QString Men50_07 = settings.value( "Men50_07", -1).toString();
//    QString Men50_10 = settings.value( "Men50_10", -1).toString();
//    QString Men50_11 = settings.value( "Men50_11", -1).toString();
//    QString Men50_12 = settings.value( "Men50_12", -1).toString();
//    QString Men50_13 = settings.value( "Men50_13", -1).toString();
//    QString Men50_14 = settings.value( "Men50_14", -1).toString();
//    QString Men50_15 = settings.value( "Men50_15", -1).toString();
//    QString Men50_16 = settings.value( "Men50_16", -1).toString();
//    QString Men50_17 = settings.value( "Men50_17", -1).toString();


//    settings.endGroup();

//    ui->tableWidget_25Men->item(0,0)->setText(Men25_00);
//    ui->tableWidget_25Men->item(0,1)->setText(Men25_01);
//    ui->tableWidget_25Men->item(0,2)->setText(Men25_02);
//    ui->tableWidget_25Men->item(0,3)->setText(Men25_03);
//    ui->tableWidget_25Men->item(0,4)->setText(Men25_04);
//    ui->tableWidget_25Men->item(0,5)->setText(Men25_05);
//    ui->tableWidget_25Men->item(0,6)->setText(Men25_06);
//    ui->tableWidget_25Men->item(0,7)->setText(Men25_07);
//    ui->tableWidget_25Men->item(1,0)->setText(Men25_10);
//    ui->tableWidget_25Men->item(1,1)->setText(Men25_11);
//    ui->tableWidget_25Men->item(1,2)->setText(Men25_12);
//    ui->tableWidget_25Men->item(1,3)->setText(Men25_13);
//    ui->tableWidget_25Men->item(1,4)->setText(Men25_14);
//    ui->tableWidget_25Men->item(1,5)->setText(Men25_15);
//    ui->tableWidget_25Men->item(1,6)->setText(Men25_16);
//    ui->tableWidget_25Men->item(1,7)->setText(Men25_17);

}

RankSettings::~RankSettings()
{
    delete ui;
}

//void RankSettings::on_pushButton_back_clicked()
//{
//    this->close();
//    emit rankMenu();
//}

void RankSettings::on_pushButton_saveChanges_clicked()
{
    QString fr1 = "ranks25men.sav";
    QFile file1(fr1);
    if (file1.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file1);
        qint32 row(ui->tableWidget_25Men->rowCount()), column(ui->tableWidget_25Men->columnCount());
        stream << row << column;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; j++){
                ui->tableWidget_25Men->item(i,j)->write(stream);}
        file1.close();
    }
    QString fr2 = "ranks50men.sav";
    QFile file2(fr2);
    if (file2.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file2);
        qint32 row(ui->tableWidget_50Men->rowCount()), column(ui->tableWidget_50Men->columnCount());
        stream << row << column;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; j++){
                ui->tableWidget_50Men->item(i,j)->write(stream);}
        file2.close();
    }
    QString fr3 = "ranks25women.sav";
    QFile file3(fr3);
    if (file3.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file3);
        qint32 row(ui->tableWidget_25Women->rowCount()), column(ui->tableWidget_25Women->columnCount());
        stream << row << column;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; j++){
                ui->tableWidget_25Women->item(i,j)->write(stream);}
        file3.close();
    }
    QString fr4 = "ranks50women.sav";
    QFile file4(fr4);
    if (file4.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file4);
        qint32 row(ui->tableWidget_50Women->rowCount()), column(ui->tableWidget_50Women->columnCount());
        stream << row << column;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; j++){
                ui->tableWidget_50Women->item(i,j)->write(stream);}
        file4.close();
    }
//    QSettings settings( "settingsRank.conf", QSettings::IniFormat );

//    settings.beginGroup( "Rank_25Men" );

//    settings.setValue("Men25_00", ui->tableWidget_25Men->item(0,0)->text());
//    settings.setValue("Men25_01", ui->tableWidget_25Men->item(0,1)->text());
//    settings.setValue("Men25_02", ui->tableWidget_25Men->item(0,2)->text());
//    settings.setValue("Men25_03", ui->tableWidget_25Men->item(0,3)->text());
//    settings.setValue("Men25_04", ui->tableWidget_25Men->item(0,4)->text());
//    settings.setValue("Men25_05", ui->tableWidget_25Men->item(0,5)->text());
//    settings.setValue("Men25_06", ui->tableWidget_25Men->item(0,6)->text());
//    settings.setValue("Men25_07", ui->tableWidget_25Men->item(0,7)->text());
//    settings.setValue("Men25_10", ui->tableWidget_25Men->item(1,0)->text());
//    settings.setValue("Men25_11", ui->tableWidget_25Men->item(1,1)->text());
//    settings.setValue("Men25_12", ui->tableWidget_25Men->item(1,2)->text());
//    settings.setValue("Men25_13", ui->tableWidget_25Men->item(1,3)->text());
//    settings.setValue("Men25_14", ui->tableWidget_25Men->item(1,4)->text());
//    settings.setValue("Men25_15", ui->tableWidget_25Men->item(1,5)->text());
//    settings.setValue("Men25_16", ui->tableWidget_25Men->item(1,6)->text());
//    settings.setValue("Men25_17", ui->tableWidget_25Men->item(1,7)->text());

//    settings.endGroup();

//    settings.beginGroup( "Rank_50Men" );

//    settings.setValue("Men50_00", ui->tableWidget_50Men->item(0,0)->text());
//    settings.setValue("Men50_01", ui->tableWidget_50Men->item(0,1)->text());
//    settings.setValue("Men50_02", ui->tableWidget_50Men->item(0,2)->text());
//    settings.setValue("Men50_03", ui->tableWidget_50Men->item(0,3)->text());
//    settings.setValue("Men50_04", ui->tableWidget_50Men->item(0,4)->text());
//    settings.setValue("Men50_05", ui->tableWidget_50Men->item(0,5)->text());
//    settings.setValue("Men50_06", ui->tableWidget_50Men->item(0,6)->text());
//    settings.setValue("Men50_07", ui->tableWidget_50Men->item(0,7)->text());
//    settings.setValue("Men50_10", ui->tableWidget_50Men->item(1,0)->text());
//    settings.setValue("Men50_11", ui->tableWidget_50Men->item(1,1)->text());
//    settings.setValue("Men50_12", ui->tableWidget_50Men->item(1,2)->text());
//    settings.setValue("Men50_13", ui->tableWidget_50Men->item(1,3)->text());
//    settings.setValue("Men50_14", ui->tableWidget_50Men->item(1,4)->text());
//    settings.setValue("Men50_15", ui->tableWidget_50Men->item(1,5)->text());
//    settings.setValue("Men50_16", ui->tableWidget_50Men->item(1,6)->text());
//    settings.setValue("Men50_17", ui->tableWidget_50Men->item(1,7)->text());

//    settings.endGroup();
}

void RankSettings::on_pushButton_clicked()
{
    QDesktopServices open;
    QString link = "https://usf.org.ua/ua/Klasyfikatsii-ta-normatyvy.html";
    open.openUrl(QUrl(link));
}
