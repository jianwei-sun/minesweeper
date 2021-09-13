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
    : QWidget(parent),
      difficulty_(Settings::easyDifficulty),
      difficultyOptions_({
          Settings::easyDifficulty,
          Settings::mediumDifficulty,
          Settings::hardDifficulty,
          Settings::hardDifficulty
      })
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
    QCheckBox* easyCheckBox = new QCheckBox("Easy", difficultySelect);
    gridLayout->addWidget(easyCheckBox, 1, 0);
    easyCheckBox->setChecked(true);
    gridLayout->addWidget(new QLabel(QString::number(Settings::easyDifficulty.rows)), 1, 1);
    gridLayout->addWidget(new QLabel(QString::number(Settings::easyDifficulty.cols)), 1, 2);
    gridLayout->addWidget(new QLabel(QString::number(Settings::easyDifficulty.mines)), 1, 3);

    QCheckBox* mediumCheckBox = new QCheckBox("Medium", difficultySelect);
    gridLayout->addWidget(mediumCheckBox, 2, 0);
    gridLayout->addWidget(new QLabel(QString::number(Settings::mediumDifficulty.rows)), 2, 1);
    gridLayout->addWidget(new QLabel(QString::number(Settings::mediumDifficulty.cols)), 2, 2);
    gridLayout->addWidget(new QLabel(QString::number(Settings::mediumDifficulty.mines)), 2, 3);

    QCheckBox* hardCheckBox = new QCheckBox("Hard", difficultySelect);
    gridLayout->addWidget(hardCheckBox, 3, 0);
    gridLayout->addWidget(new QLabel(QString::number(Settings::hardDifficulty.rows)), 3, 1);
    gridLayout->addWidget(new QLabel(QString::number(Settings::hardDifficulty.cols)), 3, 2);
    gridLayout->addWidget(new QLabel(QString::number(Settings::hardDifficulty.mines)), 3, 3);

    QCheckBox* customCheckBox = new QCheckBox("Custom", difficultySelect);
    gridLayout->addWidget(customCheckBox, 4, 0);

    QSpinBox* heightEdit = new QSpinBox(difficultySelect);
    heightEdit->setMinimum(1);
    heightEdit->setMaximum(Settings::maxHeight);
    heightEdit->setSingleStep(1);
    heightEdit->setValue(Settings::hardDifficulty.rows);

    QSpinBox* widthEdit = new QSpinBox(difficultySelect);
    widthEdit->setMinimum(1);
    widthEdit->setMaximum(Settings::maxWidth);
    widthEdit->setSingleStep(1);
    widthEdit->setValue(Settings::hardDifficulty.cols);

    QSpinBox* minesEdit = new QSpinBox(difficultySelect);
    minesEdit->setMinimum(1);
    minesEdit->setMaximum(Settings::maxHeight * Settings::maxWidth);
    minesEdit->setSingleStep(1);
    minesEdit->setValue(Settings::hardDifficulty.mines);

    gridLayout->addWidget(heightEdit, 4, 1);
    gridLayout->addWidget(widthEdit, 4, 2);
    gridLayout->addWidget(minesEdit, 4, 3);

    QButtonGroup* buttonGroup = new QButtonGroup(difficultySelect);
    buttonGroup->setExclusive(true);
    buttonGroup->addButton(easyCheckBox, 0);
    buttonGroup->addButton(mediumCheckBox, 1);
    buttonGroup->addButton(hardCheckBox, 2);
    buttonGroup->addButton(customCheckBox, 3);

    // Create the pushbuttons
    QWidget* buttons = new QWidget(this);
    QHBoxLayout* buttonsLayout = new QHBoxLayout(buttons);

    QPushButton* newGame = new QPushButton("New Game", buttons);
    this->connect(newGame, &QPushButton::clicked, [=](void){
        // Get the difficulty selected from the checkbox
        int id = buttonGroup->checkedId();
        if(id == 3){
            this->difficultyOptions_[id] = DIFFICULTY{heightEdit->value(), widthEdit->value(), minesEdit->value()};
        }
        DIFFICULTY selectedDifficulty = this->difficultyOptions_[id];

        // If a new difficulty is not selected, or the custom difficulty just differs in the number of bombs, then a soft reset suffices
        if(selectedDifficulty == this->difficulty_ 
           || ((id == 3) && (selectedDifficulty.rows == this->difficulty_.rows) && (selectedDifficulty.cols == this->difficulty_.cols))){
            this->difficulty_ = selectedDifficulty;
            emit this->softReset();
        } else{
            this->difficulty_ = selectedDifficulty;
            emit this->hardReset();
        }

        // Hide the window
        this->hide();
    });

    QPushButton* cancel = new QPushButton("Cancel", buttons);
    this->connect(cancel, &QPushButton::clicked, this, &QWidget::hide);

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
// Public functions
//----------------------------------------------------------------------------------------------------
const DIFFICULTY& Settings::getDifficulty(void){
    return this->difficulty_;
}

//----------------------------------------------------------------------------------------------------
// Static constants
//----------------------------------------------------------------------------------------------------
const DIFFICULTY Settings::easyDifficulty = {9, 9, 10};
const DIFFICULTY Settings::mediumDifficulty = {16, 16, 40};
const DIFFICULTY Settings::hardDifficulty = {16, 30, 99};

const int Settings::maxHeight = 30;
const int Settings::maxWidth = 50;