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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../../my_photo_Graphics.h"

QT_BEGIN_NAMESPACE

class Ui_Qtree_Class_UI
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *treeWidget_1;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    My_Photo_Graphics *graphicsView;

    void setupUi(QMainWindow *Qtree_Class_UI)
    {
        if (Qtree_Class_UI->objectName().isEmpty())
            Qtree_Class_UI->setObjectName(QStringLiteral("Qtree_Class_UI"));
        Qtree_Class_UI->resize(2415, 1470);
        centralwidget = new QWidget(Qtree_Class_UI);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        treeWidget_1 = new QTreeWidget(centralwidget);
        treeWidget_1->setObjectName(QStringLiteral("treeWidget_1"));
        treeWidget_1->setMaximumSize(QSize(400, 16777215));

        horizontalLayout->addWidget(treeWidget_1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 0, -1, 0);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 80));
        tabWidget->setMaximumSize(QSize(16777215, 150));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_1 = new QPushButton(tab);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));

        horizontalLayout_2->addWidget(pushButton_1);

        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(tab);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_2->addWidget(pushButton_5);

        tabWidget->addTab(tab, QString());

        verticalLayout_3->addWidget(tabWidget);

        graphicsView = new My_Photo_Graphics(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout_3->addWidget(graphicsView);


        horizontalLayout->addLayout(verticalLayout_3);

        Qtree_Class_UI->setCentralWidget(centralwidget);

        retranslateUi(Qtree_Class_UI);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Qtree_Class_UI);
    } // setupUi

    void retranslateUi(QMainWindow *Qtree_Class_UI)
    {
        Qtree_Class_UI->setWindowTitle(QApplication::translate("Qtree_Class_UI", "MainWindow", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_1->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("Qtree_Class_UI", "\346\226\207\344\273\266\345\210\227\350\241\250", Q_NULLPTR));
        pushButton_1->setText(QApplication::translate("Qtree_Class_UI", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Qtree_Class_UI", "PushButton", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Qtree_Class_UI", "PushButton", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("Qtree_Class_UI", "PushButton", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("Qtree_Class_UI", "PushButton", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Qtree_Class_UI", "\345\267\245\345\205\267\346\240\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Qtree_Class_UI: public Ui_Qtree_Class_UI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QTREE_UI_H
