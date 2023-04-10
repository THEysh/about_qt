//
// function.h
//

#ifndef QT_EXAM_FUNCTION_H
#define QT_EXAM_FUNCTION_H
#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "iostream"
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QSignalMapper>
#include <QString>
#include <QPushButton>
#include "ui/myfirst_ui.h"
#include "ui/Qstring_Interface_switching_ui.h"
#include "ui/QSlider_color_ui.h"
#include <QResource>
#include <QPixmap>

using namespace  std;

class ThreadReceiver : public QObject
{
    /**
     * /这个类用于多线程信号通信，do_work_Something函数绘睡眠，睡眠完成后会发送信号“work is done”,主函数可以参考如下：
     * main:
    ThreadReceiver receiver(ui_f); double sleep_time = 1; long dim =192 ;
    receiver.button1_connect(receiver.ui_f.pushButton,sleep_time);
    receiver.button2_connect(receiver.ui_f.pushButton_2,sleep_time, dim); //将dim10进制转为2进制(10亿以内)
     */
Q_OBJECT

signals:
    void signal_1(QWidget *qw, QString q_ans);
    //定义一个信号，并定义与这个信号连接的槽函数 void onworkFinished
    // 构造这个类时，将信号连接起来,一般情况函数onworkFinished，和signal_1的传参类型是一致的
    // 因为signal_1发出一个A类型的信号，onworkFinished也应该要接收一个A类型的信号表示任务完成
public slots:
    // 定义槽函数
    void onworkFinished(QWidget *qw, const QString& q_ans) const; // onworkFinished用于判断是否完成 doSomething 函数，
    void do_work_Something(QWidget *qw, double sleep_time); //多线程睡眠，计算随机数的一个乘法
    void do_work_decimal_to_binary(QWidget *qw,double sleep_time,long number); //多线程睡眠，计算十进制转二进制
public:
    Ui_MainWindow ui_f;
    double sleep_time = 0.5;
    ThreadReceiver(Ui_MainWindow &ui_f, QObject* parent = nullptr) : QObject(parent){
        // 创建信号的连接
        this->ui_f = ui_f;
        QObject::connect(this, &ThreadReceiver::signal_1, this, &ThreadReceiver::onworkFinished);

        this->button1_connect(ui_f.pushButton, sleep_time);
        this->button2_connect(ui_f.pushButton_2, sleep_time,12345);
    }

    void button1_connect(QPushButton *button, double sleep_time);

    void button2_connect(QPushButton *button, double sleep_time, long number);

    void print_meg(const QString& text) const;

};

class Interface_Class : public QObject{
public:
    Ui_Interface_MainWindow  ui_f;
    Interface_Class(Ui_Interface_MainWindow  &ui_f){
        this->ui_f = ui_f;
        this->connect_but1();
        this->connect_but2();
        this->connect_but2_2();
        this->connect_but3();
        this->connect_but4();
        this->connect_but5();
        this->connect_but6();
        this->connect_but7();
        this->connect_but8();
        this->connect_but9();
        this->connect_but10();
    }
    void connect_but1 (){
        QObject::connect(ui_f.pushButton_1, &QPushButton::clicked,[&](){
            QString str1 = ui_f.lineEdit1->text();
            QString str2 = ui_f.lineEdit2->text();
            QString str3 = ui_f.lineEdit3->text();
            ui_f.lineEdit3->setText(str3.append(str1).append(str2));
        });
    }
    void connect_but2 (){
        QObject::connect(ui_f.pushButton_2_1, &QPushButton::clicked,[&](){
            QString str1 = ui_f.lineEdit1->text();
            QString str2 = ui_f.lineEdit2->text();
            QString str3 = ui_f.lineEdit3->text();
            ui_f.lineEdit3->setText(str3.prepend(str1).prepend(str2));
        });
    }
    void connect_but2_2(){
        QObject::connect(ui_f.pushButton_2_2, &QPushButton::clicked,[&](){
            QString str1 = ui_f.lineEdit1->text();
            QString str2 = ui_f.lineEdit2->text();
            ui_f.lineEdit3->clear();
            QString re_text = QString("str1的长度计算： %1, str2的长度计算%2").arg(str1.size()).arg(str2.size());
            ui_f.lineEdit3->setText(re_text);
        });
    }
    void connect_but3(){
        QObject::connect(ui_f.pushButton_3, &QPushButton::clicked,[&](){
            QString str1 = ui_f.lineEdit1->text();
            QString str2 = ui_f.lineEdit2->text();
            ui_f.lineEdit3->clear();
            QString re_text = QString("str1的转换大写计算:%1, str2的长度转换大写:%2").arg(str1.toUpper()).arg(str2.toUpper());
            ui_f.lineEdit3->setText(re_text);
        });

    }

