#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localserver.h"
#include <QMessageBox>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>


using namespace std;
using namespace regex_constants;

QStringList lines;
int numero = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mLocalServer = new LocalServer(this);

    if(!mLocalServer->listen("MiServidorLocal")){
        QMessageBox::critical(this, "Error", mLocalServer->errorString());
    }
    else{
//        QMessageBox::information(this, "Servidor","Iniciando...");
        cout << "Servidor Iniciado" << endl;
    }
}


void MainWindow::on_clearButton_clicked()
{
    ui->aplicationLogConsole->clear();
}

void MainWindow::on_iniciarServidor_clicked()
{
    mLocalServer->listen("MiServidorLocal");
}

void MainWindow::on_runButton_clicked()
{
    mLocalServer->envia(ui->writeCode->toPlainText());
    ui->console->clear();
    //close();
}

void MainWindow::on_writeCode_textChanged()
{
//    ui->console->setText(ui->writeCode->toPlainText());
//    std::cout << "Text: " << ui->writeCode->toPlainText().toStdString() << std::endl;

    if(ui->writeCode->toPlainText().contains("\n")){
        lines = ui->writeCode->toPlainText().split("\n");
    }
    int j = 0;
    QString lineas = "";
    while(j<ui->writeCode->toPlainText().count("\n")+1){
        j++;
        lineas += QString::number(j) + "\n";
        ui->numeroLinea->setText(lineas);
    }

    QString texto = "";
    string textoCortado = "";
    cmatch resultados;

    smatch results;
    regex patron("[a-zA-Z]+");
    sregex_iterator lastmatch;

    for(int i=0; i<lines.size()-1; i++){
        textoCortado = lines[i].toStdString();
//        regex_match(textoCortado, results, patron);
        sregex_iterator currentMatch(textoCortado.begin(),textoCortado.end(),patron);
        while (currentMatch != lastmatch) {
            smatch match = *currentMatch;
            cout << "MATCHES: "<<match.str() << endl;
            currentMatch++;
        }

        cout<<"TextoCortado: " << textoCortado << endl;
    }
    ui->console->setText(texto);
    lines.clear();
}
