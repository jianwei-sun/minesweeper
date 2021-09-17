//----------------------------------------------------------------------------------------------------
// File: About.cpp
// Date: 09/16/2021
// Desc: Source file for the About class
//----------------------------------------------------------------------------------------------------
#include "About.hpp"

//----------------------------------------------------------------------------------------------------
// Function: About (constructor)
// Desc: constructs the About object
//----------------------------------------------------------------------------------------------------
About::About(QWidget* parent)
    : QWidget(parent)
{
    // Set window properties
    this->setWindowTitle("About");
    this->setWindowIcon(QIcon(":/images/mine.png"));
    this->setAttribute(Qt::WA_QuitOnClose, false);

    // Create the credit labels
    QLabel* title = new QLabel("Minesweeper", this);
    title->setStyleSheet("font-size: 18px; font-weight: bold;");
    title->setAlignment(Qt::AlignCenter);

    QLabel* creditsLabel = new QLabel(
        "<br>Created by <a href=\"https://jianwei-sun.github.io/\">Jianwei Sun</a>.<br><a href=\"https://github.com/jianwei-sun/minesweeper\">Source code</a> hosted on Github.<br>Built with C++ and Qt. All icons from Flaticon.<br><br>"
    , this);
    creditsLabel->setTextFormat(Qt::RichText);
    creditsLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    creditsLabel->setOpenExternalLinks(true);
    creditsLabel->setAlignment(Qt::AlignCenter);

    // Create the close button
    QPushButton* button = new QPushButton("Okay", this);
    this->connect(button, &QPushButton::clicked, this, &QWidget::hide);
    QWidget* buttonWidget = new QWidget(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(0,0,0,0);
    buttonLayout->addStretch();
    buttonLayout->addWidget(button);
    buttonLayout->addStretch();

    // Add the widgets to the main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(title);
    mainLayout->addWidget(creditsLabel);
    mainLayout->addWidget(buttonWidget);

    // Set the widget to have a fixed size
    this->setFixedSize(this->sizeHint());
}