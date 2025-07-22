#include "resultsdialog.h"

ResultsDialog::ResultsDialog(IComponent* Component) {
    setWindowTitle("Results");
    setWindowIcon(QIcon(QDir::currentPath() + "\\research.png"));
    QFormLayout *MyFormLayout = new QFormLayout(this);

    Name = new QLineEdit(this);
    Name->setText(Component->GetName());
    Name->setReadOnly(true);
    MyFormLayout->addRow("Name ", Name);

    Value = new QLineEdit(this);
    Value->setText(QString::number(Component->GetValue()));
    Value->setReadOnly(true);
    MyFormLayout->addRow("Value ", Value);

    VoltageDrop = new QLineEdit(this);
    VoltageDrop->setText(QString::number(Component->GetVoltage()));
    VoltageDrop->setReadOnly(true);
    MyFormLayout->addRow("VoltageDrop ", VoltageDrop);

    Current = new QLineEdit(this);
    Current->setText(QString::number(Component->GetCurrent()));
    Current->setReadOnly(true);
    MyFormLayout->addRow("Current ", Current);

    Power = new QLineEdit(this);
    Power->setText(QString::number(Component->GetCurrent() * Component->GetVoltage()));
    Power->setReadOnly(true);
    MyFormLayout->addRow("Power ", Power);

    Ok = new QPushButton(this);
    Ok->setText("OK");
    MyFormLayout->addWidget(Ok);

    setLayout(MyFormLayout);

    connect(Ok, &QPushButton::clicked, this, [this](){accept();});
}
