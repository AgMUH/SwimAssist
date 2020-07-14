#include "ranksettings.h"
#include "ui_ranksettings.h"
#include <QSettings>
#include <QFile>
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
//        QString Men25_20 = settings.value( "Men25_20", ui->tableWidget_25Men->item(2,0)->text()).toString();
//        QString Men25_21 = settings.value( "Men25_21", ui->tableWidget_25Men->item(2,1)->text()).toString();
//        QString Men25_22 = settings.value( "Men25_22", ui->tableWidget_25Men->item(2,2)->text()).toString();
//        QString Men25_23 = settings.value( "Men25_23", ui->tableWidget_25Men->item(2,3)->text()).toString();
//        QString Men25_24 = settings.value( "Men25_24", ui->tableWidget_25Men->item(2,4)->text()).toString();
//        QString Men25_25 = settings.value( "Men25_25", ui->tableWidget_25Men->item(2,5)->text()).toString();
//        QString Men25_26 = settings.value( "Men25_26", ui->tableWidget_25Men->item(2,6)->text()).toString();
//        QString Men25_27 = settings.value( "Men25_27", ui->tableWidget_25Men->item(2,7)->text()).toString();
//        QString Men25_30 = settings.value( "Men25_30", ui->tableWidget_25Men->item(3,0)->text()).toString();
//        QString Men25_31 = settings.value( "Men25_31", ui->tableWidget_25Men->item(3,1)->text()).toString();
//        QString Men25_32 = settings.value( "Men25_32", ui->tableWidget_25Men->item(3,2)->text()).toString();
//        QString Men25_33 = settings.value( "Men25_33", ui->tableWidget_25Men->item(3,3)->text()).toString();
//        QString Men25_34 = settings.value( "Men25_34", ui->tableWidget_25Men->item(3,4)->text()).toString();
//        QString Men25_35 = settings.value( "Men25_35", ui->tableWidget_25Men->item(3,5)->text()).toString();
//        QString Men25_36 = settings.value( "Men25_36", ui->tableWidget_25Men->item(3,6)->text()).toString();
//        QString Men25_37 = settings.value( "Men25_37", ui->tableWidget_25Men->item(3,7)->text()).toString();
//        QString Men25_40 = settings.value( "Men25_40", ui->tableWidget_25Men->item(4,0)->text()).toString();
//        QString Men25_41 = settings.value( "Men25_41", ui->tableWidget_25Men->item(4,1)->text()).toString();
//        QString Men25_42 = settings.value( "Men25_42", ui->tableWidget_25Men->item(4,2)->text()).toString();
//        QString Men25_43 = settings.value( "Men25_43", ui->tableWidget_25Men->item(4,3)->text()).toString();
//        QString Men25_44 = settings.value( "Men25_44", ui->tableWidget_25Men->item(4,4)->text()).toString();
//        QString Men25_45 = settings.value( "Men25_45", ui->tableWidget_25Men->item(4,5)->text()).toString();
//        QString Men25_46 = settings.value( "Men25_46", ui->tableWidget_25Men->item(4,6)->text()).toString();
//        QString Men25_47 = settings.value( "Men25_47", ui->tableWidget_25Men->item(4,7)->text()).toString();
//        QString Men25_50 = settings.value( "Men25_50", ui->tableWidget_25Men->item(5,0)->text()).toString();
//        QString Men25_51 = settings.value( "Men25_51", ui->tableWidget_25Men->item(5,1)->text()).toString();
//        QString Men25_52 = settings.value( "Men25_52", ui->tableWidget_25Men->item(5,2)->text()).toString();
//        QString Men25_53 = settings.value( "Men25_53", ui->tableWidget_25Men->item(5,3)->text()).toString();
//        QString Men25_54 = settings.value( "Men25_54", ui->tableWidget_25Men->item(5,4)->text()).toString();
//        QString Men25_55 = settings.value( "Men25_55", ui->tableWidget_25Men->item(5,5)->text()).toString();
//        QString Men25_56 = settings.value( "Men25_56", ui->tableWidget_25Men->item(5,6)->text()).toString();
//        QString Men25_57 = settings.value( "Men25_57", ui->tableWidget_25Men->item(5,7)->text()).toString();
//        QString Men25_60 = settings.value( "Men25_60", ui->tableWidget_25Men->item(6,0)->text()).toString();
//        QString Men25_61 = settings.value( "Men25_61", ui->tableWidget_25Men->item(6,1)->text()).toString();
//        QString Men25_62 = settings.value( "Men25_62", ui->tableWidget_25Men->item(6,2)->text()).toString();
//        QString Men25_63 = settings.value( "Men25_63", ui->tableWidget_25Men->item(6,3)->text()).toString();
//        QString Men25_64 = settings.value( "Men25_64", ui->tableWidget_25Men->item(6,4)->text()).toString();
//        QString Men25_65 = settings.value( "Men25_65", ui->tableWidget_25Men->item(6,5)->text()).toString();
//        QString Men25_66 = settings.value( "Men25_66", ui->tableWidget_25Men->item(6,6)->text()).toString();
//        QString Men25_67 = settings.value( "Men25_67", ui->tableWidget_25Men->item(6,7)->text()).toString();
//        QString Men25_70 = settings.value( "Men25_70", ui->tableWidget_25Men->item(7,0)->text()).toString();
//        QString Men25_71 = settings.value( "Men25_71", ui->tableWidget_25Men->item(7,1)->text()).toString();
//        QString Men25_72 = settings.value( "Men25_72", ui->tableWidget_25Men->item(7,2)->text()).toString();
//        QString Men25_73 = settings.value( "Men25_73", ui->tableWidget_25Men->item(7,3)->text()).toString();
//        QString Men25_74 = settings.value( "Men25_74", ui->tableWidget_25Men->item(7,4)->text()).toString();
//        QString Men25_75 = settings.value( "Men25_75", ui->tableWidget_25Men->item(7,5)->text()).toString();
//        QString Men25_76 = settings.value( "Men25_76", ui->tableWidget_25Men->item(7,6)->text()).toString();
//        QString Men25_77 = settings.value( "Men25_77", ui->tableWidget_25Men->item(7,7)->text()).toString();
//        QString Men25_80 = settings.value( "Men25_80", ui->tableWidget_25Men->item(8,0)->text()).toString();
//        QString Men25_81 = settings.value( "Men25_81", ui->tableWidget_25Men->item(8,1)->text()).toString();
//        QString Men25_82 = settings.value( "Men25_82", ui->tableWidget_25Men->item(8,2)->text()).toString();
//        QString Men25_83 = settings.value( "Men25_83", ui->tableWidget_25Men->item(8,3)->text()).toString();
//        QString Men25_84 = settings.value( "Men25_84", ui->tableWidget_25Men->item(8,4)->text()).toString();
//        QString Men25_85 = settings.value( "Men25_85", ui->tableWidget_25Men->item(8,5)->text()).toString();
//        QString Men25_86 = settings.value( "Men25_86", ui->tableWidget_25Men->item(8,6)->text()).toString();
//        QString Men25_87 = settings.value( "Men25_87", ui->tableWidget_25Men->item(8,7)->text()).toString();
//        QString Men25_90 = settings.value( "Men25_90", ui->tableWidget_25Men->item(9,0)->text()).toString();
//        QString Men25_91 = settings.value( "Men25_91", ui->tableWidget_25Men->item(9,1)->text()).toString();
//        QString Men25_92 = settings.value( "Men25_92", ui->tableWidget_25Men->item(9,2)->text()).toString();
//        QString Men25_93 = settings.value( "Men25_93", ui->tableWidget_25Men->item(9,3)->text()).toString();
//        QString Men25_94 = settings.value( "Men25_94", ui->tableWidget_25Men->item(9,4)->text()).toString();
//        QString Men25_95 = settings.value( "Men25_95", ui->tableWidget_25Men->item(9,5)->text()).toString();
//        QString Men25_96 = settings.value( "Men25_96", ui->tableWidget_25Men->item(9,6)->text()).toString();
//        QString Men25_97 = settings.value( "Men25_97", ui->tableWidget_25Men->item(9,7)->text()).toString();
    //    QString Men25_100 = settings.value( "Men25_100", ui->tableWidget_25Men->item(10,0)->text()).toString();
