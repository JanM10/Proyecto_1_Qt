#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <regex>
#include <string>
#include "json.hpp"

#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>
#include<QDebug>

using json = nlohmann::json;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class LocalServer;

///
/// \brief The MainWindow class
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ///
    /// \brief MainWindow
    /// \param parent
    ///
    MainWindow(QWidget *parent = nullptr);

private slots:
    ///
    /// \brief on_clearButton_clicked
    ///
    void on_clearButton_clicked();

    ///
    /// \brief on_runButton_clicked
    ///
    void on_runButton_clicked();

//    void on_pushButton_clicked();

    ///
    /// \brief on_writeCode_textChanged
    ///
    void on_writeCode_textChanged();

    ///
    /// \brief separarTexto
    ///
    void separarTexto();

    ///
    /// \brief printIntFloatMatches
    /// \param str
    /// \param listaJSON
    ///
    void printIntFloatMatches(std::string str,json listaJSON);

    ///
    /// \brief printCharMatches
    /// \param str
    /// \param listaJSON
    ///
    void printCharMatches(std::string str, json listaJSON);

    ///
    /// \brief on_debugButton_clicked
    ///
    void on_debugButton_clicked();

private:
    ///
    /// \brief ui
    ///
    Ui::MainWindow *ui;

    ///
    /// \brief mLocalServer
    ///
    LocalServer *mLocalServer;
};
#endif // MAINWINDOW_H
