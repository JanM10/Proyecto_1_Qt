#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localserver.h"
#include <QMessageBox>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>


using namespace std;
using namespace regex_constants;

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
//        QMessageBox::information(this, "Servidor","Iniciando...");
        cout << "Servidor Iniciado" << endl;
    }
}


void MainWindow::on_clearButton_clicked()
{
    ui->aplicationLogConsole->clear();
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

    separarTexto();

    ui->console->setText(texto);
    lines.clear();
}

void MainWindow::separarTexto( ){
    string textoCortado = "";
    smatch results;
    regex soloLetras("[a-zA-Z]+");
    regex numerosLetras("\\w+");
    regex numerosFloat("\\d+?[+-]?([0-9]*[.])?[0-9]+");
    sregex_iterator lastmatch;

    //lines[i].contains("struct")
    //lines[i].contains("reference<tipo>")

    for(int i=0; i<lines.size()-1; i++){
        textoCortado = lines[i].toStdString();

        if(lines[i].contains("int") || lines[i].contains("long") || lines[i].contains("float") || lines[i].contains("double")){
            sregex_iterator currentMatch(textoCortado.begin(),textoCortado.end(),soloLetras);
            while (currentMatch != lastmatch) {
                smatch match = *currentMatch;
                cout << "MATCHES: "<<match.str() << endl;
                currentMatch++;
            }
            sregex_iterator currentSecondMatch(textoCortado.begin(),textoCortado.end(),numerosFloat);
            while (currentSecondMatch != lastmatch) {
                smatch match = *currentSecondMatch;
                cout << "MATCHES: "<<match.str() << endl;
                currentSecondMatch++;
            }
        }
//        else if (lines[i].contains("float") || lines[i].contains("double")) {
//            sregex_iterator currentMatch(textoCortado.begin(),textoCortado.end(),soloLetras);
//            while (currentMatch != lastmatch) {
//                smatch match = *currentMatch;
//                cout << "MATCHES: "<<match.str() << endl;
//                currentMatch++;
//            }
//            sregex_iterator currentSecondMatch(textoCortado.begin(),textoCortado.end(),numerosFloat);
//            while (currentSecondMatch != lastmatch) {
//                smatch match = *currentSecondMatch;
//                cout << "MATCHES: "<<match.str() << endl;
//                currentSecondMatch++;
//            }
//        }
    else if (lines[i].contains("char")) {
            textoCortado = lines[i].remove(QString("char "), Qt::CaseInsensitive).toStdString();
            cout<< textoCortado << endl;
            textoCortado = lines[i].remove(QString("="), Qt::CaseInsensitive).toStdString();
            cout<< textoCortado << endl;
            textoCortado = lines[i].remove(QString(";"), Qt::CaseInsensitive).toStdString();
            cout<< textoCortado << endl;
            textoCortado = lines[i].remove(QString('"'), Qt::CaseInsensitive).toStdString();
            cout<< textoCortado << endl;
            textoCortado = textoCortado.substr(0,lines[i].toStdString().find("  "));
            cout<< "SUB:"<<textoCortado << endl;
            textoCortado = lines[i].toStdString().substr(lines[i].toStdString().find(" ") + 2);
            cout<< "SUB2:"<<textoCortado << endl;
        }
        cout<<"TextoCortado: " << textoCortado << endl;
    }
}

//void shallowCopy(){
//    int value = 5;
//    int *pointer = &value;
//    int *pointer2 = &value;

//    cout << "pointer:" << pointer << " -- pointer2:" << pointer2 << '\n';
//    cout << "pointer:" << *pointer << " -- pointer2:" << *pointer2 << '\n';
//}

/*void demo::deepCopy(){
    demo obj1;
    obj1.getdata(10,20,30);
    obj1.showdata();
    demo obj2 = obj1;
    obj2.showdata();
}
*/

/*
sregex_iterator currentMatch(textoCortado.begin(),textoCortado.end(),numerosLetras);
while (currentMatch != lastmatch) {
    smatch match = *currentMatch;
    cout << "MATCHES: "<<match.str() << endl;
    currentMatch++;
    if(currentMatch == lastmatch){
        cout << "ESTE ES EL: "<< match.str() << endl;
    }
}
*/
