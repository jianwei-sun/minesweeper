//----------------------------------------------------------------------------------------------------
// File: ControlPanel.hpp
// Date: 09/03/2021
// Desc: Header file for the ControlPanel class
//----------------------------------------------------------------------------------------------------
#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

// Standard library includes

// Third party library includes
#include <QWidget>
#include <QLCDNumber>
#include <QIcon>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTimer>


// Project-specific includes

//----------------------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------------------
class ControlPanel : public QWidget{
	Q_OBJECT
public:
	ControlPanel(QWidget* parent = nullptr);

public slots:
	void reset(int);
	void startTimer(void);
	void gameOver(bool);
	void updateNumberFlags(int);

signals:
	void newGame(void);

private:
	QLCDNumber* minesRemainingDisplay_;
	QLCDNumber* elapsedTimeDisplay_;
	QTimer* timer_;
	int secondsElapsed_;
	int numberBombs_;

	static const int smileyButtonSize_;
	static const int smileyIconSize_;
};

#endif