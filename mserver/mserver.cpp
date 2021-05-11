#include "mserver.h"
#include "ui_mserver.h"
#include <QLocalSocket>
#include <QTextStream>
#include "json - Copy.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "intlong.h"
#include "floatdouble.h"
#include "clasechar.h"
#include <QMessageBox>
#include "mlocalserver2.h"
#include <QDebug>
#include <QStringList>
#include "referenceintlong.h"
#include "referencefloatdouble.h"
#include "referencechar.h"

using json = nlohmann::json;
using namespace std;

intlong arregloIntLong[99];
floatdouble arregloFloatDouble[99];
claseChar arregloChar[99];
referenceIntLong arregloRefIntLong[99];
referenceFloatDouble arregloRefFloatDouble[99];
referencechar arregloRefChar[99];

int cantidadVariables;
json newJson;
json newRefJson;

///mserver servidor que recibe los datos via JSON
///Este servidor se encarga de recibir los datos que el cliente le manda via JSON, los ordena y los manda al RAM live.
mserver::mserver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mserver)
{
    ui->setupUi(this);
    mSocket = new QLocalSocket(this);

    connect(mSocket, &QLocalSocket::readyRead, [&](){
        QTextStream T(mSocket);
        string entradaJSON = T.readAll().toStdString();
        string entradaRefJSON = entradaJSON.substr(entradaJSON.find("+")+1);
        entradaJSON = entradaJSON.substr(0,entradaJSON.find("+"));
        cout << "ENTRADA JSON: " << entradaJSON << endl;
        cout << "ENTRADA REF: " << entradaRefJSON << endl;

        if(entradaJSON == entradaRefJSON){
            entradaRefJSON.erase();
        }else{
            newRefJson = json::parse(entradaRefJSON);
        }

        newJson = json::parse(entradaJSON);

        if(!newRefJson["GetValue de la variable"].empty()){
//            newRefJson = newJson;
            cout << "JSON REF: " << newRefJson << endl;
//            newJson.clear();
            cout << "JSON NORMAL: "<< newJson << endl;
        }else{
            cout << "NO HAY JSON REF" << endl;
        }

        cout << "newJSON: " << newJson << endl;

        cantidadVariables = newRefJson["Tipo de dato"].size() + newJson["Bytes del tipo de dato"].size();
        cout << "cantidad variables: " << cantidadVariables << endl;

        for(int i = 0; i<newJson["Nombre de la variable"].size(); i++){
            if(newJson["Bytes del tipo de dato"][i] == "int" || newJson["Bytes del tipo de dato"][i] == "long"){
                guardarIntLong();
            }
            else if(newJson["Bytes del tipo de dato"][i] == "float" || newJson["Bytes del tipo de dato"][i] == "double"){
                guardarFloatDouble();
            }
            else if(newJson["Bytes del tipo de dato"][i] == "char"){
                guardarChar();
            }else{
                cout << "POR SI ACASO" << endl;
            }
        }

        if(!newRefJson.empty()){
            for (int i = 0; i<newRefJson["Tipo de dato"].size(); i++) {
                if(newRefJson["Tipo de dato"][i] == "int" || newRefJson["Tipo de dato"][i] == "long"){
                    guardarRefIntLong();
                }
                else if(newRefJson["Tipo de dato"][i] == "float" || newRefJson["Tipo de dato"][i] == "double"){
                    guardarRefFloatDouble();
                }
                else if(newRefJson["Tipo de dato"][i] == "char"){
                    guardarRefChar();
                }else{
                    cout << "NO SE PUEDE GUARDAR" << endl;
                }
            }

            for (int k=0;k<cantidadVariables;k++) {
                if(arregloRefIntLong[k].get_tipoDeDato() == "int" || arregloRefIntLong[k].get_tipoDeDato() == "long"){
                    remplazarRefIntLong();
                }
                else if(arregloRefFloatDouble[k].get_tipoDeDato() == "float" || arregloRefFloatDouble[k].get_tipoDeDato() == "double"){
                    remplazarRefFloatDouble();
                }
                else if(arregloRefChar[k].get_tipoDeDato() == "char"){
                    remplazarRefChar();
                }
            }
        }
        else{
            cout << "No hay REFERENCE" << endl;
        }


        mLocalServer->envia(newJson.dump().c_str());
        cout << "SE ENVIO LA INFO" << endl;
    });
    mSocket->connectToServer("MiServidorLocal");
}

void mserver::on_iniciarServidor_clicked()
{
    mLocalServer = new MLocalServer2(this);

    if (!mLocalServer->listen("NuevoServidor")){
        QMessageBox::critical(this, "Error", mLocalServer->errorString());
    }else{
        cout << "Servidor2 Iniciado" << endl;
        QMessageBox::information(this, "EXITO", "El servidor se ha iniciado con exito.");
    }
}

//FUNCIONES GUARDAR

