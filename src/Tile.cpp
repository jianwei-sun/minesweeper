//----------------------------------------------------------------------------------------------------
// File: Tile.cpp
// Date: 08/22/2021
// Desc: Source file for the Tile class
//----------------------------------------------------------------------------------------------------
#include "Tile.hpp"

//----------------------------------------------------------------------------------------------------
// Function: Tile (constructor)
// Desc: constructs the Tile object
//----------------------------------------------------------------------------------------------------
Tile::Tile(Coordinates coordinates, QWidget* parent)
    : QPushButton(parent),
      coordinates_(coordinates),
      bomb_(false),
      neighborBombs_(0),
      revealed_(false),
      visualState_(TileVisualState::unclicked)
{
    // Fix the size
    this->setFixedSize(Tile::pixelSize_, Tile::pixelSize_);
}

void Tile::reset(bool bomb, int neighborBombs){
    this->bomb_ = bomb;
    this->neighborBombs_ = neighborBombs;
    this->revealed_ = false;
    this->visualState_ = TileVisualState::unclicked;
    this->setIcon(QIcon());
    this->setStyleSheet("");
    this->setText("");
    this->setFlat(false);
}

void Tile::reveal(void){
    if(this->bomb_){
        switch(this->visualState_){
            case TileVisualState::flag:{
                this->setIcon(QIcon(":/images/mine_flag.png"));
                break;
            }
            case TileVisualState::unsure:{
                this->setIcon(QIcon(":/images/mine_question-mark.png"));
                break;
            }
            default:{
                this->setIcon(QIcon(":/images/mine.png"));
            }
        }
        this->setIconSize(QSize(Tile::pixelIconSize_, Tile::pixelIconSize_));
    }
    this->revealed_ = true;
}

//----------------------------------------------------------------------------------------------------
// Function: mousePressEvent
// Desc: reimplement the mousePress event to respond to primary and secondary clicks
//----------------------------------------------------------------------------------------------------
void Tile::mousePressEvent(QMouseEvent* mouseEvent){
    if(mouseEvent->button() == Qt::LeftButton){
        this->primaryClicked();
    } else if(mouseEvent->button() == Qt::RightButton){
        this->secondaryClicked();
    }
}

void Tile::emptyReveal(void){
    // The goal is to reveal the largest island of tiles without neighbors, including a boundary of tiles with at least 1 neighbor
    // This logic can be realized by simulating a primary click if the tile does not have a bomb, because it ensures that the tile would either
    // continue to propagate to nearby tiles without neighbors, or display the number of neighbors with bombs (which would end the propagation at the desired boundary)
    if(!this->bomb_){
        this->primaryClicked();
    }
}

void Tile::primaryClicked(void){
    // Clicking only makes sense if the tile has not yet been revealed
    if(!(this->revealed_ || this->visualState_ == TileVisualState::flag || this->visualState_ == TileVisualState::unsure)){
        // Disable the tile from being revealed again
        this->revealed_ = true;

        // End the game if the user clicks on a bomb tile
        if(this->bomb_){
            this->setIcon(QIcon(":/images/mine.png"));
            this->setStyleSheet("background-color:red;");
            emit this->gameOver(this->coordinates_);

        // Otherwise reveal a number and/or propagate neighbors
        } else{
            // Display the number
            if(this->neighborBombs_ > 0){
                this->setText(QString::number(this->neighborBombs_));
                this->setStyleSheet(QString("font:bold;color:") + Tile::fontColors_[this->neighborBombs_ - 1] + QString(";"));
        
            // Propagate to neighbors
            } else{
                emit this->revealEmpty();
            }

            // Show the button as having been pressed
            this->setFlat(true);
        }
    }
}

void Tile::secondaryClicked(void){
    if(!this->revealed_){
        // Alternate between the unrevealed states
        switch(this->visualState_){
            case TileVisualState::unclicked:{
                this->setIcon(QIcon(":/images/flag.png"));
                this->setIconSize(QSize(Tile::pixelIconSize_, Tile::pixelIconSize_));
                this->visualState_ = TileVisualState::flag;
                break;
            }
            case TileVisualState::flag:{
                this->setIcon(QIcon(":/images/question-mark.png"));
                this->setIconSize(QSize(Tile::pixelIconSize_, Tile::pixelIconSize_));
                this->visualState_ = TileVisualState::unsure;
                break;
            }
            case TileVisualState::unsure:{
                this->setIcon(QIcon());
                this->visualState_ = TileVisualState::unclicked;
                break;
            }
            default:{

            }
        }

    }
}

//----------------------------------------------------------------------------------------------------
// Static constants
//----------------------------------------------------------------------------------------------------
const int Tile::pixelSize_ = 22;
const int Tile::pixelIconSize_ = 18;
const std::array<QString, 8> Tile::fontColors_ = {
    QString("blue"),
    QString("green"),
    QString("red"),
    QString("purple"),
    QString("maroon"),
    QString("teal"),
    QString("black"),
    QString("gray")
};