//
// Created by top on 2023-05-10.
//

#ifndef PICTURE_VIEWER_MY_QTREEWIDGET_H
#define PICTURE_VIEWER_MY_QTREEWIDGET_H

// -*- coding: utf-8 -*-
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
#include <QFileDialog>
#include <QQueue>
#include <QMenu>
#include <QInputDialog>
#include <QPointer>
#include <QClipboard>
#include <QCoreApplication>
#include <QFileSystemWatcher>

class SignalEmitter : public QObject {
Q_OBJECT
public:
    SignalEmitter(QObject *parent = nullptr) : QObject(parent) {}

signals:
    void mySignal(QTreeWidgetItem*);

public slots:
    void emitSignal(QTreeWidgetItem* sig) {
        emit mySignal(sig);
    }
};

class My_Qtreewidget : public QTreeWidget{
Q_OBJECT
signals:
    void my_signal_1(QTreeWidgetItem *item);
public slots:
public:
//    QString *ProjectDir2 = new QString(PROJECT_ROOT_DIR) ;
//    QString ProjectDir = *ProjectDir2 + R"(\src\ui\images)";
    QString ProjectDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation); //获取桌面目录

private:
    QFileSystemWatcher *my_watcher = new QFileSystemWatcher(); //监听文件的变化，然后更新目录
    QTreeWidgetItem *rootNode = new QTreeWidgetItem(this); //设置根节点信息

    const int MAX_NODE_COUNT = 1000;
    int nodeCount = 0; // 定义静态变量存储当前已经创建的节点数

    My_Photo_Graphics *my_photo = nullptr;
    QTreeWidgetItem *active_item = nullptr; //当前图片激活的节点

    QStringList imageTypes {"bmp","jpg","png","tif","gif","fpx","svg","psd"};

public:
    explicit My_Qtreewidget(QWidget *parent = nullptr) : QTreeWidget(parent) {
        //设置背景图片
        this->_dir_connect();
        this->_updata_all_Qtree_dir();
    }
    // 实现单击显示图片
    void click_photo_connect(My_Photo_Graphics &photo_g){
        my_photo = &photo_g;
        QObject::connect(this, &QTreeWidget::itemClicked,[this](QTreeWidgetItem *item){
            QString img_path = item->data(0,Qt::UserRole).toString();
            bool is_img = _is_type(img_path, this->imageTypes);
            if (is_img) {
                //注意，这个时候的this->photo_label 和 ui.photo_label共用一个地址
                //将点击的照片数据给 photo_label->activated_photo_pixmap
                //点击图片时，把这个图片数据保存到内存
                my_photo->or_activated_photo_pixmap = QPixmap(img_path);
                my_photo->click_show_photo();
                active_item = item;
            }
        });
    }

