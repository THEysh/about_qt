#include <QtCore/QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QString url = "http://www.baidu.com";

    auto *manager = new QNetworkAccessManager(&app);
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QNetworkReply *reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished, &app, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray bytes = reply->readAll();
            // 处理获取到的数据
            qDebug() << bytes;
        } else {
            // 处理错误信息
            qDebug() << reply->errorString();
        }
        app.quit(); // 退出事件循环
    });

    return app.exec(); // 进入事件循环
}
