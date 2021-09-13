//----------------------------------------------------------------------------------------------------
// File: Settings.hpp
// Date: 09/12/2021
// Desc: Header file for the Settings class
//----------------------------------------------------------------------------------------------------
#ifndef SETTINGS_H
#define SETTINGS_H

// Standard library includes
#include <array>

// Third party library includes
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QButtonGroup>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

//----------------------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------------------
typedef struct T_DIFFICULTY{
	int rows;
	int cols;
	int mines;

	bool operator==(const T_DIFFICULTY& other){
		return (this->rows == other.rows) && (this->cols == other.cols) && (this->mines == other.mines);
	}

} DIFFICULTY;

class Settings : public QWidget{
	Q_OBJECT
public:
	Settings(QWidget* parent = nullptr);
	const DIFFICULTY& getDifficulty(void);

signals:
	void softReset(void);
	void hardReset(void);

private:
	DIFFICULTY difficulty_;
	std::array<DIFFICULTY, 4> difficultyOptions_;

	static const DIFFICULTY easyDifficulty;
	static const DIFFICULTY mediumDifficulty;
	static const DIFFICULTY hardDifficulty;

	static const int maxHeight;
	static const int maxWidth;
};

#endif