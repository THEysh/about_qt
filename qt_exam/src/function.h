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
#include "ui/Qtree_ui.h"
#include <QResource>
#include <QPixmap>
#include "QDir"
#include <QDesktopServices>
#include <QTimer>
#include <QDateTime>
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
        //在Qt中，signal的参数列表必须与slot的参数列表兼容，但不一定必须完全一致。一般来说，如果signal声明了参数，则slot也必须声明相同数量和类型的参数；否则，连接会失败。
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


class Slider_Color_Class: public QObject{
Q_OBJECT
public: signals:

public slots:
    // 定义槽函数
    void onSetClolor(int val); // onworkFinished用于判断是否完成 doSomething 函数，
    void random_color();
    void on_radioButton(); //radioButton,发出一个2进制 或者 八进制 10进制信号

public:
    Ui_QSlider_Color  ui_f{};
    Slider_Color_Class(Ui_QSlider_Color &ui_f){
        this->ui_f = ui_f;
        this->connect_funtion();
        this->reset(); //初始设置
    }
    void connect_funtion();

private:
    int type_val = 10;
    QString type_Slider_or_Dial = "QSlider";
    QString* dispkay_lcdNumber(int num)const;
    void reset();

};


class Qtree_Class : public QObject{
Q_OBJECT

signals:
    void photo_changed_signals1(int w, int h);

public slots:


public:
    Qtree_Class(Ui_Qtree_Class_UI &ui_f, QMainWindow *Win){
        ui_f.setupUi(Win);
        this->ui_f = ui_f;

        q_timer();
        this->_Qtree_dir();
        _photo_connect();
        // 创建一个时钟，每x毫秒更新一次

    }
public:
    QString *ProjectDir = new QString(PROJECT_ROOT_DIR); //项目的目录
    QStringList imageTypes {"bmp","jpg","png","tif","gif","fpx","svg","psd"};
private:
    Ui_Qtree_Class_UI ui_f;
    int photo_win_size_w;
    int photo_win_size_h;
    QString activated_path = nullptr; //当前图片激活的路径
    void q_timer(){

        auto *timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, [=]() {
            emit photo_changed_signals1(ui_f.photo_label->geometry().width(),ui_f.photo_label->geometry().height());
        });
        timer->start(400);

    }


    bool is_type(const QString& name, const QStringList& strlist){
        //输出 name，这个name 算法在包含 strlist内
        // 例：name = abc.jpg, strlist = {".jpg",".png"...}  返回true
        //name =F:/code/c_code/about_qt/qt_exam/src/ui/images/pic/delete.png , strlist = {".jpg",".png"...}  返回true
        QString type = this->_rag(name);
        for (const auto& imgtype :strlist){
            if (type.endsWith(imgtype)) {//判断是否是图片格式
                return true;
            }
        }
        return false;
    }

    void _Qtree_dir(){
        // 获取当前目录，并依次添加子目录和文件
        auto *rootNode = new QTreeWidgetItem(ui_f.treeWidget_1); //设置根节点信息
        rootNode->setText(0, "目录");
        rootNode->setData(0, Qt::UserRole, *ProjectDir);
        rootNode->setIcon(0, QIcon(":images/pic/folder-solid.svg"));
        _dir_connect(rootNode);
        // 传入的为：树，根节点，路径, 递归函数用于添加子目录及其子节点
        _addSubDirs(ui_f.treeWidget_1, rootNode, *ProjectDir);

        ui_f.treeWidget_1->show();
    }

    void _photo_connect(){
        // 更新label照片的尺寸
        QObject::connect(this,&Qtree_Class::photo_changed_signals1,[this](int w, int h){
            this->photo_win_size_w = w;
            this->photo_win_size_h = h;
            //Qt::KeepAspectRatio保持比例
            bool is_img = is_type(activated_path,imageTypes);
            if (is_img){
                QPixmap new_pixmap = QPixmap(activated_path).scaled(w,h,Qt::KeepAspectRatio);
                ui_f.photo_label->setPixmap(new_pixmap);
            }
        });
    }

    void _dir_connect(QTreeWidgetItem* rootNode){
        // 连接目录的图片的信号

        // 节点的文件夹的 图片开关设置
        QObject::connect(ui_f.treeWidget_1, &QTreeWidget::itemExpanded,[](QTreeWidgetItem *item){
            item->setIcon(0, QIcon(":images/pic/folder-open-regular.svg"));
        });
        QObject::connect(ui_f.treeWidget_1, &QTreeWidget::itemCollapsed,[](QTreeWidgetItem *item){
            item->setIcon(0, QIcon(":images/pic/folder-solid.svg"));
        });
        //双击打开文件夹目录
        QObject::connect(ui_f.treeWidget_1, &QTreeWidget::itemDoubleClicked, [](QTreeWidgetItem *item, int column){
            qDebug() << "Item double clicked:" << item->text(column);
            QString dirPath = item->data(0, Qt::UserRole).toString();
            qDebug() << "Item double clicked path:" << dirPath;
            QDesktopServices::openUrl(QUrl(dirPath));
        });
        //单击显示图片
        QObject::connect(ui_f.treeWidget_1, &QTreeWidget::itemClicked,[this](QTreeWidgetItem *item){
            QString img_path = item->data(0,Qt::UserRole).toString();
            activated_path = img_path;
            bool is_img = is_type(img_path, this->imageTypes);
            if (is_img){
                ui_f.photo_label->setPixmap(img_path);
            }

            cout<<item->data(0,Qt::UserRole).toString().toStdString()<<endl;

        });

    }

    void _addSubDirs(QTreeWidget *tree, QTreeWidgetItem *parentNode, const QString& path) {
        QDir directory(path);
        //具体地说，这个代码使用entryInfoList函数获取了directory目录下的所有文件和目录的信息，包括隐藏文件和当前目录以及父级目录（"."和".."），并将它们的QFileInfo对象添加到QFileInfoList列表中。
        //参数QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot是用来设置entryInfoList函数的选项，其中：
        //QDir::Files指示返回文件的信息
        //QDir::AllDirs指示返回子目录的信息
        //QDir::NoDotAndDotDot指示过滤掉"."和".."目录
        QFileInfoList fileList = directory.entryInfoList(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
        for (int i = 0; i < fileList.count(); ++i) {
            QFileInfo fileInfo = fileList.at(i);
            QString fileName = fileInfo.fileName();
            QString fileType = fileInfo.isFile() ? "files" : "folders";

            // 创建节点
            auto *node = new QTreeWidgetItem(parentNode);
            //下面 设置节点的信息
            node->setText(0, fileName);
            node->setData(0, Qt::UserRole, fileInfo.filePath());
            if (fileType == "files"){

                bool is_img = is_type(fileName,imageTypes);
                if (is_img){
                    node->setIcon(0, QIcon(":images/pic/file-image-solid.svg"));
                }
                else{
                    node->setIcon(0, QIcon(":images/pic/file-lines-solid.svg"));
                }
            }
            else{
                node->setIcon(0, QIcon(":images/pic/folder-solid.svg"));
                _addSubDirs(ui_f.treeWidget_1, node, fileInfo.filePath());
            }
        }
    }

    QString _rag(const QString& name){
        //利用正则表达式，获取类型
        QRegularExpression pattern("\\.([A-Za-z0-9]+)$"); //qt的正则表达式获取 链接"."后面的类型
        QRegularExpressionMatch match = pattern.match(name);
        if (match.hasMatch()) {
            QString fileExtension = match.captured(1);
            return "."+ fileExtension;
        }
        else{
            return ".";
        }
    }

};


#endif //QT_EXAM_FUNCTION_H
