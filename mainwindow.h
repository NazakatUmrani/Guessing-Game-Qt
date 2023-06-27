#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QPushButton>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_newGameButton_clicked();

private:
    Ui::MainWindow *ui;
    int levels = 1;
    bool isUserTurn = false;
    std::string computerSequence ="";
    std::string userSequence = "";
    QColor colors[9];
    QColor colorsDarker[9];
    void highlightSequence(int);
    void darkenCircles();
    QPushButton *circleButtons[9];
};
#endif // MAINWINDOW_H
