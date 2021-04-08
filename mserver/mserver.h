#ifndef MSERVER_H
#define MSERVER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class mserver; }
QT_END_NAMESPACE

class mserver : public QMainWindow
{
    Q_OBJECT

public:
    mserver(QWidget *parent = nullptr);
    ~mserver();

private:
    Ui::mserver *ui;
};
#endif // MSERVER_H
