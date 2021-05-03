#ifndef MLOCALSERVER2_H
#define MLOCALSERVER2_H

#include <QLocalServer>

class QLocalSocket;

class MLocalServer2 : public QLocalServer
{
    Q_OBJECT
public:
    explicit MLocalServer2(QObject *parent = 0);

    void envia(const QString &msj);

private:
    QLocalSocket *mSocket;
};

#endif // MLOCALSERVER2_H
