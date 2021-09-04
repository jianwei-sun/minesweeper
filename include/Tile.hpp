//----------------------------------------------------------------------------------------------------
// File: Tile.hpp
// Date: 08/22/2021
// Desc: Header file for the Tile class
//----------------------------------------------------------------------------------------------------
#ifndef TILE_H
#define TILE_H

// Standard library includes
#include <utility>
#include <array>
#include <vector>

// Third party library includes
#include <QPushButton>
#include <QMouseEvent>
#include <QString>
#include <QIcon>

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

typedef std::pair<int, int> Coordinates;

//----------------------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------------------
class Tile : public QPushButton{
	Q_OBJECT
public:
	Tile(Coordinates, bool, int, QWidget* parent = nullptr);
	void reveal(void);

protected:
	void mousePressEvent(QMouseEvent*) override;

public slots:
	void emptyReveal(void);

signals:
	void revealEmpty(void);
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
	static const std::array<QString, 8> fontColors_;
};

#endif