#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <regex>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class LocalServer;
class QLocalSocket;

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
    void printIntFloatMatches(std::string str);

    ///
    /// \brief printCharMatches
    /// \param str
    /// \param listaJSON
    ///
    void printCharMatches(std::string str);

    void printReference(std::string str);

    ///
    /// \brief on_debugButton_clicked
    ///
    void on_debugButton_clicked();

    void on_conectar_con_servidor_clicked();

    void on_botonDerecha_clicked();

    void on_botonIzquierda_clicked();

    void on_stopButton_clicked();

private:
    json listaJSON;
    json listaJSONRef;

    ///
    /// \brief ui
    ///
    Ui::MainWindow *ui;

    ///
    /// \brief mLocalServer
    ///
    LocalServer *mLocalServer;

    QLocalSocket *mSocket;
};
#endif // MAINWINDOW_H
