//----------------------------------------------------------------------------------------------------
// File: GameMainWindow.cpp
// Date: 09/03/2021
// Desc: Source file for the GameMainWindow class
//----------------------------------------------------------------------------------------------------
#include "GameMainWindow.hpp"

//----------------------------------------------------------------------------------------------------
// Function: GameMainWindow (constructor)
// Desc: constructs the GameMainWindow object
//----------------------------------------------------------------------------------------------------
GameMainWindow::GameMainWindow(QWidget* parent)
    : QWidget(parent),
      gameBoard_(new GameBoard(BOARD_SIZE{GameMainWindow::numberRows_, GameMainWindow::numberColumns_}, GameMainWindow::mineDensity_, this))
{
    // Set window properties
    this->setWindowTitle("Minesweeper");
    this->setWindowIcon(QIcon(":/images/mine.png"));
    
    // Add a counter for the total number of mines
    QLCDNumber* minesRemaining = new QLCDNumber(3, this);
    minesRemaining->setFixedSize(minesRemaining->sizeHint());

    // Add the smiley face button for starting a new game
    QPushButton* faceButton = new QPushButton(this);
    faceButton->setFixedSize(GameMainWindow::smileyButtonSize_, GameMainWindow::smileyButtonSize_);
    faceButton->setIcon(QIcon(":/images/smile.png"));
    faceButton->setIconSize(QSize(GameMainWindow::smileyIconSize_, GameMainWindow::smileyIconSize_));

    // Add a counter for the number of elapsed seconds
    QLCDNumber* elapsedTime = new QLCDNumber(3, this);
    elapsedTime->setFixedSize(elapsedTime->sizeHint());

    // Create the top row widget consisting of the counters and smiley face button
    QWidget* topRow = new QWidget(this);
    QHBoxLayout* topLayout = new QHBoxLayout(topRow);
    topLayout->setContentsMargins(0,0,0,0);
    topLayout->addWidget(minesRemaining);
    topLayout->addStretch();
    topLayout->addWidget(faceButton);
    topLayout->addStretch();
    topLayout->addWidget(elapsedTime);

    // Add the game board underneath
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(topRow);
    mainLayout->addWidget(this->gameBoard_);

    // Fix the size
    this->setFixedSize(this->sizeHint());

    // Connect the smiley push button to the new game slot
    this->connect(faceButton, &QPushButton::clicked, [this](){
        this->gameBoard_->newGame(GameMainWindow::mineDensity_);
    });
}

//----------------------------------------------------------------------------------------------------
// Static constants
//----------------------------------------------------------------------------------------------------
const int GameMainWindow::smileyButtonSize_ = 34;
const int GameMainWindow::smileyIconSize_ = 30;
const int GameMainWindow::numberRows_ = 10;
const int GameMainWindow::numberColumns_ = 20;
const double GameMainWindow::mineDensity_ = 0.2;