//----------------------------------------------------------------------------------------------------
// File: main.cpp
// Date: 8/22/2021
// Desc: Top level main source file for the minesweeper game
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------------------------------
// Third party library includes
#include <QApplication>
#include <Windows.h>

// Project-specific includes
#include "GameMainWindow.hpp"

//----------------------------------------------------------------------------------------------------
// Main program structure
//----------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
    // Set scaling for high-DPI monitors
    SetProcessDPIAware();
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Setup the GUI
    std::unique_ptr<QApplication> app = std::make_unique<QApplication>(argc, argv);
    std::unique_ptr<GameMainWindow> gameMainWindow = std::make_unique<GameMainWindow>();
    gameMainWindow->show();

    // Execute the main GUI event loop, which is a blocking call
    return app->exec();
}