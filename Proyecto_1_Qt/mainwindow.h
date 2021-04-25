#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <regex>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class LocalServer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void on_clearButton_clicked();

    void on_runButton_clicked();

//    void on_pushButton_clicked();

    void on_writeCode_textChanged();

    void separarTexto();

    void printIntFloatMatches(std::string str);

    void printCharMatches(std::string str, std::regex reg);

    void on_debugButton_clicked();

private:
    Ui::MainWindow *ui;
    LocalServer *mLocalServer;
};
#endif // MAINWINDOW_H
