#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include <QObject>

class LocalServer : public QObject
{
    Q_OBJECT
public:
    explicit LocalServer(QObject *parent = nullptr);

signals:

};

#endif // LOCALSERVER_H
