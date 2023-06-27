#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QColor>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Define colors for the circles
    QColor colors[] = {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta, Qt::gray, Qt::darkGreen, Qt::darkCyan};
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
                                            "}").arg(colors[i].name()));

        // Add the circle button to the grid layout
        ui->gridLayout->addWidget(circleButton, row, col);

        // Connect the button's clicked signal to a custom slot function
        connect(circleButton, &QPushButton::clicked, this, [=]() {
            qDebug() << "Circle" << i << "clicked!";
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

