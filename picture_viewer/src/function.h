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
#include "ui/ui_file/Qtree_ui.h"
#include "Qurl"
#include <QResource>
#include <QPixmap>
#include "QDir"
#include <QTimer>
#include <QDateTime>
#include <QPainter>
#include <QDesktopServices>
using namespace  std;



class Qtree_Class : public QWidget{
Q_OBJECT

signals:

public slots:

public:
    Qtree_Class(Ui_Qtree_Class_UI &ui_f, QMainWindow *Win){
        ui_f.setupUi(Win);
        this->ui_f = ui_f;
        photo_g = ui_f.graphicsView;  //这样是实现，ui_f.photo_label 和 这个类中的photo_label共用一个地址
        this->_Qtree_dir();

    }
public:
    QString *ProjectDir2 = new QString(PROJECT_ROOT_DIR);
    QString ProjectDir = *ProjectDir2 + R"(\src\ui\images)";
private:
    Ui_Qtree_Class_UI ui_f;
    My_Photo_Graphics *photo_g;
    QString activated_path = nullptr; //当前图片激活的路径
    QStringList imageTypes {"bmp","jpg","png","tif","gif","fpx","svg","psd"};

    bool is_type(const QString& name, const QStringList& strlist){
        //输出 name，这个name 算法在包含 strlist内
        //例：name = abc.jpg, strlist = {".jpg",".png"...}  返回true
        //name = F:/code/c_code/about_qt/picture_viewer/src/ui/images/pic/delete.png , strlist = {".jpg",".png"...}  返回true
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
        rootNode->setData(0, Qt::UserRole, ProjectDir);
        rootNode->setIcon(0, QIcon(":ui/images//pic/folder-solid.svg"));
        _dir_connect(rootNode);
        // 传入的为：树，根节点，路径, 递归函数用于添加子目录及其子节点
        _addSubDirs(ui_f.treeWidget_1, rootNode, ProjectDir);

        ui_f.treeWidget_1->show();
    }

    void _dir_connect(QTreeWidgetItem* rootNode){
        // 连接目录的图片的信号

        // 节点的文件夹的 图片开关设置
        QObject::connect(ui_f.treeWidget_1, &QTreeWidget::itemExpanded,[](QTreeWidgetItem *item){
            item->setIcon(0, QIcon(":ui/images//pic/folder-open-regular.svg"));
        });
        QObject::connect(ui_f.treeWidget_1, &QTreeWidget::itemCollapsed,[](QTreeWidgetItem *item){
            item->setIcon(0, QIcon(":ui/images//pic/folder-solid.svg"));
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
            cout<<activated_path.toStdString()<<endl;
            bool is_img = is_type(img_path, this->imageTypes);
            if (is_img) {
                //注意，这个时候的this->photo_label 和 ui.photo_label共用一个地址
                //将点击的照片数据给 photo_label->activated_photo_pixmap
                //点击图片时，把这个图片数据保存到内存
                photo_g->or_activated_photo_pixmap = QPixmap(img_path);
                photo_g->click_show_photo();
            }

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
                    node->setIcon(0, QIcon(":ui/images//pic/file-image-solid.svg"));
                }
                else{
                    node->setIcon(0, QIcon(":ui/images//pic/file-lines-solid.svg"));
                }
            }
            else{
                node->setIcon(0, QIcon(":ui/images//pic/folder-solid.svg"));
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