//        QString Men25_101 = settings.value( "Men25_101", ui->tableWidget_25Men->item(10,1)->text()).toString();
//        QString Men25_102 = settings.value( "Men25_102", ui->tableWidget_25Men->item(10,2)->text()).toString();
//        QString Men25_103 = settings.value( "Men25_103", ui->tableWidget_25Men->item(10,3)->text()).toString();
//        QString Men25_104 = settings.value( "Men25_104", ui->tableWidget_25Men->item(10,4)->text()).toString();
//        QString Men25_105 = settings.value( "Men25_105", ui->tableWidget_25Men->item(10,5)->text()).toString();
//        QString Men25_106 = settings.value( "Men25_106", ui->tableWidget_25Men->item(10,6)->text()).toString();
//        QString Men25_107 = settings.value( "Men25_107", ui->tableWidget_25Men->item(10,7)->text()).toString();
    //    QString Men25_110 = settings.value( "Men25_110", ui->tableWidget_25Men->item(11,0)->text()).toString();
    //    QString Men25_111 = settings.value( "Men25_111", ui->tableWidget_25Men->item(11,1)->text()).toString();
    //    QString Men25_112 = settings.value( "Men25_112", ui->tableWidget_25Men->item(11,2)->text()).toString();
    //    QString Men25_113 = settings.value( "Men25_113", ui->tableWidget_25Men->item(11,3)->text()).toString();
    //    QString Men25_114 = settings.value( "Men25_114", ui->tableWidget_25Men->item(11,4)->text()).toString();
    //    QString Men25_115 = settings.value( "Men25_115", ui->tableWidget_25Men->item(11,5)->text()).toString();
    //    QString Men25_116 = settings.value( "Men25_116", ui->tableWidget_25Men->item(11,6)->text()).toString();
    //    QString Men25_117 = settings.value( "Men25_117", ui->tableWidget_25Men->item(11,7)->text()).toString();
    //    QString Men25_120 = settings.value( "Men25_120", ui->tableWidget_25Men->item(12,0)->text()).toString();
    //    QString Men25_121 = settings.value( "Men25_121", ui->tableWidget_25Men->item(12,1)->text()).toString();
    //    QString Men25_122 = settings.value( "Men25_122", ui->tableWidget_25Men->item(12,2)->text()).toString();
    //    QString Men25_123 = settings.value( "Men25_123", ui->tableWidget_25Men->item(12,3)->text()).toString();
    //    QString Men25_124 = settings.value( "Men25_124", ui->tableWidget_25Men->item(12,4)->text()).toString();
    //    QString Men25_125 = settings.value( "Men25_125", ui->tableWidget_25Men->item(12,5)->text()).toString();
    //    QString Men25_126 = settings.value( "Men25_126", ui->tableWidget_25Men->item(12,6)->text()).toString();
    //    QString Men25_127 = settings.value( "Men25_127", ui->tableWidget_25Men->item(12,7)->text()).toString();
    //    QString Men25_130 = settings.value( "Men25_130", ui->tableWidget_25Men->item(13,0)->text()).toString();
    //    QString Men25_131 = settings.value( "Men25_131", ui->tableWidget_25Men->item(13,1)->text()).toString();
    //    QString Men25_132 = settings.value( "Men25_132", ui->tableWidget_25Men->item(13,2)->text()).toString();
    //    QString Men25_133 = settings.value( "Men25_133", ui->tableWidget_25Men->item(13,3)->text()).toString();
    //    QString Men25_134 = settings.value( "Men25_134", ui->tableWidget_25Men->item(13,4)->text()).toString();
    //    QString Men25_135 = settings.value( "Men25_135", ui->tableWidget_25Men->item(13,5)->text()).toString();
    //    QString Men25_136 = settings.value( "Men25_136", ui->tableWidget_25Men->item(13,6)->text()).toString();
    //    QString Men25_137 = settings.value( "Men25_137", ui->tableWidget_25Men->item(13,7)->text()).toString();
    //    QString Men25_140 = settings.value( "Men25_140", ui->tableWidget_25Men->item(14,0)->text()).toString();
    //    QString Men25_141 = settings.value( "Men25_141", ui->tableWidget_25Men->item(14,1)->text()).toString();
    //    QString Men25_142 = settings.value( "Men25_142", ui->tableWidget_25Men->item(14,2)->text()).toString();
    //    QString Men25_143 = settings.value( "Men25_143", ui->tableWidget_25Men->item(14,3)->text()).toString();
    //    QString Men25_144 = settings.value( "Men25_144", ui->tableWidget_25Men->item(14,4)->text()).toString();
    //    QString Men25_145 = settings.value( "Men25_145", ui->tableWidget_25Men->item(14,5)->text()).toString();
    //    QString Men25_146 = settings.value( "Men25_146", ui->tableWidget_25Men->item(14,6)->text()).toString();
    //    QString Men25_147 = settings.value( "Men25_147", ui->tableWidget_25Men->item(14,7)->text()).toString();
    //    QString Men25_150 = settings.value( "Men25_150", ui->tableWidget_25Men->item(15,0)->text()).toString();
    //    QString Men25_151 = settings.value( "Men25_151", ui->tableWidget_25Men->item(15,1)->text()).toString();
    //    QString Men25_152 = settings.value( "Men25_152", ui->tableWidget_25Men->item(15,2)->text()).toString();
    //    QString Men25_153 = settings.value( "Men25_153", ui->tableWidget_25Men->item(15,3)->text()).toString();
    //    QString Men25_154 = settings.value( "Men25_154", ui->tableWidget_25Men->item(15,4)->text()).toString();
    //    QString Men25_155 = settings.value( "Men25_155", ui->tableWidget_25Men->item(15,5)->text()).toString();
    //    QString Men25_156 = settings.value( "Men25_156", ui->tableWidget_25Men->item(15,6)->text()).toString();
    //    QString Men25_157 = settings.value( "Men25_157", ui->tableWidget_25Men->item(15,7)->text()).toString();
    //    QString Men25_160 = settings.value( "Men25_160", ui->tableWidget_25Men->item(16,0)->text()).toString();
    //    QString Men25_161 = settings.value( "Men25_161", ui->tableWidget_25Men->item(16,1)->text()).toString();
    //    QString Men25_162 = settings.value( "Men25_162", ui->tableWidget_25Men->item(16,2)->text()).toString();
    //    QString Men25_163 = settings.value( "Men25_163", ui->tableWidget_25Men->item(16,3)->text()).toString();
    //    QString Men25_164 = settings.value( "Men25_164", ui->tableWidget_25Men->item(16,4)->text()).toString();
    //    QString Men25_165 = settings.value( "Men25_165", ui->tableWidget_25Men->item(16,5)->text()).toString();
    //    QString Men25_166 = settings.value( "Men25_166", ui->tableWidget_25Men->item(16,6)->text()).toString();
    //    QString Men25_167 = settings.value( "Men25_167", ui->tableWidget_25Men->item(16,7)->text()).toString();
    //    QString Men25_170 = settings.value( "Men25_170", ui->tableWidget_25Men->item(17,0)->text()).toString();
    //    QString Men25_171 = settings.value( "Men25_171", ui->tableWidget_25Men->item(17,1)->text()).toString();
    //    QString Men25_172 = settings.value( "Men25_172", ui->tableWidget_25Men->item(17,2)->text()).toString();
    //    QString Men25_173 = settings.value( "Men25_173", ui->tableWidget_25Men->item(17,3)->text()).toString();
    //    QString Men25_174 = settings.value( "Men25_174", ui->tableWidget_25Men->item(17,4)->text()).toString();
    //    QString Men25_175 = settings.value( "Men25_175", ui->tableWidget_25Men->item(17,5)->text()).toString();
    //    QString Men25_176 = settings.value( "Men25_176", ui->tableWidget_25Men->item(17,6)->text()).toString();
    //    QString Men25_177 = settings.value( "Men25_177", ui->tableWidget_25Men->item(17,7)->text()).toString();

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
//    QString Men50_20 = settings.value( "Men50_20", -1).toString();
//    QString Men50_21 = settings.value( "Men50_21", -1).toString();
//    QString Men50_22 = settings.value( "Men50_22", -1).toString();
//    QString Men50_23 = settings.value( "Men50_23", -1).toString();
//    QString Men50_24 = settings.value( "Men50_24", -1).toString();
//    QString Men50_25 = settings.value( "Men50_25", -1).toString();
//    QString Men50_26 = settings.value( "Men50_26", -1).toString();
//    QString Men50_27 = settings.value( "Men50_27", -1).toString();
//    QString Men50_30 = settings.value( "Men50_30", -1).toString();
//    QString Men50_31 = settings.value( "Men50_31", -1).toString();
//    QString Men50_32 = settings.value( "Men50_32", -1).toString();
//    QString Men50_33 = settings.value( "Men50_33", -1).toString();
//    QString Men50_34 = settings.value( "Men50_34", -1).toString();
//    QString Men50_35 = settings.value( "Men50_35", -1).toString();
//    QString Men50_36 = settings.value( "Men50_36", -1).toString();
//    QString Men50_37 = settings.value( "Men50_37", -1).toString();
//    QString Men50_40 = settings.value( "Men50_40", -1).toString();
//    QString Men50_41 = settings.value( "Men50_41", -1).toString();
//    QString Men50_42 = settings.value( "Men50_42", -1).toString();
//    QString Men50_43 = settings.value( "Men50_43", -1).toString();
//    QString Men50_44 = settings.value( "Men50_44", -1).toString();
//    QString Men50_45 = settings.value( "Men50_45", -1).toString();
//    QString Men50_46 = settings.value( "Men50_46", -1).toString();
//    QString Men50_47 = settings.value( "Men50_47", -1).toString();
//    QString Men50_50 = settings.value( "Men50_50", -1).toString();
//    QString Men50_51 = settings.value( "Men50_51", -1).toString();
//    QString Men50_52 = settings.value( "Men50_52", -1).toString();
//    QString Men50_53 = settings.value( "Men50_53", -1).toString();
//    QString Men50_54 = settings.value( "Men50_54", -1).toString();
//    QString Men50_55 = settings.value( "Men50_55", -1).toString();
//    QString Men50_56 = settings.value( "Men50_56", -1).toString();
//    QString Men50_57 = settings.value( "Men50_57", -1).toString();
//    QString Men50_60 = settings.value( "Men50_60", -1).toString();
//    QString Men50_61 = settings.value( "Men50_61", -1).toString();
//    QString Men50_62 = settings.value( "Men50_62", -1).toString();
//    QString Men50_63 = settings.value( "Men50_63", -1).toString();
//    QString Men50_64 = settings.value( "Men50_64", -1).toString();
//    QString Men50_65 = settings.value( "Men50_65", -1).toString();
//    QString Men50_66 = settings.value( "Men50_66", -1).toString();
//    QString Men50_67 = settings.value( "Men50_67", -1).toString();
//    QString Men50_70 = settings.value( "Men50_70", -1).toString();
//    QString Men50_71 = settings.value( "Men50_71", -1).toString();
//    QString Men50_72 = settings.value( "Men50_72", -1).toString();
//    QString Men50_73 = settings.value( "Men50_73", -1).toString();
//    QString Men50_74 = settings.value( "Men50_74", -1).toString();
//    QString Men50_75 = settings.value( "Men50_75", -1).toString();
//    QString Men50_76 = settings.value( "Men50_76", -1).toString();
//    QString Men50_77 = settings.value( "Men50_77", -1).toString();
//    QString Men50_80 = settings.value( "Men50_80", -1).toString();
//    QString Men50_81 = settings.value( "Men50_81", -1).toString();
//    QString Men50_82 = settings.value( "Men50_82", -1).toString();
//    QString Men50_83 = settings.value( "Men50_83", -1).toString();
//    QString Men50_84 = settings.value( "Men50_84", -1).toString();
//    QString Men50_85 = settings.value( "Men50_85", -1).toString();
//    QString Men50_86 = settings.value( "Men50_86", -1).toString();
//    QString Men50_87 = settings.value( "Men50_87", -1).toString();
//    QString Men50_90 = settings.value( "Men50_90", -1).toString();
//    QString Men50_91 = settings.value( "Men50_91", -1).toString();
//    QString Men50_92 = settings.value( "Men50_92", -1).toString();
//    QString Men50_93 = settings.value( "Men50_93", -1).toString();
//    QString Men50_94 = settings.value( "Men50_94", -1).toString();
//    QString Men50_95 = settings.value( "Men50_95", -1).toString();
//    QString Men50_96 = settings.value( "Men50_96", -1).toString();
//    QString Men50_97 = settings.value( "Men50_97", -1).toString();
//    QString Men50_100 = settings.value( "Men50_100", -1).toString();
//    QString Men50_101 = settings.value( "Men50_101", -1).toString();
//    QString Men50_102 = settings.value( "Men50_102", -1).toString();
//    QString Men50_103 = settings.value( "Men50_103", -1).toString();
//    QString Men50_104 = settings.value( "Men50_104", -1).toString();
//    QString Men50_105 = settings.value( "Men50_105", -1).toString();
//    QString Men50_106 = settings.value( "Men50_106", -1).toString();
//    QString Men50_107 = settings.value( "Men50_107", -1).toString();
//    QString Men50_110 = settings.value( "Men50_110", -1).toString();
//    QString Men50_111 = settings.value( "Men50_111", -1).toString();
//    QString Men50_112 = settings.value( "Men50_112", -1).toString();
//    QString Men50_113 = settings.value( "Men50_113", -1).toString();
//    QString Men50_114 = settings.value( "Men50_114", -1).toString();
//    QString Men50_115 = settings.value( "Men50_115", -1).toString();
//    QString Men50_116 = settings.value( "Men50_116", -1).toString();
//    QString Men50_117 = settings.value( "Men50_117", -1).toString();
//    QString Men50_120 = settings.value( "Men50_120", -1).toString();
//    QString Men50_121 = settings.value( "Men50_121", -1).toString();
//    QString Men50_122 = settings.value( "Men50_122", -1).toString();
//    QString Men50_123 = settings.value( "Men50_123", -1).toString();
//    QString Men50_124 = settings.value( "Men50_124", -1).toString();
//    QString Men50_125 = settings.value( "Men50_125", -1).toString();
//    QString Men50_126 = settings.value( "Men50_126", -1).toString();
//    QString Men50_127 = settings.value( "Men50_127", -1).toString();
//    QString Men50_130 = settings.value( "Men50_130", -1).toString();
//    QString Men50_131 = settings.value( "Men50_131", -1).toString();
//    QString Men50_132 = settings.value( "Men50_132", -1).toString();
//    QString Men50_133 = settings.value( "Men50_133", -1).toString();
//    QString Men50_134 = settings.value( "Men50_134", -1).toString();
//    QString Men50_135 = settings.value( "Men50_135", -1).toString();
//    QString Men50_136 = settings.value( "Men50_136", -1).toString();
//    QString Men50_137 = settings.value( "Men50_137", -1).toString();
//    QString Men50_140 = settings.value( "Men50_140", -1).toString();
//    QString Men50_141 = settings.value( "Men50_141", -1).toString();
//    QString Men50_142 = settings.value( "Men50_142", -1).toString();
//    QString Men50_143 = settings.value( "Men50_143", -1).toString();
//    QString Men50_144 = settings.value( "Men50_144", -1).toString();
//    QString Men50_145 = settings.value( "Men50_145", -1).toString();
//    QString Men50_146 = settings.value( "Men50_146", -1).toString();
//    QString Men50_147 = settings.value( "Men50_147", -1).toString();
//    QString Men50_150 = settings.value( "Men50_150", -1).toString();
//    QString Men50_151 = settings.value( "Men50_151", -1).toString();
//    QString Men50_152 = settings.value( "Men50_152", -1).toString();
//    QString Men50_153 = settings.value( "Men50_153", -1).toString();
//    QString Men50_154 = settings.value( "Men50_154", -1).toString();
//    QString Men50_155 = settings.value( "Men50_155", -1).toString();
//    QString Men50_156 = settings.value( "Men50_156", -1).toString();
//    QString Men50_157 = settings.value( "Men50_157", -1).toString();
//    QString Men50_160 = settings.value( "Men50_160", -1).toString();
//    QString Men50_161 = settings.value( "Men50_161", -1).toString();
//    QString Men50_162 = settings.value( "Men50_162", -1).toString();
//    QString Men50_163 = settings.value( "Men50_163", -1).toString();
//    QString Men50_164 = settings.value( "Men50_164", -1).toString();
//    QString Men50_165 = settings.value( "Men50_165", -1).toString();
//    QString Men50_166 = settings.value( "Men50_166", -1).toString();
//    QString Men50_167 = settings.value( "Men50_167", -1).toString();
//    QString Men50_170 = settings.value( "Men50_170", -1).toString();
//    QString Men50_171 = settings.value( "Men50_171", -1).toString();
//    QString Men50_172 = settings.value( "Men50_172", -1).toString();
//    QString Men50_173 = settings.value( "Men50_173", -1).toString();
//    QString Men50_174 = settings.value( "Men50_174", -1).toString();
//    QString Men50_175 = settings.value( "Men50_175", -1).toString();
//    QString Men50_176 = settings.value( "Men50_176", -1).toString();
//    QString Men50_177 = settings.value( "Men50_177", -1).toString();

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
//    ui->tableWidget_25Men->item(2,0)->setText(Men25_20);
//    ui->tableWidget_25Men->item(2,1)->setText(Men25_21);
//    ui->tableWidget_25Men->item(2,2)->setText(Men25_22);
//    ui->tableWidget_25Men->item(2,3)->setText(Men25_23);
//    ui->tableWidget_25Men->item(2,4)->setText(Men25_24);
//    ui->tableWidget_25Men->item(2,5)->setText(Men25_25);
//    ui->tableWidget_25Men->item(2,6)->setText(Men25_26);
//    ui->tableWidget_25Men->item(2,7)->setText(Men25_27);
//    ui->tableWidget_25Men->item(3,0)->setText(Men25_30);
//    ui->tableWidget_25Men->item(3,1)->setText(Men25_31);
//    ui->tableWidget_25Men->item(3,2)->setText(Men25_32);
//    ui->tableWidget_25Men->item(3,3)->setText(Men25_33);
//    ui->tableWidget_25Men->item(3,4)->setText(Men25_34);
//    ui->tableWidget_25Men->item(3,5)->setText(Men25_35);
//    ui->tableWidget_25Men->item(3,6)->setText(Men25_36);
//    ui->tableWidget_25Men->item(3,7)->setText(Men25_37);
//    ui->tableWidget_25Men->item(4,0)->setText(Men25_40);
//    ui->tableWidget_25Men->item(4,1)->setText(Men25_41);
//    ui->tableWidget_25Men->item(4,2)->setText(Men25_42);
//    ui->tableWidget_25Men->item(4,3)->setText(Men25_43);
//    ui->tableWidget_25Men->item(4,4)->setText(Men25_44);
//    ui->tableWidget_25Men->item(4,5)->setText(Men25_45);
//    ui->tableWidget_25Men->item(4,6)->setText(Men25_46);
//    ui->tableWidget_25Men->item(4,7)->setText(Men25_47);
//    ui->tableWidget_25Men->item(5,0)->setText(Men25_50);
//    ui->tableWidget_25Men->item(5,1)->setText(Men25_51);
//    ui->tableWidget_25Men->item(5,2)->setText(Men25_52);
//    ui->tableWidget_25Men->item(5,3)->setText(Men25_53);
//    ui->tableWidget_25Men->item(5,4)->setText(Men25_54);
//    ui->tableWidget_25Men->item(5,5)->setText(Men25_55);
//    ui->tableWidget_25Men->item(5,6)->setText(Men25_56);
//    ui->tableWidget_25Men->item(5,7)->setText(Men25_57);
//    ui->tableWidget_25Men->item(6,0)->setText(Men25_60);
//    ui->tableWidget_25Men->item(6,1)->setText(Men25_61);
//    ui->tableWidget_25Men->item(6,2)->setText(Men25_62);
//    ui->tableWidget_25Men->item(6,3)->setText(Men25_63);
//    ui->tableWidget_25Men->item(6,4)->setText(Men25_64);
//    ui->tableWidget_25Men->item(6,5)->setText(Men25_65);
//    ui->tableWidget_25Men->item(6,6)->setText(Men25_66);
//    ui->tableWidget_25Men->item(6,7)->setText(Men25_67);
//    ui->tableWidget_25Men->item(7,0)->setText(Men25_70);
//    ui->tableWidget_25Men->item(7,1)->setText(Men25_71);
//    ui->tableWidget_25Men->item(7,2)->setText(Men25_72);
//    ui->tableWidget_25Men->item(7,3)->setText(Men25_73);
//    ui->tableWidget_25Men->item(7,4)->setText(Men25_74);
//    ui->tableWidget_25Men->item(7,5)->setText(Men25_75);
//    ui->tableWidget_25Men->item(7,6)->setText(Men25_76);
//    ui->tableWidget_25Men->item(7,7)->setText(Men25_77);
//    ui->tableWidget_25Men->item(8,0)->setText(Men25_80);
//    ui->tableWidget_25Men->item(8,1)->setText(Men25_81);
//    ui->tableWidget_25Men->item(8,2)->setText(Men25_82);
//    ui->tableWidget_25Men->item(8,3)->setText(Men25_83);
//    ui->tableWidget_25Men->item(8,4)->setText(Men25_84);
//    ui->tableWidget_25Men->item(8,5)->setText(Men25_85);
//    ui->tableWidget_25Men->item(8,6)->setText(Men25_86);
//    ui->tableWidget_25Men->item(8,7)->setText(Men25_87);
//    ui->tableWidget_25Men->item(9,0)->setText(Men25_90);
//    ui->tableWidget_25Men->item(9,1)->setText(Men25_91);
//    ui->tableWidget_25Men->item(9,2)->setText(Men25_92);
//    ui->tableWidget_25Men->item(9,3)->setText(Men25_93);
//    ui->tableWidget_25Men->item(9,4)->setText(Men25_94);
//    ui->tableWidget_25Men->item(9,5)->setText(Men25_95);
//    ui->tableWidget_25Men->item(9,6)->setText(Men25_96);
//    ui->tableWidget_25Men->item(9,7)->setText(Men25_97);
//    ui->tableWidget_25Men->item(10,0)->setText(Men25_100);
//    ui->tableWidget_25Men->item(10,1)->setText(Men25_101);
//    ui->tableWidget_25Men->item(10,2)->setText(Men25_102);
//    ui->tableWidget_25Men->item(10,3)->setText(Men25_103);
//    ui->tableWidget_25Men->item(10,4)->setText(Men25_104);
//    ui->tableWidget_25Men->item(10,5)->setText(Men25_105);
//    ui->tableWidget_25Men->item(10,6)->setText(Men25_106);
//    ui->tableWidget_25Men->item(10,7)->setText(Men25_107);
//    ui->tableWidget_25Men->item(11,0)->setText(Men25_110);
//    ui->tableWidget_25Men->item(11,1)->setText(Men25_111);
//    ui->tableWidget_25Men->item(11,2)->setText(Men25_112);
//    ui->tableWidget_25Men->item(11,3)->setText(Men25_113);
//    ui->tableWidget_25Men->item(11,4)->setText(Men25_114);
//    ui->tableWidget_25Men->item(11,5)->setText(Men25_115);
//    ui->tableWidget_25Men->item(11,6)->setText(Men25_116);
//    ui->tableWidget_25Men->item(11,7)->setText(Men25_117);
//    ui->tableWidget_25Men->item(12,0)->setText(Men25_120);
//    ui->tableWidget_25Men->item(12,1)->setText(Men25_121);
//    ui->tableWidget_25Men->item(12,2)->setText(Men25_122);
//    ui->tableWidget_25Men->item(12,3)->setText(Men25_123);
//    ui->tableWidget_25Men->item(12,4)->setText(Men25_124);
//    ui->tableWidget_25Men->item(12,5)->setText(Men25_125);
//    ui->tableWidget_25Men->item(12,6)->setText(Men25_126);
//    ui->tableWidget_25Men->item(12,7)->setText(Men25_127);
//    ui->tableWidget_25Men->item(13,0)->setText(Men25_130);
//    ui->tableWidget_25Men->item(13,1)->setText(Men25_131);
//    ui->tableWidget_25Men->item(13,2)->setText(Men25_132);
//    ui->tableWidget_25Men->item(13,3)->setText(Men25_133);
//    ui->tableWidget_25Men->item(13,4)->setText(Men25_134);
//    ui->tableWidget_25Men->item(13,5)->setText(Men25_135);
//    ui->tableWidget_25Men->item(13,6)->setText(Men25_136);
//    ui->tableWidget_25Men->item(13,7)->setText(Men25_137);
//    ui->tableWidget_25Men->item(14,0)->setText(Men25_140);
//    ui->tableWidget_25Men->item(14,1)->setText(Men25_141);
//    ui->tableWidget_25Men->item(14,2)->setText(Men25_142);
//    ui->tableWidget_25Men->item(14,3)->setText(Men25_143);
//    ui->tableWidget_25Men->item(14,4)->setText(Men25_144);
//    ui->tableWidget_25Men->item(14,5)->setText(Men25_145);
//    ui->tableWidget_25Men->item(14,6)->setText(Men25_146);
//    ui->tableWidget_25Men->item(14,7)->setText(Men25_147);
//    ui->tableWidget_25Men->item(15,0)->setText(Men25_150);
//    ui->tableWidget_25Men->item(15,1)->setText(Men25_151);
//    ui->tableWidget_25Men->item(15,2)->setText(Men25_152);
//    ui->tableWidget_25Men->item(15,3)->setText(Men25_153);
//    ui->tableWidget_25Men->item(15,4)->setText(Men25_154);
//    ui->tableWidget_25Men->item(15,5)->setText(Men25_155);
//    ui->tableWidget_25Men->item(15,6)->setText(Men25_156);
//    ui->tableWidget_25Men->item(15,7)->setText(Men25_157);
//    ui->tableWidget_25Men->item(16,0)->setText(Men25_160);
//    ui->tableWidget_25Men->item(16,1)->setText(Men25_161);
//    ui->tableWidget_25Men->item(16,2)->setText(Men25_162);
//    ui->tableWidget_25Men->item(16,3)->setText(Men25_163);
//    ui->tableWidget_25Men->item(16,4)->setText(Men25_164);
//    ui->tableWidget_25Men->item(16,5)->setText(Men25_165);
//    ui->tableWidget_25Men->item(16,6)->setText(Men25_166);
//    ui->tableWidget_25Men->item(16,7)->setText(Men25_167);
//    ui->tableWidget_25Men->item(17,0)->setText(Men25_170);
//    ui->tableWidget_25Men->item(17,1)->setText(Men25_171);
//    ui->tableWidget_25Men->item(17,2)->setText(Men25_172);
//    ui->tableWidget_25Men->item(17,3)->setText(Men25_173);
//    ui->tableWidget_25Men->item(17,4)->setText(Men25_174);
//    ui->tableWidget_25Men->item(17,5)->setText(Men25_175);
//    ui->tableWidget_25Men->item(17,6)->setText(Men25_176);
//    ui->tableWidget_25Men->item(17,7)->setText(Men25_177);
}

