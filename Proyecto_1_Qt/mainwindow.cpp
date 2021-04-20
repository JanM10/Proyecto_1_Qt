#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localserver.h"
#include <QMessageBox>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <list>


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
    string textoCortado = "";

//    for(int i=0; i<lines.size()-1; i++){
////        textoCortado = lines[i].remove(QString(" "), Qt::CaseInsensitive).toStdString();
////        cout<< textoCortado << endl;
//        textoCortado = lines[1].toStdString();
//        const regex patron("[a-z]");
//        cout<<"REDEX: " <<regex << endl;
//    }

    for(int i=0; i<lines.size()-1; i++){
        texto += lines[i] + "\n";
        if(lines[i].contains("int")){
            textoCortado = lines[i].remove(QString("int "), Qt::CaseInsensitive).toStdString();
            cout<< textoCortado << endl;
            textoCortado = lines[i].remove(QString("="), Qt::CaseInsensitive).toStdString();
            cout<< textoCortado << endl;
            textoCortado = lines[i].remove(QString(";"), Qt::CaseInsensitive).toStdString();
            cout<< textoCortado << endl;
            textoCortado = textoCortado.substr(0,lines[i].toStdString().find("  "));
            cout<< "SUB:"<<textoCortado << endl;
            textoCortado = lines[i].toStdString().substr(lines[i].toStdString().find(" ") + 2);
            cout<< "SUB2:"<<textoCortado << endl;
//            x.substr(x.find(":") + 1);
        }
    }
    ui->console->setText(texto);
    lines.clear();
}

//    ui->console->setText(lines.count());
//    QStringList lines = ui->writeCode->toPlainText().split("\n");
