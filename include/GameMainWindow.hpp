//----------------------------------------------------------------------------------------------------
// File: GameMainWindow.hpp
// Date: 09/03/2021
// Desc: Header file for the GameMainWindow class
//----------------------------------------------------------------------------------------------------
#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

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
#include "About.hpp"
#include "Settings.hpp"

//----------------------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------------------
class GameMainWindow : public QMainWindow{
	Q_OBJECT
public:
	GameMainWindow(QWidget* parent = nullptr);

public slots:
	void softReset(void);
	void hardReset(void);

private:
	QVBoxLayout* centralLayout_;
	ControlPanel* controlPanel_;
	GameBoard* gameBoard_;

	std::unique_ptr<About> about_;
	std::unique_ptr<Settings> settings_;
	const DIFFICULTY& difficulty_;
};

#endif