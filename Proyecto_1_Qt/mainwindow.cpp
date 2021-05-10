#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localserver.h"
#include <QMessageBox>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include "json.hpp"
#include <map>
#include<QJsonObject>
#include<QJsonValue>
#include <QLocalSocket>
#include <QTextStream>


using namespace std;
using namespace regex_constants;
using json = nlohmann::json;

QStringList lines;
int numero = 1;

///MainWindow se inicia la ventana principal y se inica la conexion con el servidor
/// Esta funcion inicia la ventana principal del IDE, ademas crea un socket para conectarse con el servidor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); 
    mLocalServer = new LocalServer(this);
    mSocket = new QLocalSocket(this);


    if(!mLocalServer->listen("MiServidorLocal")){
        QMessageBox::critical(this, "Error", mLocalServer->errorString());
    }
    else{
        cout << "Servidor Iniciado" << endl;
    }

}

///on_clearButton_clicked borra el texto de aplicationLogConsole
/// Todos los datos que se muestren en aplicationLogConsole son borrados al estripar el boton
void MainWindow::on_clearButton_clicked()
{
    ui->aplicationLogConsole->clear();
}

///on_runButton_clicked este boton lee todo el texto dentro de writeCode y manda los resultados a la consola
/// Esta funcion lee todo lo que se haya escrito en el cuadro de texto writeCode, en caso de que haya alguna suma, resta, print etc, de variables, los resultados se imprimen en la consola.
void MainWindow::on_runButton_clicked()
{
    ui->console->clear();
    //close();
    if(ui->writeCode->toPlainText().contains("\n")){
        lines = ui->writeCode->toPlainText().split("\n");
    }
    listaJSON["Direccion de Memoria"] = {};
    listaJSON["Bytes del tipo de dato"] = {};
    listaJSON["Nombre de la variable"] = {};
    listaJSON["Valor de la variable"] = {};

    listaJSONRef["Tipo de dato"] = {};
    listaJSONRef["Nombre de la variable"] = {};
    listaJSONRef["GetValue de la variable"] = {};
    listaJSONRef["Direccion de Memoria"] = {};

    separarTexto();
    lines.clear();
}

/// on_writeCode_textChanged detecta cuadno hay un cambio dentro de writeCode
/// Esta funcion detecta cada vez que se haga un cambio dentro del campo de texto writeCode y ejecuta diferentes funciones para verificar el texto
void MainWindow::on_writeCode_textChanged()
{
    int j = 0;
    QString lineas = "";
    while(j<ui->writeCode->toPlainText().count("\n")+1){
        j++;
        lineas += QString::number(j) + "\n";
        ui->numeroLinea->setText(lineas);
    }
}

///separarTexto separa un string en sub-strings
/// Esta funcion separa el texto en sub-strings con la informacion que necesitamos para luego mandarlo al JSON.
void MainWindow::separarTexto(){
    string textoCortado = "";
    smatch results;
    regex soloLetras("[a-zA-Z]+");
    regex igualDespues("^\\w+( +\\w+)*$");
    sregex_iterator lastmatch;

    //lines[i].contains("struct")

    string tiposDeDatos[6] = {"int","float","long","double","char","struct"};

    for(int i=0; i<lines.size()-1; i++){
        textoCortado = lines[i].toStdString();
        if(lines[i].contains("reference<int>") || lines[i].contains("reference<long>")
                || lines[i].contains("reference<char>") || lines[i].contains("reference<float>")
                || lines[i].contains("reference<double>")){
            printReference(textoCortado);
        }else if(lines[i].contains("int") || lines[i].contains("long") || lines[i].contains("float") || lines[i].contains("double")){
            printIntFloatMatches(textoCortado);
        }else if(lines[i].contains("char")){
            printCharMatches(textoCortado);
        }
        else{
            cout << "NO SE PUDO" << endl;
        }
    }
    if(!listaJSON["Nombre de la variable"].empty()){
        if(!listaJSONRef["Nombre de la variable"].empty()){
            string dataJson = listaJSON.dump();
            string refJson = listaJSONRef.dump();
            cout << "LISTA JSON: "<< dataJson << endl;
            cout << "LISTA REF JSON: "<< refJson << endl;
            dataJson += "+";
            mLocalServer->envia(dataJson.c_str());
            mLocalServer->envia(refJson.c_str());
            cout<<"TextoCortado: " << textoCortado << endl;
        }else{
            string dataJson = listaJSON.dump();
            cout << "LISTA JSON: "<< dataJson << endl;
            mLocalServer->envia(dataJson.c_str());
            cout<<"TextoCortado: " << textoCortado << endl;
        }
    }else if (!listaJSONRef["Nombre de la variable"].empty()){
        string refJson = listaJSONRef.dump();
        cout << "LISTA REF JSON: "<< refJson << endl;
        mLocalServer->envia(refJson.c_str());
        cout<<"TextoCortado: " << textoCortado << endl;
    }else{
        cout << "No hay nada que enviar" << endl;
    }
}

