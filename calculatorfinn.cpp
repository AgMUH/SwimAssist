#include "calculatorfinn.h"
#include "ui_calculatorfinn.h"
#include "settingsrecords.h"
#include "ui_settingsrecords.h"
#include "math.h"
CalculatorFinn::CalculatorFinn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatorFinn)
{
    ui->setupUi(this);
}

CalculatorFinn::~CalculatorFinn()
{
    delete ui;
}

void CalculatorFinn::on_pushButton_calculate_clicked()
{
    SettingsRecords * finn = new SettingsRecords();
    QString
            poolLength = ui->comboBox_lengthPool->currentText(),
            gender     = ui->comboBox_sex->currentText(),
            distance   = ui->comboBox_distance->currentText(),
            typeSwim   = ui->comboBox_typeSwim->currentText();
    double
            seconds    = ui->comboBox_seconds->currentText().toInt(),
            milisec    = ui->comboBox_miliseconds->currentText().toInt(),
            minutes    = ui->comboBox_minutes->currentText().toInt(),
            recSeconds = 0;
    int     points     = 0;

    //----------------------------50m-------------------------
    if(poolLength == "50м"){
        //------------------------Ч---------------------------
        if(gender == "Ч"){
            if(typeSwim == "Вільний стиль"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_men50->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_men100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_men200->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="400м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men400->text().mid(0,2).toDouble()*60;
                    seconds = seconds + (minutes*60);
                    seconds = seconds + (milisec/100);
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_men400->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men400->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="800м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men800->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_men800->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men800->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="1500м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men1500->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_men1500->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men1500->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x100м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men4x100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_men4x100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men4x100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x200м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_men4x200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_men4x200->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_men4x200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Брас"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_50m_bras_men50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_bras_men50->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_bras_men50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_50m_bras_men100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_bras_men100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_bras_men100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_50m_bras_men200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_bras_men200->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_bras_men200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Батерфляй"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_50m_but_men50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_but_men50->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_men50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_50m_but_men100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_but_men100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_men100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_50m_but_men200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_but_men200->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_men200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "На спині"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_50m_back_men50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_back_men50->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_back_men50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_50m_back_men100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_back_men100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_back_men100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_50m_back_men200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_back_men200->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_back_men200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Комплекс"){
                if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_50m_complex_men200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_complex_men200->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_men200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="400м"){
                    recSeconds = finn->ui->lineEdit_50m_complex_men400->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_complex_men400->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_men400->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x100м"){
                    recSeconds = finn->ui->lineEdit_50m_complex_men4x100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_complex_men4x100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_men4x100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
        }
        //------------------------Ж---------------------------
        else if(gender == "Ж"){
            if(typeSwim == "Вільний стиль"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_women50->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_women100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_women200->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="400м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women400->text().mid(0,2).toDouble()*60;
                    seconds = seconds + (minutes*60);
                    seconds = seconds + (milisec/100);
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_women400->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women400->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="800м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women800->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_women800->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women800->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="1500м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women1500->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_women1500->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women1500->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x100м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women4x100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_women4x100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women4x100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x200м"){
                    recSeconds = finn->ui->lineEdit_50m_freestyle_women4x200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_freestyle_women4x200->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_freestyle_women4x200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Брас"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_50m_bras_women50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_bras_women50->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_bras_women50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_50m_bras_women100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_bras_women100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_bras_women100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_50m_bras_women200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_bras_women200->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_bras_women200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Батерфляй"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_50m_but_women50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_but_women50->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_women50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_50m_but_women100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_but_women100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_women100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_50m_but_women200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_but_women200->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_women200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "На спині"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_50m_back_women50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_back_women50->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_back_women50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_50m_back_women100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_back_women100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_back_women100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_50m_back_women200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_back_women200->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_back_women200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Комплекс"){
                if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_50m_complex_women200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_complex_women200->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_women200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="400м"){
                    recSeconds = finn->ui->lineEdit_50m_complex_women400->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_complex_women400->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_women400->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x100м"){
                    recSeconds = finn->ui->lineEdit_50m_complex_women4x100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_complex_women4x100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_women4x100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
        }
        else if(gender == "Зм"){
            if(typeSwim == "Вільний стиль"){
                if(distance=="4x100м"){
                    recSeconds = finn->ui->lineEdit_50m_Freestyle_Mixed_4x100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_Freestyle_Mixed_4x100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_Freestyle_Mixed_4x100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Комплекс"){
                if(distance=="4x100м"){
                    recSeconds = finn->ui->lineEdit_50m_complex_Mixed_4x100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_complex_Mixed_4x100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_Mixed_4x100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
        }
    }
    //----------------------------25m-------------------------
    else if(poolLength=="25м"){
        //------------------------Ч---------------------------
        if(gender == "Ч"){
            if(typeSwim == "Вільний стиль"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_men50->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_men100->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_men200->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="400м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men400->text().mid(0,2).toDouble()*60;
                    seconds = seconds + (minutes*60);
                    seconds = seconds + (milisec/100);
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_men400->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men400->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="800м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men800->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_men800->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men800->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="1500м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men1500->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_men1500->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men1500->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x50м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men4x50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_men4x50->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men4x50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x100м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men4x100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_men4x100->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men4x100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x200м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_men4x200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_men4x200->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_men4x200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Брас"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_25m_bras_men50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_bras_men50->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_bras_men50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_25m_bras_men100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_bras_men100->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_bras_men100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_25m_bras_men200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_bras_men200->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_bras_men200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Батерфляй"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_25m_but_men50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_but_men50->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_men50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_25m_but_men100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_but_men100->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_but_men100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_25m_but_men200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_but_men200->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_but_men200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "На спині"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_25m_back_men50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_back_men50->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_back_men50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_25m_back_men100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_back_men100->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_back_men100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_25m_back_men200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_back_men200->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_back_men200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Комплекс"){
                if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_25m_complex_men200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_complex_men200->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_men200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="400м"){
                    recSeconds = finn->ui->lineEdit_25m_complex_men400->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_complex_men400->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_men400->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x50м"){
                    recSeconds = finn->ui->lineEdit_25m_complex_men4x50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_complex_men4x50->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_men4x50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x100м"){
                    recSeconds = finn->ui->lineEdit_25m_complex_men4x100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_complex_men4x100->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_men4x100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
        }
        //------------------------Ж---------------------------
        else if(gender == "Ж"){
            if(typeSwim == "Вільний стиль"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_women50->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_women100->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_women200->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="400м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women400->text().mid(0,2).toDouble()*60;
                    seconds = seconds + (minutes*60);
                    seconds = seconds + (milisec/100);
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_women400->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women400->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="800м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women800->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_women800->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women800->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="1500м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women1500->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_women1500->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women1500->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x50м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women4x50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_women4x50->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women4x50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x100м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women4x100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_women4x100->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women4x100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x200м"){
                    recSeconds = finn->ui->lineEdit_25m_freestyle_women4x200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_freestyle_women4x200->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_freestyle_women4x200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Брас"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_25m_bras_women50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_bras_women50->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_bras_women50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_25m_bras_women100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_bras_women100->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_bras_women100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_25m_bras_women200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_bras_women200->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_bras_women200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Батерфляй"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_25m_but_women50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_but_women50->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_but_women50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_25m_but_women100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_but_women100->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_but_women100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_25m_but_women200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_but_women200->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_but_women200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "На спині"){
                if(distance=="50м"){
                    recSeconds = finn->ui->lineEdit_25m_back_women50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_back_women50->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_back_women50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="100м"){
                    recSeconds = finn->ui->lineEdit_25m_back_women100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_back_women100->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_back_women100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_25m_back_women200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_back_women200->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_back_women200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Комплекс"){
                if(distance=="200м"){
                    recSeconds = finn->ui->lineEdit_25m_complex_women200->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_complex_women200->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_women200->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="400м"){
                    recSeconds = finn->ui->lineEdit_25m_complex_women400->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_complex_women400->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_women400->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x50м"){
                    recSeconds = finn->ui->lineEdit_25m_complex_women4x50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_complex_women4x50->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_women4x50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x100м"){
                    recSeconds = finn->ui->lineEdit_25m_complex_women4x100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_complex_women4x100->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_complex_women4x100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
        }
        else if(gender == "Зм"){
            if(typeSwim == "Вільний стиль"){
                if(distance=="4x100м"){
                    recSeconds = finn->ui->lineEdit_50m_Freestyle_Mixed_4x100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_Freestyle_Mixed_4x100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_Freestyle_Mixed_4x100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x50м"){
                    recSeconds = finn->ui->lineEdit_25m_Freestyle_Mixed_4x50m->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_Freestyle_Mixed_4x50m->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_Freestyle_Mixed_4x50m->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
            else if(typeSwim == "Комплекс"){
                if(distance=="4x100м"){
                    recSeconds = finn->ui->lineEdit_50m_complex_Mixed_4x100->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_50m_complex_Mixed_4x100->text());
                    points = 1000* pow(((finn->ui->lineEdit_50m_complex_Mixed_4x100->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
                else if(distance=="4x50м"){
                    recSeconds = finn->ui->lineEdit_25m_Complex_Mixed_4x50->text().mid(0,2).toDouble()*60;
                    if(minutes!=0){
                        seconds=seconds+(minutes*60);
                    }
                    seconds = seconds + milisec/100;
                    ui->lineEdit_baseTime->setText(finn->ui->lineEdit_25m_Complex_Mixed_4x50->text());
                    points = 1000* pow(((finn->ui->lineEdit_25m_Complex_Mixed_4x50->text().mid(3,7).toDouble() + recSeconds) / seconds),3);
                }
            }
        }
    }
    ui->lineEdit_pointsFina->setText(QString::number(points));
}
