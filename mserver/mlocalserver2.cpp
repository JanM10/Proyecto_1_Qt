#include "mlocalserver2.h"
#include <QLocalSocket>

MLocalServer2::MLocalServer2(QObject *parent)
    : QLocalServer(parent)
{
    mSocket = nullptr;

    connect(this, &MLocalServer2::newConnection, [&](){
        mSocket = nextPendingConnection();
    });
}

void MLocalServer2::envia(const QString &msj){
    if(mSocket){
        QTextStream T(mSocket);
        T << msj;
        mSocket->flush();
    }
}
