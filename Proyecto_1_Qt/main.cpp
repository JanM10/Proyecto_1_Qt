#include "mainwindow.h"

#include <QApplication>

///main clase principal del codigo
/// En esta clase se inicia todo el codigo, aqui se inicia la ventana del IDE
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    MainWindow w;
    w.show();
    return a.exec();
}
