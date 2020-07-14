#ifndef CREATEFORM_H
#define CREATEFORM_H
#include <QMainWindow>
#include <QTableWidget>
#include "QStandardItemModel"
#include "QStandardItem"
#include <QComboBox>
#include <QVector>
#include <QAxObject>
#include <QModelIndex>
#include <QDir>
namespace Ui {
class CreateForm;
}
class CreateForm : public QMainWindow
{
    Q_OBJECT
public:
    explicit CreateForm(QWidget *parent = nullptr);
    ~CreateForm();
private slots:
    void on_pushButton_AddPerson_clicked();
    void on_pushButton_Save_clicked();
    void on_pushButton_OpenMsWord_clicked();
    void on_pushButton_openForm_clicked();
    void on_pushButton_Return_clicked();
    void on_pushButton_clicked();
    void on_pushButton_deleteRow_clicked();
    void on_checkBox_personalOrTeam_clicked(bool checked);

signals:
    void firstWindow();
private:
    Ui::CreateForm *ui;
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
};
#endif // CREATEFORM_H
