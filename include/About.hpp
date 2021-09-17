//----------------------------------------------------------------------------------------------------
// File: About.hpp
// Date: 09/16/2021
// Desc: Header file for the About class
//----------------------------------------------------------------------------------------------------
#ifndef ABOUT_H
#define ABOUT_H

// Third party library includes
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

//----------------------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------------------
class About : public QWidget{
	Q_OBJECT
public:
	About(QWidget* parent = nullptr);

private:

};

#endif