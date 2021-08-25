//----------------------------------------------------------------------------------------------------
// File: GameBoard.cpp
// Date: 08/22/2021
// Desc: Source file for the GameBoard class
//----------------------------------------------------------------------------------------------------
#include "GameBoard.hpp"

//----------------------------------------------------------------------------------------------------
// Function: GameBoard (constructor)
// Desc: constructs the GameBoard object
//----------------------------------------------------------------------------------------------------
GameBoard::GameBoard(const BOARD_SIZE& boardSize, const double mineDensity, QWidget* parent)
    : QWidget(parent),
      boardSize_(boardSize),
      bombStats_(BOMB_STATS{
          (int)(mineDensity * boardSize.rows * boardSize.cols),
          (int)(mineDensity * boardSize.rows * boardSize.cols),
          std::vector<std::vector<bool>>(boardSize.rows, std::vector<bool>(boardSize.cols, false))
      })
{
    // Generate a vector of all coordinates
    std::vector<std::pair<int,int>> bombCoordinates;
    for(int i = 0; i < boardSize.rows; i++){
        for(int j = 0; j < boardSize.cols; j++){
            bombCoordinates.push_back(std::make_pair(i,j));
        }
    }

    // Shuffle the vector of coordinates
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(bombCoordinates.begin(), bombCoordinates.end(), std::default_random_engine(seed));

    // The first N number of them will be the location of N bombs
    for(int i = 0; i < this->bombStats_.totalBombs; i++){
        this->bombStats_.map[bombCoordinates[i].first][bombCoordinates[i].second] = true;
    }

    // Create a grid of tiles
    QGridLayout* gridLayout = new QGridLayout(this);
    for(int i = 0; i < boardSize.rows; i++){
        for(int j = 0; j < boardSize.cols; j++){
            gridLayout->addWidget(new Tile(this->bombStats_.map[i][j], this), i, j);
        }
    }
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->setSpacing(0);

    // Fix the size
    this->setFixedSize(this->minimumSize());
}   