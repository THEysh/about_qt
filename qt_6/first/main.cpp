
#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Qt version:" << qVersion();
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "first_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();

    return a.exec();
}
