//
// Created by top on 2023-05-17.
//

#include <QFileInfo>
#include "my_photo_Graphics.h"
#include "Item_Interface.h"
#include "qDebug.h"

Item_Interface::Item_Interface(My_Photo_Graphics *parent) {
    interface_scene = parent->scene;
}

void Item_Interface::click_element() {

}

void Item_Interface::show_photo(void (*my_fun_Pointer)()) {
    if (interface_scene!= nullptr){interface_scene->clear();}
}

void Item_Interface::interface_load_image(const QString &path, const QStringList &imageTypes) {
    // 进行判断，是加入什么类型的图片
    QFileInfo fileInfo(path);
    qDebug() << imageTypes;
    if (fileInfo.suffix().compare("svg", Qt::CaseInsensitive) == 0) {
        qDebug() << "The file is an SVG format file.";
        QSvgRenderer svgRenderer(fileInfo.path());
    }
    else if(path.contains(imageTypes.join(","))){// 查看是不是能读取的类型
        QPixmap(path,imageTypes.join(",").toUtf8().constData());
    } else{

    }

}

//====================================================================================================






