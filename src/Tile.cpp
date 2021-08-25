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
Tile::Tile(Coordinates coordinates, bool bomb, QWidget* parent)
    : QPushButton(parent),
      coordinates_(coordinates),
      bomb_(bomb),
      neighborBombs_(0),
      revealed_(false),
      visualState_(TileVisualState::unclicked)
{
    // Fix the size
    this->setFixedSize(Tile::pixelSize_, Tile::pixelSize_);
}

void Tile::mousePressEvent(QMouseEvent* mouseEvent){
    if(mouseEvent->button() == Qt::LeftButton){
        this->primaryClicked();
    } else if(mouseEvent->button() == Qt::RightButton){
        this->secondaryClicked();
    }
}

void Tile::primaryClicked(void){
    // Clicking only makes sense if the tile has not yet been revealed
    if(!this->revealed_){
        // End the game if the user clicks on a bomb tile
        if(this->bomb_){
            this->setIcon(QIcon(":/images/mine.png"));
            this->setStyleSheet("background-color:red;");
            emit this->gameOver(this->coordinates_);
        // Otherwise reveal a number and/or propagate neighbors
        } else{
            // Display the number
            if(this->neighborBombs_ > 0){

            // Propagate to neighbors
            } else{

            }
        }

        // Disable the primary and secondary click connect signals
        this->revealed_ = true;
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

const int Tile::pixelSize_ = 22;
const int Tile::pixelIconSize_ = 18;