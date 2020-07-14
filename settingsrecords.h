#ifndef SETTINGSRECORDS_H
#define SETTINGSRECORDS_H

#include <QWidget>

namespace Ui {
class SettingsRecords;
}

class SettingsRecords : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsRecords(QWidget *parent = nullptr);
    ~SettingsRecords();
    Ui::SettingsRecords *ui;

private slots:
    void on_pushButton_save_recordsSettings_clicked();

private:

};

#endif // SETTINGSRECORDS_H
