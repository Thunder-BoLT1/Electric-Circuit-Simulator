#ifndef COMPONENTSMENU_H
#define COMPONENTSMENU_H
#include <QDialog>
#include <QComboBox>
#include <QVboxLayout>
#include <QHboxLayout>
#include <QPushButton>
#include <QMap>
#include <QDir>

class ComponentsMenu: public QDialog
{
    Q_OBJECT
    QComboBox *Type, *Items;
    QPushButton * add, *cancel;
    QMap<QString, QStringList> ComponentsMap;
public:
    ComponentsMenu();
    QString Get_Type();

private slots:
    void UpdateItems();
};

#endif // COMPONENTSMENU_H
