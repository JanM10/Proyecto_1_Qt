#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localserver.h"
#include <QMessageBox>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

QStringList lines;
int numero = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mLocalServer = new LocalServer(this);

    if(!mLocalServer->listen("MiServidorLocal")){
        QMessageBox::critical(this, "Error", mLocalServer->errorString());
    }
    else{
        QMessageBox::information(this, "Servidor","Iniciando...");
    }
}


void MainWindow::on_clearButton_clicked()
{
    ui->aplicationLogConsole->clear();
}

void MainWindow::on_iniciarServidor_clicked()
{
    mLocalServer->listen("MiServidorLocal");
}

void MainWindow::on_runButton_clicked()
{
    mLocalServer->envia(ui->writeCode->toPlainText());
    ui->console->clear();
    //close();
}

void MainWindow::on_writeCode_textChanged()
{
//    ui->console->setText(ui->writeCode->toPlainText());
//    std::cout << "Text: " << ui->writeCode->toPlainText().toStdString() << std::endl;

    if(ui->writeCode->toPlainText().contains("\n")){
        lines = ui->writeCode->toPlainText().split("\n");
    }
    int j = 0;
    QString lineas = "";
    while(j<ui->writeCode->toPlainText().count("\n")+1){
        j++;
        lineas += QString::number(j) + "\n";
        ui->numeroLinea->setText(lineas);
    }

    QString texto = "";
    int cantidadInt = 0;
    int cantidadLong = 0;
    int cantidadChar = 0;
    int cantidadFloat = 0;
    int cantidadDouble = 0;
    int cantidadStruct = 0;

    for(int i=0; i<lines.size()-1; i++){
        texto += lines[i] + "\n";
        if(lines[i].contains("int")){
            cantidadInt++;
            cout<<"CONTIENE "<<cantidadInt<<" de Ints"<<endl;
        }else if(lines[i].contains("long")){
            cantidadLong++;
            cout<<"CONTIENE "<<cantidadLong<<" de Longs"<<endl;
        }else if(lines[i].contains("char")){
            cantidadChar++;
            cout<<"CONTIENE "<<cantidadChar<<" de Chars"<<endl;
        }else if(lines[i].contains("float")){
            cantidadFloat++;
            cout<<"CONTIENE "<<cantidadFloat<<" de Floats"<<endl;
        }else if(lines[i].contains("double")){
            cantidadDouble++;
            cout<<"CONTIENE "<<cantidadDouble<<" de Doubles"<<endl;
        }else if(lines[i].contains("struct")){
            cantidadStruct++;
            cout<<"CONTIENE "<<cantidadStruct<<" de Structs"<<endl;
        }
        else{
            cout<<"NO CONTIENE INT"<<endl;
        }
    }
    ui->console->setText(texto);
    lines.clear();
}

//    ui->console->setText(lines.count());
//    QStringList lines = ui->writeCode->toPlainText().split("\n");
