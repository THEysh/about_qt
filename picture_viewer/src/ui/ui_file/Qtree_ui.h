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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "../../some_function/my_photo_Graphics.h"
#include "../../some_function/my_qtreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_Qtree_Class_UI
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    My_Qtreewidget *treeWidget_1;
    My_Photo_Graphics *graphicsView;

    void setupUi(QMainWindow *Qtree_Class_UI)
    {
        if (Qtree_Class_UI->objectName().isEmpty())
            Qtree_Class_UI->setObjectName(QStringLiteral("Qtree_Class_UI"));
        Qtree_Class_UI->resize(2324, 1470);
        Qtree_Class_UI->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(Qtree_Class_UI);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        treeWidget_1 = new My_Qtreewidget(centralwidget);
        treeWidget_1->setObjectName(QStringLiteral("treeWidget_1"));
        treeWidget_1->setMaximumSize(QSize(16777214, 16777215));
        treeWidget_1->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(treeWidget_1);

        graphicsView = new My_Photo_Graphics(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setStyleSheet(QStringLiteral("QGraphicsView {background-image:url(:/ui/images/pic_2d/wallhaven-3z32j3.jpg);}"));

        horizontalLayout_2->addWidget(graphicsView);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);

        horizontalLayout->addLayout(horizontalLayout_2);

        Qtree_Class_UI->setCentralWidget(centralwidget);

        retranslateUi(Qtree_Class_UI);

        QMetaObject::connectSlotsByName(Qtree_Class_UI);
    } // setupUi

    void retranslateUi(QMainWindow *Qtree_Class_UI)
    {
        Qtree_Class_UI->setWindowTitle(QApplication::translate("Qtree_Class_UI", "MainWindow", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_1->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("Qtree_Class_UI", "\346\226\207\344\273\266\345\210\227\350\241\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Qtree_Class_UI: public Ui_Qtree_Class_UI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QTREE_UI_H
