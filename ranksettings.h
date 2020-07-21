#ifndef RANKSETTINGS_H
#define RANKSETTINGS_H

#include <QWidget>

namespace Ui {
class RankSettings;
}

class RankSettings : public QWidget
{
    Q_OBJECT
signals:
    void rankMenu();
public:
    explicit RankSettings(QWidget *parent = nullptr);
    ~RankSettings();
    Ui::RankSettings *ui;
private slots:
   // void on_pushButton_back_clicked();
    void on_pushButton_saveChanges_clicked();
    void on_pushButton_clicked();

private:

};

#endif // RANKSETTINGS_H
