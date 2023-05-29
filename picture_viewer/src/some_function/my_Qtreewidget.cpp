//
// Created by top on 2023-05-10.
//

#include "QLineEdit"
#include <QGuiApplication>
#include <QQueue>
#include "QClipboard"
#include "My_Qtreewidget.h"
#include "qdebug.h"
#include "QMimeData"
#include <QtConcurrent/QtConcurrent>
My_Qtreewidget::My_Qtreewidget(QWidget *parent)
        : QTreeWidget(parent),
          MAX_NODE_COUNT(1000000),
          nodeCount(0),
          rootNode(new QTreeWidgetItem(this)),
          ProjectDir(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)),
          my_photo(nullptr),
          my_watcher (new QFileSystemWatcher()),
          active_item(nullptr),
          lineEdit(nullptr),
          imageTypes({"bmp","jpg","png","tif","ico","gif","svg"})

{

    this->setHeaderHidden(true);
    this->setDragEnabled(true);
    rootNode->setText(0, "双击此处打开目录");
    rootNode->setData(0, Qt::UserRole, ProjectDir);
    rootNode->setIcon(0, QIcon(":ui/images/pic/folder-solid.svg"));
    _dir_connect();
    _updata_all_Qtree_dir();

}

void My_Qtreewidget::connect_photo(My_Photo_Graphics *name) {
    // 运行之前必须要初始化类My_Photo_Graphics
    if (name!= nullptr){
        my_photo = name;
        name->in_tree = this;
    }
    else{
        qDebug()<<"connect_photo is nullpter";}
}

void My_Qtreewidget::_updata_all_Qtree_dir()
{
    nodeCount = 0;
    // 异步删除节点
    delete_roots(rootNode);
    rootNode->setText(0, "双击此处打开目录");
    rootNode->setText(1, "folders");
    rootNode->setData(0, Qt::UserRole, ProjectDir);
    rootNode->setIcon(0, QIcon(":ui/images/pic/folder-solid.svg"));
    my_watcher->addPath(rootNode->data(0,Qt::UserRole).toString());
    hash_item.insert(rootNode->data(0,Qt::UserRole).toString(),rootNode);
    // 这里表示这个节点可以展开
    rootNode->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

}

void My_Qtreewidget::_dir_connect()
{
    QObject::connect(this, &QTreeWidget::itemClicked, this, &My_Qtreewidget::on_itemClicked);
    // 动态显示节点，展开的时候加载
    // 收拢的时候删除，在一次展开时候重新加载
    QObject::connect(this, &QTreeWidget::itemExpanded, this, &My_Qtreewidget::on_itemExpanded);
    QObject::connect(this, &QTreeWidget::itemCollapsed, this, &My_Qtreewidget::on_itemCollapsed);
    QObject::connect(my_watcher, &QFileSystemWatcher::fileChanged, this, &My_Qtreewidget::on_fileChanged);
    QObject::connect(this, &QTreeWidget::itemDoubleClicked, this, &My_Qtreewidget::on_itemDoubleClicked);
}

