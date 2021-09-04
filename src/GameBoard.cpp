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
      }),
      tiles_(boardSize.rows, std::vector<Tile*>(boardSize.cols, nullptr))
{
    // Create a grid of tiles
    QGridLayout* gridLayout = new QGridLayout(this);
    for(int i = 0; i < boardSize.rows; i++){
        for(int j = 0; j < boardSize.cols; j++){
            this->tiles_[i][j] = new Tile(std::make_pair(i,j), this);
            gridLayout->addWidget(this->tiles_[i][j], i, j);
        }
    }
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->setSpacing(0);

    // Make the necessary signal and slot connections for the tiles
    for(int i = 0; i < boardSize.rows; i++){
        for(int j = 0; j < boardSize.cols; j++){
            // Connect the tiles to each other for revealing empty tiles
            for(const std::pair<int, int>& coordinates : GameBoard::neighbors_){
                int x1 = i + coordinates.first;
                int x2 = j + coordinates.second;
                if(!(x1 < 0 || x1 >= boardSize.rows || x2 < 0 || x2 >= boardSize.cols)){
                    this->connect(this->tiles_[i][j], &Tile::revealEmpty, this->tiles_[x1][x2], &Tile::emptyReveal);
                }
            }

            // Connect the game over signal to the board
            this->connect(this->tiles_[i][j], &Tile::gameOver, this, &GameBoard::gameOver);
        }
    }

    // Fix the size
    this->setFixedSize(this->sizeHint());

    // Start a new game
    this->newGame(mineDensity);
}   

//----------------------------------------------------------------------------------------------------
// Public slots
//----------------------------------------------------------------------------------------------------
void GameBoard::newGame(double mineDensity){
    // Generate a vector of all coordinates
    std::vector<std::pair<int,int>> bombCoordinates;
    for(int i = 0; i < this->boardSize_.rows; i++){
        for(int j = 0; j < this->boardSize_.cols; j++){
            bombCoordinates.push_back(std::make_pair(i,j));
        }
    }

    // Shuffle the vector of coordinates
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(bombCoordinates.begin(), bombCoordinates.end(), std::default_random_engine(seed));

    // Update the mine information
    int numberBombs = (int)(mineDensity * this->boardSize_.rows * this->boardSize_.cols);
    this->bombStats_.totalBombs = numberBombs;
    this->bombStats_.numberRemaining = numberBombs;

    // Clear the existing bomb map
    for(int i = 0; i < this->boardSize_.rows; i++){
        for(int j = 0; j < this->boardSize_.cols; j++){
            this->bombStats_.map[i][j] = false;
        }
    }

    // The first N number of them will be the location of N bombs
    for(int i = 0; i < this->bombStats_.totalBombs; i++){
        this->bombStats_.map[bombCoordinates[i].first][bombCoordinates[i].second] = true;
    }

    // Count the number of neighboring bombs for each tile
    
    Grid<int> bombCounter(this->boardSize_.rows, std::vector<int>(this->boardSize_.cols, 0));
    for(int i = 0; i < this->boardSize_.rows; i++){
        for(int j = 0; j < this->boardSize_.cols; j++){
            bombCounter[i][j] = 0;
            for(const std::pair<int, int>& coordinates : GameBoard::neighbors_){
                int x1 = i + coordinates.first;
                int x2 = j + coordinates.second;
                // If the neighbor coordinate is not out of bounds and it has a bomb, increment the count
                if(!(x1 < 0 || x1 >= this->boardSize_.rows || x2 < 0 || x2 >= this->boardSize_.cols) && this->bombStats_.map[x1][x2]){
                    bombCounter[i][j]++;
                }
            }
        }
    }

    // Reset all the tiles with the bomb information
    for(int i = 0; i < this->boardSize_.rows; i++){
        for(int j = 0; j < this->boardSize_.cols; j++){
            this->tiles_[i][j]->reset(this->bombStats_.map[i][j], bombCounter[i][j]);
        }
    }
}

void GameBoard::gameOver(Coordinates coordinates){
    for(int i = 0; i < this->boardSize_.rows; i++){
        for(int j = 0; j < this->boardSize_.cols; j++){
            if(i != coordinates.first || j != coordinates.second){
                this->tiles_[i][j]->reveal();
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------
// Static constants
//----------------------------------------------------------------------------------------------------
const std::array<std::pair<int, int>, 8> GameBoard::neighbors_ = {
    std::make_pair(-1,-1), std::make_pair(-1,0), std::make_pair(-1,1),
    std::make_pair(0,-1),  /*       x        */  std::make_pair(0,1),
    std::make_pair(1,-1),  std::make_pair(1,0),  std::make_pair(1,1)
};