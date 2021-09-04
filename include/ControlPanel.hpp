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

// Project-specific includes

//----------------------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------------------
class ControlPanel : public QWidget{
	Q_OBJECT
public:
	ControlPanel(QWidget* parent = nullptr);

public slots:
	void reset(void);

signals:
	void newGame(void);

private:

	static const int smileyButtonSize_;
	static const int smileyIconSize_;
};

#endif