#include "localserver.h"
#include <QLocalSocket>
#include <QTextStream>
#include <string>
#include <iostream>

using namespace std;

///LocalServer se crea un servidor local
///Esta clase cea un servidor y espera a que el cliente se conecte
LocalServer::LocalServer(QObject *parent)
    : QLocalServer(parent)
{
    mSocket = nullptr;

    connect(this, &LocalServer::newConnection, [&](){
       mSocket = nextPendingConnection();
    });
}

///envia envia mensajes atraves de sockets
///Esta funcion hace lo que dice el nombre, envia mensajes atraves de un socket para que lo resiva el cliente
void LocalServer::envia(const QString &msj)
{
    if(mSocket){
    QTextStream T(mSocket);
    T << msj;
    cout << "MSJ: "<<msj.toStdString() << endl;
    mSocket->flush();
    }
}
