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
GameBoard::GameBoard(const BOARD_SIZE& boardSize, QWidget* parent)
    : QWidget(parent),
      boardSize_(boardSize),
      bombStats_(BOMB_STATS{
          0,
          0,
          0,
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

            // Connect the tile delta signal from the tiles to check the win condition. The condition is if the player reveals the number
            // of tiles equal to the total number less the number of bombs. 
            this->connect(this->tiles_[i][j], &Tile::tileDelta, [this](){
                this->bombStats_.numberRevealedTiles++;
                if(this->bombStats_.numberRevealedTiles == (this->boardSize_.rows * this->boardSize_.cols - this->bombStats_.totalBombs)){
                    this->revealAll();
                    emit this->gameOver(true);
                }
            });

            // Connect the flag state changing signal from the tiles
            this->connect(this->tiles_[i][j], &Tile::flagDelta, [this](int delta){
                this->bombStats_.numberFlags += delta;
                emit this->numberFlagsChanged(this->bombStats_.numberFlags);
            });

            // Connect the game started signal from the tiles
            this->connect(this->tiles_[i][j], &Tile::gameStarted, [this](void){
                emit this->gameStarted();
            });

            // Connect the game over signal to the board
            this->connect(this->tiles_[i][j], &Tile::gameOver, [=](Coordinates coordinates){
                this->revealAllExcept(coordinates);
                emit this->gameOver(false);
            });
        }
    }

    // Fix the size
    this->setFixedSize(this->sizeHint());
}   

//----------------------------------------------------------------------------------------------------
// Public slots
//----------------------------------------------------------------------------------------------------
void GameBoard::reset(int numberBombs){
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
    this->bombStats_.totalBombs = numberBombs;
    this->bombStats_.numberRevealedTiles = 0;
    this->bombStats_.numberFlags = 0;

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

void GameBoard::revealAll(void){
    for(int i = 0; i < this->boardSize_.rows; i++){
        for(int j = 0; j < this->boardSize_.cols; j++){
            this->tiles_[i][j]->reveal();
        }
    }
}

void GameBoard::revealAllExcept(Coordinates coordinates){
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