//----------------------------------------------------------------------------------------------------
// File: GameMainWindow.cpp
// Date: 09/03/2021
// Desc: Source file for the GameMainWindow class
//----------------------------------------------------------------------------------------------------
#include "GameMainWindow.hpp"

//----------------------------------------------------------------------------------------------------
// Function: GameMainWindow (constructor)
// Desc: constructs the GameMainWindow object
//----------------------------------------------------------------------------------------------------
GameMainWindow::GameMainWindow(QWidget* parent)
    : QMainWindow(parent),
      controlPanel_(new ControlPanel(this)),
      gameBoard_(new GameBoard(BOARD_SIZE{GameMainWindow::numberRows_, GameMainWindow::numberColumns_}, GameMainWindow::mineDensity_, this))
{
    // Set window properties
    this->setWindowTitle("Minesweeper");
    this->setWindowIcon(QIcon(":/images/mine.png"));

    // Add a settings menu
    QAction* newGameAction = new QAction("&New Game", this);
    newGameAction->setShortcut(tr("CTRL+N"));

    QAction* adjustDifficultyAction = new QAction("Adjust difficulty", this);

    QAction* quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(tr("CTRL+Q"));

    QMenu* settingsMenu = this->menuBar()->addMenu("&Settings");
    settingsMenu->addAction(newGameAction);
    settingsMenu->addSeparator();
    settingsMenu->addAction(adjustDifficultyAction);
    settingsMenu->addSeparator();
    settingsMenu->addAction(quitAction);

    // Connect the settings action signals
    this->connect(newGameAction, &QAction::triggered, this, &GameMainWindow::reset);
    this->connect(quitAction, &QAction::triggered, qApp, QApplication::quit);

    // Create a central widget for adding the children widgets
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Add the game board underneath
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(this->controlPanel_);
    mainLayout->addWidget(this->gameBoard_);

    // Connect the signals and slots of the children widgets
    this->connect(this->controlPanel_, &ControlPanel::newGame, this, &GameMainWindow::reset);

    // Fix the size
    this->setFixedSize(this->sizeHint());    

    // Start a new game
    this->reset();
}

//----------------------------------------------------------------------------------------------------
// Public slots
//----------------------------------------------------------------------------------------------------
void GameMainWindow::reset(void){
    this->controlPanel_->reset();
    this->gameBoard_->reset(GameMainWindow::mineDensity_);
}

//----------------------------------------------------------------------------------------------------
// Static constants
//----------------------------------------------------------------------------------------------------
const int GameMainWindow::numberRows_ = 10;
const int GameMainWindow::numberColumns_ = 20;
const double GameMainWindow::mineDensity_ = 0.2;