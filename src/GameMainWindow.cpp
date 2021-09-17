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
      gameBoard_(nullptr),
      about_(std::make_unique<About>()),
      settings_(std::make_unique<Settings>()), // Use a unique_ptr because Settings does not have a parent to call its destructor
      difficulty_(this->settings_->getDifficulty())
{
    // Set window properties
    this->setWindowTitle("Minesweeper");
    this->setWindowIcon(QIcon(":/images/mine.png"));

    // Add a settings menu
    QAction* newGameAction = new QAction("&New Game", this);
    newGameAction->setShortcut(tr("CTRL+N"));

    QAction* aboutAction = new QAction("About", this);
    QAction* adjustDifficultyAction = new QAction("Settings", this);

    QAction* quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(tr("CTRL+Q"));

    QMenu* settingsMenu = this->menuBar()->addMenu("Game");
    settingsMenu->addAction(newGameAction);
    settingsMenu->addSeparator();
    settingsMenu->addAction(aboutAction);
    settingsMenu->addAction(adjustDifficultyAction);
    settingsMenu->addSeparator();
    settingsMenu->addAction(quitAction);

    // Connect the menu action signals
    this->connect(newGameAction, &QAction::triggered, this, &GameMainWindow::softReset);
    this->connect(aboutAction, &QAction::triggered, [this](){
        this->about_->show();
    });
    this->connect(adjustDifficultyAction, &QAction::triggered, [this](){
        this->settings_->show();
    });
    this->connect(quitAction, &QAction::triggered, qApp, QApplication::quit);

    // Create a central widget for adding the children widgets
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Add the game board underneath
    this->centralLayout_ = new QVBoxLayout(centralWidget);
    this->centralLayout_->addWidget(this->controlPanel_);

    // Connect the signals and slots of the children widgets
    this->connect(this->controlPanel_, &ControlPanel::newGame, this, &GameMainWindow::softReset);
    this->connect(this->settings_.get(), &Settings::softReset, this, &GameMainWindow::softReset);
    this->connect(this->settings_.get(), &Settings::hardReset, this, &GameMainWindow::hardReset);

    // Set the main layout of the QMainWindow to be fixed
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    // Instantiate a new game board
    this->hardReset();   
}

//----------------------------------------------------------------------------------------------------
// Public slots
//----------------------------------------------------------------------------------------------------
void GameMainWindow::softReset(void){
    // A soft reset only resets the bombs' positions or quantity
    this->controlPanel_->reset(this->difficulty_.mines);
    this->gameBoard_->reset(this->difficulty_.mines);
}

void GameMainWindow::hardReset(void){
    // A hard reset creates a new instance of GameBoard, which allows it to be of a different size
    if(this->gameBoard_){
        this->gameBoard_->disconnect();
        this->centralLayout_->removeWidget(this->gameBoard_);
        delete this->gameBoard_;
    }

    // Create and connect a new instance 
    this->gameBoard_ = new GameBoard(BOARD_SIZE{this->difficulty_.rows, this->difficulty_.cols}, this);
    this->centralLayout_->addWidget(this->gameBoard_);
    this->connect(this->gameBoard_, &GameBoard::gameStarted, this->controlPanel_, &ControlPanel::startTimer);
    this->connect(this->gameBoard_, &GameBoard::numberFlagsChanged, this->controlPanel_, &ControlPanel::updateNumberFlags);
    this->connect(this->gameBoard_, &GameBoard::gameOver, this->controlPanel_, &ControlPanel::gameOver);

    // Add the mines
    this->softReset();
}