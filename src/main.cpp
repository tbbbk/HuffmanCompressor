//This program uses to write and read functions.
#include <queue>
#include "Utils/DataProcess.cpp"
#include "Utils/GUI.h"
#include <QApplication>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GUI *tbk = new GUI;
    tbk->show();
    return app.exec();
}