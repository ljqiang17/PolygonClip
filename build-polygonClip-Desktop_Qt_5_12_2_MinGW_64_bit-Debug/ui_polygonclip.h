/********************************************************************************
** Form generated from reading UI file 'polygonclip.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLYGONCLIP_H
#define UI_POLYGONCLIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_polygonClip
{
public:

    void setupUi(QWidget *polygonClip)
    {
        if (polygonClip->objectName().isEmpty())
            polygonClip->setObjectName(QString::fromUtf8("polygonClip"));
        polygonClip->resize(400, 300);

        retranslateUi(polygonClip);

        QMetaObject::connectSlotsByName(polygonClip);
    } // setupUi

    void retranslateUi(QWidget *polygonClip)
    {
        polygonClip->setWindowTitle(QApplication::translate("polygonClip", "polygonClip", nullptr));
    } // retranslateUi

};

namespace Ui {
    class polygonClip: public Ui_polygonClip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLYGONCLIP_H
