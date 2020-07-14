#ifndef CALCULATORFINN_H
#define CALCULATORFINN_H

#include <QWidget>
#include "settingsrecords.h"
namespace Ui {
class CalculatorFinn;
}

class CalculatorFinn : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorFinn(QWidget *parent = nullptr);
    ~CalculatorFinn();

private slots:
    void on_pushButton_calculate_clicked();

private:
    Ui::CalculatorFinn *ui;
};

#endif // CALCULATORFINN_H
