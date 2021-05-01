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
//    QString texto = "";
    listaJSON["Direccion de Memoria"] = {};
    listaJSON["Bytes del tipo de dato"] = {};
    listaJSON["Nombre de la variable"] = {};
    listaJSON["Valor de la variable"] = {};
    separarTexto();

//    ui->console->setText(texto);
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

        string dataJson = listaJSON.dump();
        cout << "LISTA JSON: "<<listaJSON << endl;
        cout<<"JSON SERVER str: "<< dataJson <<endl;
        cout << "QUE SE MANDA?: " << dataJson.c_str() << endl;
        mLocalServer->envia(dataJson.c_str());
        cout<<"TextoCortado: " << textoCortado << endl;
    }
}

///printIntFloatMatches es una funcion que separa una linea de texto en ints o float
///Esta funcion utliza regex para identificar 2 strings, el primer string es el tipo de dato, el segundo es el nombre de la variable y tercero se identifica si es int o float.
void MainWindow::printIntFloatMatches(string str){
    smatch matches;
    regex numerosLetras("\\w+");
    regex numerosFloat("\\d+?[+-]?([0-9]*[.])?[0-9]+");
    int i = 0;
    map<string,string>tipoDeDato = {{"int","4"},{"long","8"},{"float","4"},{"double","8"}};

    while (i<3){
        if(i == 0){
            regex_search(str,matches,numerosLetras);
            listaJSON["Bytes del tipo de dato"] += tipoDeDato[matches.str(0)];
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
//    string getJSON = listaJSON.dump();
    cout << "JSON: " << listaJSON << endl;
}

///printCharMatches es una funcion que separa una linea de texto en strings y char
///Esta funcion utliza regex para identificar 2 strings, el primer string es el tipo de dato, el segundo es el nombre de la variable y tercero se identifica un char.
void MainWindow::printCharMatches(string str){
    smatch matches;
    regex numerosLetras("\\w+");
    int i = 0;
    map<string,string>tipoDeDato = {{"int","4"},{"long","8"},{"float","4"},{"double","8"}};
    while (i<3){
        if(i == 0){
            regex_search(str,matches,numerosLetras);
            cout<<matches.str(0) << endl;
            listaJSON["Bytes del tipo de dato"] += tipoDeDato[matches.str(0)];
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
    string getJSON = listaJSON.dump();
    cout << "JSON: " << getJSON << endl;
}

///on_debugButton_clicked este boton de debug corre el codigo linea por linea
///Este boton va recorriendo el codigo linea por linea e identifica si hay algun tipo de error.
void MainWindow::on_debugButton_clicked(){
//    separarTexto();
//    QJsonArray listaQJSON;
//    listaQJSON["Valores"];
//    cout << "LISTA JSON: " << listaQJSON << endl;
}

/*
void shallowCopy(){
    int value = 5;
    int *pointer = &value;
    int *pointer2 = &value;

    cout << "pointer:" << pointer << " -- pointer2:" << pointer2 << '\n';
    cout << "pointer:" << *pointer << " -- pointer2:" << *pointer2 << '\n';
}

void demo::deepCopy(){
    demo obj1;
    obj1.getdata(10,20,30);
    obj1.showdata();
    demo obj2 = obj1;
    obj2.showdata();
}
*/
