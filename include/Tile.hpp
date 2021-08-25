//----------------------------------------------------------------------------------------------------
// File: Tile.hpp
// Date: 08/22/2021
// Desc: Header file for the Tile class
//----------------------------------------------------------------------------------------------------
#ifndef TILE_H
#define TILE_H

// Standard library includes
#include <utility>

// Third party library includes
#include <QPushButton>
#include <QMouseEvent>

// Project-specific includes

//----------------------------------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------------------------------
enum class TileVisualState{
	unclicked,
	flag,
	unsure,
	number,
	mine,
	exploded
};

enum class TileUnrevealedStates{
	unclicked,
	flag,
	unsure
};

enum class TileRevealedStates{
	empty,
	exploded
};

typedef std::pair<int, int> Coordinates;

//----------------------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------------------
class Tile : public QPushButton{
	Q_OBJECT
public:
	Tile(Coordinates, bool, QWidget* parent = nullptr);

protected:
	void mousePressEvent(QMouseEvent*) override;

signals:
	void gameOver(Coordinates);

private:
	void primaryClicked(void);
	void secondaryClicked(void);

	const Coordinates coordinates_;

	const bool bomb_;
	const int neighborBombs_;

	bool revealed_;

	TileVisualState visualState_;

	static const int pixelSize_;
	static const int pixelIconSize_;
};

#endif