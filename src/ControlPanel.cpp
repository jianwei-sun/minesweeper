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
    : QWidget(parent)
{
    // Add a counter for the total number of mines
    QLCDNumber* minesRemaining = new QLCDNumber(3, this);
    minesRemaining->setFixedSize(minesRemaining->sizeHint());

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
    QLCDNumber* elapsedTime = new QLCDNumber(3, this);
    elapsedTime->setFixedSize(elapsedTime->sizeHint());

    // Create the top row widget consisting of the counters and smiley face button
    QHBoxLayout* topLayout = new QHBoxLayout(this);
    topLayout->setContentsMargins(0,0,0,0);
    topLayout->addWidget(minesRemaining);
    topLayout->addStretch();
    topLayout->addWidget(faceButton);
    topLayout->addStretch();
    topLayout->addWidget(elapsedTime);
}

//----------------------------------------------------------------------------------------------------
// Slots
//----------------------------------------------------------------------------------------------------
void ControlPanel::reset(void){

}

//----------------------------------------------------------------------------------------------------
// Static constants
//----------------------------------------------------------------------------------------------------
const int ControlPanel::smileyButtonSize_ = 34;
const int ControlPanel::smileyIconSize_ = 30;