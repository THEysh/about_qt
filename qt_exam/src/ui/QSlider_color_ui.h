/********************************************************************************
** Form generated from reading UI file 'QSlider_color_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QSLIDER_COLOR_UI_H
#define QSLIDER_COLOR_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QSlider_Color
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QSlider *sliderRed;
    QLabel *labRed;
    QSlider *sliderBlue;
    QLabel *labAlpha;
    QSlider *sliderGreen;
    QSlider *sliderAlpha;
    QLabel *labBlue;
    QLabel *labGreen;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton_random;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_5;
    QLCDNumber *lcdNumber_4;
    QLCDNumber *lcdNumber_1;
    QLCDNumber *lcdNumber_3;
    QLCDNumber *lcdNumber_2;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QListWidget *listWidget;
    QLabel *label_9;
    QRadioButton *radioButton_3;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *labRgbVal;
    QDial *dial_2;
    QDial *dial_3;
    QDial *dial_4;
    QDial *dial_1;
    QTextEdit *textColour;

    void setupUi(QWidget *QSlider_Color)
    {
        if (QSlider_Color->objectName().isEmpty())
            QSlider_Color->setObjectName(QStringLiteral("QSlider_Color"));
        QSlider_Color->resize(1333, 806);
        QSlider_Color->setMinimumSize(QSize(0, 800));
        horizontalLayout = new QHBoxLayout(QSlider_Color);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        sliderRed = new QSlider(QSlider_Color);
        sliderRed->setObjectName(QStringLiteral("sliderRed"));
        sliderRed->setMinimumSize(QSize(320, 0));
        sliderRed->setMaximum(255);
        sliderRed->setValue(145);
        sliderRed->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderRed, 0, 1, 1, 1);

        labRed = new QLabel(QSlider_Color);
        labRed->setObjectName(QStringLiteral("labRed"));
        labRed->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labRed, 0, 0, 1, 1);

        sliderBlue = new QSlider(QSlider_Color);
        sliderBlue->setObjectName(QStringLiteral("sliderBlue"));
        sliderBlue->setMaximum(255);
        sliderBlue->setValue(251);
        sliderBlue->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderBlue, 2, 1, 1, 1);

        labAlpha = new QLabel(QSlider_Color);
        labAlpha->setObjectName(QStringLiteral("labAlpha"));
        labAlpha->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labAlpha, 3, 0, 1, 1);

        sliderGreen = new QSlider(QSlider_Color);
        sliderGreen->setObjectName(QStringLiteral("sliderGreen"));
        sliderGreen->setMaximum(255);
        sliderGreen->setValue(190);
        sliderGreen->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderGreen, 1, 1, 1, 1);

        sliderAlpha = new QSlider(QSlider_Color);
        sliderAlpha->setObjectName(QStringLiteral("sliderAlpha"));
        sliderAlpha->setMaximum(255);
        sliderAlpha->setValue(255);
        sliderAlpha->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderAlpha, 3, 1, 1, 1);

        labBlue = new QLabel(QSlider_Color);
        labBlue->setObjectName(QStringLiteral("labBlue"));
        labBlue->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labBlue, 2, 0, 1, 1);

        labGreen = new QLabel(QSlider_Color);
        labGreen->setObjectName(QStringLiteral("labGreen"));
        labGreen->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labGreen, 1, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        pushButton_random = new QPushButton(QSlider_Color);
        pushButton_random->setObjectName(QStringLiteral("pushButton_random"));

        gridLayout_4->addWidget(pushButton_random, 5, 0, 1, 1);

        radioButton_1 = new QRadioButton(QSlider_Color);
        radioButton_1->setObjectName(QStringLiteral("radioButton_1"));

        gridLayout_4->addWidget(radioButton_1, 2, 0, 1, 1);

        radioButton_2 = new QRadioButton(QSlider_Color);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        gridLayout_4->addWidget(radioButton_2, 3, 0, 1, 1);

        tabWidget = new QTabWidget(QSlider_Color);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_5 = new QGridLayout(tab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        lcdNumber_4 = new QLCDNumber(tab);
        lcdNumber_4->setObjectName(QStringLiteral("lcdNumber_4"));
        lcdNumber_4->setDigitCount(8);

        gridLayout_5->addWidget(lcdNumber_4, 1, 1, 1, 1);

        lcdNumber_1 = new QLCDNumber(tab);
        lcdNumber_1->setObjectName(QStringLiteral("lcdNumber_1"));
        lcdNumber_1->setDigitCount(8);

        gridLayout_5->addWidget(lcdNumber_1, 0, 1, 1, 1);

        lcdNumber_3 = new QLCDNumber(tab);
        lcdNumber_3->setObjectName(QStringLiteral("lcdNumber_3"));
        lcdNumber_3->setDigitCount(8);

        gridLayout_5->addWidget(lcdNumber_3, 3, 1, 1, 1);

        lcdNumber_2 = new QLCDNumber(tab);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        lcdNumber_2->setDigitCount(8);

        gridLayout_5->addWidget(lcdNumber_2, 2, 1, 1, 1);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_5->addWidget(label_4, 1, 0, 1, 1);

        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_5->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_5->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_5->addWidget(label_3, 3, 0, 1, 1);

        gridLayout_5->setColumnStretch(0, 1);
        gridLayout_5->setColumnStretch(1, 6);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        comboBox = new QComboBox(tab_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);

        listWidget = new QListWidget(tab_2);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/pic/github.png"), QSize(), QIcon::Normal, QIcon::Off);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(11);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setCheckState(Qt::Unchecked);
        __qlistwidgetitem->setFont(font);
        __qlistwidgetitem->setIcon(icon);
        __qlistwidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);

        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/images/pic_2d/wallhaven-j3m12w.jpg")));

        verticalLayout->addWidget(label_9);

        tabWidget->addTab(tab_2, QString());

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 1);

        radioButton_3 = new QRadioButton(QSlider_Color);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setAutoRepeat(false);

        gridLayout_4->addWidget(radioButton_3, 4, 0, 1, 1);


        gridLayout->addLayout(gridLayout_4, 4, 0, 1, 2);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 6);

        horizontalLayout->addLayout(gridLayout);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        labRgbVal = new QLabel(QSlider_Color);
        labRgbVal->setObjectName(QStringLiteral("labRgbVal"));
        labRgbVal->setEnabled(false);
        labRgbVal->setScaledContents(false);
        labRgbVal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(labRgbVal, 1, 4, 1, 1);

        dial_2 = new QDial(QSlider_Color);
        dial_2->setObjectName(QStringLiteral("dial_2"));
        dial_2->setMaximum(255);

        gridLayout_2->addWidget(dial_2, 1, 1, 1, 1);

        dial_3 = new QDial(QSlider_Color);
        dial_3->setObjectName(QStringLiteral("dial_3"));
        dial_3->setMaximum(255);

        gridLayout_2->addWidget(dial_3, 1, 2, 1, 1);

        dial_4 = new QDial(QSlider_Color);
        dial_4->setObjectName(QStringLiteral("dial_4"));
        dial_4->setMaximum(255);

        gridLayout_2->addWidget(dial_4, 1, 3, 1, 1);

        dial_1 = new QDial(QSlider_Color);
        dial_1->setObjectName(QStringLiteral("dial_1"));
        dial_1->setMaximum(255);

        gridLayout_2->addWidget(dial_1, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 2);

        textColour = new QTextEdit(QSlider_Color);
        textColour->setObjectName(QStringLiteral("textColour"));
        textColour->setEnabled(false);
        textColour->setMinimumSize(QSize(200, 0));

        gridLayout_3->addWidget(textColour, 0, 0, 1, 2);


        horizontalLayout->addLayout(gridLayout_3);


        retranslateUi(QSlider_Color);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QSlider_Color);
    } // setupUi

    void retranslateUi(QWidget *QSlider_Color)
    {
        QSlider_Color->setWindowTitle(QApplication::translate("QSlider_Color", "ExQSlider", Q_NULLPTR));
        labRed->setText(QApplication::translate("QSlider_Color", "Red", Q_NULLPTR));
        labAlpha->setText(QApplication::translate("QSlider_Color", "Alpha", Q_NULLPTR));
        labBlue->setText(QApplication::translate("QSlider_Color", "Blue", Q_NULLPTR));
        labGreen->setText(QApplication::translate("QSlider_Color", "Green", Q_NULLPTR));
        pushButton_random->setText(QApplication::translate("QSlider_Color", "\351\232\217\346\234\272\350\216\267\345\217\226\344\270\200\347\247\215\351\242\234\350\211\262", Q_NULLPTR));
        radioButton_1->setText(QApplication::translate("QSlider_Color", "2\350\277\233\345\210\266", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("QSlider_Color", "8\350\277\233\345\210\266", Q_NULLPTR));
        label_4->setText(QApplication::translate("QSlider_Color", "Green", Q_NULLPTR));
        label->setText(QApplication::translate("QSlider_Color", "Red", Q_NULLPTR));
        label_2->setText(QApplication::translate("QSlider_Color", "Blue", Q_NULLPTR));
        label_3->setText(QApplication::translate("QSlider_Color", "Alpha", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QSlider_Color", "Tab 1", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("QSlider_Color", "\346\265\213\350\257\225\347\273\204\345\220\210\346\241\2061", Q_NULLPTR)
         << QApplication::translate("QSlider_Color", "\346\265\213\350\257\225\347\273\204\345\220\210\346\241\2062", Q_NULLPTR)
        );

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("QSlider_Color", "\344\272\221\346\203\263\350\241\243\350\243\263\350\212\261\346\203\263\345\256\271\357\274\214\346\230\245\351\243\216\346\213\202\346\247\233\351\234\262\345\215\216\346\265\223", Q_NULLPTR));
        listWidget->setSortingEnabled(__sortingEnabled);

        label_9->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("QSlider_Color", "Tab 2", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("QSlider_Color", "10\350\277\233\345\210\266", Q_NULLPTR));
        labRgbVal->setText(QApplication::translate("QSlider_Color", "RGB(145, 190, 251, 255)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QSlider_Color: public Ui_QSlider_Color {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QSLIDER_COLOR_UI_H