RankSettings::~RankSettings()
{
    delete ui;
}

void RankSettings::on_pushButton_back_clicked()
{
    this->close();
    emit rankMenu();
}

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
//    settings.setValue("Men25_20", ui->tableWidget_25Men->item(2,0)->text());
//    settings.setValue("Men25_21", ui->tableWidget_25Men->item(2,1)->text());
//    settings.setValue("Men25_22", ui->tableWidget_25Men->item(2,2)->text());
//    settings.setValue("Men25_23", ui->tableWidget_25Men->item(2,3)->text());
//    settings.setValue("Men25_24", ui->tableWidget_25Men->item(2,4)->text());
//    settings.setValue("Men25_25", ui->tableWidget_25Men->item(2,5)->text());
//    settings.setValue("Men25_26", ui->tableWidget_25Men->item(2,6)->text());
//    settings.setValue("Men25_27", ui->tableWidget_25Men->item(2,7)->text());
//    settings.setValue("Men25_30", ui->tableWidget_25Men->item(3,0)->text());
//    settings.setValue("Men25_31", ui->tableWidget_25Men->item(3,1)->text());
//    settings.setValue("Men25_32", ui->tableWidget_25Men->item(3,2)->text());
//    settings.setValue("Men25_33", ui->tableWidget_25Men->item(3,3)->text());
//    settings.setValue("Men25_34", ui->tableWidget_25Men->item(3,4)->text());
//    settings.setValue("Men25_35", ui->tableWidget_25Men->item(3,5)->text());
//    settings.setValue("Men25_36", ui->tableWidget_25Men->item(3,6)->text());
//    settings.setValue("Men25_37", ui->tableWidget_25Men->item(3,7)->text());
//    settings.setValue("Men25_40", ui->tableWidget_25Men->item(4,0)->text());
//    settings.setValue("Men25_41", ui->tableWidget_25Men->item(4,1)->text());
//    settings.setValue("Men25_42", ui->tableWidget_25Men->item(4,2)->text());
//    settings.setValue("Men25_43", ui->tableWidget_25Men->item(4,3)->text());
//    settings.setValue("Men25_44", ui->tableWidget_25Men->item(4,4)->text());
//    settings.setValue("Men25_45", ui->tableWidget_25Men->item(4,5)->text());
//    settings.setValue("Men25_46", ui->tableWidget_25Men->item(4,6)->text());
//    settings.setValue("Men25_47", ui->tableWidget_25Men->item(4,7)->text());
//    settings.setValue("Men25_50", ui->tableWidget_25Men->item(5,0)->text());
//    settings.setValue("Men25_51", ui->tableWidget_25Men->item(5,1)->text());
//    settings.setValue("Men25_52", ui->tableWidget_25Men->item(5,2)->text());
//    settings.setValue("Men25_53", ui->tableWidget_25Men->item(5,3)->text());
//    settings.setValue("Men25_54", ui->tableWidget_25Men->item(5,4)->text());
//    settings.setValue("Men25_55", ui->tableWidget_25Men->item(5,5)->text());
//    settings.setValue("Men25_56", ui->tableWidget_25Men->item(5,6)->text());
//    settings.setValue("Men25_57", ui->tableWidget_25Men->item(5,7)->text());
//    settings.setValue("Men25_60", ui->tableWidget_25Men->item(6,0)->text());
//    settings.setValue("Men25_61", ui->tableWidget_25Men->item(6,1)->text());
//    settings.setValue("Men25_62", ui->tableWidget_25Men->item(6,2)->text());
//    settings.setValue("Men25_63", ui->tableWidget_25Men->item(6,3)->text());
//    settings.setValue("Men25_64", ui->tableWidget_25Men->item(6,4)->text());
//    settings.setValue("Men25_65", ui->tableWidget_25Men->item(6,5)->text());
//    settings.setValue("Men25_66", ui->tableWidget_25Men->item(6,6)->text());
//    settings.setValue("Men25_67", ui->tableWidget_25Men->item(6,7)->text());
//    settings.setValue("Men25_70", ui->tableWidget_25Men->item(7,0)->text());
//    settings.setValue("Men25_71", ui->tableWidget_25Men->item(7,1)->text());
//    settings.setValue("Men25_72", ui->tableWidget_25Men->item(7,2)->text());
//    settings.setValue("Men25_73", ui->tableWidget_25Men->item(7,3)->text());
//    settings.setValue("Men25_74", ui->tableWidget_25Men->item(7,4)->text());
//    settings.setValue("Men25_75", ui->tableWidget_25Men->item(7,5)->text());
//    settings.setValue("Men25_76", ui->tableWidget_25Men->item(7,6)->text());
//    settings.setValue("Men25_77", ui->tableWidget_25Men->item(7,7)->text());
//    settings.setValue("Men25_80", ui->tableWidget_25Men->item(8,0)->text());
//    settings.setValue("Men25_81", ui->tableWidget_25Men->item(8,1)->text());
//    settings.setValue("Men25_82", ui->tableWidget_25Men->item(8,2)->text());
//    settings.setValue("Men25_83", ui->tableWidget_25Men->item(8,3)->text());
//    settings.setValue("Men25_84", ui->tableWidget_25Men->item(8,4)->text());
//    settings.setValue("Men25_85", ui->tableWidget_25Men->item(8,5)->text());
//    settings.setValue("Men25_86", ui->tableWidget_25Men->item(8,6)->text());
//    settings.setValue("Men25_87", ui->tableWidget_25Men->item(8,7)->text());
//    settings.setValue("Men25_90", ui->tableWidget_25Men->item(9,0)->text());
//    settings.setValue("Men25_91", ui->tableWidget_25Men->item(9,1)->text());
//    settings.setValue("Men25_92", ui->tableWidget_25Men->item(9,2)->text());
//    settings.setValue("Men25_93", ui->tableWidget_25Men->item(9,3)->text());
//    settings.setValue("Men25_94", ui->tableWidget_25Men->item(9,4)->text());
//    settings.setValue("Men25_95", ui->tableWidget_25Men->item(9,5)->text());
//    settings.setValue("Men25_96", ui->tableWidget_25Men->item(9,6)->text());
//    settings.setValue("Men25_97", ui->tableWidget_25Men->item(9,7)->text());
//    settings.setValue("Men25_100", ui->tableWidget_25Men->item(10,0)->text());
//    settings.setValue("Men25_101", ui->tableWidget_25Men->item(10,1)->text());
//    settings.setValue("Men25_102", ui->tableWidget_25Men->item(10,2)->text());
//    settings.setValue("Men25_103", ui->tableWidget_25Men->item(10,3)->text());
//    settings.setValue("Men25_104", ui->tableWidget_25Men->item(10,4)->text());
//    settings.setValue("Men25_105", ui->tableWidget_25Men->item(10,5)->text());
//    settings.setValue("Men25_106", ui->tableWidget_25Men->item(10,6)->text());
//    settings.setValue("Men25_107", ui->tableWidget_25Men->item(10,7)->text());
//    settings.setValue("Men25_110", ui->tableWidget_25Men->item(11,0)->text());
//    settings.setValue("Men25_111", ui->tableWidget_25Men->item(11,1)->text());
//    settings.setValue("Men25_112", ui->tableWidget_25Men->item(11,2)->text());
//    settings.setValue("Men25_113", ui->tableWidget_25Men->item(11,3)->text());
//    settings.setValue("Men25_114", ui->tableWidget_25Men->item(11,4)->text());
//    settings.setValue("Men25_115", ui->tableWidget_25Men->item(11,5)->text());
//    settings.setValue("Men25_116", ui->tableWidget_25Men->item(11,6)->text());
//    settings.setValue("Men25_117", ui->tableWidget_25Men->item(11,7)->text());
//    settings.setValue("Men25_120", ui->tableWidget_25Men->item(12,0)->text());
//    settings.setValue("Men25_121", ui->tableWidget_25Men->item(12,1)->text());
//    settings.setValue("Men25_122", ui->tableWidget_25Men->item(12,2)->text());
//    settings.setValue("Men25_123", ui->tableWidget_25Men->item(12,3)->text());
//    settings.setValue("Men25_124", ui->tableWidget_25Men->item(12,4)->text());
//    settings.setValue("Men25_125", ui->tableWidget_25Men->item(12,5)->text());
//    settings.setValue("Men25_126", ui->tableWidget_25Men->item(12,6)->text());
//    settings.setValue("Men25_127", ui->tableWidget_25Men->item(12,7)->text());
//    settings.setValue("Men25_130", ui->tableWidget_25Men->item(13,0)->text());
//    settings.setValue("Men25_131", ui->tableWidget_25Men->item(13,1)->text());
//    settings.setValue("Men25_132", ui->tableWidget_25Men->item(13,2)->text());
//    settings.setValue("Men25_133", ui->tableWidget_25Men->item(13,3)->text());
//    settings.setValue("Men25_134", ui->tableWidget_25Men->item(13,4)->text());
//    settings.setValue("Men25_135", ui->tableWidget_25Men->item(13,5)->text());
//    settings.setValue("Men25_136", ui->tableWidget_25Men->item(13,6)->text());
//    settings.setValue("Men25_137", ui->tableWidget_25Men->item(13,7)->text());
//    settings.setValue("Men25_140", ui->tableWidget_25Men->item(14,0)->text());
//    settings.setValue("Men25_141", ui->tableWidget_25Men->item(14,1)->text());
//    settings.setValue("Men25_142", ui->tableWidget_25Men->item(14,2)->text());
//    settings.setValue("Men25_143", ui->tableWidget_25Men->item(14,3)->text());
//    settings.setValue("Men25_144", ui->tableWidget_25Men->item(14,4)->text());
//    settings.setValue("Men25_145", ui->tableWidget_25Men->item(14,5)->text());
//    settings.setValue("Men25_146", ui->tableWidget_25Men->item(14,6)->text());
//    settings.setValue("Men25_147", ui->tableWidget_25Men->item(14,7)->text());
//    settings.setValue("Men25_150", ui->tableWidget_25Men->item(15,0)->text());
//    settings.setValue("Men25_151", ui->tableWidget_25Men->item(15,1)->text());
//    settings.setValue("Men25_152", ui->tableWidget_25Men->item(15,2)->text());
//    settings.setValue("Men25_153", ui->tableWidget_25Men->item(15,3)->text());
//    settings.setValue("Men25_154", ui->tableWidget_25Men->item(15,4)->text());
//    settings.setValue("Men25_155", ui->tableWidget_25Men->item(15,5)->text());
//    settings.setValue("Men25_156", ui->tableWidget_25Men->item(15,6)->text());
//    settings.setValue("Men25_157", ui->tableWidget_25Men->item(15,7)->text());
//    settings.setValue("Men25_160", ui->tableWidget_25Men->item(16,0)->text());
//    settings.setValue("Men25_161", ui->tableWidget_25Men->item(16,1)->text());
//    settings.setValue("Men25_162", ui->tableWidget_25Men->item(16,2)->text());
//    settings.setValue("Men25_163", ui->tableWidget_25Men->item(16,3)->text());
//    settings.setValue("Men25_164", ui->tableWidget_25Men->item(16,4)->text());
//    settings.setValue("Men25_165", ui->tableWidget_25Men->item(16,5)->text());
//    settings.setValue("Men25_166", ui->tableWidget_25Men->item(16,6)->text());
//    settings.setValue("Men25_167", ui->tableWidget_25Men->item(16,7)->text());
//    settings.setValue("Men25_170", ui->tableWidget_25Men->item(17,0)->text());
//    settings.setValue("Men25_171", ui->tableWidget_25Men->item(17,1)->text());
//    settings.setValue("Men25_172", ui->tableWidget_25Men->item(17,2)->text());
//    settings.setValue("Men25_173", ui->tableWidget_25Men->item(17,3)->text());
//    settings.setValue("Men25_174", ui->tableWidget_25Men->item(17,4)->text());
//    settings.setValue("Men25_175", ui->tableWidget_25Men->item(17,5)->text());
//    settings.setValue("Men25_176", ui->tableWidget_25Men->item(17,6)->text());
//    settings.setValue("Men25_177", ui->tableWidget_25Men->item(17,7)->text());
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
//    settings.setValue("Men50_20", ui->tableWidget_50Men->item(2,0)->text());
//    settings.setValue("Men50_21", ui->tableWidget_50Men->item(2,1)->text());
//    settings.setValue("Men50_22", ui->tableWidget_50Men->item(2,2)->text());
//    settings.setValue("Men50_23", ui->tableWidget_50Men->item(2,3)->text());
//    settings.setValue("Men50_24", ui->tableWidget_50Men->item(2,4)->text());
//    settings.setValue("Men50_25", ui->tableWidget_50Men->item(2,5)->text());
//    settings.setValue("Men50_26", ui->tableWidget_50Men->item(2,6)->text());
//    settings.setValue("Men50_27", ui->tableWidget_50Men->item(2,7)->text());
//    settings.setValue("Men50_30", ui->tableWidget_50Men->item(3,0)->text());
//    settings.setValue("Men50_31", ui->tableWidget_50Men->item(3,1)->text());
//    settings.setValue("Men50_32", ui->tableWidget_50Men->item(3,2)->text());
//    settings.setValue("Men50_33", ui->tableWidget_50Men->item(3,3)->text());
//    settings.setValue("Men50_34", ui->tableWidget_50Men->item(3,4)->text());
//    settings.setValue("Men50_35", ui->tableWidget_50Men->item(3,5)->text());
//    settings.setValue("Men50_36", ui->tableWidget_50Men->item(3,6)->text());
//    settings.setValue("Men50_37", ui->tableWidget_50Men->item(3,7)->text());
//    settings.setValue("Men50_40", ui->tableWidget_50Men->item(4,0)->text());
//    settings.setValue("Men50_41", ui->tableWidget_50Men->item(4,1)->text());
//    settings.setValue("Men50_42", ui->tableWidget_50Men->item(4,2)->text());
//    settings.setValue("Men50_43", ui->tableWidget_50Men->item(4,3)->text());
//    settings.setValue("Men50_44", ui->tableWidget_50Men->item(4,4)->text());
//    settings.setValue("Men50_45", ui->tableWidget_50Men->item(4,5)->text());
//    settings.setValue("Men50_46", ui->tableWidget_50Men->item(4,6)->text());
//    settings.setValue("Men50_47", ui->tableWidget_50Men->item(4,7)->text());
//    settings.setValue("Men50_50", ui->tableWidget_50Men->item(5,0)->text());
//    settings.setValue("Men50_51", ui->tableWidget_50Men->item(5,1)->text());
//    settings.setValue("Men50_52", ui->tableWidget_50Men->item(5,2)->text());
//    settings.setValue("Men50_53", ui->tableWidget_50Men->item(5,3)->text());
//    settings.setValue("Men50_54", ui->tableWidget_50Men->item(5,4)->text());
//    settings.setValue("Men50_55", ui->tableWidget_50Men->item(5,5)->text());
//    settings.setValue("Men50_56", ui->tableWidget_50Men->item(5,6)->text());
//    settings.setValue("Men50_57", ui->tableWidget_50Men->item(5,7)->text());
//    settings.setValue("Men50_60", ui->tableWidget_50Men->item(6,0)->text());
//    settings.setValue("Men50_61", ui->tableWidget_50Men->item(6,1)->text());
//    settings.setValue("Men50_62", ui->tableWidget_50Men->item(6,2)->text());
//    settings.setValue("Men50_63", ui->tableWidget_50Men->item(6,3)->text());
//    settings.setValue("Men50_64", ui->tableWidget_50Men->item(6,4)->text());
//    settings.setValue("Men50_65", ui->tableWidget_50Men->item(6,5)->text());
//    settings.setValue("Men50_66", ui->tableWidget_50Men->item(6,6)->text());
//    settings.setValue("Men50_67", ui->tableWidget_50Men->item(6,7)->text());
//    settings.setValue("Men50_70", ui->tableWidget_50Men->item(7,0)->text());
//    settings.setValue("Men50_71", ui->tableWidget_50Men->item(7,1)->text());
//    settings.setValue("Men50_72", ui->tableWidget_50Men->item(7,2)->text());
//    settings.setValue("Men50_73", ui->tableWidget_50Men->item(7,3)->text());
//    settings.setValue("Men50_74", ui->tableWidget_50Men->item(7,4)->text());
//    settings.setValue("Men50_75", ui->tableWidget_50Men->item(7,5)->text());
//    settings.setValue("Men50_76", ui->tableWidget_50Men->item(7,6)->text());
//    settings.setValue("Men50_77", ui->tableWidget_50Men->item(7,7)->text());
//    settings.setValue("Men50_80", ui->tableWidget_50Men->item(8,0)->text());
//    settings.setValue("Men50_81", ui->tableWidget_50Men->item(8,1)->text());
//    settings.setValue("Men50_82", ui->tableWidget_50Men->item(8,2)->text());
//    settings.setValue("Men50_83", ui->tableWidget_50Men->item(8,3)->text());
//    settings.setValue("Men50_84", ui->tableWidget_50Men->item(8,4)->text());
//    settings.setValue("Men50_85", ui->tableWidget_50Men->item(8,5)->text());
//    settings.setValue("Men50_86", ui->tableWidget_50Men->item(8,6)->text());
//    settings.setValue("Men50_87", ui->tableWidget_50Men->item(8,7)->text());
//    settings.setValue("Men50_90", ui->tableWidget_50Men->item(9,0)->text());
//    settings.setValue("Men50_91", ui->tableWidget_50Men->item(9,1)->text());
//    settings.setValue("Men50_92", ui->tableWidget_50Men->item(9,2)->text());
//    settings.setValue("Men50_93", ui->tableWidget_50Men->item(9,3)->text());
//    settings.setValue("Men50_94", ui->tableWidget_50Men->item(9,4)->text());
//    settings.setValue("Men50_95", ui->tableWidget_50Men->item(9,5)->text());
//    settings.setValue("Men50_96", ui->tableWidget_50Men->item(9,6)->text());
//    settings.setValue("Men50_97", ui->tableWidget_50Men->item(9,7)->text());
//    settings.setValue("Men50_100", ui->tableWidget_50Men->item(10,0)->text());
//    settings.setValue("Men50_101", ui->tableWidget_50Men->item(10,1)->text());
//    settings.setValue("Men50_102", ui->tableWidget_50Men->item(10,2)->text());
//    settings.setValue("Men50_103", ui->tableWidget_50Men->item(10,3)->text());
//    settings.setValue("Men50_104", ui->tableWidget_50Men->item(10,4)->text());
//    settings.setValue("Men50_105", ui->tableWidget_50Men->item(10,5)->text());
//    settings.setValue("Men50_106", ui->tableWidget_50Men->item(10,6)->text());
//    settings.setValue("Men50_107", ui->tableWidget_50Men->item(10,7)->text());
//    settings.setValue("Men50_110", ui->tableWidget_50Men->item(11,0)->text());
//    settings.setValue("Men50_111", ui->tableWidget_50Men->item(11,1)->text());
//    settings.setValue("Men50_112", ui->tableWidget_50Men->item(11,2)->text());
//    settings.setValue("Men50_113", ui->tableWidget_50Men->item(11,3)->text());
//    settings.setValue("Men50_114", ui->tableWidget_50Men->item(11,4)->text());
//    settings.setValue("Men50_115", ui->tableWidget_50Men->item(11,5)->text());
//    settings.setValue("Men50_116", ui->tableWidget_50Men->item(11,6)->text());
//    settings.setValue("Men50_117", ui->tableWidget_50Men->item(11,7)->text());
//    settings.setValue("Men50_120", ui->tableWidget_50Men->item(12,0)->text());
//    settings.setValue("Men50_121", ui->tableWidget_50Men->item(12,1)->text());
//    settings.setValue("Men50_122", ui->tableWidget_50Men->item(12,2)->text());
//    settings.setValue("Men50_123", ui->tableWidget_50Men->item(12,3)->text());
//    settings.setValue("Men50_124", ui->tableWidget_50Men->item(12,4)->text());
//    settings.setValue("Men50_125", ui->tableWidget_50Men->item(12,5)->text());
//    settings.setValue("Men50_126", ui->tableWidget_50Men->item(12,6)->text());
//    settings.setValue("Men50_127", ui->tableWidget_50Men->item(12,7)->text());
//    settings.setValue("Men50_130", ui->tableWidget_50Men->item(13,0)->text());
//    settings.setValue("Men50_131", ui->tableWidget_50Men->item(13,1)->text());
//    settings.setValue("Men50_132", ui->tableWidget_50Men->item(13,2)->text());
//    settings.setValue("Men50_133", ui->tableWidget_50Men->item(13,3)->text());
//    settings.setValue("Men50_134", ui->tableWidget_50Men->item(13,4)->text());
//    settings.setValue("Men50_135", ui->tableWidget_50Men->item(13,5)->text());
//    settings.setValue("Men50_136", ui->tableWidget_50Men->item(13,6)->text());
//    settings.setValue("Men50_137", ui->tableWidget_50Men->item(13,7)->text());
//    settings.setValue("Men50_140", ui->tableWidget_50Men->item(14,0)->text());
//    settings.setValue("Men50_141", ui->tableWidget_50Men->item(14,1)->text());
//    settings.setValue("Men50_142", ui->tableWidget_50Men->item(14,2)->text());
//    settings.setValue("Men50_143", ui->tableWidget_50Men->item(14,3)->text());
//    settings.setValue("Men50_144", ui->tableWidget_50Men->item(14,4)->text());
//    settings.setValue("Men50_145", ui->tableWidget_50Men->item(14,5)->text());
//    settings.setValue("Men50_146", ui->tableWidget_50Men->item(14,6)->text());
//    settings.setValue("Men50_147", ui->tableWidget_50Men->item(14,7)->text());
//    settings.setValue("Men50_150", ui->tableWidget_50Men->item(15,0)->text());
//    settings.setValue("Men50_151", ui->tableWidget_50Men->item(15,1)->text());
//    settings.setValue("Men50_152", ui->tableWidget_50Men->item(15,2)->text());
//    settings.setValue("Men50_153", ui->tableWidget_50Men->item(15,3)->text());
//    settings.setValue("Men50_154", ui->tableWidget_50Men->item(15,4)->text());
//    settings.setValue("Men50_155", ui->tableWidget_50Men->item(15,5)->text());
//    settings.setValue("Men50_156", ui->tableWidget_50Men->item(15,6)->text());
//    settings.setValue("Men50_157", ui->tableWidget_50Men->item(15,7)->text());
//    settings.setValue("Men50_160", ui->tableWidget_50Men->item(16,0)->text());
//    settings.setValue("Men50_161", ui->tableWidget_50Men->item(16,1)->text());
//    settings.setValue("Men50_162", ui->tableWidget_50Men->item(16,2)->text());
//    settings.setValue("Men50_163", ui->tableWidget_50Men->item(16,3)->text());
//    settings.setValue("Men50_164", ui->tableWidget_50Men->item(16,4)->text());
//    settings.setValue("Men50_165", ui->tableWidget_50Men->item(16,5)->text());
//    settings.setValue("Men50_166", ui->tableWidget_50Men->item(16,6)->text());
//    settings.setValue("Men50_167", ui->tableWidget_50Men->item(16,7)->text());
//    settings.setValue("Men50_170", ui->tableWidget_50Men->item(17,0)->text());
//    settings.setValue("Men50_171", ui->tableWidget_50Men->item(17,1)->text());
//    settings.setValue("Men50_172", ui->tableWidget_50Men->item(17,2)->text());
//    settings.setValue("Men50_173", ui->tableWidget_50Men->item(17,3)->text());
//    settings.setValue("Men50_174", ui->tableWidget_50Men->item(17,4)->text());
//    settings.setValue("Men50_175", ui->tableWidget_50Men->item(17,5)->text());
//    settings.setValue("Men50_176", ui->tableWidget_50Men->item(17,6)->text());
//    settings.setValue("Men50_177", ui->tableWidget_50Men->item(17,7)->text());
//    settings.endGroup();
}