///printIntFloatMatches es una funcion que separa una linea de texto en ints o float
///Esta funcion utliza regex para identificar 2 strings, el primer string es el tipo de dato, el segundo es el nombre de la variable y tercero se identifica si es int o float.
void MainWindow::printIntFloatMatches(string str){
    smatch matches;
    regex numerosLetras("\\w+");
    regex numerosFloat("\\d+?[+-]?([0-9]*[.])?[0-9]+");
    int i = 0;
//    map<string,string>tipoDeDato = {{"int","4"},{"long","8"},{"float","4"},{"double","8"}};

    while (i<3){
        if(i == 0){
            regex_search(str,matches,numerosLetras);
            listaJSON["Bytes del tipo de dato"] += matches.str(0);
            cout << listaJSON["Bytes del tipo de dato"] << endl;
            str = matches.suffix().str();
        }
        else if(i == 1){
            regex_search(str,matches,numerosLetras);
            listaJSON["Nombre de la variable"] += matches.str(0);
            cout << listaJSON["Nombre de la variable"] << endl;
            str = matches.suffix().str();
        }
        else{
            regex_search(str,matches,numerosFloat);
            listaJSON["Valor de la variable"] += matches.str(0);
            cout << listaJSON["Valor de la variable"] << endl;
            str = matches.suffix().str();
        }
        i++;
    }
}

///printCharMatches es una funcion que separa una linea de texto en strings y char
///Esta funcion utliza regex para identificar 2 strings, el primer string es el tipo de dato, el segundo es el nombre de la variable y tercero se identifica un char.
void MainWindow::printCharMatches(string str){
    smatch matches;
    regex numerosLetras("\\w+");
//    map<string,string>tipoDeDato = {{"char","1"}};
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
            regex_search(str,matches,numerosLetras);
            cout<<matches.str(0) << endl;
            listaJSON["Valor de la variable"] += matches.str(0);
            str = matches.suffix().str();
        }
        i++;
    }
}

void MainWindow::printReference(string str){
    smatch matches;
    regex numerosLetras("\\w+");
    int i = 0;
    while (i<5){
        if(i == 0){
            regex_search(str,matches,numerosLetras);
            cout<<matches.str(0) << endl;
            str = matches.suffix().str();
        }
        else if(i == 1){
            regex_search(str,matches,numerosLetras);
            cout<<matches.str(0) << endl;
            listaJSONRef["Tipo de dato"] += matches.str(0);
//            listaJSON["Bytes del tipo de dato"] += matches.str(0);
//            listaJSON["Tipo de dato"] += matches.str(0);
            str = matches.suffix().str();
        }
        else if(i == 2){
            regex_search(str,matches,numerosLetras);
            cout<<matches.str(0) << endl;
            listaJSONRef["Nombre de la variable"] += matches.str(0);
//            listaJSON["Nombre de la variable"] += matches.str(0);
            str = matches.suffix().str();
        }
        else if(i == 3){
            regex_search(str,matches,numerosLetras);
            cout<<matches.str(0) << endl;
            str = matches.suffix().str();
        }
        else{
            regex_search(str,matches,numerosLetras);
            cout<<matches.str(0) << endl;
            listaJSONRef["GetValue de la variable"] += matches.str(0);
//            listaJSON["Valor de la variable"] += matches.str(0);
//            listaJSON["GetValue de la variable"] += matches.str(0);
            str = matches.suffix().str();
        }
        i++;
    }
    cout << "JSON REF: " << listaJSONRef.dump() << endl;
}

///on_debugButton_clicked este boton de debug corre el codigo linea por linea
///Este boton va recorriendo el codigo linea por linea e identifica si hay algun tipo de error.
void MainWindow::on_debugButton_clicked(){
//    separarTexto();
//    QJsonArray listaQJSON;
//    listaQJSON["Valores"];
//    cout << "LISTA JSON: " << listaQJSON << endl;
}

void MainWindow::on_conectar_con_servidor_clicked()
{
    mSocket->connectToServer("NuevoServidor");
    connect(mSocket, &QLocalSocket::readyRead, [&](){
        QTextStream T(mSocket);
        string entradaJSON = T.readAll().toStdString();
        json newJson = json::parse(entradaJSON);

        for (int i=0;i<newJson["Nombre de la variable"].size();i++) {
            ui->tablaRAM->setRowCount(i+1);
//            ui->tablaRAM->insertRow(ui->tablaRAM->rowCount());
            QString str = QString::fromUtf8(to_string(newJson["Direccion de Memoria"][i]).c_str());
            ui->tablaRAM->setItem(i, 0, new QTableWidgetItem(str));
            QString str2 = QString::fromUtf8(to_string(newJson["Valor de la variable"][i]).c_str());
            ui->tablaRAM->setItem(i, 1, new QTableWidgetItem(str2));
            QString str3 = QString::fromUtf8(to_string(newJson["Nombre de la variable"][i]).c_str());
            ui->tablaRAM->setItem(i, 2, new QTableWidgetItem(str3));
        }
    });
}