    void connect_but4(){
        QObject::connect(ui_f.pushButton_4, &QPushButton::clicked,[&](){
            QString str1 = ui_f.lineEdit1->text();
            QString str2 = ui_f.lineEdit2->text();
            ui_f.lineEdit3->clear();
            QString re_text = QString("str1的转换大写计算:%1, str2的长度转换大写:%2").arg(str1.toLower()).arg(str2.toLower());
            ui_f.lineEdit3->setText(re_text);
        });
    }
    void connect_but5 (){
        connect(ui_f.pushButton_5, &QPushButton::clicked,[=]{
            ui_f.stackedWidget->setCurrentIndex(0);
        });
    }
    void connect_but6 (){
        QObject::connect(ui_f.pushButton_6, &QPushButton::clicked,[&](){
            QString str1 = ui_f.lineEdit1->text();
            QString str2 = ui_f.lineEdit2->text();
            ui_f.lineEdit3->clear();
            QString re_text;
            if(str1.isEmpty() || str2.isEmpty()){
                re_text = "str1中不存在str2";
            }
            else if (str1.contains(str2)){
                re_text = "str1中存在str2";
            }
            else{
                re_text = "str1中不存在str2";
            }
            ui_f.lineEdit3->setText(re_text);
        });
    }

    void connect_but7 (){
        QObject::connect(ui_f.pushButton_7, &QPushButton::clicked,[&](){
            QString str1 = ui_f.lineEdit1->text();
            QString str2 = ui_f.lineEdit2->text();
            ui_f.lineEdit3->clear();
            QString re_text = QString("str1:%1,str2:%2").arg(str1.isNull()).arg(str2.isNull());
            ui_f.lineEdit3->setText(re_text);
        });
    }
    void connect_but8 (){
        QObject::connect(ui_f.pushButton_7, &QPushButton::clicked,[&](){
            QString str1 = ui_f.lineEdit1->text();
            QString str2 = ui_f.lineEdit2->text();
            ui_f.lineEdit3->clear();
            QString re_text = QString("str1:%1,str2:%2").arg(str1.isEmpty()).arg(str2.isEmpty());
            ui_f.lineEdit3->setText(re_text);
        });
    }
    void connect_but9(){
        QObject::connect(ui_f.pushButton_9, &QPushButton::clicked,[&](){
            QString str1 = ui_f.lineEdit1->text();
            QString& text = str1;
            // 定义单词分隔符和忽略列表
            const QRegExp wordSeparator(R"(\W+)");
            const QStringList ignoreList = {"a", "an", "the", "and", "but", "or", "for", "nor", "on", "at", "to", "from",
                                            "by", "up", "as", "in", "out", "off", "via", "per"};
            // 定义结果字符串、单词列表和当前处理状态
            QString result;
            QStringList words = text.split(wordSeparator, QString::SkipEmptyParts);
            bool inName = false;

            for (int i = 0; i < words.length(); ++i) {
                QString currentWord = words[i];

                // 处理姓名
                if (!inName && i < words.length() - 1 && words[i + 1].startsWith("'")) {
                    inName = true;
                } else if (inName && i > 0 && !words[i - 1].endsWith(",")) {
                    inName = false;
                }

                // 根据当前处理状态和忽略列表判断是否应该处理当前单词
                bool shouldCapitalize = true;
                if (ignoreList.contains(currentWord.toLower())) {
                    shouldCapitalize = false;
                } else if (inName) {
                    shouldCapitalize = true;
                } else if (currentWord.contains("-")) {
                    QStringList hyphenatedWords = currentWord.split("-");
                    shouldCapitalize = std::all_of(hyphenatedWords.begin(), hyphenatedWords.end(),
                                                   [](const QString& w){ return !w.isEmpty(); });
                } else if (currentWord.length() <= 2 && i > 0) {
                    shouldCapitalize = false;
                }

                // 处理当前单词
                if (shouldCapitalize) {
                    QChar firstChar = currentWord.at(0);
                    result += firstChar.toUpper();
                    result += currentWord.mid(1).toLower();
                } else {
                    result += currentWord.toLower();
                }

                // 将单词加入结果字符串中，并添加合适的分隔符
                if (i < words.length() - 1) {
                    result += " ";
                }
            }
            ui_f.lineEdit3->clear();
            ui_f.lineEdit3->setText(result);

        });
    }
    void connect_but10 (){
        connect(ui_f.pushButton_10, &QPushButton::clicked,[=]{
            ui_f.stackedWidget->setCurrentIndex(1);
        });
    }
};

class Slider_Color: public QObject{
Q_OBJECT
public slots:
    // 定义槽函数
    void onSetClolor(int value) const; // onworkFinished用于判断是否完成 doSomething 函数，

public:
    Ui_QSlider_Color  ui_f{};
    Slider_Color(Ui_QSlider_Color &ui_f){
        this->ui_f = ui_f;
        this->connect_funtion();
    }
    void connect_funtion();
};



#endif //QT_EXAM_FUNCTION_H
