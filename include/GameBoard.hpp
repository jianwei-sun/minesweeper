//----------------------------------------------------------------------------------------------------
// File: GameBoard.hpp
// Date: 08/22/2021
// Desc: Header file for the GameBoard class
//----------------------------------------------------------------------------------------------------
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

// Standard library includes
#include <array>
#include <vector>
#include <utility>
#include <random>
#include <chrono>

// Third party library includes
#include <QWidget>
#include <QGridLayout>

// Project-specific includes
#include "Tile.hpp"

//----------------------------------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------------------------------
template<class T>
using Grid = std::vector<std::vector<T>>;

typedef struct T_BOARD_SIZE{
	int rows;
	int cols;
} BOARD_SIZE;

typedef struct T_BOMB_STATS{
	int totalBombs;
	int numberFlags;
	Grid<bool> map;
} BOMB_STATS;

//----------------------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------------------
class GameBoard : public QWidget{
	Q_OBJECT
public:
	GameBoard(const BOARD_SIZE&, QWidget* parent = nullptr);

public slots:
	void reset(int);
	void gameOver(Coordinates);

signals:
	void numberFlagsChanged(int);
	void gameStarted(void);

private:
	BOARD_SIZE boardSize_;
	BOMB_STATS bombStats_;

	Grid<Tile*> tiles_;

	static const std::array<std::pair<int, int>, 8> neighbors_;
};

#endif