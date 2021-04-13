#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localserver.h"
#include <QMessageBox>
#include <iostream>

QString variable = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mLocalServer = new LocalServer(this);

    if(!mLocalServer->listen("MiServidorLocal")){
        QMessageBox::critical(this, "Error", mLocalServer->errorString());
    }
//    else{
//        QMessageBox::information(this, "Servidor","Iniciando...");
//    }
}


void MainWindow::on_clearButton_clicked()
{
    ui->aplicationLogConsole->clear();
}



void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_runButton_clicked()
{
    mLocalServer->envia(ui->writeCode->toPlainText());
    ui->console->clear();
    //close();
}

void MainWindow::on_writeCode_textChanged()
{
    ui->console->setText(ui->writeCode->toPlainText());
    //std::cout << "Text: " << ui->writeCode->toPlainText().toStdString() << std::endl;
}