void My_Qtreewidget::_add_a_layerDirs(QTreeWidgetItem *parentNode) {

    // 把文件夹的更新包装为匿名函数 用于异步更新文件节点
    auto add_layerDirs = [this,parentNode](){
        if (parentNode== nullptr){
            return;
        }
        QDir temp_directory(parentNode->data(0, Qt::UserRole).toString());
        QFileInfoList fileList = temp_directory.entryInfoList(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
        int size = fileList.count();
        for (int i = 0; i < size; i++) {
            if (nodeCount++>MAX_NODE_COUNT){ break;}
            QFileInfo fileInfo = fileList.at(i);
            QString fileName = fileInfo.fileName();
            QString fileType = fileInfo.isFile() ? "files" : "folders";
            bool is_img = _is_type(fileName,imageTypes);
            if (fileType=="files" && is_img){
                //下面 设置节点的信息
                nodeCount ++;
                auto *node = new QTreeWidgetItem(parentNode);
                node->setText(0, fileName);
                node->setText(1, fileType);
                node->setText(2, parentNode->data(0,Qt::UserRole).toString()); //保存父类的路径
                // 获取文件目录
                node->setData(0, Qt::UserRole, fileInfo.filePath());
                QString item_type = fileInfo.suffix();
                // 添加文件监控
                my_watcher->addPath(fileInfo.filePath());
                // 添加hash
                hash_item.insert(fileInfo.filePath(),node);
                // 设置图标
                for(auto t: imageTypes){
                    if (item_type==t){
                        QString qicon = ":ui/images/pic/"+ t +".svg";
                        node->setIcon(0, QIcon(qicon));
                        break;
                    }
                }
            }
            else if (fileType=="folders"){
                // 如果是文件夹就创建一个空节点表示其可以展开
                nodeCount ++;
                auto *node = new QTreeWidgetItem(parentNode);
                // 表示可以展开
                node->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
                node->setText(0, fileName);
                node->setText(1, fileType);
                node->setText(2, parentNode->data(0,Qt::UserRole).toString()); //保存父类的路径
                // 获取文件目录
                node->setData(0, Qt::UserRole, fileInfo.filePath());
                node->setIcon(0, QIcon(":ui/images//pic/folder-solid.svg"));
                // 添加文件监控
                my_watcher->addPath(fileInfo.filePath()); //添加监控，文件夹路径下的变化监控
                // 添加hash
                hash_item.insert(fileInfo.filePath(),node);
            }
        }
    };

    ar_future= QtConcurrent::run(add_layerDirs);

}

void My_Qtreewidget::delete_roots(QTreeWidgetItem *item) {
    // 默认初始值为true 表示，如果线程在运行。那么我将等待,随后运行这段代码
    // 定义一个删除节点的匿名函数
    auto deleteChildren = [this](QTreeWidgetItem *item) {
        if (item == nullptr){return ;}
        while (item->childCount() > 0) {
            QTreeWidgetItem *child = item->takeChild(0);
            if (child!= nullptr){
                my_watcher->removePath(child->data(0,Qt::UserRole).toString());
                hash_item.remove(child->data(0,Qt::UserRole).toString());
                nodeCount--;
            }
            delete child;
        }
    };

    ar_future = QtConcurrent::run(deleteChildren, item);


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
    if ((my_photo == nullptr)||(active_item == nullptr)){
        qDebug()<<"My_Qtreewidget::keyPressEvent:bug";
        return;
    }
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Up) {
        _updata_treewidgetItem(false); //计算上一个节点,并更新
        my_photo->graphics_load_image(active_item->data(0,Qt::UserRole).toString(),imageTypes);
    }
    else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_Down){
        _updata_treewidgetItem(true);
        my_photo->graphics_load_image(active_item->data(0,Qt::UserRole).toString(),imageTypes);
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

        lineEdit = new QLineEdit(item->text(0),this);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        this->setItemWidget(item, 0, lineEdit);
        this->editItem(item, 0);

        connect(lineEdit, &QLineEdit::editingFinished, this, [this,item]() {
            qDebug()<<"rename";
            QString newName = lineEdit->text();
            qDebug()<<"newName"<<item->text(0);
            if (newName.isEmpty()){
                qDebug()<<item->text(0);
                qDebug()<<"newName"<<item->text(0);
                newName = item->text(0);
                lineEdit->setText(newName);
                lineEdit = nullptr;
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
            // 如果是重命名的是文件夹的话 需要手动更新节点,删除节点并更新
            _add_a_layerDirs(item->parent());
        });
    }
    else if (selectedItem == copyAction){
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(item->data(0, Qt::UserRole).toString());
    }
}

void My_Qtreewidget::on_itemClicked(QTreeWidgetItem *item)
{
    if (active_item==item || my_photo == nullptr){
        qDebug()<<"My_Qtreewidget::on_itemClicked:bug";
        return;
    }
    QString img_path = item->data(0,Qt::UserRole).toString();
    bool is_img = _is_type(img_path, this->imageTypes);
    if (is_img) {
        active_item = item;
        my_photo->graphics_load_image(active_item->data(0, Qt::UserRole).toString(), imageTypes);
    }
}

