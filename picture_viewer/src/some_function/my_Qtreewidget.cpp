//
// Created by top on 2023-05-10.
//

#include "QLineEdit"
#include <QGuiApplication>
#include <QQueue>
#include "QClipboard"
#include "My_Qtreewidget.h"
#include "qdebug.h"

My_Qtreewidget::My_Qtreewidget(QWidget *parent)
        : QTreeWidget(parent),
          MAX_NODE_COUNT(1000),
          nodeCount(0),
          rootNode(new QTreeWidgetItem(this)),
          ProjectDir(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)),
          my_photo(nullptr),
          my_watcher (new QFileSystemWatcher()),
          active_item(nullptr),
          imageTypes({"bmp","jpg","png","tif","gif","fpx","svg","psd"})

{
    this->setHeaderHidden(true);
    rootNode->setText(0, "双击此处打开目录");
    rootNode->setData(0, Qt::UserRole, ProjectDir);
    rootNode->setIcon(0, QIcon(":ui/images/pic/folder-solid.svg"));

    _dir_connect();
    _updata_all_Qtree_dir();
}

void My_Qtreewidget::connect_photo(My_Photo_Graphics *name) {
    // 运行之前必须要初始化类My_Photo_Graphics
    if (name!= nullptr){ my_photo = name;}
    else{qDebug()<<"connect_photo is nullpter";}

}

void My_Qtreewidget::_updata_all_Qtree_dir()
{
    nodeCount = 0;
    while (rootNode->childCount() > 0) {
        QTreeWidgetItem *child = rootNode->takeChild(0);
        delete child;
    }
    rootNode->setText(0, "双击此处打开目录");
    rootNode->setData(0, Qt::UserRole, ProjectDir);
    rootNode->setIcon(0, QIcon(":ui/images/pic/folder-solid.svg"));
    my_watcher->addPath(rootNode->data(0,Qt::UserRole).toString());
    _addSubDirs(rootNode, ProjectDir);
}

void My_Qtreewidget::_updata_someone_QTreeWidgetItem(QTreeWidgetItem *parentNode, const QString& path)
{
    nodeCount = rootNode->childCount();
    while (parentNode->childCount() > 0) {
        QTreeWidgetItem *child = parentNode->takeChild(0);
        delete child;
    }
    if (path!= nullptr){
        _addSubDirs(parentNode, path);}

}

void My_Qtreewidget::_dir_connect()
{
    QObject::connect(this, &QTreeWidget::itemClicked, this, &My_Qtreewidget::on_itemClicked);
    QObject::connect(this, &QTreeWidget::itemExpanded, this, &My_Qtreewidget::on_itemExpanded);
    QObject::connect(this, &QTreeWidget::itemCollapsed, this, &My_Qtreewidget::on_itemCollapsed);
    QObject::connect(my_watcher, &QFileSystemWatcher::directoryChanged, this, &My_Qtreewidget::on_directoryChanged);
    QObject::connect(this, &QTreeWidget::itemDoubleClicked, this, &My_Qtreewidget::on_itemDoubleClicked);
}

