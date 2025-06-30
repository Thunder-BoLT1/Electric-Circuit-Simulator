#include "componentsmenu.h"

ComponentsMenu::ComponentsMenu() {

    QVBoxLayout* Layout = new QVBoxLayout(this);
    QHBoxLayout* SubLayout = new QHBoxLayout();

    Type = new QComboBox(this);
    Items = new QComboBox(this);

    add = new QPushButton(this);
    add->setText("Add");

    cancel = new QPushButton(this);
    cancel->setText("Cancel");

    SubLayout->addWidget(cancel);

    SubLayout->addWidget(add);

    Layout->addWidget(Type);
    Layout->addWidget(Items);
    Layout->addItem(SubLayout);

    ComponentsMap["Independent Sources"] = {"Voltage Source", "Current Source"};
    ComponentsMap["Dependent Sources"] = {"VCCS", "VCVS", "CCCS", "CCVS"};
    ComponentsMap["Passive Components"] = {"Resistor"};

    Type->addItems(ComponentsMap.keys());

    UpdateItems();
    connect(Type, &QComboBox::currentTextChanged, this, &ComponentsMenu::UpdateItems);

    //OK Button -> Accept
    connect(add, &QPushButton::clicked, this, [this](){accept();});
    //Cancel Button -> Reject
    connect(cancel, &QPushButton::clicked, this, [this](){reject();});

}

void ComponentsMenu::UpdateItems(){
    Items->clear();
    Items->addItems(ComponentsMap[Type->currentText()]);
}

QString ComponentsMenu::Get_Type(){
    return Items->currentText();
}
