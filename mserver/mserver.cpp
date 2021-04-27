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

intlong intlongprueba("hola","10","4");

mserver::mserver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mserver)
{
    ui->setupUi(this);
    mSocket = new QLocalSocket(this);

    cout << intlongprueba.get_nombreVariable() << endl;
    cout << intlongprueba.get_valorVariable() << endl;
    cout << intlongprueba.get_direccionMem() << endl;
    cout << intlongprueba.get_valorBytes() << endl;

    connect(mSocket, &QLocalSocket::readyRead, [&](){
        QTextStream T(mSocket);
        ui->listWidget->clear();
        QString hola = T.readAll();
        cout << hola.toStdString() << endl;
//        json newJson = json::parse(dataJson);
//        cout<<newJson["Nombre de la variable"]<<endl;
        ui->listWidget->addItem(hola);
    });
    mSocket->connectToServer("MiServidorLocal");
}
