/********************************************************************************
** Form generated from reading UI file 'Qtree_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QTREE_UI_H
#define QTREE_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../../some_function/my_photo_Graphics.h"
#include "../../some_function/my_qtreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_Qtree_Class_UI
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_1;
    QWidget *verticalWidget;
    QVBoxLayout *v2;
    QCheckBox *checkBox;
    My_Qtreewidget *treeWidget_1;
    My_Photo_Graphics *graphicsView;

    void setupUi(QMainWindow *Qtree_Class_UI)
    {
        if (Qtree_Class_UI->objectName().isEmpty())
            Qtree_Class_UI->setObjectName(QStringLiteral("Qtree_Class_UI"));
        Qtree_Class_UI->resize(1843, 1361);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Qtree_Class_UI->sizePolicy().hasHeightForWidth());
        Qtree_Class_UI->setSizePolicy(sizePolicy);
        Qtree_Class_UI->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(Qtree_Class_UI);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setSpacing(0);
        horizontalLayout_1->setObjectName(QStringLiteral("horizontalLayout_1"));
        horizontalLayout_1->setContentsMargins(-1, 0, -1, 0);
        verticalWidget = new QWidget(centralwidget);
        verticalWidget->setObjectName(QStringLiteral("verticalWidget"));
        v2 = new QVBoxLayout(verticalWidget);
        v2->setSpacing(10);
        v2->setObjectName(QStringLiteral("v2"));
        v2->setContentsMargins(10, 10, 5, 10);
        checkBox = new QCheckBox(verticalWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy1);
        checkBox->setTristate(true);

        v2->addWidget(checkBox);

        treeWidget_1 = new My_Qtreewidget(verticalWidget);
        treeWidget_1->setObjectName(QStringLiteral("treeWidget_1"));
        treeWidget_1->setMaximumSize(QSize(16777214, 16777215));
        treeWidget_1->setStyleSheet(QStringLiteral(""));

        v2->addWidget(treeWidget_1);


        horizontalLayout_1->addWidget(verticalWidget);

        graphicsView = new My_Photo_Graphics(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setStyleSheet(QStringLiteral(""));

        horizontalLayout_1->addWidget(graphicsView);

        horizontalLayout_1->setStretch(1, 4);

        verticalLayout->addLayout(horizontalLayout_1);

        Qtree_Class_UI->setCentralWidget(centralwidget);

        retranslateUi(Qtree_Class_UI);

        QMetaObject::connectSlotsByName(Qtree_Class_UI);
    } // setupUi

    void retranslateUi(QMainWindow *Qtree_Class_UI)
    {
        Qtree_Class_UI->setWindowTitle(QApplication::translate("Qtree_Class_UI", "MainWindow", Q_NULLPTR));
        checkBox->setText(QApplication::translate("Qtree_Class_UI", "\350\207\252\351\200\202\345\272\224\347\274\251\346\224\276", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_1->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("Qtree_Class_UI", "\346\226\207\344\273\266\345\210\227\350\241\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Qtree_Class_UI: public Ui_Qtree_Class_UI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QTREE_UI_H
