#include "mserver.h"
#include "ui_mserver.h"
#include <QLocalSocket>
#include <QTextStream>
#include "json - Copy.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "intlong.h"

using json = nlohmann::json;
using namespace std;
intlong arregloIntLong[99];

///mserver servidor que recibe los datos via JSON
///Este servidor se encarga de recibir los datos que el cliente le manda via JSON, los ordena y los manda al RAM live.
mserver::mserver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mserver)
{
    ui->setupUi(this);
    mSocket = new QLocalSocket(this);

//    arregloIntLong[0].nombreVariable = "Hola";
//    arregloIntLong[0].valorVariable = "10";
//    arregloIntLong[0].valorBytes = "4";


    connect(mSocket, &QLocalSocket::readyRead, [&](){
        QTextStream T(mSocket);
        ui->listWidget->clear();
        string entradaJSON = T.readAll().toStdString();
        json newJson = json::parse(entradaJSON);
        for(int i = 0; i<newJson["Nombre de la variable"].size(); i++){
            cout << "TAMANO: "<<newJson["Nombre de la variable"].size() << endl;
            arregloIntLong[i].nombreVariable = newJson["Nombre de la variable"][i];
            arregloIntLong[i].valorVariable = newJson["Valor de la variable"][i];
            arregloIntLong[i].valorBytes = newJson["Bytes del tipo de dato"][i];

            cout << arregloIntLong[i].get_nombreVariable() << endl;
            cout << arregloIntLong[i].get_valorVariable() << endl;
            cout << arregloIntLong[i].get_valorBytes() << endl;
//            cout << arregloIntLong[i].get_direccionMem() << endl;
        }
        cout<<"NOMBRE: "<<newJson["Nombre de la variable"]<<endl;
        ui->listWidget->addItem(newJson);
        cout << entradaJSON << endl;
    });
    mSocket->connectToServer("MiServidorLocal");
}
