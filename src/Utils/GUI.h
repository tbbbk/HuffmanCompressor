//
// Created by TBK on 2022/11/29.
//

#ifndef QTTEST_GUI_H
#define QTTEST_GUI_H


#include <QDialog>
#include <QTextEdit>
#include <QLabel>

class GUI : public QDialog {
Q_OBJECT
public:
    GUI(QWidget *parent = 0);

private slots:
    void Compress();
    void Decompress();

private:
    QPushButton *compress;
    QPushButton *decompress;
    QLabel *Image;
};


#endif //QTTEST_GUI_H
