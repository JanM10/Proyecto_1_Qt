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

using json = nlohmann::json;
using namespace std;
intlong arregloIntLong[99];
floatdouble arregloFloatDouble[99];
claseChar arregloChar[99];


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
        json newJson = json::parse(entradaJSON);


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
        string listaStrings[99] = {newJson["Direccion de Memoria"].dump(),"\n",
                                   newJson["Nombre de la variable"].dump(),"\n",
                                   newJson["Valor de la variable"].dump(),"\n"};
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

/*
        cout << "Nv: "<<arregloIntLong[i].get_nombreVariable() << endl;
        cout << "Vv: " <<arregloIntLong[i].get_valorVariable() << endl;
        cout << "Vb: "<<arregloIntLong[i].get_valorBytes() << endl;
        cout << "Dm: "<<arregloIntLong[i].get_direccionMem() << endl;
*/
