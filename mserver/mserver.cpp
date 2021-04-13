#include "mserver.h"
#include "ui_mserver.h"
#include <QLocalSocket>
#include <QTextStream>

mserver::mserver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mserver)
{
    ui->setupUi(this);
    mSocket = new QLocalSocket(this);

    connect(mSocket, &QLocalSocket::readyRead, [&](){
        QTextStream T(mSocket);
        ui->listWidget->addItem(T.readAll());
    });

    mSocket->connectToServer("MiServidorLocal");
}


void mserver::on_conectButton_clicked()
{

}

void mserver::on_quitButton_clicked()
{
    close();
}
