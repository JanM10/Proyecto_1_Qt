#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include <QLocalServer>

class QLocalSocket;

class LocalServer : public QLocalServer
{
    Q_OBJECT
public:
    explicit LocalServer(QObject *parent = 0);
    void envia(const QString &msj);

private:
    QLocalSocket *mSocket;

};

#endif // LOCALSERVER_H
