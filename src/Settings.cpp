//----------------------------------------------------------------------------------------------------
// File: Settings.cpp
// Date: 09/12/2021
// Desc: Source file for the Settings class
//----------------------------------------------------------------------------------------------------
#include "Settings.hpp"

//----------------------------------------------------------------------------------------------------
// Function: Settings (constructor)
// Desc: constructs the Settings object
//----------------------------------------------------------------------------------------------------
Settings::Settings(QWidget* parent)
    : QWidget(parent)
{
    // Set window properties
    this->setWindowTitle("Settings");
    this->setWindowIcon(QIcon(":/images/mine.png"));
    this->setAttribute(Qt::WA_QuitOnClose, false);
    
    // Create the difficulty select widget
    QWidget* difficultySelect = new QWidget(this);
    QGridLayout* gridLayout = new QGridLayout(difficultySelect);
    gridLayout->setContentsMargins(0,0,0,0);

    // Create the heading for the table
    gridLayout->addWidget(new QLabel("Height"), 0, 1);
    gridLayout->addWidget(new QLabel("Width"), 0, 2);
    gridLayout->addWidget(new QLabel("Mines"), 0, 3);

    // Create the difficulty options
    QCheckBox* easyMode = new QCheckBox("Easy", difficultySelect);
    gridLayout->addWidget(easyMode, 1, 0);
    gridLayout->addWidget(new QLabel(QString::number(Settings::easyDifficulty.rows)), 1, 1);
    gridLayout->addWidget(new QLabel(QString::number(Settings::easyDifficulty.cols)), 1, 2);
    gridLayout->addWidget(new QLabel(QString::number(Settings::easyDifficulty.mines)), 1, 3);

    QCheckBox* mediumMode = new QCheckBox("Medium", difficultySelect);
    gridLayout->addWidget(mediumMode, 2, 0);
    gridLayout->addWidget(new QLabel(QString::number(Settings::mediumDifficulty.rows)), 2, 1);
    gridLayout->addWidget(new QLabel(QString::number(Settings::mediumDifficulty.cols)), 2, 2);
    gridLayout->addWidget(new QLabel(QString::number(Settings::mediumDifficulty.mines)), 2, 3);

    QCheckBox* hardMode = new QCheckBox("Hard", difficultySelect);
    gridLayout->addWidget(hardMode, 3, 0);
    gridLayout->addWidget(new QLabel(QString::number(Settings::hardDifficulty.rows)), 3, 1);
    gridLayout->addWidget(new QLabel(QString::number(Settings::hardDifficulty.cols)), 3, 2);
    gridLayout->addWidget(new QLabel(QString::number(Settings::hardDifficulty.mines)), 3, 3);

    QCheckBox* customMode = new QCheckBox("Custom", difficultySelect);
    gridLayout->addWidget(customMode, 4, 0);
    QLineEdit* heightEdit = new QLineEdit("", difficultySelect);
    QLineEdit* widthEdit = new QLineEdit("", difficultySelect);
    QLineEdit* minesEdit = new QLineEdit("", difficultySelect);
    gridLayout->addWidget(heightEdit, 4, 1);
    gridLayout->addWidget(widthEdit, 4, 2);
    gridLayout->addWidget(minesEdit, 4, 3);

    // Create the pushbuttons
    QWidget* buttons = new QWidget(this);
    QHBoxLayout* buttonsLayout = new QHBoxLayout(buttons);

    QPushButton* newGame = new QPushButton("New Game", buttons);

    QPushButton* cancel = new QPushButton("Cancel", buttons);

    buttonsLayout->addWidget(newGame);
    buttonsLayout->addWidget(cancel);

    // Create the overall layout of the widget
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(difficultySelect);
    mainLayout->addWidget(buttons);

    // Set the widget to have a fixed size
    this->setFixedSize(this->minimumSize());
}

//----------------------------------------------------------------------------------------------------
// Static constants
//----------------------------------------------------------------------------------------------------
const DIFFICULTY Settings::easyDifficulty = {9, 9, 10};
const DIFFICULTY Settings::mediumDifficulty = {16, 16, 40};
const DIFFICULTY Settings::hardDifficulty = {16, 30, 99};