void mserver::guardarIntLong(){
    for (int i = 0; i<newJson["Nombre de la variable"].size(); i++) {
        if(newJson["Bytes del tipo de dato"][i] != "" and newJson["Bytes del tipo de dato"][i] == "int"
                || newJson["Bytes del tipo de dato"][i] != "" and newJson["Bytes del tipo de dato"][i] == "long"){
            arregloIntLong[i].nombreVariable = newJson["Nombre de la variable"][i];
//                string auxiliar = newJson["Valor de la variable"][i];
//                arregloIntLong[i].valorVariable = stoi(auxiliar);
            arregloIntLong[i].valorVariable = newJson["Valor de la variable"][i];
            arregloIntLong[i].valorBytes = newJson["Bytes del tipo de dato"][i];
            newJson["Direccion de Memoria"] += arregloIntLong[i].get_direccionMem();
            cout << "TIPO DE DATO INTLONG: " << arregloIntLong[i].get_valorBytes() << endl;
        }else{
            cout << "NADA" << endl;
        }
    }
}


void mserver::guardarFloatDouble(){
    for (int i = 0; i<newJson["Nombre de la variable"].size(); i++) {
        if(newJson["Bytes del tipo de dato"][i] != "" and newJson["Bytes del tipo de dato"][i] == "float"
                || newJson["Bytes del tipo de dato"][i] != "" and newJson["Bytes del tipo de dato"][i] == "double"){
            arregloFloatDouble[i].nombreVariable = newJson["Nombre de la variable"][i];
//        string auxiliar = newJson["Valor de la variable"][i];
//        arregloFloatDouble[i].valorVariable = stof(auxiliar);
            arregloFloatDouble[i].valorVariable = newJson["Valor de la variable"][i];
            arregloFloatDouble[i].valorBytes = newJson["Bytes del tipo de dato"][i];
            newJson["Direccion de Memoria"] += arregloFloatDouble[i].get_direccionMem();
            cout << "TIPO DE DATO FLOATDOUBLE: " << arregloFloatDouble[i].get_valorBytes() << endl;
        }else{
            cout << "NADA" << endl;
        }
    }
}

void mserver::guardarChar(){
    for (int i = 0; i<newJson["Nombre de la variable"].size(); i++) {
        if(newJson["Bytes del tipo de dato"][i] != "" and newJson["Bytes del tipo de dato"][i] == "char"){
            arregloChar[i].nombreVariable = newJson["Nombre de la variable"][i];
            arregloChar[i].valorVariable = newJson["Valor de la variable"][i];
            arregloChar[i].valorBytes = newJson["Bytes del tipo de dato"][i];
            newJson["Direccion de Memoria"] += arregloChar[i].get_direccionMem();
            cout << "TIPO DE DATO CHAR: " << arregloChar[i].get_valorBytes() << endl;
        }else{
            cout << "NADA" << endl;
        }
    }
}


//FUNCIONES GUARDAR REF

void mserver::guardarRefIntLong(){
    for (int j=0;j<newRefJson["GetValue de la variable"].size();j++) {
        arregloRefIntLong[j].nombreVariable = newRefJson["Nombre de la variable"][j];
        arregloRefIntLong[j].tipoDeDato = newRefJson["Tipo de dato"][j];
        arregloRefIntLong[j].valorVariable = newRefJson["GetValue de la variable"][j];
        newRefJson["Direccion de Memoria"] += arregloRefIntLong[j].get_direccionMem();
        cout << "REF INTLONG Nv: "<<arregloRefIntLong[j].get_nombreVariable() << endl;
        cout << "REF INTLONG Vv: " <<arregloRefIntLong[j].get_valorVariable() << endl;
        cout << "REF INTLONG Td: "<<arregloRefIntLong[j].get_tipoDeDato() << endl;
        cout << "REF INTLONG Dm: "<<arregloRefIntLong[j].get_direccionMem() << endl;
    }
}

void mserver::guardarRefFloatDouble(){
    for (int j=0;j<newRefJson["GetValue de la variable"].size();j++) {
        arregloRefFloatDouble[j].nombreVariable = newRefJson["Nombre de la variable"][j];
        arregloRefFloatDouble[j].tipoDeDato = newRefJson["Tipo de dato"][j];
        arregloRefFloatDouble[j].valorVariable = newRefJson["GetValue de la variable"][j];
        newRefJson["Direccion de Memoria"] += arregloRefFloatDouble[j].get_direccionMem();
        cout << "REF FLOATDOUBLE Nv: "<<arregloRefFloatDouble[j].get_nombreVariable() << endl;
        cout << "REF FLOATDOUBLE Vv: " <<arregloRefFloatDouble[j].get_valorVariable() << endl;
        cout << "REF FLOATDOUBLE Td: "<<arregloRefFloatDouble[j].get_tipoDeDato() << endl;
        cout << "REF FLOATDOUBLE Dm: "<<arregloRefFloatDouble[j].get_direccionMem() << endl;
    }
}

