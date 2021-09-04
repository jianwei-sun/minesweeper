//----------------------------------------------------------------------------------------------------
// File: GameMainWindow.hpp
// Date: 09/03/2021
// Desc: Header file for the GameMainWindow class
//----------------------------------------------------------------------------------------------------
#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

// Standard library includes

// Third party library includes
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QWidget>
#include <QLCDNumber>
#include <QIcon>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

// Project-specific includes
#include "GameBoard.hpp"

//----------------------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------------------
class GameMainWindow : public QMainWindow{
	Q_OBJECT
public:
	GameMainWindow(QWidget* parent = nullptr);

public slots:
	void newGame(void);

private:
	GameBoard* gameBoard_;

	static const int smileyButtonSize_;
	static const int smileyIconSize_;
	static const int numberRows_;
	static const int numberColumns_;
	static const double mineDensity_;
};

#endif