#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include <QLocalServer>

class QLocalSocket;

///
/// \brief The LocalServer class
///
class LocalServer : public QLocalServer
{
    Q_OBJECT
public:
    ///
    /// \brief LocalServer
    /// \param parent
    ///
    explicit LocalServer(QObject *parent = 0);

    ///
    /// \brief envia
    /// \param msj
    ///
    void envia(const QString &msj);

private:
    ///
    /// \brief mSocket
    ///
    QLocalSocket *mSocket;

};

#endif // LOCALSERVER_H
