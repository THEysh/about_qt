#include "ExQTreeWidget.h"
#include <QApplication>
#include <QHBoxLayout>
#include "iostream"
#include <QResource>
#include <QDir>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QFontDatabase>
#include "QMovie"
#include "QTimer"
#include <QUrl>
#include <QApplication>

QString* Resource_Registration(){


    QString path_rcc = QString("F:\\code\\c_code\\about_qt\\qt_exam\\QtExamples-master\\QtQTreeWidgetEx\\resources.rcc"); //获取项目的.rcc路径
    QFile file(path_rcc);
    std::cout << "Project directory of .rcc: " <<  path_rcc.toStdString() << std::endl; //
    if (QResource::registerResource(path_rcc)) { //获取项目的资源文件
        qDebug() << "Resource file registered successfully!";
    } else {
        qWarning() << "Failed to register resource file";
    }
    return &path_rcc;
}

int main(int argc, char *argv[])
{
    QString *ABProjectDir = Resource_Registration(); // 注册资源文件（包括图片的rcc文件，这是由qrc转换出来的）,返回路径
    QApplication a(argc, argv);
    ExQTreeWidget w;
    w.show();
// 创建一个 QTreeWidget
    QTreeWidget *tree = new QTreeWidget();

// 设置列标题
    tree->setHeaderLabels(QStringList() << "名称" << "类型");

// 创建根节点
    QTreeWidgetItem *rootNode = new QTreeWidgetItem(tree);
    rootNode->setText(0, "根目录");
    rootNode->setIcon(0, QIcon(":image/Image004.jpg"));

// 创建子节点表示文件夹
    QTreeWidgetItem *folderNode = new QTreeWidgetItem(rootNode);
    folderNode->setText(0, "文件夹");
    folderNode->setText(1, "xxx另一个说明"); //并行显示

    // 创建子节点表示文件夹
    QTreeWidgetItem *folderNode2 = new QTreeWidgetItem(rootNode);
    folderNode2->setText(0, "文件夹2");
    folderNode2->setText(1, "xxx2另一个说明"); //并行显示

// 创建文件节点
    QTreeWidgetItem *fileNode = new QTreeWidgetItem(folderNode);
    fileNode->setText(0, "Item with icon");


// 添加子节点到根节点
    rootNode->addChild(folderNode);
    rootNode->addChild(folderNode2);
    QTreeWidget* treeWidget = new QTreeWidget();


// 将此项添加到树中
    treeWidget->addTopLevelItem(fileNode);
// 将 QTreeWidget 显示出来
    tree->show();

    return a.exec();
}


