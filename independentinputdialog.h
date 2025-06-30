#ifndef INDEPENDENTINPUTDIALOG_H
#define INDEPENDENTINPUTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QHboxLayout>
#include <QFormLayout>

class IndependentInputDialog: public QDialog
{
    Q_OBJECT // Helps in connection of signals
    QLineEdit* name, *value;
    QPushButton*  ok, * cancel;
public:
    IndependentInputDialog();
    //Getters For the Inputs
    QString Get_Name();
    double Get_Value();
};

#endif // INDEPENDENTINPUTDIALOG_H
