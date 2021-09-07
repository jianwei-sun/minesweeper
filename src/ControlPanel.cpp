//----------------------------------------------------------------------------------------------------
// File: ControlPanel.cpp
// Date: 09/03/2021
// Desc: Source file for the ControlPanel class
//----------------------------------------------------------------------------------------------------
#include "ControlPanel.hpp"

//----------------------------------------------------------------------------------------------------
// Function: ControlPanel (constructor)
// Desc: constructs the ControlPanel object
//----------------------------------------------------------------------------------------------------
ControlPanel::ControlPanel(QWidget* parent)
    : QWidget(parent),
      secondsElapsed_(0),
      numberBombs_(0)
{
    // Add a counter for the total number of mines
    this->minesRemainingDisplay_ = new QLCDNumber(3, this);
    this->minesRemainingDisplay_->setFixedSize(this->minesRemainingDisplay_->sizeHint());

    // Add the smiley face button for starting a new game
    QPushButton* faceButton = new QPushButton(this);
    faceButton->setFixedSize(ControlPanel::smileyButtonSize_, ControlPanel::smileyButtonSize_);
    faceButton->setIcon(QIcon(":/images/smile.png"));
    faceButton->setIconSize(QSize(ControlPanel::smileyIconSize_, ControlPanel::smileyIconSize_));

    // Connect the smiley push button to the new game slot
    this->connect(faceButton, &QPushButton::clicked, [this](){
        emit this->newGame();
    });

    // Add a counter for the number of elapsed seconds
    this->elapsedTimeDisplay_ = new QLCDNumber(3, this);
    this->elapsedTimeDisplay_->setFixedSize(this->elapsedTimeDisplay_->sizeHint());
    this->timer_ = new QTimer(this);
    this->connect(this->timer_, &QTimer::timeout, [this](void){
        this->elapsedTimeDisplay_->display(this->secondsElapsed_++);
    });

    // Create the top row widget consisting of the counters and smiley face button
    QHBoxLayout* topLayout = new QHBoxLayout(this);
    topLayout->setContentsMargins(0,0,0,0);
    topLayout->addWidget(this->minesRemainingDisplay_);
    topLayout->addStretch();
    topLayout->addWidget(faceButton);
    topLayout->addStretch();
    topLayout->addWidget(this->elapsedTimeDisplay_);
}

//----------------------------------------------------------------------------------------------------
// Slots
//----------------------------------------------------------------------------------------------------
void ControlPanel::reset(int numberBombs){
    this->secondsElapsed_ = 0;
    this->elapsedTimeDisplay_->display(0);
    this->numberBombs_ = numberBombs;
    this->minesRemainingDisplay_->display(numberBombs);
    this->timer_->stop();
}

void ControlPanel::startTimer(void){
    this->timer_->start(1000);
}

void ControlPanel::gameOver(bool victory){
    this->timer_->stop();
}

void ControlPanel::updateNumberFlags(int numberFlags){
    int remainingBombs = this->numberBombs_ - numberFlags;
    this->minesRemainingDisplay_->display(remainingBombs);
}

//----------------------------------------------------------------------------------------------------
// Static constants
//----------------------------------------------------------------------------------------------------
const int ControlPanel::smileyButtonSize_ = 34;
const int ControlPanel::smileyIconSize_ = 30;