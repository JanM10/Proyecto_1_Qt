#ifndef MSERVER_H
#define MSERVER_H

#include <QMainWindow>
#include <string>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class mserver;
}
QT_END_NAMESPACE

class QLocalSocket;
//class mlocalserver;
class MLocalServer2;

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

    void guardarIntLong();

    void guardarFloatDouble();

    void guardarChar();


    void guardarRefIntLong();

    void guardarRefFloatDouble();

    void guardarRefChar();


    void remplazarRefIntLong();

    void remplazarRefFloatDouble();

    void remplazarRefChar();



private slots:
    void on_iniciarServidor_clicked();

private:
    ///
    /// \brief ui
    ///
    Ui::mserver *ui;

    ///
    /// \brief mSocket
    ///
    QLocalSocket *mSocket;

//    mlocalserver *myLocalServer;

    MLocalServer2 *mLocalServer;
};
#endif // MSERVER_H