void My_Qtreewidget::on_itemExpanded(QTreeWidgetItem *item)
{
    item->setIcon(0, QIcon(":ui/images//pic/folder-solid.svg"));
    if(item->text(1)=="folders"&& !ar_future.isRunning()){
        _add_a_layerDirs(item);
        item->setIcon(0, QIcon(":ui/images//pic/folder-open-regular.svg"));
    }
}

void My_Qtreewidget::on_itemCollapsed(QTreeWidgetItem *item)
{
    item->setIcon(0, QIcon(":ui/images//pic/folder-solid.svg"));
    // 删除所有节点，每次展开的时候更新
    if(item->text(1)=="folders"&&!ar_future.isRunning()){
        // 遍历删除所有子节点,异步线程
        delete_roots(item);
    }
}

void My_Qtreewidget::on_fileChanged(const QString &filedPath) {
    // 监控是否有文件删除，重命名
    // 这里是文件监控，当监控文件被改变，遍历这个当前文件目录。
    // 根据哈希表增减键值，修改文件目录节点和哈希表
    qDebug()<<"on_fileChanged"<<filedPath;
    // 获取旧节点的指针
    QTreeWidgetItem* hash_temp_root = hash_item.value(filedPath);
    // 获取父亲节点
    if (hash_temp_root->parent()== nullptr) {
        qDebug()<<"on_fileChanged hash_temp_root->parent() IS NULL ";
        return;
    } else{
        // 遍历一层
        // 获取父类文件夹
        QDir temp_directory(hash_temp_root->parent()->data(0, Qt::UserRole).toString());
        QFileInfoList fileList = temp_directory.entryInfoList(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
        int size = fileList.count();
        bool is_oldroot = false; //查看旧节点是否存在，不存在就删除
        for (int i = 0; i < size; i++) {
            QFileInfo fileInfo = fileList.at(i);
            QString fileName = fileInfo.fileName();
            QString fileType = fileInfo.isFile() ? "files" : "folders";
            bool is_img = _is_type(fileName,imageTypes);
            if (fileType=="files" && is_img){
                // 查看哈希表 path 有没有变化。
                QTreeWidgetItem *temp_child = hash_item.value(fileInfo.filePath());
                if(temp_child==hash_temp_root){
                    is_oldroot = true;
                }
                if(temp_child== nullptr){
                    // 添加这个节点
                    nodeCount ++;
                    auto *node = new QTreeWidgetItem(hash_temp_root->parent()); // 这里填父类节点
                    node->setText(0, fileName);
                    node->setText(1, fileType);
                    node->setText(2, hash_temp_root->parent()->data(0,Qt::UserRole).toString()); //保存父类的路径
                    // 获取文件目录
                    node->setData(0, Qt::UserRole, fileInfo.filePath());
                    QString item_type = fileInfo.suffix();
                    // 添加文件监控
                    my_watcher->addPath(fileInfo.filePath());
                    // 添加hash
                    hash_item.insert(fileInfo.filePath(),node);
                    // 设置图标
                    for(auto t: imageTypes){
                        if (item_type==t){
                            QString qicon = ":ui/images/pic/"+ t +".svg";
                            node->setIcon(0, QIcon(qicon));
                            break;
                        }
                    }

                }
            }
        }
        // 删除被修改的键值,节点,删除旧文件监控
        if (!is_oldroot){
            // 只删除一个节点
            hash_item.remove(filedPath);
            my_watcher->removePath(filedPath);
            delete hash_temp_root;
        }

    }

}

void My_Qtreewidget::on_itemDoubleClicked(QTreeWidgetItem *item)
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
        // 是文件夹双击打开
        if (item->text(1)=="folders"){
            QString dirPath = item->data(0, Qt::UserRole).toString();
            QUrl QUrl_path = QUrl::fromLocalFile(dirPath);
            QDesktopServices::openUrl(QUrl_path);
        }

    }
}

My_Qtreewidget::~My_Qtreewidget(){
    // 遍历删除所有子节点
    delete_roots(rootNode);
    delete my_photo;
    delete active_item;
    delete my_watcher;
}

