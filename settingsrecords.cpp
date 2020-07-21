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
    QString Men25_VS_100 = settings.value( "Men25_VS_100", ui->lineEdit_25m_freestyle_men50->text()).toString();
    QString Men25_VS_200 = settings.value( "Men25_VS_200", ui->lineEdit_25m_freestyle_men50->text()).toString();
    QString Men25_VS_400 = settings.value( "Men25_VS_400", ui->lineEdit_25m_freestyle_men50->text()).toString();
    QString Men25_VS_800 = settings.value( "Men25_VS_800", ui->lineEdit_25m_freestyle_men50->text()).toString();
    QString Men25_VS_1500 = settings.value( "Men25_VS_1500", ui->lineEdit_25m_freestyle_men50->text()).toString();

    settings.endGroup();
}

SettingsRecords::~SettingsRecords()
{
    delete ui;
}

void SettingsRecords::on_pushButton_save_recordsSettings_clicked()
{
//        QSettings settings( "settingsRecords.conf", QSettings::IniFormat );

//        settings.beginGroup( "Rank_25Men" );


}

void SettingsRecords::on_pushButton_openLinkRecords_clicked()
{
    QDesktopServices open;
    QString link = "http://www.fina.org/fina-rankings/filter/records";
    open.openUrl(QUrl(link));
}