void mserver::guardarRefChar(){
    for (int j=0;j<newRefJson["GetValue de la variable"].size();j++) {
        arregloRefChar[j].nombreVariable = newRefJson["Nombre de la variable"][j];
        arregloRefChar[j].tipoDeDato = newRefJson["Tipo de dato"][j];
        arregloRefChar[j].valorVariable = newRefJson["GetValue de la variable"][j];
        newRefJson["Direccion de Memoria"] += arregloRefChar[j].get_direccionMem();
        cout << "REF CHAR Nv: "<<arregloRefChar[j].get_nombreVariable() << endl;
        cout << "REF CHAR Vv: " <<arregloRefChar[j].get_valorVariable() << endl;
        cout << "REF CHAR Td: "<<arregloRefChar[j].get_tipoDeDato() << endl;
        cout << "REF CHAR Dm: "<<arregloRefChar[j].get_direccionMem() << endl;
    }
}

//FUNCIONES REMPLAZAR

void mserver::remplazarRefIntLong(){
    int j =0;
    for (int i=0;i<cantidadVariables;i++) {
        if(arregloRefIntLong[i].get_valorVariable() == arregloIntLong[j].get_nombreVariable() and arregloIntLong[i].get_valorVariable() != ""){
            arregloRefIntLong[i].valorVariable = arregloIntLong[j].get_valorVariable();
            cout << "Valor de la variable nueva: " << arregloRefIntLong[i].get_valorVariable() << endl;
            cout << "REM INTLONG Nv: "<<arregloRefIntLong[i].get_nombreVariable() << endl;
            cout << "REM INTLONG Vv: " <<arregloRefIntLong[i].get_valorVariable() << endl;
            cout << "REM INTLONG Vb: "<<arregloRefIntLong[i].get_tipoDeDato() << endl;
            cout << "REM INTLONG Dm: "<<arregloRefIntLong[i].get_direccionMem() << endl;
            newJson["Direccion de Memoria"] += arregloRefIntLong[i].get_direccionMem();
            newJson["Nombre de la variable"] += arregloRefIntLong[i].get_nombreVariable();
            newJson["Valor de la variable"] += arregloRefIntLong[i].get_valorVariable();
            newJson["Bytes del tipo de dato"] += arregloRefIntLong[i].get_tipoDeDato();
            j = 0;
        }else{
            j++;
        }
    }
    cout << "TERMINO" << endl;
}

void mserver::remplazarRefFloatDouble(){
    int j =0;
    for (int i=0;i<cantidadVariables;i++) {
        if(arregloRefFloatDouble[i].get_valorVariable() == arregloFloatDouble[j].get_nombreVariable() and arregloFloatDouble[i].get_valorVariable() != ""){
            arregloRefFloatDouble[i].valorVariable = arregloFloatDouble[j].get_valorVariable();
            cout << "Valor de la variable nueva: " << arregloFloatDouble[i].get_valorVariable() << endl;
            cout << "REM FLOATDOUBLE Nv: "<<arregloRefFloatDouble[i].get_nombreVariable() << endl;
            cout << "REM FLOATDOUBLE Vv: " <<arregloRefFloatDouble[i].get_valorVariable() << endl;
            cout << "REM FLOATDOUBLE Vb: "<<arregloRefFloatDouble[i].get_tipoDeDato() << endl;
            cout << "REM FLOATDOUBLE Dm: "<<arregloRefFloatDouble[i].get_direccionMem() << endl;
            newJson["Direccion de Memoria"] += arregloRefFloatDouble[i].get_direccionMem();
            newJson["Nombre de la variable"] += arregloRefFloatDouble[i].get_nombreVariable();
            newJson["Valor de la variable"] += arregloRefFloatDouble[i].get_valorVariable();
            newJson["Bytes del tipo de dato"] += arregloRefFloatDouble[i].get_tipoDeDato();
            j = 0;
        }else{
            j++;
        }
    }
    cout << "TERMINO" << endl;
}

void mserver::remplazarRefChar(){
    int j =0;
    for (int i=0;i<cantidadVariables;i++) {
        if(arregloRefChar[i].get_valorVariable() == arregloChar[j].get_nombreVariable() and arregloRefChar[i].get_valorVariable() != ""){
            arregloRefChar[i].valorVariable = arregloChar[j].get_valorVariable();
            cout << "Valor de la variable nueva: " << arregloChar[i].get_valorVariable() << endl;
            cout << "REM CHAR Nv: "<<arregloRefChar[i].get_nombreVariable() << endl;
            cout << "REM CHAR Vv: " <<arregloRefChar[i].get_valorVariable() << endl;
            cout << "REM CHAR Vb: "<<arregloRefChar[i].get_tipoDeDato() << endl;
            cout << "REM CHAR Dm: "<<arregloRefChar[i].get_direccionMem() << endl;
            newJson["Direccion de Memoria"] += arregloRefChar[i].get_direccionMem();
            newJson["Nombre de la variable"] += arregloRefChar[i].get_nombreVariable();
            newJson["Valor de la variable"] += arregloRefChar[i].get_valorVariable();
            newJson["Bytes del tipo de dato"] += arregloRefChar[i].get_tipoDeDato();
            j = 0;
        }else{
            j++;
        }
    }
    cout << "TERMINO" << endl;
}
