//
// Created by top on 2023-06-18.
//

#ifndef QML_FITST_PROJIECT_QML_RELOADER_H
#define QML_FITST_PROJIECT_QML_RELOADER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QFileSystemWatcher>
#include <QQuickWindow>
#include <QGuiApplication>
#include <QQmlComponent>
#include <QFile>
#include "QTimer"

class QMLReloader : public QObject
{
Q_OBJECT
public:
    QMLReloader(QQmlApplicationEngine &engine, const QString &qmlPath, QObject *parent = nullptr)
            : QObject(parent),
            m_engine(engine),
            m_qmlPath(qmlPath),
            timer(new QTimer()),
            count(0)
    {
        connect(timer, &QTimer::timeout, this, &QMLReloader::onTime_interval);
        // 设置计时间隔为1秒
        timer->setInterval(500);
        timer->start();
        reloadQML();
    }

private slots:
    void onFileChanged()
    {
        qDebug() << "changed,count:" << count++;
        m_engine.clearComponentCache();
        reloadQML();
    }
    void onTime_interval(){
        // 检测qmlPath的内容是否发生变化
        QFile file(m_qmlPath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString new_content;
            while (!in.atEnd()) {
                QString line = in.readLine();
                new_content = new_content + line;
            }
            if (content!=new_content){
                qDebug()<<content;
                qDebug()<<new_content;
                content = new_content;
                onFileChanged();
            }

        } else {
            qDebug() << "Failed to open file for reading:" << file.errorString();
        }

}

private:
    void reloadQML()
    {
        // 删除之前的指针
        if (!m_engine.rootObjects().isEmpty()) {
            auto rootWin = m_engine.rootObjects().first();
            delete rootWin;
        }
        m_engine.load(QUrl::fromLocalFile(m_qmlPath));
        if (m_engine.rootObjects().isEmpty()) {
            qWarning() << "Unable to load QML file!";
            return;
        }

    }

    QQmlApplicationEngine &m_engine;
    const QString m_qmlPath;
    QString content = "";
    int count = 0;
    QTimer* timer;
};

#endif //QML_FITST_PROJIECT_QML_RELOADER_H
