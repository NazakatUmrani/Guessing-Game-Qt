#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QColor>
#include <QTime>
#include <random>
#include <QChar>

//Function for delay
void delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//Dakrens colors of all circles
void MainWindow::darkenCircles(){
    for(int i=0; i<9; i++){
        ui->gridLayout->itemAt(i)->widget()->setStyleSheet(QString("QPushButton {"
                                                "background-color: %1;"
                                                "border-radius: 50%;"
                                                "color: black;"
                                                "}").arg(colorsDarker[i].name()));
    }
}

void MainWindow::highlightSequence(int i){
    //Base Condition
    if(i==0)
        return;

    // Create a random number generator engine
    random_device rd;
    mt19937 gen(rd());

    // Generate random numbers between 1 and 100
    uniform_int_distribution<int> dist(0, 8);

    // Generate random numbers
    int randomNum = dist(gen);

    //Highlight Circles and Display Emoji
    circleButtons[randomNum]->setStyleSheet(QString("QPushButton {"
                                                    "background-color: %1;"
                                                    "border-radius: 50%;"
                                                    "color: black;"
                                                    "}").arg(colors[randomNum].name()));
    circleButtons[randomNum]->setText(QString(QChar(0xF60A)));

    //Add index to string
    computerSequence = computerSequence+to_string(randomNum+1);
    delay(1);

    //Remove Highlight and emoji
    circleButtons[randomNum]->setStyleSheet(QString("QPushButton {"
                                                    "background-color: %1;"
                                                    "border-radius: 50%;"
                                                    "color: black;"
                                                    "}").arg(colorsDarker[randomNum].name()));
    circleButtons[randomNum]->setText(QString(""));
    delay(1);
    //Recursively call this function
    highlightSequence(i-1);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Define colors for the circles
    colors[0].setRgb(203, 55, 113);
    colors[1].setRgb(239, 68, 51);
    colors[2].setRgb(243, 117, 43);
    colors[3].setRgb(255, 189, 51);
    colors[4].setRgb(250, 241, 88);
    colors[5].setRgb(133, 200, 123);
    colors[6].setRgb(41, 172, 192);
    colors[7].setRgb(84, 108, 180);
    colors[8].setRgb(107, 78, 160);
    colorsDarker[0].setRgb(153, 32, 80);
    colorsDarker[1].setRgb(176, 47, 35);
    colorsDarker[2].setRgb(186, 86, 28);
    colorsDarker[3].setRgb(181, 134, 36);
    colorsDarker[4].setRgb(158, 152, 57);
    colorsDarker[5].setRgb(83, 125, 76);
    colorsDarker[6].setRgb(23, 98, 110);
    colorsDarker[7].setRgb(47, 56, 99);
    colorsDarker[8].setRgb(62, 45, 92);

    // Add circles to the grid layout
    int row = 0;
    int col = 0;
    //Create and add circles in gridLayout
    for (int i = 0; i < 9; i++) {
        // Create a circle button
        QPushButton* circleButton = new QPushButton();
        circleButton->setFixedSize(100, 100);
        circleButton->setStyleSheet(QString("QPushButton {"
                                            "background-color: %1;"
                                            "border-radius: 50%;"
                                            "color: black;"
                                            "}").arg(colors[i].name()));
        circleButton->setFont(QFont("Arial",70));

        // Add the circle button to the grid layout
        circleButtons[i] = circleButton;
        ui->gridLayout->addWidget(circleButtons[i], row, col);

        // Connect the button's clicked signal to a custom slot function
        connect(circleButton, &QPushButton::clicked, this, [=]() {
            if(isUserTurn){
                isUserTurn = false;

                //Highlight circle and display emoji
                circleButton->setStyleSheet(QString("QPushButton {"
                                                    "background-color: %1;"
                                                    "border-radius: 50%;"
                                                    "color: black;"
                                                    "}").arg(colors[i].name()));
                circleButtons[i]->setText(QString(QChar(0xF60A)));
                //Add index to sequence
                userSequence = userSequence + to_string(i+1);
                delay(1);
                //Darken circle and remove emoji
                circleButton->setStyleSheet(QString("QPushButton {"
                                                    "background-color: %1;"
                                                    "border-radius: 50%;"
                                                    "color: black;"
                                                    "}").arg(colorsDarker[i].name()));
                circleButtons[i]->setText(QString(""));
                //If Sequence are equals
                if(computerSequence.length()==userSequence.length()){
                    if(computerSequence==userSequence){
                        //Increase level and update labels
                        levels++;
                        ui->levelLabel->setText(QString::fromStdString("Level: "+to_string(levels)));
                        ui->messageLabel->setText(QString::fromStdString("You got it correct"));
                        delay(1);
                        ui->messageLabel->setText(QString::fromStdString("Okay now, get ready for sequence of "+to_string(levels+2)));
                        delay(3);
                        ui->messageLabel->setText(QString::fromStdString("Remember this sequence"));
                        //Move to next level with more highlights
                        highlightSequence(levels+2);
                        ui->messageLabel->setText(QString::fromStdString("Now your turn, repeat the sequence"));
                        isUserTurn=true;
                    }
                    else{
                        //If lose reset variables and messages
                        levels=1;
                        computerSequence="";
                        userSequence="";
                        ui->messageLabel->setText(QString::fromStdString("You Failed"));
                        delay(2);
                        ui->levelLabel->setText(QString::fromStdString(""));
                        ui->messageLabel->setText(QString::fromStdString("Press Button to start game"));
                        isUserTurn=false;
                        ui->newGameButton->setDisabled(false);
                    }
                }
                else{
                    isUserTurn = true;
                }
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

void MainWindow::on_newGameButton_clicked()
{
    //Disable button and update labels
    ui->newGameButton->setDisabled(true);
    ui->messageLabel->setText(QString::fromStdString("Okay let's go, get ready for sequence of "+to_string(levels+2)));
    ui->levelLabel->setText(QString::fromStdString("Level: 1"));
    //Darken Circles
    darkenCircles();
    delay(3);
    ui->messageLabel->setText(QString::fromStdString("Remember this sequence"));
    //Highlight circles
    highlightSequence(levels+2);
    ui->messageLabel->setText(QString::fromStdString("Now your turn, repeat the sequence"));
    isUserTurn=true;
}
