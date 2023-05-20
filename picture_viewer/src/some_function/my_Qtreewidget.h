#ifndef MY_QTREEWIDGET_H
#define MY_QTREEWIDGET_H
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QUrl>
#include <QDesktopServices>
#include <QFileSystemWatcher>
#include "My_Photo_Graphics.h"

class My_Qtreewidget : public QTreeWidget {
Q_OBJECT
signals:
public:
    explicit My_Qtreewidget(QWidget *name);
    ~My_Qtreewidget() override;
    void connect_photo(My_Photo_Graphics* name);
    QString ProjectDir;
    My_Photo_Graphics* my_photo;
    QTreeWidgetItem* active_item;
    QFileSystemWatcher* my_watcher;

private slots:
    void on_itemClicked(QTreeWidgetItem *item);
    void on_itemExpanded(QTreeWidgetItem *item);
    void on_itemCollapsed(QTreeWidgetItem *item);
    void on_directoryChanged(const QString &changedPath);
    void on_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:

    const int MAX_NODE_COUNT;
    int nodeCount;
    QTreeWidgetItem* rootNode;
    QStringList imageTypes;

    void _updata_all_Qtree_dir();
    void _updata_someone_QTreeWidgetItem(QTreeWidgetItem *parentNode, const QString& path);
    void _dir_connect();
    void _addSubDirs(QTreeWidgetItem *parentNode, const QString& path);
    void keyPressEvent(QKeyEvent *event) override;
    void _updata_treewidgetItem(bool is_next);
    void contextMenuEvent(QContextMenuEvent *event) override;
    QString _rag(const QString &qString);
    bool _is_type(const QString &name, const QStringList &strlist);
};

#endif // MY_QTREEWIDGET_H
