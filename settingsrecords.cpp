#include "settingsrecords.h"
#include "ui_settingsrecords.h"
#include <QSettings>
#include <qdesktopservices.h>
#include <qurl.h>
SettingsRecords::SettingsRecords(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsRecords)
{
    ui->setupUi(this);
    QSettings settings( "settingsRecords.conf", QSettings::IniFormat );

    settings.beginGroup( "Rank_25Men" );
    QString Men25_VS_50 = settings.value( "Men25_VS_50", ui->lineEdit_25m_freestyle_men50->text()).toString();
    QString Men25_VS_100 = settings.value( "Men25_VS_100", ui->lineEdit_25m_freestyle_men100->text()).toString();
    QString Men25_VS_200 = settings.value( "Men25_VS_200", ui->lineEdit_25m_freestyle_men200->text()).toString();
    QString Men25_VS_400 = settings.value( "Men25_VS_400", ui->lineEdit_25m_freestyle_men400->text()).toString();
    QString Men25_VS_800 = settings.value( "Men25_VS_800", ui->lineEdit_25m_freestyle_men800->text()).toString();
    QString Men25_VS_1500 = settings.value( "Men25_VS_1500", ui->lineEdit_25m_freestyle_men1500->text()).toString();
    QString Men25_VS_4x50 = settings.value( "Men25_VS_4x50", ui->lineEdit_25m_freestyle_men4x50->text()).toString();
    QString Men25_VS_4x100 = settings.value( "Men25_VS_4x100", ui->lineEdit_25m_freestyle_men4x100->text()).toString();
    QString Men25_VS_4x200 = settings.value( "Men25_VS_4x200", ui->lineEdit_25m_freestyle_men4x200->text()).toString();
    QString Men25_back_50 = settings.value( "Men25_back_50", ui->lineEdit_25m_back_men50->text()).toString();
    QString Men25_back_100 = settings.value( "Men25_back_100", ui->lineEdit_25m_back_men100->text()).toString();
    QString Men25_back_200 = settings.value( "Men25_back_200", ui->lineEdit_25m_back_men200->text()).toString();
    QString Men25_but_50 = settings.value( "Men25_but_50", ui->lineEdit_25m_but_men50->text()).toString();
    QString Men25_but_100 = settings.value( "Men25_but_100", ui->lineEdit_25m_but_men100->text()).toString();
    QString Men25_but_200 = settings.value( "Men25_but_200", ui->lineEdit_25m_but_men200->text()).toString();
    QString Men25_bras_50 = settings.value( "Men25_bras_50", ui->lineEdit_25m_bras_men50->text()).toString();
    QString Men25_bras_100 = settings.value( "Men25_bras_100", ui->lineEdit_25m_bras_men100->text()).toString();
    QString Men25_bras_200 = settings.value( "Men25_bras_200", ui->lineEdit_25m_bras_men200->text()).toString();
    QString Men25_complex_100 = settings.value( "Men25_complex_100", ui->lineEdit_25m_complex_men100->text()).toString();
    QString Men25_complex_200 = settings.value( "Men25_complex_100", ui->lineEdit_25m_complex_men200->text()).toString();
    QString Men25_complex_400 = settings.value( "Men25_complex_200", ui->lineEdit_25m_complex_men400->text()).toString();
    QString Men25_complex_4x50 = settings.value( "Men25_complex_4x50", ui->lineEdit_25m_complex_men4x50->text()).toString();
    QString Men25_complex_4x100 = settings.value( "Men25_complex_4x100", ui->lineEdit_25m_complex_men4x100->text()).toString();
    settings.endGroup();
    ui->lineEdit_25m_freestyle_men50->setText(Men25_VS_50);
    ui->lineEdit_25m_freestyle_men100->setText(Men25_VS_100);
    ui->lineEdit_25m_freestyle_men200->setText(Men25_VS_200);
    ui->lineEdit_25m_freestyle_men400->setText(Men25_VS_400);
    ui->lineEdit_25m_freestyle_men800->setText(Men25_VS_800);
    ui->lineEdit_25m_freestyle_men1500->setText(Men25_VS_1500);
    ui->lineEdit_25m_freestyle_men1500->setText(Men25_VS_4x50);
    ui->lineEdit_25m_freestyle_men1500->setText(Men25_VS_4x100);
    ui->lineEdit_25m_freestyle_men1500->setText(Men25_VS_4x200);
    ui->lineEdit_25m_but_men50->setText(Men25_but_50);
    ui->lineEdit_25m_but_men100->setText(Men25_but_100);
    ui->lineEdit_25m_but_men200->setText(Men25_but_200);
    ui->lineEdit_25m_bras_men50->setText(Men25_bras_50);
    ui->lineEdit_25m_bras_men100->setText(Men25_bras_100);
    ui->lineEdit_25m_bras_men200->setText(Men25_bras_200);
    ui->lineEdit_25m_back_men50->setText(Men25_back_50);
    ui->lineEdit_25m_back_men100->setText(Men25_back_100);
    ui->lineEdit_25m_back_men200->setText(Men25_back_200);

}

SettingsRecords::~SettingsRecords()
{
    delete ui;
}

void SettingsRecords::on_pushButton_save_recordsSettings_clicked()
{
        QSettings settings( "settingsRecords.conf", QSettings::IniFormat );

        settings.beginGroup( "Rank_25Men" );

        settings.setValue("Men25_VS_50", ui->lineEdit_25m_freestyle_men50->text());
        settings.setValue("Men25_VS_100", ui->lineEdit_25m_freestyle_men100->text());
        settings.setValue("Men25_VS_200", ui->lineEdit_25m_freestyle_men200->text());
        settings.setValue("Men25_VS_400", ui->lineEdit_25m_freestyle_men400->text());
        settings.setValue("Men25_VS_800", ui->lineEdit_25m_freestyle_men800->text());
        settings.setValue("Men25_VS_1500", ui->lineEdit_25m_freestyle_men1500->text());
        settings.setValue("Men25_VS_4x50", ui->lineEdit_25m_freestyle_men4x50->text());
        settings.setValue("Men25_VS_4x100", ui->lineEdit_25m_freestyle_men4x100->text());
        settings.setValue("Men25_VS_4x200", ui->lineEdit_25m_freestyle_men4x200->text());


        settings.endGroup();
}

void SettingsRecords::on_pushButton_openLinkRecords_clicked()
{
    QDesktopServices open;
    QString link = "http://www.fina.org/fina-rankings/filter/records";
    open.openUrl(QUrl(link));
}
