#ifndef MSERVER_H
#define MSERVER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class mserver;
}
QT_END_NAMESPACE

class QLocalSocket;

class mserver : public QMainWindow
{
    Q_OBJECT

public:
    mserver(QWidget *parent = nullptr);

private slots:
    void on_conectButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::mserver *ui;
    QLocalSocket *mSocket;
};
#endif // MSERVER_H
