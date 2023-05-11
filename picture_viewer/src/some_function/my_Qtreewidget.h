//
// Created by top on 2023-05-10.
//

#ifndef PICTURE_VIEWER_MY_QTREEWIDGET_H
#define PICTURE_VIEWER_MY_QTREEWIDGET_H


#include <QWidget>
#include <QTreeWidget>
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
#include "Qurl"
#include <QResource>
#include <QPixmap>
#include "QDir"
#include "my_photo_Graphics.h"
#include <QTimer>
#include <QDateTime>
#include <QPainter>
#include <QDesktopServices>

class My_Qtreewidget : public QTreeWidget{
Q_OBJECT

signals:

public slots:
public:
    QString *ProjectDir2 = new QString(PROJECT_ROOT_DIR);
    QString ProjectDir = *ProjectDir2 + R"(\src\ui\images)";
private:
    My_Photo_Graphics *my_photo = nullptr;
    QTreeWidgetItem *active_item = nullptr; //当前图片激活的节点
    QTreeWidgetItem *activated_path_parent= nullptr;//当前图片激活的路径的父节点
    QStringList path_list ;
    int path_list_index ;
    QString activated_path = nullptr; //当前图片激活的路径
    QStringList imageTypes {"bmp","jpg","png","tif","gif","fpx","svg","psd"};

public:
    explicit My_Qtreewidget(QWidget *parent = nullptr) : QTreeWidget(parent) {
        this->_Qtree_dir();
    }
    // 实现单击显示图片
    void click_photo_connect(My_Photo_Graphics &photo_g){
        my_photo = &photo_g;
        QObject::connect(this, &QTreeWidget::itemClicked,[this](QTreeWidgetItem *item){
            QString img_path = item->data(0,Qt::UserRole).toString();
            activated_path = img_path;
            std::cout<<activated_path.toStdString()<<endl;
            bool is_img = _is_type(img_path, this->imageTypes);
            if (is_img) {
                //注意，这个时候的this->photo_label 和 ui.photo_label共用一个地址
                //将点击的照片数据给 photo_label->activated_photo_pixmap
                //点击图片时，把这个图片数据保存到内存
                my_photo->or_activated_photo_pixmap = QPixmap(img_path);
                my_photo->click_show_photo();
                active_item = item;
                // 更新path_list
                QTreeWidgetItem *parent = item->parent();
                _updata_path_list(parent);

            }
        });

    }



private:
    void keyPressEvent(QKeyEvent *event) override
    { //
        if (event->key() == Qt::Key_Left) {
            if (my_photo != nullptr && !path_list.empty()){
                path_list_index = path_list_index - 1;
                if (path_list_index < 0){
                    path_list_index = path_list.size() - 1;
                }
                activated_path = path_list[path_list_index];
                active_item.nextSibling();
                my_photo->or_activated_photo_pixmap = QPixmap(activated_path);
                my_photo->click_show_photo();
            }

        } else if (event->key() == Qt::Key_Right) {
            if (my_photo != nullptr && !path_list.empty()){
                path_list_index = path_list_index + 1;
                if (path_list_index >= path_list.size()){
                    path_list_index = 0;
                }
                activated_path = path_list[path_list_index];
                my_photo->or_activated_photo_pixmap = QPixmap(activated_path);
                my_photo->click_show_photo();
            }
        } else {
            // 其他按键的事件处理
        }
    }

    void _updata_path_list(QTreeWidgetItem *parent){
        if (parent!=activated_path_parent){
            //指向的地址不一样，就重新获取父节点的所有文件路径，
            path_list.clear();
            activated_path_parent = parent;
            if (parent != nullptr) { // 确保当前节点有父节点
                int child_count = parent->childCount();
                for (int i = 0; i < child_count; ++i) {
                    QTreeWidgetItem *child = parent->child(i);
                    if (child != nullptr) { // 检查子节点是否存在
                        QString child_path = child->data(0, Qt::UserRole).toString();
                        bool is_img = _is_type(child_path, this->imageTypes);
                        if (is_img){
                            path_list.append(child_path);
                        }
                        if(child_path==activated_path){
                            path_list_index = i;
                        }
                    }
                }
            }
        }
        else{
            // path_list 不用更新，更新一下index
            path_list_index = path_list.indexOf( activated_path );
        }
    }

    bool _is_type(const QString& name, const QStringList& strlist){
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
        auto *rootNode = new QTreeWidgetItem(this); //设置根节点信息
        rootNode->setText(0, "目录");
        rootNode->setData(0, Qt::UserRole, ProjectDir);
        rootNode->setIcon(0, QIcon(":ui/images/pic/folder-solid.svg"));
        // 传入的为：树，根节点，路径, 递归函数用于添加子目录及其子节点
        _addSubDirs( this, rootNode, ProjectDir);

        _dir_connect();
        this->show();

    }

    void _dir_connect(){
        // 连接目录的图片的信号

        // 节点的文件夹的 图片开关设置
        QObject::connect(this, &QTreeWidget::itemExpanded,[](QTreeWidgetItem *item){
            item->setIcon(0, QIcon(":ui/images//pic/folder-open-regular.svg"));
        });
        QObject::connect(this, &QTreeWidget::itemCollapsed,[](QTreeWidgetItem *item){
            item->setIcon(0, QIcon(":ui/images//pic/folder-solid.svg"));
        });
        //双击打开文件夹目录
        QObject::connect(this, &QTreeWidget::itemDoubleClicked, [](QTreeWidgetItem *item, int column){
            qDebug() << "Item double clicked:" << item->text(column);
            QString dirPath = item->data(0, Qt::UserRole).toString();
            qDebug() << "Item double clicked path:" << dirPath;
            QDesktopServices::openUrl(QUrl(dirPath));
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
            node->setText(1, fileType);
            // 获取文件目录
            node->setData(0, Qt::UserRole, fileInfo.filePath());
            if (fileType == "files"){
                bool is_img = _is_type(fileName,imageTypes);
                if (is_img){
                    node->setIcon(0, QIcon(":ui/images//pic/file-image-solid.svg"));
                }
                else{
                    node->setIcon(0, QIcon(":ui/images//pic/file-lines-solid.svg"));
                }
            }
            else{
                node->setIcon(0, QIcon(":ui/images//pic/folder-solid.svg"));
                _addSubDirs(this, node, fileInfo.filePath());
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


#endif //PICTURE_VIEWER_MY_QTREEWIDGET_H