private:

    void _updata_all_Qtree_dir(){
        // 获取当前目录，并依次添加子目录和文件
        nodeCount = 0;
        //先清空rootNode下的所有节点
        while (rootNode->childCount() > 0){
            QTreeWidgetItem *child = rootNode->takeChild(0);
            delete child;
        }
        rootNode->setText(0, "双击此处打开目录");
        rootNode->setData(0, Qt::UserRole, ProjectDir);
        rootNode->setIcon(0, QIcon(":ui/images/pic/folder-solid.svg"));
        my_watcher->addPath(rootNode->data(0,Qt::UserRole).toString()); //添加监控
        // 传入的为：树，根节点，路径, 递归函数用于添加子目录及其子节点
        _addSubDirs(rootNode, ProjectDir);

    }

    void _updata_someone_QTreeWidgetItem(QTreeWidgetItem *parentNode, const QString& path){
        nodeCount = rootNode->childCount();
        while (parentNode->childCount() > 0){
            QTreeWidgetItem *child = parentNode->takeChild(0);
            delete child;
        }
        _addSubDirs(parentNode, path);

    }

    void _dir_connect(){

        // 节点的文件夹的 图片开关设置
        QObject::connect(this, &QTreeWidget::itemExpanded,[](QTreeWidgetItem *item){
            item->setIcon(0, QIcon(":ui/images//pic/folder-open-regular.svg"));
        });
        //文件节点变化的监控
        // _updata_someone_QTreeWidgetItem(child,child->data(0,Qt::UserRole).toString());
        QObject::connect(my_watcher, &QFileSystemWatcher::directoryChanged, [this](const QString &changedPath){
            qDebug() << "Directory changed:" << changedPath;
            // 使用lambda函数，遍历所有的子节点, 检查到底是哪个节点发生变化
            // 注意，这个lambad函数，不能进行异步线程，它操作的对象属于GUI主线程，例如QTreeWidgetItem，从其他线程访问这些对象是不安全的。
            // 任何修改或访问GUI对象的代码都应该只在主线程上运行，因为Qt的GUI类和函数都不是可重入的。试图从其他线程修改/访问这些对象会导致崩溃
            std::function<QTreeWidgetItem*(QTreeWidgetItem*)> lambda_traverseTreeItems = [&](QTreeWidgetItem *item)-> QTreeWidgetItem*{
                if(item->data(0,Qt::UserRole).toString()==changedPath){
                    return item;
                }
                int childCount = item->childCount(); // 获取当前节点的子节点数量
                for (int i = 0; i < childCount; i++) {
                    QTreeWidgetItem *child = item->child(i); // 获取子节点
                    // 在这里对子节点进行操作
                    // 递归遍历该子节点的所有子节点
                    QTreeWidgetItem *result = lambda_traverseTreeItems(child);
                    if(result != nullptr) { // 如果找到了目标节点，则直接返回该节点
                        return result;
                    }
                }
                // 如果在当前节点及其子节点中未找到目标节点，则返回空指针
                return nullptr;
            };
            auto *child = lambda_traverseTreeItems(rootNode);
            if (child!= nullptr){
                _updata_someone_QTreeWidgetItem(child,child->data(0,Qt::UserRole).toString());
            }
        });

        // 双击打开目录
        QObject::connect(this, &QTreeWidget::itemDoubleClicked, [this](QTreeWidgetItem *item, int column){
            if (item==rootNode){ //如果是根节点就打开文件，重新读目录
                QString folderPath = QFileDialog::getExistingDirectory(nullptr, QObject::tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
                if (!folderPath.isEmpty()) {
                    QDir folderDir(folderPath);
                    QString absoluteFolderPath = folderDir.absolutePath();
                    ProjectDir = absoluteFolderPath;
                    //更新目录，删除节点
                    this->_updata_all_Qtree_dir();
                }
            } else{
                //双击打开路径
                QString dirPath = item->data(0, Qt::UserRole).toString();
                //以上代码将文件夹路径传递给 QUrl::fromLocalFile() 函数创建一个 QUrl 对象。该对象可以正确地处理包含非 ASCII 字符的文件路径，避免了出现乱码的问题
                QUrl QUrl_path = QUrl::fromLocalFile(dirPath);
                QDesktopServices::openUrl(QUrl_path);
            }
        });


    }

    // 键盘切换上一张下一张图片
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Left) {
            _updata_treewidgetItem(false); //计算上一个节点,并更新
            my_photo->or_activated_photo_pixmap = QPixmap(active_item->data(0,Qt::UserRole).toString());
            my_photo->click_show_photo();
        }
        else if (event->key() == Qt::Key_Right){
            _updata_treewidgetItem(true);
            my_photo->or_activated_photo_pixmap = QPixmap(active_item->data(0,Qt::UserRole).toString());
            my_photo->click_show_photo();
        }
    }

    /*计算下一兄弟节点或者上一兄弟节点,is_next=true就是计算下一兄弟节点，否则计算上一个兄弟节点*/
    void _updata_treewidgetItem(bool is_next){

        QTreeWidgetItem *siblingItem = nullptr;
        if (is_next && active_item && active_item->parent() && active_item->parent()->childCount() >= 1) {
            int siblingIndex = active_item->parent()->indexOfChild(active_item); //返回当前节点的索引

            if (siblingIndex < active_item->parent()->childCount() - 1) {
                siblingItem = active_item->parent()->child(siblingIndex + 1);
            }
            else if(siblingIndex==active_item->parent()->childCount() - 1) {
                siblingItem = active_item->parent()->child(0);
            }
        } else if( !is_next && active_item && active_item->parent() && active_item->parent()->childCount() >= 1){
            int siblingIndex = active_item->parent()->indexOfChild(active_item); //返回当前节点的索引

            if (siblingIndex > 0) {
                siblingItem = active_item->parent()->child(siblingIndex - 1);
            }
            else if(siblingIndex==0) {
                siblingItem = active_item->parent()->child(active_item->parent()->childCount()-1);
            }
        }

        active_item->setSelected(false);
        active_item = siblingItem;
        active_item->setSelected(true);

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

    void _addSubDirs(QTreeWidgetItem *parentNode, const QString& path) {
        //BFS
        QDir directory(path);
        // QTreeWidgetItem *temp_parentNode = parentNode; //创建一个 QTreeWidgetItem指针，用于传值
        QQueue<QTreeWidgetItem*> file_queue;
        file_queue.enqueue(parentNode);
        while (!file_queue.isEmpty()) {
            if (nodeCount++>MAX_NODE_COUNT){return;}
            // 取出队列中的第一个节点,构建树节点，同时也用作下一个节点的父类
            QTreeWidgetItem *temp_parentNode = file_queue.front();
            QDir temp_directory(temp_parentNode->data(0, Qt::UserRole).toString());
            //具体地说，这个代码使用entryInfoList函数获取了directory目录下的所有文件和目录的信息，包括隐藏文件和当前目录以及父级目录（"."和".."），并将它们的QFileInfo对象添加到QFileInfoList列表中。
            //参数QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot是用来设置entryInfoList函数的选项，其中：
            //QDir::Files指示返回文件的信息
            //QDir::AllDirs指示返回子目录的信息
            //QDir::NoDotAndDotDot指示过滤掉"."和".."目录
            QFileInfoList fileList = temp_directory.entryInfoList(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
            int size = fileList.count();
            // 队列中删除这个节点
            file_queue.dequeue();
            // 遍历与当前节点相连的所有节点
            for (int i = 0; i < size; i++) {
                QFileInfo fileInfo = fileList.at(i);
                QString fileName = fileInfo.fileName();
                QString fileType = fileInfo.isFile() ? "files" : "folders";
                bool is_img = _is_type(fileName,imageTypes);
                if (fileType=="files" && is_img){
                    //下面 设置节点的信息
                    nodeCount ++;
                    auto *node = new QTreeWidgetItem(temp_parentNode);
                    node->setText(0, fileName);
                    node->setText(1, fileType);
                    node->setText(2, temp_parentNode->data(0,Qt::UserRole).toString()); //保存父类的路径
                    // 获取文件目录
                    node->setData(0, Qt::UserRole, fileInfo.filePath());
                    node->setIcon(0, QIcon(":ui/images//pic/file-image-solid.svg"));

                }

                else if (fileType=="folders"){
                    nodeCount ++;
                    auto *node = new QTreeWidgetItem(temp_parentNode);
                    node->setText(0, fileName);
                    node->setText(1, fileType);
                    node->setText(2, temp_parentNode->data(0,Qt::UserRole).toString()); //保存父类的路径
                    // 获取文件目录
                    node->setData(0, Qt::UserRole, fileInfo.filePath());
                    node->setIcon(0, QIcon(":ui/images//pic/folder-solid.svg"));
                    my_watcher->addPath(node->data(0,Qt::UserRole).toString()); //添加监控，文件夹路径下的变化监控
                    // 是目录，将其加入队列中
                    file_queue.enqueue(node);
                }
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

    // 右键菜单
    void contextMenuEvent(QContextMenuEvent *event) override
    {
        // 右键菜单
        QTreeWidget::contextMenuEvent(event);
        QTreeWidgetItem* item = currentItem();

        if (!item)
            return;
        // 创建右键菜单并添加动作
        QMenu menu(this);
        QAction* openAction = menu.addAction("打开");
        QAction* copyAction = menu.addAction("复制路径");
        QAction* RenameAction = menu.addAction("Rename");
        QAction* removeAction = menu.addAction("永久删除");

        // 显示右键菜单，并获取用户选择的动作
        QAction* selectedItem = menu.exec(event->globalPos());

        if (selectedItem == removeAction) {
            QTreeWidgetItem *parent = item->parent();
            if (parent!= nullptr){
                // 有父类才可以删除
                parent->takeChild(parent->indexOfChild(item)); //删除节点
                // os 删除文件，文件夹
                QString remove_Path = item->data(0, Qt::UserRole).toString();
                QString filetype = item->text(1);
                if (filetype=="files"){
                    QFile file(remove_Path);
                    file.remove();
                }
                else{
                    QDir dir(remove_Path);
                    dir.removeRecursively();
                }
            }
        }
        else if (selectedItem == openAction) {
            QString path = item->data(0, Qt::UserRole).toString();
            QDesktopServices::openUrl(QUrl::fromLocalFile(path));
        }
        else if (selectedItem == RenameAction){
            QTreeWidgetItem* item = currentItem();
            if (!item)
                return;
            QString oldName = item->text(0);
            // 创建一个QLineEdit对象
            QLineEdit *lineEdit = new QLineEdit();
            // 将QTreeWidgetItem的setFlags()函数设置为允许编辑
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            // 调用QTreeWidget的setItemWidget()函数将QLineEdit添加到QTreeWidgetItem中
            this->setItemWidget(item, 0, lineEdit);
            // 调用QTreeWidget的editItem()函数进入编辑模式
            this->editItem(item, 0);

            connect(lineEdit, &QLineEdit::editingFinished, this, [=]() {
                item->setText(0, lineEdit->text());
                item->setText(2, item->parent()->data(0,Qt::UserRole).toString()); //保存父类的路径
                // 获取文件目录
                QString new_path = item->parent()->data(0,Qt::UserRole).toString()+"/"+lineEdit->text();
                qDebug()<<new_path;
                item->setData(0, Qt::UserRole, new_path);//写入新的路径
                _updata_someone_QTreeWidgetItem(item,new_path);
                // 这行代码是关闭当前的编辑器，第一个参数lineEdit是当前所在的编辑器，第二个参数QAbstractItemDelegate::NoHint表示不修改任何标志位。
                this->closeEditor(lineEdit, QAbstractItemDelegate::NoHint);
                // 这行代码是将QLineEdit从QTreeWidgetItem中删除，第一个参数item是当前正在编辑的树形结构中的项，
                // 第二个参数0表示所在的列，第三个参数NULL表示移除该控件。
                this->setItemWidget(item, 0, NULL);
            });

//            if (!lineEdit->text().isEmpty()) {
//                // 更新节点名称
//                item->setText(0, lineEdit->text());
//                // os 重命名文件，文件夹
//                QString oldPath = item->data(0, Qt::UserRole).toString();
//                QString newPath = oldPath;
//                int index = newPath.lastIndexOf("/");
//                newPath.remove(index+1, oldName.length());
//                newPath += lineEdit->text();
//                QFile file(oldPath);
//                QDir dir(oldPath);
//                if (file.exists()){
//                    file.rename(newPath);
//                }
//                else{
//                    dir.rename(oldPath,newPath);
//                }
//            }
        }

        else if (selectedItem == copyAction){
            // 获取剪贴板
            QClipboard *clipboard = QGuiApplication::clipboard();
            // 要复制到剪贴板的文本
            QString path = item->data(0, Qt::UserRole).toString();
            // 将文本复制到剪贴板中
            clipboard->setText(path);
        }
    }

};






#endif //PICTURE_VIEWER_MY_QTREEWIDGET_H
