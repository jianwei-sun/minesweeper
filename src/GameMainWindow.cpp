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
      gameBoard_(new GameBoard(BOARD_SIZE{GameMainWindow::numberRows_, GameMainWindow::numberColumns_}, this))
{
    // Set window properties
    this->setWindowTitle("Minesweeper");
    this->setWindowIcon(QIcon(":/images/mine.png"));

    // Add a settings menu
    QAction* newGameAction = new QAction("&New Game", this);
    newGameAction->setShortcut(tr("CTRL+N"));

    QAction* adjustDifficultyAction = new QAction("Settings", this);

    QAction* quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(tr("CTRL+Q"));

    QMenu* settingsMenu = this->menuBar()->addMenu("Game");
    settingsMenu->addAction(newGameAction);
    settingsMenu->addSeparator();
    settingsMenu->addAction(adjustDifficultyAction);
    settingsMenu->addSeparator();
    settingsMenu->addAction(quitAction);

    // Connect the settings action signals
    this->connect(newGameAction, &QAction::triggered, this, &GameMainWindow::reset);
    this->connect(adjustDifficultyAction, &QAction::triggered, [this](){
        this->settings_->show();
    });
    this->connect(quitAction, &QAction::triggered, qApp, QApplication::quit);

    // Instantiate the settings widget. Use a unique pointer here because the Settings widget does not have a parent to call its destructor
    this->settings_ = std::make_unique<Settings>();

    // Create a central widget for adding the children widgets
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Add the game board underneath
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(this->controlPanel_);
    mainLayout->addWidget(this->gameBoard_);

    // Connect the signals and slots of the children widgets
    this->connect(this->controlPanel_, &ControlPanel::newGame, this, &GameMainWindow::reset);
    this->connect(this->gameBoard_, &GameBoard::gameStarted, this->controlPanel_, &ControlPanel::startTimer);
    this->connect(this->gameBoard_, &GameBoard::numberFlagsChanged, this->controlPanel_, &ControlPanel::updateNumberFlags);
    this->connect(this->gameBoard_, &GameBoard::gameOver, this->controlPanel_, &ControlPanel::gameOver);

    // Fix the size
    this->setFixedSize(this->sizeHint());    

    // Start a new game
    this->reset();
}

//----------------------------------------------------------------------------------------------------
// Public slots
//----------------------------------------------------------------------------------------------------
void GameMainWindow::reset(void){
    int numberBombs = (int)(GameMainWindow::mineDensity_ * GameMainWindow::numberRows_ * GameMainWindow::numberColumns_);
    this->controlPanel_->reset(numberBombs);
    this->gameBoard_->reset(numberBombs);
}

//----------------------------------------------------------------------------------------------------
// Static constants
//----------------------------------------------------------------------------------------------------
const int GameMainWindow::numberRows_ = 10;
const int GameMainWindow::numberColumns_ = 20;
const double GameMainWindow::mineDensity_ = 0.2;