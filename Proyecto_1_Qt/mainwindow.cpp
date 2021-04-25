#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localserver.h"
#include <QMessageBox>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include "json.hpp"


using namespace std;
using namespace regex_constants;
using json = nlohmann::json;

QStringList lines;
int numero = 1;
json listaJSON;

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
    regex prueba("^([a-zA-Z]+)(?=.)([+-]?([0-9]*)(\\.([0-9]+))?)$");
    regex igualDespues("^\\w+( +\\w+)*$");
    sregex_iterator lastmatch;

    listaJSON["Direccion de Memoria"] = {};
    listaJSON["Bytes del tipo de dato"] = {};
    listaJSON["Nombre de la variable"] = {};
    listaJSON["Valor de la variable"] = {};

    //lines[i].contains("struct")
    //lines[i].contains("reference<tipo>")

    for(int i=0; i<lines.size()-1; i++){
        textoCortado = lines[i].toStdString();

        if(lines[i].contains("int") || lines[i].contains("long") || lines[i].contains("float") || lines[i].contains("double")){
            printIntFloatMatches(textoCortado);
        }
        else if (lines[i].contains("char")) {
//            printMatches(textoCortado,igualDespues);
            textoCortado = lines[i].remove(QString("char "), Qt::CaseInsensitive).toStdString();
            listaJSON["Bytes del tipo de dato"] += "char";
            cout<< textoCortado << endl;
            textoCortado = lines[i].remove(QString("="), Qt::CaseInsensitive).toStdString();
            cout<< textoCortado << endl;
            textoCortado = lines[i].remove(QString(";"), Qt::CaseInsensitive).toStdString();
            cout<< textoCortado << endl;
            textoCortado = lines[i].remove(QString('"'), Qt::CaseInsensitive).toStdString();
            cout<< textoCortado << endl;
            textoCortado = textoCortado.substr(0,lines[i].toStdString().find("  "));
            listaJSON["Nombre de la variable"] += textoCortado;
            cout<< "SUB:"<<textoCortado << endl;
            textoCortado = lines[i].toStdString().substr(lines[i].toStdString().find(" ") + 2);
            listaJSON["Valor de la variable"] += textoCortado;
            cout<< "SUB2:"<<textoCortado << endl;
        }
//        string getJSON = listaJSON.dump();
//        cout << "JSON: " << getJSON << endl;
        ;
        string dataJson = listaJSON.dump();
        cout<<dataJson<<endl;
        mLocalServer->envia(dataJson.c_str());
        cout<<"TextoCortado: " << textoCortado << endl;
    }
}

void MainWindow::printIntFloatMatches(string str){
    smatch matches;
    regex numerosLetras("\\w+");
    regex numerosFloat("\\d+?[+-]?([0-9]*[.])?[0-9]+");
    int i = 0;

    while (i<3){
        if(i == 0){
            regex_search(str,matches,numerosLetras);
            cout<<matches.str(0) << endl;
            listaJSON["Bytes del tipo de dato"] += matches.str(0);
            str = matches.suffix().str();
        }
        else if(i == 1){
            regex_search(str,matches,numerosLetras);
            cout<<matches.str(0) << endl;
            listaJSON["Nombre de la variable"] += matches.str(0);
            str = matches.suffix().str();
        }
        else{
            regex_search(str,matches,numerosFloat);
            cout<<matches.str(0) << endl;
            listaJSON["Valor de la variable"] += matches.str(0);
            str = matches.suffix().str();
        }
        i++;
    }
    string getJSON = listaJSON.dump();
    cout << "JSON: " << getJSON << endl;
}

void MainWindow::printCharMatches(std::string str, std::regex reg){
//    textoCortado = lines[i].remove(QString("char "), Qt::CaseInsensitive).toStdString();
//    cout<< textoCortado << endl;
//    textoCortado = lines[i].remove(QString("="), Qt::CaseInsensitive).toStdString();
//    cout<< textoCortado << endl;
//    textoCortado = lines[i].remove(QString(";"), Qt::CaseInsensitive).toStdString();
//    cout<< textoCortado << endl;
//    textoCortado = lines[i].remove(QString('"'), Qt::CaseInsensitive).toStdString();
//    cout<< textoCortado << endl;
//    textoCortado = textoCortado.substr(0,lines[i].toStdString().find("  "));
//    cout<< "SUB:"<<textoCortado << endl;
//    textoCortado = lines[i].toStdString().substr(lines[i].toStdString().find(" ") + 2);
//    cout<< "SUB2:"<<textoCortado << endl;
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

void MainWindow::on_debugButton_clicked()
{
    cout<< "EL BOTON FUNCIONA" << endl;
}
