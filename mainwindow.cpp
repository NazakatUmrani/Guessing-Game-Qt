#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QColor>
#include <QDebug>
#include <QTime>

void delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    static bool isUserTurn = true;
    ui->setupUi(this);

    // Define colors for the circles
    QColor colors[9];
    colors[0].setRgb(203, 55, 113);
    colors[1].setRgb(239, 68, 51);
    colors[2].setRgb(243, 117, 43);
    colors[3].setRgb(255, 189, 51);
    colors[4].setRgb(250, 241, 88);
    colors[5].setRgb(133, 200, 123);
    colors[6].setRgb(41, 172, 192);
    colors[7].setRgb(84, 108, 180);
    colors[8].setRgb(107, 78, 160);
    QColor colorsDarker[9];
    colorsDarker[0].setRgb(153, 32, 80);
    colorsDarker[1].setRgb(176, 47, 35);
    colorsDarker[2].setRgb(186, 86, 28);
    colorsDarker[3].setRgb(181, 134, 36);
    colorsDarker[4].setRgb(158, 152, 57);
    colorsDarker[5].setRgb(83, 125, 76);
    colorsDarker[6].setRgb(23, 98, 110);
    colorsDarker[7].setRgb(47, 56, 99);
    colorsDarker[8].setRgb(62, 45, 92);

    int numCircles = sizeof(colors) / sizeof(colors[0]);

    // Add circles to the grid layout
    int row = 0;
    int col = 0;
    for (int i = 0; i < numCircles; i++) {
        // Create a circle button
        QPushButton* circleButton = new QPushButton();
        circleButton->setFixedSize(100, 100);
        circleButton->setStyleSheet(QString("QPushButton {"
                                            "background-color: %1;"
                                            "border-radius: 50%;"
                                            "}").arg(colorsDarker[i].name()));

        // Add the circle button to the grid layout
        ui->gridLayout->addWidget(circleButton, row, col);

        // Connect the button's clicked signal to a custom slot function
        connect(circleButton, &QPushButton::clicked, this, [=]() {
            if(isUserTurn){
                isUserTurn = false;
                circleButton->setStyleSheet(QString("QPushButton {"
                                                    "background-color: %1;"
                                                    "border-radius: 50%;"
                                                    "}").arg(colors[i].name()));
                delay(1);
                circleButton->setStyleSheet(QString("QPushButton {"
                                                    "background-color: %1;"
                                                    "border-radius: 50%;"
                                                    "}").arg(colorsDarker[i].name()));
                isUserTurn = true;
                qDebug() << "Circle" << i+1 << "clicked!";
            }
        });

        // Update row and column indices
        col++;
        if (col >= 3) {
            col = 0;
            row++;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

