//
// Created by TBK on 2022/11/29.
//

#include "GUI.h"
#include "FileOperation.h"
#include "DataProcess.cpp"
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QInputDialog>

using namespace std;

GUI::GUI(QWidget *parent) : QDialog(parent) {
    this->setFixedSize(300, 300);
    compress = new QPushButton("压缩");
    decompress = new QPushButton("解压");
    Image = new QLabel("<h2><font color='red'>童柄魁</font>制作<h2>", this);
    Image->alignment();
    connect(compress, SIGNAL(clicked()), this, SLOT(Compress()));
    connect(decompress, SIGNAL(clicked()), this, SLOT(Decompress()));
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(compress);
    buttonLayout->addWidget(decompress);
    QHBoxLayout *imageLayout = new QHBoxLayout;
    imageLayout->addWidget(Image);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(imageLayout);
    mainLayout->addLayout(buttonLayout);
    this->setLayout(mainLayout);
}

void GUI::Compress() {
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("选择需要压缩的文件"));
    fileDialog->setDirectory(".");
    if (fileDialog->exec() == QDialog::Accepted) {
        QString path = fileDialog->selectedFiles()[0];
        QString tmp = path;
        string Path = path.toStdString();
        int index_1 = path.lastIndexOf(".");
        path.chop(path.length() - index_1);
        string resultPath = path.toStdString() + ".dat";
        int index_2 = path.lastIndexOf("/");
        string name = path.mid(index_2 + 1).toStdString();
        cout << Path << endl << resultPath << endl << name << endl;
        // 权重
        string weightName = tmp.mid(index_1 + 1).toStdString();

        FileOperation fileOp;
        fileOp.setPath(Path);
        fileOp.BinaryRead();
        auto q = CountData(fileOp.getBuffer(), fileOp.Length());
        PNI res = CreateHuffmanTree(q);
        map<char, pair<char *, int>> result = HuffmanCode(res);
        try {
            system("md d:\\Huffman_Compressor");
        } catch (exception e) {
            cout << e.what();
        }
        storeTree(result, "D:/Huffman_Compressor/" + name + "." + weightName);
        pair<char *, int> finalResult = Encode(fileOp.getBuffer(), fileOp.Length(), result);
        fileOp.setPath(resultPath);
        fileOp.setBuffer(finalResult.first, finalResult.second);
        fileOp.BinaryWrite();
        QMessageBox::information(NULL, tr("恭喜"), tr("压缩成功！"));
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("请选择文件"));
    }
}

void GUI::Decompress() {
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("选择需要解压的文件"));
    fileDialog->setDirectory(".");

    if (fileDialog->exec() == QDialog::Accepted) {
        QString path = fileDialog->selectedFiles()[0];
        QString temp = path;
        string Path = path.toStdString();
        int index_1 = path.lastIndexOf(".");
        // 获得压缩后文件
        path.chop(path.length() - index_1);
        int index_2 = path.lastIndexOf("/");
        temp = temp.mid(0, index_2 + 1);
        string name = path.mid(index_2 + 1).toStdString();
        // 开始解压
        bool bRet = false;
        QString text = QInputDialog::getText(this, tr("文件后缀"),
                                             tr("输入解压后文件后缀"), QLineEdit::Normal,
                                             "", &bRet);
        string w = text.toStdString();
        string resultPath = temp.toStdString() + name + "_new." + w;
        cout << resultPath << endl;
        cout << name + "." << w << endl;

        FileOperation fileOp;
        fileOp.setPath(Path);
        fileOp.BinaryRead();
        map<char, pair<char *, int>> weight = attainTree("D:/Huffman_Compressor/" + name + "." + w);
        string OriginData = Decode(fileOp.getBuffer(), fileOp.Length(), CodeTurnover(weight));
        fileOp.setPath(resultPath);
        fileOp.setBuffer(const_cast<char *>(OriginData.c_str()), OriginData.length());
        fileOp.BinaryWrite();
        QMessageBox::information(NULL, tr("恭喜"), tr("解压成功！") + path);
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("请选择文件"));
    }
}