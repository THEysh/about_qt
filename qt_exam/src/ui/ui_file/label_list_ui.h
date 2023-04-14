/********************************************************************************
** Form generated from reading UI file 'label_list_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LABEL_LIST_UI_H
#define LABEL_LIST_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Show_Label
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_1;
    QLabel *label_2;

    void setupUi(QMainWindow *Show_Label)
    {
        if (Show_Label->objectName().isEmpty())
            Show_Label->setObjectName(QStringLiteral("Show_Label"));
        Show_Label->resize(453, 600);
        centralwidget = new QWidget(Show_Label);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMaximumSize(QSize(200, 200));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMaximumSize(QSize(200, 200));

        gridLayout->addWidget(label_4, 1, 1, 1, 1);

        label_1 = new QLabel(centralwidget);
        label_1->setObjectName(QStringLiteral("label_1"));
        sizePolicy.setHeightForWidth(label_1->sizePolicy().hasHeightForWidth());
        label_1->setSizePolicy(sizePolicy);
        label_1->setMaximumSize(QSize(200, 200));

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(200, 200));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        Show_Label->setCentralWidget(centralwidget);

        retranslateUi(Show_Label);

        QMetaObject::connectSlotsByName(Show_Label);
    } // setupUi

    void retranslateUi(QMainWindow *Show_Label)
    {
        Show_Label->setWindowTitle(QApplication::translate("Show_Label", "MainWindow", Q_NULLPTR));
        label_3->setText(QApplication::translate("Show_Label", "TextLabel", Q_NULLPTR));
        label_4->setText(QApplication::translate("Show_Label", "TextLabel", Q_NULLPTR));
        label_1->setText(QApplication::translate("Show_Label", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("Show_Label", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Show_Label: public Ui_Show_Label {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LABEL_LIST_UI_H