bool My_Qtreewidget::_is_type(const QString& name, const QStringList& strlist){
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


void My_Qtreewidget::keyPressEvent(QKeyEvent *event)
{// 键盘切换上一张下一张图片
    if (event->key() == Qt::Key_Left) {
        _updata_treewidgetItem(false); //计算上一个节点,并更新
        if ((my_photo!= nullptr)&&(active_item!= nullptr)){
            my_photo->graphics_load_image(active_item->data(0,Qt::UserRole).toString(),imageTypes);}
        else{qDebug()<<"my_photo is nullpter";}

    }
    else if (event->key() == Qt::Key_Right){
        _updata_treewidgetItem(true);
        if ((my_photo!= nullptr)&&(active_item!= nullptr)){
            my_photo->graphics_load_image(active_item->data(0,Qt::UserRole).toString(),imageTypes);}
        else{qDebug()<<"my_photo is nullpter";}
    }
}

void My_Qtreewidget::_updata_treewidgetItem(bool is_next){
    /*计算下一兄弟节点或者上一兄弟节点,is_next=true就是计算下一兄弟节点，否则计算上一个兄弟节点*/

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

QString My_Qtreewidget::_rag(const QString& name){
    //利用正则表达式，获取类型
    QRegularExpression pattern("\\.([A-Za-z0-9]+)$"); //qt的正则表达式获取 链接"."后面的类型
    QRegularExpressionMatch match = pattern.match(name);
    if (match.hasMatch()) {
        QString fileExtension = match.captured(1);
        return "."+ fileExtension;
    }
    else{
        return ".";}
}

void My_Qtreewidget::_addSubDirs(QTreeWidgetItem *parentNode, const QString& path) {
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

void My_Qtreewidget::contextMenuEvent(QContextMenuEvent *event){
    QTreeWidget::contextMenuEvent(event);

    QTreeWidgetItem* item = currentItem();
    if (!item)
        return;

    QMenu menu(this);
    QAction* openAction = menu.addAction("打开");
    QAction* copyAction = menu.addAction("复制路径");
    QAction* renameAction = menu.addAction("重命名");
    QAction* removeAction = menu.addAction("永久删除");

    QAction* selectedItem = menu.exec(event->globalPos());
    if (!selectedItem)
        return;

    if (selectedItem == removeAction) {
        QTreeWidgetItem *parent = item->parent();
        if (!parent)
            return;

        parent->takeChild(parent->indexOfChild(item));

        QString removePath = item->data(0, Qt::UserRole).toString();
        QString fileType = item->text(1);
        if (fileType == "files"){
            QFile file(removePath);
            file.remove();
        }
        else{
            QDir dir(removePath);
            dir.removeRecursively();
        }
        // 删除完成后自动更新节点
    }
    else if (selectedItem == openAction) {
        QString path = item->data(0, Qt::UserRole).toString();
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
    else if (selectedItem == renameAction){
        QLineEdit *lineEdit = new QLineEdit(this);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        this->setItemWidget(item, 0, lineEdit);
        this->editItem(item, 0);
        connect(lineEdit, &QLineEdit::editingFinished, this, [=]() {
            QString newName = lineEdit->text();
            if (newName.isEmpty()){

                return;
            }

            QString oldPath = item->data(0, Qt::UserRole).toString();
            QString newPath = item->parent()->data(0,Qt::UserRole).toString()+"/"+ newName;

            QFile file(oldPath);
            QDir dir(oldPath);
            if (file.exists()){
                file.rename(newPath);
            }
            else{
                dir.rename(oldPath,newPath);
            }
            // 更改完成后自动更新节点
        });
    }
    else if (selectedItem == copyAction){
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(item->data(0, Qt::UserRole).toString());
    }
}


void My_Qtreewidget::on_itemClicked(QTreeWidgetItem *item)
{
    QString img_path = item->data(0,Qt::UserRole).toString();
    bool is_img = _is_type(img_path, this->imageTypes);
    if (is_img) {
        // imageTypes.join(",").toUtf8().constData() 用于解决用户手动改图片格式导致图片加载失败的情况
        if (my_photo != nullptr){
            active_item = item;
            my_photo->graphics_load_image(active_item->data(0,Qt::UserRole).toString(),imageTypes);
            }
        else{qDebug()<<"my_photo is nullpter";}

    }
}

void My_Qtreewidget::on_itemExpanded(QTreeWidgetItem *item)
{
    item->setIcon(0, QIcon(":ui/images//pic/folder-open-regular.svg"));
}

void My_Qtreewidget::on_itemCollapsed(QTreeWidgetItem *item)
{
    item->setIcon(0, QIcon(":ui/images//pic/folder-solid.svg"));
}

void My_Qtreewidget::on_directoryChanged(const QString &changedPath)
{
    std::function<QTreeWidgetItem*(QTreeWidgetItem*)> lambda_traverseTreeItems = [&](QTreeWidgetItem *item) -> QTreeWidgetItem* {
        if(item->data(0,Qt::UserRole).toString() == changedPath) {
            return item;
        }
        int childCount = item->childCount();
        for (int i = 0; i < childCount; i++) {
            QTreeWidgetItem *child = item->child(i);
            QTreeWidgetItem *result = lambda_traverseTreeItems(child);
            if(result != nullptr) {
                return result;
            }
        }
        return nullptr;
    };
    auto *child = lambda_traverseTreeItems(rootNode);
    if (child != nullptr) {
        _updata_someone_QTreeWidgetItem(child, child->data(0, Qt::UserRole).toString());
    }
}

void My_Qtreewidget::on_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if (item == rootNode) {
        QString folderPath = QFileDialog::getExistingDirectory(nullptr, QObject::tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (!folderPath.isEmpty()) {
            QDir folderDir(folderPath);
            QString absoluteFolderPath = folderDir.absolutePath();
            ProjectDir = absoluteFolderPath;
            _updata_all_Qtree_dir();
        }
    } else {
        QString dirPath = item->data(0, Qt::UserRole).toString();
        QUrl QUrl_path = QUrl::fromLocalFile(dirPath);
        QDesktopServices::openUrl(QUrl_path);
    }
}


