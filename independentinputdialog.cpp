#include "independentinputdialog.h"
#include <QDir>

IndependentInputDialog::IndependentInputDialog(QString n, double v) {

    setWindowTitle("Attributes");
    setWindowIcon(QIcon(QDir::currentPath() + "\\input.png"));
    //Set LineEdits (this) is important for automatic memory allocation as it makes QT handles it Automatically with the main widget
    name = new QLineEdit(this);
    name->setPlaceholderText(n);
    value = new QLineEdit(this);
    value->setPlaceholderText(QString::number(v));
    //Set PushButtons
    ok = new QPushButton(this);
    ok->setText("OK");
    cancel = new QPushButton(this);
    cancel->setText("Cancel");
    //Design The Layout
    QFormLayout *MyFormLayout = new QFormLayout(this);
    QHBoxLayout *MyButtonsLayout = new QHBoxLayout();
    MyFormLayout->addRow("Name ", name);
    MyFormLayout->addRow("Value ", value);
    MyButtonsLayout->addWidget(cancel);
    MyButtonsLayout->addWidget(ok);
    MyFormLayout->addRow(MyButtonsLayout);

    setLayout(MyFormLayout);

    //OK Button -> Accept
    connect(ok, &QPushButton::clicked, this, [this](){accept();});
    //Cancel Button -> Reject
    connect(cancel, &QPushButton::clicked, this, [this](){reject();});

    //This is A CSS StyleSheet I Found Looks Better Now :D
    setStyleSheet(R"(
        QDialog {
            background-color: #f8f9fa;
            border: 1px solid #ccc;
            border-radius: 8px;
            font-family: 'Segoe UI', sans-serif;
            font-size: 14px;
        }

        QLabel {
            color: #333;
            min-width: 70px;
        }

        QLineEdit {
            background-color: #fff;
            border: 1px solid #aaa;
            border-radius: 4px;
            padding: 5px;
        }

        QLineEdit:focus {
            border: 1px solid #0078d7;
            outline: none;
        }

        QPushButton {
            background-color: #0078d7;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 6px 12px;
        }

        QPushButton:hover {
            background-color: #005fa1;
        }

        QPushButton:pressed {
            background-color: #004b87;
        }
    )");

}

QString IndependentInputDialog::Get_Name(){return name->text();}
double IndependentInputDialog::Get_Value(){return value->text().toDouble();}


