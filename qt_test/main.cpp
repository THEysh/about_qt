#include <QApplication>
#include <QMimeData>
#include <QClipboard>
#include <QDebug>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建一个待复制的文件路径
    QString filePath = "C:\\Users\\Administrator\\Desktop\\myimage\\images\\ad\\wallhaven-3z32j3.jpg";

    // 创建一个 QUrl 对象
    QUrl url = QUrl::fromLocalFile(filePath);
    if (!url.isValid()) {
        qDebug() << "The URL is not valid.";
        return 0;
    }

    // 将 QUrl 对象添加到 QList<QUrl> 中
    QList<QUrl> copyFiles;
    copyFiles.push_back(url);

    // 创建一个 QMimeData 对象，并将 QList<QUrl> 对象设置为它的数据
    QMimeData *mimeData = new QMimeData;
    mimeData->setUrls(copyFiles);

    // 将 QMimeData 对象设置到剪贴板中
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setMimeData(mimeData);

    // 输出成功提示信息
    qDebug() << "The file has been copied to the clipboard.";

    return a.exec();
}
