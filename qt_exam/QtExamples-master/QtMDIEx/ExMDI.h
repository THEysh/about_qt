/*
 * Copyright (C)  2019 ~ 2019 touwoyimuli.  All rights reserved.
 *
 * Author:  touwoyimuli <touwoyimuli@gmai.com>
 *
 * github:  https://github.com/touwoyimuli
 * blogs:   https://touwoyimuli.github.io/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://touwoyimuli.github.io/>.
 */
#ifndef EXMDI_H
#define EXMDI_H

#include <QWidget>
#include <QTextStream>
#include <QFileInfo>
#include <QFontDialog>
#include <QFile>
#include <QIODevice>
#include <QIcon>

namespace Ui {
class ExMDI;
}

class ExMDI : public QWidget
{
    Q_OBJECT

public:
    explicit ExMDI(QWidget *parent = nullptr);
    ~ExMDI();

    void loadFromFile(QString& fileName);  //打开文件
    QString currentFileName();             //返回当前文件名
    bool isFileOpended();                  //文件已经打开

    void setEditFont();
    void textCut();
    void textCopy();
    void textPaste();


private:
    Ui::ExMDI *ui;

    QString m_currentFile;  //当前文件
    bool    m_fileOpened;   //true 打开；false 未打开
};

#endif // EXMDI_H
;
