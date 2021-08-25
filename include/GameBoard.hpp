//----------------------------------------------------------------------------------------------------
// File: GameBoard.hpp
// Date: 08/22/2021
// Desc: Header file for the GameBoard class
//----------------------------------------------------------------------------------------------------
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

// Standard library includes
#include <vector>
#include <utility>
#include <random>
#include <chrono>

// Third party library includes
#include <QGridLayout>

// Project-specific includes
#include "Tile.hpp"

//----------------------------------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------------------------------
typedef struct T_BOARD_SIZE{
	int rows;
	int cols;
} BOARD_SIZE;

typedef struct T_BOMB_STATS{
	int totalBombs;
	int numberRemaining;
	std::vector<std::vector<bool>> map;
} BOMB_STATS;

//----------------------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------------------
class GameBoard : public QWidget{
	Q_OBJECT
public:
	GameBoard(const BOARD_SIZE&, const double, QWidget* parent = nullptr);

public slots:
	// void reset(void);
	// void gameOver(void);

private:
	BOARD_SIZE boardSize_;
	BOMB_STATS bombStats_;
};

#endif