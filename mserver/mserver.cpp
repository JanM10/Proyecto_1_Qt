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

using json = nlohmann::json;
using namespace std;
intlong arregloIntLong[99];
floatdouble arregloFloatDouble[99];
claseChar arregloChar[99];
referenceIntLong arregloRefIntLong[99];
int cantidadVariables;
json newJson;

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
        json newRefJson;

        if(entradaJSON == entradaRefJSON){
            entradaRefJSON.erase();
        }else{
            newRefJson = json::parse(entradaRefJSON);
        }

        newJson = json::parse(entradaJSON);
        if(!newJson["GetValue de la variable"].empty()){
            newRefJson = newJson;
            cout << "JSON REF: " << newRefJson << endl;
            newJson.clear();
            cout << "JSON NORMAL: "<< newJson << endl;
        }

        if(!newRefJson.empty()){
            string x = newRefJson["GetValue de la variable"][0];
            cout << "X vale: " << x << endl;
        }else{
            cout << "Esta vacio " << endl;
        }

        cout << "newJSON: " << newJson << endl;

        cantidadVariables = newRefJson["Tipo de dato"].size() + newJson["Bytes del tipo de dato"].size();
        cout << "cantidad variables: " << cantidadVariables << endl;

        for(int i = 0; i<newJson["Nombre de la variable"].size(); i++){
            if(newJson["Bytes del tipo de dato"][i] == "int" || newJson["Bytes del tipo de dato"][i] == "long"){
                arregloIntLong[i].nombreVariable = newJson["Nombre de la variable"][i];
//                string auxiliar = newJson["Valor de la variable"][i];
//                arregloIntLong[i].valorVariable = stoi(auxiliar);
                arregloIntLong[i].valorVariable = newJson["Valor de la variable"][i];
                arregloIntLong[i].valorBytes = newJson["Bytes del tipo de dato"][i];
                newJson["Direccion de Memoria"] += arregloIntLong[i].get_direccionMem();
            }
            else if(newJson["Bytes del tipo de dato"][i] == "float" || newJson["Bytes del tipo de dato"][i] == "double"){
                arregloFloatDouble[i].nombreVariable = newJson["Nombre de la variable"][i];
                string auxiliar = newJson["Valor de la variable"][i];
                arregloFloatDouble[i].valorVariable = stof(auxiliar);
                arregloFloatDouble[i].valorBytes = newJson["Bytes del tipo de dato"][i];
                newJson["Direccion de Memoria"] += arregloFloatDouble[i].get_direccionMem();
            }
            else if(newJson["Bytes del tipo de dato"][i] == "char"){
                arregloChar[i].nombreVariable = newJson["Nombre de la variable"][i];
                arregloChar[i].valorVariable = newJson["Valor de la variable"][i];
                arregloChar[i].valorBytes = newJson["Bytes del tipo de dato"][i];
                newJson["Direccion de Memoria"] += arregloChar[i].get_direccionMem();
            }
        }

        for (int j=0;j<newRefJson["GetValue de la variable"].size();j++) {
            arregloRefIntLong[j].nombreVariable = newRefJson["Nombre de la variable"][j];
            arregloRefIntLong[j].tipoDeDato = newRefJson["Tipo de dato"][j];
            arregloRefIntLong[j].valorVariable = newRefJson["GetValue de la variable"][j];
            newRefJson["Direccion de Memoria"] += arregloRefIntLong[j].get_direccionMem();
            cout << "Nv: "<<arregloRefIntLong[j].get_nombreVariable() << endl;
            cout << "Vv: " <<arregloRefIntLong[j].get_valorVariable() << endl;
            cout << "Td: "<<arregloRefIntLong[j].get_tipoDeDato() << endl;
            cout << "Dm: "<<arregloRefIntLong[j].get_direccionMem() << endl;
        }

        for (int k=0;k<cantidadVariables;k++) {
            if(arregloRefIntLong[k].get_tipoDeDato() == "int" or arregloRefIntLong[k].get_tipoDeDato() == "long"){
                cout << "PASA POR AQUI" << endl;
                remplazarRefIntLong();
            }
            else if(arregloRefIntLong[k].get_tipoDeDato() == "float" or arregloRefIntLong[k].get_tipoDeDato() == "double"){
                cout << "NADA POR AHORA" << endl;
            }
            else if(arregloRefIntLong[k].get_tipoDeDato() == "char"){
                cout << "NADA POR AHORA" << endl;
            }
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

void mserver::remplazarRefIntLong(){
    int j =0;
    for (int i=0;i<cantidadVariables;i++) {
        if(arregloRefIntLong[i].get_valorVariable() == arregloIntLong[j].get_nombreVariable()){
            arregloRefIntLong[i].valorVariable = arregloIntLong[j].get_valorVariable();
            cout << "Valor de la variable nueva: " << arregloRefIntLong[i].get_valorVariable() << endl;
            cout << "Nv: "<<arregloRefIntLong[i].get_nombreVariable() << endl;
            cout << "Vv: " <<arregloRefIntLong[i].get_valorVariable() << endl;
            cout << "Vb: "<<arregloRefIntLong[i].get_tipoDeDato() << endl;
            cout << "Dm: "<<arregloRefIntLong[i].get_direccionMem() << endl;
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

/*
        cout << "Nv: "<<arregloIntLong[i].get_nombreVariable() << endl;
        cout << "Vv: " <<arregloIntLong[i].get_valorVariable() << endl;
        cout << "Vb: "<<arregloIntLong[i].get_valorBytes() << endl;
        cout << "Dm: "<<arregloIntLong[i].get_direccionMem() << endl;
*/
