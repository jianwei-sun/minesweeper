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
          Grid<bool>(boardSize.rows, std::vector<bool>(boardSize.cols, false))
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

    // Count the number of neighboring bombs for each tile
    const std::array<std::pair<int, int>, 8> neighbors{
        std::make_pair(-1,-1), std::make_pair(-1,0), std::make_pair(-1,1),
        std::make_pair(0,-1),  /*       x        */  std::make_pair(0,1),
        std::make_pair(1,-1),  std::make_pair(1,0),  std::make_pair(1,1)
    };
    Grid<int> bombCounter_(boardSize.rows, std::vector<int>(boardSize.cols, 0));
    for(int i = 0; i < boardSize.rows; i++){
        for(int j = 0; j < boardSize.cols; j++){
            bombCounter_[i][j] = 0;
            for(const std::pair<int, int>& coordinates : neighbors){
                int x1 = i + coordinates.first;
                int x2 = j + coordinates.second;
                // If the neighbor coordinate is not out of bounds and it has a bomb, increment the count
                if(!(x1 < 0 || x1 >= boardSize.rows || x2 < 0 || x2 >= boardSize.cols) && this->bombStats_.map[x1][x2]){
                    bombCounter_[i][j]++;
                }
            }
        }
    }

    // Create a grid of tiles
    QGridLayout* gridLayout = new QGridLayout(this);
    for(int i = 0; i < boardSize.rows; i++){
        for(int j = 0; j < boardSize.cols; j++){
            gridLayout->addWidget(new Tile(std::make_pair(i,j), this->bombStats_.map[i][j], bombCounter_[i][j], this), i, j);
        }
    }
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->setSpacing(0);

    // Connect the tiles to each other for revealing empty tiles
    for(int i = 0; i < boardSize.rows; i++){
        for(int j = 0; j < boardSize.cols; j++){
            for(const std::pair<int, int>& coordinates : neighbors){
                int x1 = i + coordinates.first;
                int x2 = j + coordinates.second;
                if(!(x1 < 0 || x1 >= boardSize.rows || x2 < 0 || x2 >= boardSize.cols)){
                    this->connect(
                        static_cast<Tile*>(gridLayout->itemAtPosition(i,j)->widget()), 
                        &Tile::revealEmpty, 
                        static_cast<Tile*>(gridLayout->itemAtPosition(x1,x2)->widget()), 
                        &Tile::emptyReveal);
                }
            }
        }
    }

    // Fix the size
    this->setFixedSize(this->minimumSize());
}   