QMimeData* My_Qtreewidget::mimeData(const QList<QTreeWidgetItem *> items) const{
    // 拖动节点会自动调这个函数
    QMimeData *mimeData = new QMimeData;
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    for (auto item : items) {
        auto filetype = item->text(1);
        auto filename = item->text(0);
        auto path = item->data(0,Qt::UserRole);
        stream << filetype<<filename<<path.toString();
    }
    mimeData->setData("application/x-qtreewidget-values", encodedData);
    return mimeData;
}

//void My_Qtreewidget::_addSubDirs(QTreeWidgetItem *parentNode, const QString& path) {
//    qDebug()<<"RUN:_addSubDirs";
//    //BFS 添加全部节点
//    QDir directory(path);
//    // QTreeWidgetItem *temp_parentNode = parentNode; //创建一个 QTreeWidgetItem指针，用于传值
//    QQueue<QTreeWidgetItem*> file_queue;
//    file_queue.enqueue(parentNode);
//    while (!file_queue.isEmpty()) {
//        if (nodeCount++>MAX_NODE_COUNT){return;}
//        // 取出队列中的第一个节点,构建树节点，同时也用作下一个节点的父类
//        QTreeWidgetItem *temp_parentNode = file_queue.front();
//        QDir temp_directory(temp_parentNode->data(0, Qt::UserRole).toString());
//        //具体地说，这个代码使用entryInfoList函数获取了directory目录下的所有文件和目录的信息，包括隐藏文件和当前目录以及父级目录（"."和".."），并将它们的QFileInfo对象添加到QFileInfoList列表中。
//        //参数QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot是用来设置entryInfoList函数的选项，其中：
//        //QDir::Files指示返回文件的信息
//        //QDir::AllDirs指示返回子目录的信息
//        //QDir::NoDotAndDotDot指示过滤掉"."和".."目录
//        QFileInfoList fileList = temp_directory.entryInfoList(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
//        int size = fileList.count();
//        // 队列中删除这个节点
//        file_queue.dequeue();
//        // 遍历与当前节点相连的所有节点
//        for (int i = 0; i < size; i++) {
//            QFileInfo fileInfo = fileList.at(i);
//            QString fileName = fileInfo.fileName();
//            QString fileType = fileInfo.isFile() ? "files" : "folders";
//            bool is_img = _is_type(fileName,imageTypes);
//            if (fileType=="files" && is_img){
//                //下面 设置节点的信息
//                nodeCount ++;
//                auto *node = new QTreeWidgetItem(temp_parentNode);
//                node->setText(0, fileName);
//                node->setText(1, fileType);
//                node->setText(2, temp_parentNode->data(0,Qt::UserRole).toString()); //保存父类的路径
//                // 获取文件目录
//                node->setData(0, Qt::UserRole, fileInfo.filePath());
//                QString item_type = fileInfo.suffix();
//                // 添加文件监控
//                my_watcher->addPath(fileInfo.filePath());
//                // 添加hash
//                hash_item.insert(fileInfo.filePath(),node);
//                // 设置图标
//                for(auto t: imageTypes){
//                    if (item_type==t){
//                        QString qicon = ":ui/images/pic/"+ t +".svg";
//                        node->setIcon(0, QIcon(qicon));
//                        break;
//                    }
//                }
//            }
//            else if (fileType=="folders"){
//                nodeCount ++;
//                auto *node = new QTreeWidgetItem(temp_parentNode);
//                node->setText(0, fileName);
//                node->setText(1, fileType);
//                node->setText(2, temp_parentNode->data(0,Qt::UserRole).toString()); //保存父类的路径
//                // 获取文件目录
//                node->setData(0, Qt::UserRole, fileInfo.filePath());
//                node->setIcon(0, QIcon(":ui/images//pic/folder-solid.svg"));
//                // 添加文件监控
//                my_watcher->addPath(fileInfo.filePath()); //添加监控，文件夹路径下的变化监控
//                // 添加hash
//                hash_item.insert(fileInfo.filePath(),node);
//                // 是目录，将其加入队列中
//                file_queue.enqueue(node);
//            }
//        }
//    }
//}
//




