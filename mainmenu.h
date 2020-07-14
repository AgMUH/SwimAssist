#ifndef MAINMENU_H
#define MAINMENU_H
#include <QMainWindow>
#include <createform.h>
#include <ranksettings.h>
#include <startingprotocol.h>

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    Ui::MainMenu *ui;
private slots:
    void on_pushButton_CreateForm_clicked();
    void on_pushButton_calculatorFin_clicked();
    void on_pushButton_SettingsRecords_clicked();
    void on_pushButton_startingProtocol_clicked();
    void on_pushButton_sportRank_clicked();
private:
    CreateForm *newCreateForm;
    StartingProtocol *startingProtocol;
    RankSettings * rankSettings;
};
#endif // MAINMENU_H
