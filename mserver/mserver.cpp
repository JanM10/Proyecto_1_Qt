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
        ui->listWidget->clear();
        string entradaJSON = T.readAll().toStdString();
        cout << "ENTRADA: "<< entradaJSON << endl;
        json newJson = json::parse(entradaJSON);

        for(int i = 0; i<newJson["Nombre de la variable"].size(); i++){
            if(newJson["Bytes del tipo de dato"][i] == "int" || newJson["Bytes del tipo de dato"][i] == "long"){
                arregloIntLong[i].nombreVariable = newJson["Nombre de la variable"][i];
                string auxiliar = newJson["Valor de la variable"][i];
                arregloIntLong[i].valorVariable = stoi(auxiliar);
                arregloIntLong[i].valorBytes = newJson["Bytes del tipo de dato"][i];
                cout << "Nv: "<<arregloIntLong[i].get_nombreVariable() << endl;
                cout << "Vv: " <<arregloIntLong[i].get_valorVariable() << endl;
                cout << "Vb: "<<arregloIntLong[i].get_valorBytes() << endl;
                cout << "Dm: "<<arregloIntLong[i].get_direccionMem() << endl;
            }else if(newJson["Bytes del tipo de dato"][i] == "float" || newJson["Bytes del tipo de dato"][i] == "double"){
                arregloFloatDouble[i].nombreVariable = newJson["Nombre de la variable"][i];
                string auxiliar = newJson["Valor de la variable"][i];
                arregloFloatDouble[i].valorVariable = stof(auxiliar);
                arregloFloatDouble[i].valorBytes = newJson["Bytes del tipo de dato"][i];
                cout << "Nv: "<<arregloFloatDouble[i].get_nombreVariable() << endl;
                cout << "Vv: "<<arregloFloatDouble[i].get_valorVariable() << endl;
                cout << "Vb: "<<arregloFloatDouble[i].get_valorBytes() << endl;
                cout << "Dm: "<<arregloFloatDouble[i].get_direccionMem() << endl;
            }else if(newJson["Bytes del tipo de dato"][i] == "char"){
                arregloChar[i].nombreVariable = newJson["Nombre de la variable"][i];
                arregloChar[i].valorVariable = newJson["Valor de la variable"][i];
                arregloChar[i].valorBytes = newJson["Bytes del tipo de dato"][i];
                cout << "Nv: "<<arregloChar[i].get_nombreVariable() << endl;
                cout << "Vv: "<<arregloChar[i].get_valorVariable() << endl;
                cout << "Vb: "<<arregloChar[i].get_valorBytes() << endl;
                cout << "Dm: "<<arregloChar[i].get_direccionMem() << endl;
            }
        }
    });
    mSocket->connectToServer("MiServidorLocal");
}

void mserver::envia(const QString &msj){
    if(mSocket){
    QTextStream T(mSocket);
    T << msj;
    mSocket->flush();
    }
}
