#include <iostream>
#include <windows.h>
#include <shlobj.h>
#include <QTreeWidgetItem>
#include "qdebug.h"
int CopyFileToClipboard(char szFileName[]);

int main()
{
    QTreeWidgetItem *active_item = nullptr; // 当前图片激活的节点
    QTreeWidgetItem **pa = &active_item; // 新建指针pa，初始时指向active_item所指向的地址

// 假设现在有一个新的item需要被激活，将active_item指向该item
    QTreeWidgetItem *new_item = new QTreeWidgetItem();
    active_item = new_item;

// 检查pa是否仍然指向active_item所指向的地址
    if (*pa == active_item) {
        qDebug() << "pa still points to the same address as active_item"<<*pa<<","<<active_item;
    } else {
        qDebug() << "pa does not point to the same address as active_item"<<*pa<<","<<active_item;
    }
    return 0;
}
