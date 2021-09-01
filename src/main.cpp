//----------------------------------------------------------------------------------------------------
// File: main.cpp
// Date: 8/22/2021
// Desc: Top level main source file for the minesweeper game
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------------------------------
// Standard libraries includes


// Third party library includes
#include <QApplication>

// Project-specific includes
#include "GameBoard.hpp"

//----------------------------------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
// Main program structure
//----------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
    // Setup the GUI
    std::unique_ptr<QApplication> app = std::make_unique<QApplication>(argc, argv);
    // std::unique_ptr<MainWindow> mainWindow = std::make_unique<MainWindow>();
    // mainWindow->show();
    GameBoard* gameBoard = new GameBoard(BOARD_SIZE{10, 20}, 0.2);
    gameBoard->show();

    // Execute the main GUI event loop, which is a blocking call
    return app->exec();
}