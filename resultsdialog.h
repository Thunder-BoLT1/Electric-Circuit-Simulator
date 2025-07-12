#ifndef RESULTSDIALOG_H
#define RESULTSDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include "IComponent.h"

class ResultsDialog: public QDialog
{
    QLineEdit* Name, *Value, *VoltageDrop, *Current, *Power;
    QPushButton* Ok;
public:
    ResultsDialog(IComponent*);
};

#endif // RESULTSDIALOG_H
