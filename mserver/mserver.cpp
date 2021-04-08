#include "mserver.h"
#include "ui_mserver.h"

mserver::mserver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mserver)
{
    ui->setupUi(this);
}

mserver::~mserver()
{
    delete ui;
}

