#ifndef STARTINGPROTOCOL_H
#define STARTINGPROTOCOL_H

#include <QWidget>
#include <ranksettings.h>
#include <ui_ranksettings.h>
#include <ui_settingsrecords.h>
#include <settingsrecords.h>
namespace Ui {
class StartingProtocol;
}

class StartingProtocol : public QWidget
{
    Q_OBJECT

public:
    explicit StartingProtocol(QWidget *parent = nullptr);
    ~StartingProtocol();
     Ui::StartingProtocol *ui;

signals:
    void protocolWindow();
private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_openFile_clicked();
    void on_pushButton_createSwim_clicked();
    void on_pushButton_copyTableSwim_clicked();
    void on_pushButton_copyTableReitings_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_createNewReiting_clicked();
    void on_pushButton_clearTableReiting_clicked();
    void on_pushButton_deleteRow_clicked();
    void on_pushButton_addParticipant_clicked();
    void on_pushButton_sortByYears_clicked();
    void on_pushButton_OK_timeInput_clicked();
    void on_tableWidget_startSwim_itemPressed(QTableWidgetItem *item);
    void on_pushButton_closeWidgetAddPerson_clicked();
    void on_pushButton_copyTableProtocol_clicked();
    void on_pushButton_DK_clicked();
    void on_comboBox_swimPool_currentTextChanged(const QString &arg1);
    void on_pushButton_saveStartSwim_clicked();
    void on_pushButton_clicked();
    void on_pushButton_copyManyFights_clicked();
    void on_pushButton_clearTableTeams_clicked();
    void on_pushButton_goToManyFights_clicked();
    void on_pushButton_goToTeams_clicked();
    void on_pushButton_openFileFights_clicked();
    void on_pushButton_saveFileFights_clicked();
    void on_pushButton_saveFileTeam_clicked();
    void on_pushButton_openFileTeam_clicked();
    void on_pushButton_openFileProtocol_clicked();
    void on_pushButton_cleanFightTable_clicked();
    void on_pushButton_cleanProtocol_clicked();
    void on_pushButton_copyStartProtocolEstafet_clicked();
    void on_comboBox_protocolFiles_currentIndexChanged(const QString &arg1);
    void on_pushButton_OK_timeInput_2_clicked();
    void on_pushButton_DK_2_clicked();
    void on_pushButton_cleanProtocol_2_clicked();
    void on_pushButton_createNewReiting_2_clicked();
    void on_pushButton_copyTableSwim_2_clicked();
    void on_pushButton_update_2_clicked();
    void on_comboBox_swimPool_2_currentIndexChanged(const QString &arg1);
    void on_pushButton_sortByYears_2_clicked();
    void on_pushButton_openFileProtocol_2_clicked();
    void on_comboBox_protocolFiles_2_currentTextChanged(const QString &arg1);
    void on_comboBox_swimPool_2_currentTextChanged(const QString &arg1);
    void on_pushButton_goToTeams_2_clicked();
    void on_pushButton_copyTableProtocol_2_clicked();
    void on_pushButton_goToManyFights_2_clicked();
    void on_tableWidget_startSwim_2_itemPressed(QTableWidgetItem *item);
    void on_lineEdit_firstSportsmen_textChanged(const QString &arg1);
    void on_comboBox_category_currentTextChanged(const QString &arg1);
    void on_pushButton_addSortYear_2_clicked();
    void on_pushButton_removeSortYear_2_clicked();
    void on_pushButton_updateByYears_2_clicked();
    void on_pushButton_clearSortTable_2_clicked();
    void on_pushButton_addSortYear_clicked();
    void on_pushButton_removeSortYear_clicked();
    void on_pushButton_clearSortTable_clicked();
    void on_pushButton_updateByYears_clicked();
    void on_pushButton_PK_2_clicked();
    void on_pushButton_addSortYear_3_clicked();
    void on_pushButton_removeSortYear_3_clicked();
    void on_pushButton_updateByYears_3_clicked();
    void on_pushButton_clearSortTable_3_clicked();
    void on_pushButton_addSortYear_4_clicked();

    void on_pushButton_removeSortYear_4_clicked();

    void on_pushButton_clearSortTable_4_clicked();

    void on_pushButton_updateByYears_4_clicked();

    void on_pushButton_AddOnePerson_clicked();

    void on_checkBox_personalOrTeam_clicked(bool checked);

    void on_lineEdit_findHuman_textChanged(const QString &arg1);
    void updateRatingTable();
    void setTableRowsHidden(QTableWidget * table,bool isHidden);
    void setRowsNumbering(QTableWidget * table);
    void on_comboBox_sortBagatoborstvoGender_currentIndexChanged(const QString &arg1);

private:

};

#endif // STARTINGPROTOCOL_H
