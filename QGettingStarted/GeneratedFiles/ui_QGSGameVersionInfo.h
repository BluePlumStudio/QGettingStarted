/********************************************************************************
** Form generated from reading UI file 'QGSGameVersionInfo.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGSGAMEVERSIONINFO_H
#define UI_QGSGAMEVERSIONINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QGSGameVersionInfo
{
public:

    void setupUi(QWidget *QGSGameVersionInfo)
    {
        if (QGSGameVersionInfo->objectName().isEmpty())
            QGSGameVersionInfo->setObjectName(QStringLiteral("QGSGameVersionInfo"));
        QGSGameVersionInfo->resize(400, 300);

        retranslateUi(QGSGameVersionInfo);

        QMetaObject::connectSlotsByName(QGSGameVersionInfo);
    } // setupUi

    void retranslateUi(QWidget *QGSGameVersionInfo)
    {
        QGSGameVersionInfo->setWindowTitle(QApplication::translate("QGSGameVersionInfo", "QGSGameVersionInfo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QGSGameVersionInfo: public Ui_QGSGameVersionInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGSGAMEVERSIONINFO_H
