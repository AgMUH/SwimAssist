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
    QString Men25_complex_200 = settings.value( "Men25_complex_200", ui->lineEdit_25m_complex_men200->text()).toString();
    QString Men25_complex_400 = settings.value( "Men25_complex_400", ui->lineEdit_25m_complex_men400->text()).toString();
    QString Men25_complex_4x50 = settings.value( "Men25_complex_4x50", ui->lineEdit_25m_complex_men4x50->text()).toString();
    QString Men25_complex_4x100 = settings.value( "Men25_complex_4x100", ui->lineEdit_25m_complex_men4x100->text()).toString();
    settings.endGroup();
    settings.beginGroup( "Rank_25Women" );
    QString Women25_VS_50 = settings.value( "Women25_VS_50", ui->lineEdit_25m_freestyle_women50->text()).toString();
    QString Women25_VS_100 = settings.value( "Women25_VS_100", ui->lineEdit_25m_freestyle_women100->text()).toString();
    QString Women25_VS_200 = settings.value( "Women25_VS_200", ui->lineEdit_25m_freestyle_women200->text()).toString();
    QString Women25_VS_400 = settings.value( "Women25_VS_400", ui->lineEdit_25m_freestyle_women400->text()).toString();
    QString Women25_VS_800 = settings.value( "Women25_VS_800", ui->lineEdit_25m_freestyle_women800->text()).toString();
    QString Women25_VS_1500 = settings.value( "Women25_VS_1500", ui->lineEdit_25m_freestyle_women1500->text()).toString();
    QString Women25_VS_4x50 = settings.value( "Women25_VS_4x50", ui->lineEdit_25m_freestyle_women4x50->text()).toString();
    QString Women25_VS_4x100 = settings.value( "Women25_VS_4x100", ui->lineEdit_25m_freestyle_women4x100->text()).toString();
    QString Women25_VS_4x200 = settings.value( "Women25_VS_4x200", ui->lineEdit_25m_freestyle_women4x200->text()).toString();
    QString Women25_back_50 = settings.value( "Women25_back_50", ui->lineEdit_25m_back_women50->text()).toString();
    QString Women25_back_100 = settings.value( "Women25_back_100", ui->lineEdit_25m_back_women100->text()).toString();
    QString Women25_back_200 = settings.value( "Women25_back_200", ui->lineEdit_25m_back_women200->text()).toString();
    QString Women25_but_50 = settings.value( "Women25_but_50", ui->lineEdit_25m_but_women50->text()).toString();
    QString Women25_but_100 = settings.value( "Women25_but_100", ui->lineEdit_25m_but_women100->text()).toString();
    QString Women25_but_200 = settings.value( "Women25_but_200", ui->lineEdit_25m_but_women200->text()).toString();
    QString Women25_bras_50 = settings.value( "Women25_bras_50", ui->lineEdit_25m_bras_women50->text()).toString();
    QString Women25_bras_100 = settings.value( "Women25_bras_100", ui->lineEdit_25m_bras_women100->text()).toString();
    QString Women25_bras_200 = settings.value( "Women25_bras_200", ui->lineEdit_25m_bras_women200->text()).toString();
    QString Women25_complex_100 = settings.value( "Women25_complex_100", ui->lineEdit_25m_complex_women100->text()).toString();
    QString Women25_complex_200 = settings.value( "Women25_complex_200", ui->lineEdit_25m_complex_women200->text()).toString();
    QString Women25_complex_400 = settings.value( "Women25_complex_400", ui->lineEdit_25m_complex_women400->text()).toString();
    QString Women25_complex_4x50 = settings.value( "Women25_complex_4x50", ui->lineEdit_25m_complex_women4x50->text()).toString();
    QString Women25_complex_4x100 = settings.value( "Women25_complex_4x100", ui->lineEdit_25m_complex_women4x100->text()).toString();
    settings.endGroup();

    settings.beginGroup( "Rank_50Men" );
    QString Men50_VS_50 = settings.value( "Men50_VS_50", ui->lineEdit_50m_freestyle_men50->text()).toString();
    QString Men50_VS_100 = settings.value( "Men50_VS_100", ui->lineEdit_50m_freestyle_men100->text()).toString();
    QString Men50_VS_200 = settings.value( "Men50_VS_200", ui->lineEdit_50m_freestyle_men200->text()).toString();
    QString Men50_VS_400 = settings.value( "Men50_VS_400", ui->lineEdit_50m_freestyle_men400->text()).toString();
    QString Men50_VS_800 = settings.value( "Men50_VS_800", ui->lineEdit_50m_freestyle_men800->text()).toString();
    QString Men50_VS_1500 = settings.value( "Men50_VS_1500", ui->lineEdit_50m_freestyle_men1500->text()).toString();
    QString Men50_VS_4x100 = settings.value( "Men50_VS_4x100", ui->lineEdit_50m_freestyle_men4x100->text()).toString();
    QString Men50_VS_4x200 = settings.value( "Men50_VS_4x200", ui->lineEdit_50m_freestyle_men4x200->text()).toString();
    QString Men50_back_50 = settings.value( "Men50_back_50", ui->lineEdit_50m_back_men50->text()).toString();
    QString Men50_back_100 = settings.value( "Men50_back_100", ui->lineEdit_50m_back_men100->text()).toString();
    QString Men50_back_200 = settings.value( "Men50_back_200", ui->lineEdit_50m_back_men200->text()).toString();
    QString Men50_but_50 = settings.value( "Men50_but_50", ui->lineEdit_50m_but_men50->text()).toString();
    QString Men50_but_100 = settings.value( "Men50_but_100", ui->lineEdit_50m_but_men100->text()).toString();
    QString Men50_but_200 = settings.value( "Men50_but_200", ui->lineEdit_50m_but_men200->text()).toString();
    QString Men50_bras_50 = settings.value( "Men50_bras_50", ui->lineEdit_50m_bras_men50->text()).toString();
    QString Men50_bras_100 = settings.value( "Men50_bras_100", ui->lineEdit_50m_bras_men100->text()).toString();
    QString Men50_bras_200 = settings.value( "Men50_bras_200", ui->lineEdit_50m_bras_men200->text()).toString();
    QString Men50_complex_200 = settings.value( "Men50_complex_200", ui->lineEdit_50m_complex_men200->text()).toString();
    QString Men50_complex_400 = settings.value( "Men50_complex_400", ui->lineEdit_50m_complex_men400->text()).toString();
    QString Men50_complex_4x100 = settings.value( "Men50_complex_4x100", ui->lineEdit_50m_complex_men4x100->text()).toString();
    settings.endGroup();
    settings.beginGroup( "Rank_50Women" );
    QString Women50_VS_50 = settings.value( "Women50_VS_50", ui->lineEdit_50m_freestyle_women50->text()).toString();
    QString Women50_VS_100 = settings.value( "Women50_VS_100", ui->lineEdit_50m_freestyle_women100->text()).toString();
    QString Women50_VS_200 = settings.value( "Women50_VS_200", ui->lineEdit_50m_freestyle_women200->text()).toString();
    QString Women50_VS_400 = settings.value( "Women50_VS_400", ui->lineEdit_50m_freestyle_women400->text()).toString();
    QString Women50_VS_800 = settings.value( "Women50_VS_800", ui->lineEdit_50m_freestyle_women800->text()).toString();
    QString Women50_VS_1500 = settings.value( "Women50_VS_1500", ui->lineEdit_50m_freestyle_women1500->text()).toString();
    QString Women50_VS_4x100 = settings.value( "Women50_VS_4x100", ui->lineEdit_50m_freestyle_women4x100->text()).toString();
    QString Women50_VS_4x200 = settings.value( "Women50_VS_4x200", ui->lineEdit_50m_freestyle_women4x200->text()).toString();
    QString Women50_back_50 = settings.value( "Women50_back_50", ui->lineEdit_50m_back_women50->text()).toString();
    QString Women50_back_100 = settings.value( "Women50_back_100", ui->lineEdit_50m_back_women100->text()).toString();
    QString Women50_back_200 = settings.value( "Women50_back_200", ui->lineEdit_50m_back_women200->text()).toString();
    QString Women50_but_50 = settings.value( "Women50_but_50", ui->lineEdit_50m_but_women50->text()).toString();
    QString Women50_but_100 = settings.value( "Women50_but_100", ui->lineEdit_50m_but_women100->text()).toString();
    QString Women50_but_200 = settings.value( "Women50_but_200", ui->lineEdit_50m_but_women200->text()).toString();
    QString Women50_bras_50 = settings.value( "Women50_bras_50", ui->lineEdit_50m_bras_women50->text()).toString();
    QString Women50_bras_100 = settings.value( "Women50_bras_100", ui->lineEdit_50m_bras_women100->text()).toString();
    QString Women50_bras_200 = settings.value( "Women50_bras_200", ui->lineEdit_50m_bras_women200->text()).toString();
    QString Women50_complex_200 = settings.value( "Women50_complex_200", ui->lineEdit_50m_complex_women200->text()).toString();
    QString Women50_complex_400 = settings.value( "Women50_complex_400", ui->lineEdit_50m_complex_women400->text()).toString();
    QString Women50_complex_4x100 = settings.value( "Women50_complex_4x100", ui->lineEdit_50m_complex_women4x100->text()).toString();
    settings.endGroup();

    settings.beginGroup("Rank_Common");
    QString Mixed50_VS_4x100 = settings.value( "Mixed50_VS_4x100", ui->lineEdit_50m_Freestyle_Mixed_4x100->text()).toString();
    QString Mixed50_complex_4x100 = settings.value( "Mixed50_complex_4x100", ui->lineEdit_50m_complex_Mixed_4x100->text()).toString();
    QString Mixed25_VS_4x50 = settings.value( "Mixed25_VS_4x50", ui->lineEdit_25m_Freestyle_Mixed_4x50m->text()).toString();
    QString Mixed25_VS_4x100 = settings.value( "Mixed25_VS_4x100", ui->lineEdit_25m_Freestyle_Mixed_4x100->text()).toString();
    QString Mixed25_complex_4x50 = settings.value( "Mixed25_complex_4x25", ui->lineEdit_25m_Complex_Mixed_4x50->text()).toString();
    QString Mixed25_complex_4x100 = settings.value( "Mixed25_complex_4x100", ui->lineEdit_25m_Complex_Mixed_4x100->text()).toString();

    settings.endGroup();
    ui->lineEdit_50m_Freestyle_Mixed_4x100->setText(Mixed50_VS_4x100);
    ui->lineEdit_50m_complex_Mixed_4x100->setText(Mixed50_complex_4x100);
    ui->lineEdit_25m_Freestyle_Mixed_4x50m->setText(Mixed25_VS_4x50);
    ui->lineEdit_25m_Freestyle_Mixed_4x100->setText(Mixed25_VS_4x100);
    ui->lineEdit_25m_Complex_Mixed_4x50->setText(Mixed25_complex_4x50);
    ui->lineEdit_25m_Complex_Mixed_4x100->setText(Mixed25_complex_4x100);

    ui->lineEdit_25m_freestyle_men50->setText(Men25_VS_50);
    ui->lineEdit_25m_freestyle_men100->setText(Men25_VS_100);
    ui->lineEdit_25m_freestyle_men200->setText(Men25_VS_200);
    ui->lineEdit_25m_freestyle_men400->setText(Men25_VS_400);
    ui->lineEdit_25m_freestyle_men800->setText(Men25_VS_800);
    ui->lineEdit_25m_freestyle_men1500->setText(Men25_VS_1500);
    ui->lineEdit_25m_freestyle_men4x50->setText(Men25_VS_4x50);
    ui->lineEdit_25m_freestyle_men4x100->setText(Men25_VS_4x100);
    ui->lineEdit_25m_freestyle_men4x200->setText(Men25_VS_4x200);
    ui->lineEdit_25m_but_men50->setText(Men25_but_50);
    ui->lineEdit_25m_but_men100->setText(Men25_but_100);
    ui->lineEdit_25m_but_men200->setText(Men25_but_200);
    ui->lineEdit_25m_bras_men50->setText(Men25_bras_50);
    ui->lineEdit_25m_bras_men100->setText(Men25_bras_100);
    ui->lineEdit_25m_bras_men200->setText(Men25_bras_200);
    ui->lineEdit_25m_back_men50->setText(Men25_back_50);
    ui->lineEdit_25m_back_men100->setText(Men25_back_100);
    ui->lineEdit_25m_back_men200->setText(Men25_back_200);
    ui->lineEdit_25m_complex_men100->setText(Men25_complex_100);
    ui->lineEdit_25m_complex_men200->setText(Men25_complex_200);
    ui->lineEdit_25m_complex_men400->setText(Men25_complex_400);
    ui->lineEdit_25m_complex_men4x50->setText(Men25_complex_4x50);
    ui->lineEdit_25m_complex_men4x100->setText(Men25_complex_4x100);

    ui->lineEdit_25m_freestyle_women50->setText(Women25_VS_50);
    ui->lineEdit_25m_freestyle_women100->setText(Women25_VS_100);
    ui->lineEdit_25m_freestyle_women200->setText(Women25_VS_200);
    ui->lineEdit_25m_freestyle_women400->setText(Women25_VS_400);
    ui->lineEdit_25m_freestyle_women800->setText(Women25_VS_800);
    ui->lineEdit_25m_freestyle_women1500->setText(Women25_VS_1500);
    ui->lineEdit_25m_freestyle_women4x50->setText(Women25_VS_4x50);
    ui->lineEdit_25m_freestyle_women4x100->setText(Women25_VS_4x100);
    ui->lineEdit_25m_freestyle_women4x200->setText(Women25_VS_4x200);
    ui->lineEdit_25m_but_women50->setText(Women25_but_50);
    ui->lineEdit_25m_but_women100->setText(Women25_but_100);
    ui->lineEdit_25m_but_women200->setText(Women25_but_200);
    ui->lineEdit_25m_bras_women50->setText(Women25_bras_50);
    ui->lineEdit_25m_bras_women100->setText(Women25_bras_100);
    ui->lineEdit_25m_bras_women200->setText(Women25_bras_200);
    ui->lineEdit_25m_back_women50->setText(Women25_back_50);
    ui->lineEdit_25m_back_women100->setText(Women25_back_100);
    ui->lineEdit_25m_back_women200->setText(Women25_back_200);
    ui->lineEdit_25m_complex_women100->setText(Women25_complex_100);
    ui->lineEdit_25m_complex_women200->setText(Women25_complex_200);
    ui->lineEdit_25m_complex_women400->setText(Women25_complex_400);
    ui->lineEdit_25m_complex_women4x50->setText(Women25_complex_4x50);
    ui->lineEdit_25m_complex_women4x100->setText(Women25_complex_4x100);

    ui->lineEdit_50m_freestyle_men50->setText(Men50_VS_50);
    ui->lineEdit_50m_freestyle_men100->setText(Men50_VS_100);
    ui->lineEdit_50m_freestyle_men200->setText(Men50_VS_200);
    ui->lineEdit_50m_freestyle_men400->setText(Men50_VS_400);
    ui->lineEdit_50m_freestyle_men800->setText(Men50_VS_800);
    ui->lineEdit_50m_freestyle_men1500->setText(Men50_VS_1500);
    ui->lineEdit_50m_freestyle_men4x100->setText(Men50_VS_4x100);
    ui->lineEdit_50m_freestyle_men4x200->setText(Men50_VS_4x200);
    ui->lineEdit_50m_but_men50->setText(Men50_but_50);
    ui->lineEdit_50m_but_men100->setText(Men50_but_100);
    ui->lineEdit_50m_but_men200->setText(Men50_but_200);
    ui->lineEdit_50m_bras_men50->setText(Men50_bras_50);
    ui->lineEdit_50m_bras_men100->setText(Men50_bras_100);
    ui->lineEdit_50m_bras_men200->setText(Men50_bras_200);
    ui->lineEdit_50m_back_men50->setText(Men50_back_50);
    ui->lineEdit_50m_back_men100->setText(Men50_back_100);
    ui->lineEdit_50m_back_men200->setText(Men50_back_200);
    ui->lineEdit_50m_complex_men200->setText(Men50_complex_200);
    ui->lineEdit_50m_complex_men400->setText(Men50_complex_400);
    ui->lineEdit_50m_complex_men4x100->setText(Men50_complex_4x100);

    ui->lineEdit_50m_freestyle_women50->setText(Women50_VS_50);
    ui->lineEdit_50m_freestyle_women100->setText(Women50_VS_100);
    ui->lineEdit_50m_freestyle_women200->setText(Women50_VS_200);
    ui->lineEdit_50m_freestyle_women400->setText(Women50_VS_400);
    ui->lineEdit_50m_freestyle_women800->setText(Women50_VS_800);
    ui->lineEdit_50m_freestyle_women1500->setText(Women50_VS_1500);
    ui->lineEdit_50m_freestyle_women4x100->setText(Women50_VS_4x100);
    ui->lineEdit_50m_freestyle_women4x200->setText(Women50_VS_4x200);
    ui->lineEdit_50m_but_women50->setText(Women50_but_50);
    ui->lineEdit_50m_but_women100->setText(Women50_but_100);
    ui->lineEdit_50m_but_women200->setText(Women50_but_200);
    ui->lineEdit_50m_bras_women50->setText(Women50_bras_50);
    ui->lineEdit_50m_bras_women100->setText(Women50_bras_100);
    ui->lineEdit_50m_bras_women200->setText(Women50_bras_200);
    ui->lineEdit_50m_back_women50->setText(Women50_back_50);
    ui->lineEdit_50m_back_women100->setText(Women50_back_100);
    ui->lineEdit_50m_back_women200->setText(Women50_back_200);
    ui->lineEdit_50m_complex_women200->setText(Women50_complex_200);
    ui->lineEdit_50m_complex_women400->setText(Women50_complex_400);
    ui->lineEdit_50m_complex_women4x100->setText(Women50_complex_4x100);
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
        settings.setValue("Men25_but_50", ui->lineEdit_25m_but_men50->text());
        settings.setValue("Men25_but_100", ui->lineEdit_25m_but_men100->text());
        settings.setValue("Men25_but_200", ui->lineEdit_25m_but_men200->text());
        settings.setValue("Men25_bras_50", ui->lineEdit_25m_bras_men50->text());
        settings.setValue("Men25_bras_100", ui->lineEdit_25m_bras_men100->text());
        settings.setValue("Men25_bras_200", ui->lineEdit_25m_bras_men200->text());
        settings.setValue("Men25_back_50", ui->lineEdit_25m_back_men50->text());
        settings.setValue("Men25_back_100", ui->lineEdit_25m_back_men100->text());
        settings.setValue("Men25_back_200", ui->lineEdit_25m_back_men200->text());
        settings.setValue("Men25_complex_100", ui->lineEdit_25m_complex_men100->text());
        settings.setValue("Men25_complex_200", ui->lineEdit_25m_complex_men200->text());
        settings.setValue("Men25_complex_400", ui->lineEdit_25m_complex_men400->text());
        settings.setValue("Men25_complex_4x50", ui->lineEdit_25m_complex_men4x50->text());
        settings.setValue("Men25_complex_4x100", ui->lineEdit_25m_complex_men4x100->text());

        settings.endGroup();

        settings.beginGroup( "Rank_25Women" );

        settings.setValue("Women25_VS_50", ui->lineEdit_25m_freestyle_women50->text());
        settings.setValue("Women25_VS_100", ui->lineEdit_25m_freestyle_women100->text());
        settings.setValue("Women25_VS_200", ui->lineEdit_25m_freestyle_women200->text());
        settings.setValue("Women25_VS_400", ui->lineEdit_25m_freestyle_women400->text());
        settings.setValue("Women25_VS_800", ui->lineEdit_25m_freestyle_women800->text());
        settings.setValue("Women25_VS_1500", ui->lineEdit_25m_freestyle_women1500->text());
        settings.setValue("Women25_VS_4x50", ui->lineEdit_25m_freestyle_women4x50->text());
        settings.setValue("Women25_VS_4x100", ui->lineEdit_25m_freestyle_women4x100->text());
        settings.setValue("Women25_VS_4x200", ui->lineEdit_25m_freestyle_women4x200->text());
        settings.setValue("Women25_but_50", ui->lineEdit_25m_but_women50->text());
        settings.setValue("Women25_but_100", ui->lineEdit_25m_but_women100->text());
        settings.setValue("Women25_but_200", ui->lineEdit_25m_but_women200->text());
        settings.setValue("Women25_bras_50", ui->lineEdit_25m_bras_women50->text());
        settings.setValue("Women25_bras_100", ui->lineEdit_25m_bras_women100->text());
        settings.setValue("Women25_bras_200", ui->lineEdit_25m_bras_women200->text());
        settings.setValue("Women25_back_50", ui->lineEdit_25m_back_women50->text());
        settings.setValue("Women25_back_100", ui->lineEdit_25m_back_women100->text());
        settings.setValue("Women25_back_200", ui->lineEdit_25m_back_women200->text());
        settings.setValue("Women25_complex_100", ui->lineEdit_25m_complex_women100->text());
        settings.setValue("Women25_complex_200", ui->lineEdit_25m_complex_women200->text());
        settings.setValue("Women25_complex_400", ui->lineEdit_25m_complex_women400->text());
        settings.setValue("Women25_complex_4x50", ui->lineEdit_25m_complex_women4x50->text());
        settings.setValue("Women25_complex_4x100", ui->lineEdit_25m_complex_women4x100->text());

        settings.endGroup();

        settings.beginGroup( "Rank_50Men" );

        settings.setValue("Men50_VS_50", ui->lineEdit_50m_freestyle_men50->text());
        settings.setValue("Men50_VS_100", ui->lineEdit_50m_freestyle_men100->text());
        settings.setValue("Men50_VS_200", ui->lineEdit_50m_freestyle_men200->text());
        settings.setValue("Men50_VS_400", ui->lineEdit_50m_freestyle_men400->text());
        settings.setValue("Men50_VS_800", ui->lineEdit_50m_freestyle_men800->text());
        settings.setValue("Men50_VS_1500", ui->lineEdit_50m_freestyle_men1500->text());
        settings.setValue("Men50_VS_4x100", ui->lineEdit_50m_freestyle_men4x100->text());
        settings.setValue("Men50_VS_4x200", ui->lineEdit_50m_freestyle_men4x200->text());
        settings.setValue("Men50_but_50", ui->lineEdit_50m_but_men50->text());
        settings.setValue("Men50_but_100", ui->lineEdit_50m_but_men100->text());
        settings.setValue("Men50_but_200", ui->lineEdit_50m_but_men200->text());
        settings.setValue("Men50_bras_50", ui->lineEdit_50m_bras_men50->text());
        settings.setValue("Men50_bras_100", ui->lineEdit_50m_bras_men100->text());
        settings.setValue("Men50_bras_200", ui->lineEdit_50m_bras_men200->text());
        settings.setValue("Men50_back_50", ui->lineEdit_50m_back_men50->text());
        settings.setValue("Men50_back_100", ui->lineEdit_50m_back_men100->text());
        settings.setValue("Men50_back_200", ui->lineEdit_50m_back_men200->text());
        settings.setValue("Men50_complex_200", ui->lineEdit_50m_complex_men200->text());
        settings.setValue("Men50_complex_400", ui->lineEdit_50m_complex_men400->text());
        settings.setValue("Men50_complex_4x100", ui->lineEdit_50m_complex_men4x100->text());

        settings.endGroup();

        settings.beginGroup( "Rank_50Women" );

        settings.setValue("Women50_VS_50", ui->lineEdit_50m_freestyle_women50->text());
        settings.setValue("Women50_VS_100", ui->lineEdit_50m_freestyle_women100->text());
        settings.setValue("Women50_VS_200", ui->lineEdit_50m_freestyle_women200->text());
        settings.setValue("Women50_VS_400", ui->lineEdit_50m_freestyle_women400->text());
        settings.setValue("Women50_VS_800", ui->lineEdit_50m_freestyle_women800->text());
        settings.setValue("Women50_VS_1500", ui->lineEdit_50m_freestyle_women1500->text());
        settings.setValue("Women50_VS_4x100", ui->lineEdit_50m_freestyle_women4x100->text());
        settings.setValue("Women50_VS_4x200", ui->lineEdit_50m_freestyle_women4x200->text());
        settings.setValue("Women50_but_50", ui->lineEdit_50m_but_women50->text());
        settings.setValue("Women50_but_100", ui->lineEdit_50m_but_women100->text());
        settings.setValue("Women50_but_200", ui->lineEdit_50m_but_women200->text());
        settings.setValue("Women50_bras_50", ui->lineEdit_50m_bras_women50->text());
        settings.setValue("Women50_bras_100", ui->lineEdit_50m_bras_women100->text());
        settings.setValue("Women50_bras_200", ui->lineEdit_50m_bras_women200->text());
        settings.setValue("Women50_back_50", ui->lineEdit_50m_back_women50->text());
        settings.setValue("Women50_back_100", ui->lineEdit_50m_back_women100->text());
        settings.setValue("Women50_back_200", ui->lineEdit_50m_back_women200->text());
        settings.setValue("Women50_complex_200", ui->lineEdit_50m_complex_women200->text());
        settings.setValue("Women50_complex_400", ui->lineEdit_50m_complex_women400->text());
        settings.setValue("Women50_complex_4x100", ui->lineEdit_50m_complex_women4x100->text());

        settings.endGroup();


        settings.beginGroup("Rank_Common");
        settings.setValue("Mixed50_VS_4x100", ui->lineEdit_50m_Freestyle_Mixed_4x100->text());
        settings.setValue("Mixed50_complex_4x100", ui->lineEdit_50m_complex_Mixed_4x100->text());
        settings.setValue("Mixed25_VS_4x50", ui->lineEdit_25m_Freestyle_Mixed_4x50m->text());
        settings.setValue("Mixed25_VS_4x100", ui->lineEdit_25m_Freestyle_Mixed_4x100->text());
        settings.setValue("Mixed25_complex_4x50", ui->lineEdit_25m_Complex_Mixed_4x50->text());
        settings.setValue("Mixed25_complex_4x100", ui->lineEdit_25m_Complex_Mixed_4x100->text());
        settings.endGroup();
}

void SettingsRecords::on_pushButton_openLinkRecords_clicked()
{
    QDesktopServices open;
    QString link = "http://www.fina.org/fina-rankings/filter/records";
    open.openUrl(QUrl(link));
}
