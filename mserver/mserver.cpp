#include "mserver.h"
#include "ui_mserver.h"
#include <QLocalSocket>
#include <QTextStream>
#include "json - Copy.hpp"
#include <iostream>

using json = nlohmann::json;
using namespace std;

mserver::mserver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mserver)
{
    ui->setupUi(this);
    mSocket = new QLocalSocket(this);

    connect(mSocket, &QLocalSocket::readyRead, [&](){
        QTextStream T(mSocket);
        ui->listWidget->clear();
        QString hola = T.readAll();
        cout << hola.toStdString() << endl;
//        json newJson = json::parse(dataJson);
//        cout<<newJson["Nombre de la variable"]<<endl;
        ui->listWidget->addItem(T.readAll());
    });

    mSocket->connectToServer("MiServidorLocal");
}
