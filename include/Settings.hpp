//----------------------------------------------------------------------------------------------------
// File: Settings.hpp
// Date: 09/12/2021
// Desc: Header file for the Settings class
//----------------------------------------------------------------------------------------------------
#ifndef SETTINGS_H
#define SETTINGS_H

// Standard library includes

// Third party library includes
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

// Project-specific includes

//----------------------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------------------
typedef struct T_DIFFICULTY{
	int rows;
	int cols;
	int mines;
} DIFFICULTY;

class Settings : public QWidget{
	Q_OBJECT
public:
	Settings(QWidget* parent = nullptr);

private:
	static const DIFFICULTY easyDifficulty;
	static const DIFFICULTY mediumDifficulty;
	static const DIFFICULTY hardDifficulty;
};

#endif