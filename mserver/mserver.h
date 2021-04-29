#ifndef MSERVER_H
#define MSERVER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class mserver;
}
QT_END_NAMESPACE

class QLocalSocket;

///
/// \brief The mserver class
///
class mserver : public QMainWindow
{
    Q_OBJECT

public:
    ///
    /// \brief mserver
    /// \param parent
    ///
    mserver(QWidget *parent = nullptr);

private slots:

private:
    ///
    /// \brief ui
    ///
    Ui::mserver *ui;

    ///
    /// \brief mSocket
    ///
    QLocalSocket *mSocket;
};
#endif // MSERVER_H
