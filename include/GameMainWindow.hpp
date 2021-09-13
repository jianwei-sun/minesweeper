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
#include <QVBoxLayout>

// Project-specific includes
#include "ControlPanel.hpp"
#include "GameBoard.hpp"
#include "Settings.hpp"

//----------------------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------------------
class GameMainWindow : public QMainWindow{
	Q_OBJECT
public:
	GameMainWindow(QWidget* parent = nullptr);

public slots:
	void reset(void);

private:
	ControlPanel* controlPanel_;
	GameBoard* gameBoard_;
	std::unique_ptr<Settings> settings_;

	static const int numberRows_;
	static const int numberColumns_;
	static const double mineDensity_;
};

#endif