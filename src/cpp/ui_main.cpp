
#include <QFileDialog>

#include "ui_main.h"

#include <iostream>

mainDisplay::mainDisplay( )
{
	QWidget *mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);
	
	QWidget *controlWidget = new QWidget(this);
	
	QGridLayout *layout = new QGridLayout(this);
	
	createWidgets();
	
	layout -> addWidget(eax, 0, 0);
	layout -> addWidget(ebx, 0, 1);
	layout -> addWidget(ecx, 1, 0);
	layout -> addWidget(edx, 1, 1);
	
	layout -> addWidget(valtozok, 2, 0, 1, 3);
	layout -> addWidget(verem, 3, 0, 1, 3);
	
	layout -> addWidget(zeroFlag, 0, 2);
	layout -> addWidget(signFlag, 1, 2);
	
	layout -> addWidget(controlWidget, 0, 3, 1, 2);
	
	mainWidget -> setLayout(layout);
	
}

mainDisplay::~mainDisplay( )
{
	
}

void mainDisplay::openFile()
{
	std::cout << "asd" << std::endl;
	//QString fileName = QFileDialog::getOpenFileName( this, tr("File megnyitasa") );
	//std::cout << "filename: " << fileName.toStdString() << std::endl;
}

void mainDisplay::createWidgets()
{
	eax = new regDisplay(4, "eax", this );
	ebx = new regDisplay(4, "ebx", this );
	ecx = new regDisplay(4, "ecx", this );
	edx = new regDisplay(4, "edx", this );
	
	valtozok = new veremDisplay( "valtozok", this );
	verem = new veremDisplay( "verem", this );
	
	signFlag = new flagDisplay( "sign", this );
	zeroFlag = new flagDisplay( "zero", this );
	
	openAct = new QAction( QString::fromUtf8("File megnyitása"), this);
	quitAct = new QAction( QString::fromUtf8("Kilépés"), this);
	
	connect( openAct, SIGNAL( triggered() ), this, SLOT( openFile() ));	// TODO FIX DOESNT WORK
	connect( quitAct, SIGNAL( triggered() ), this, SLOT( close() ));
	
	fileMenu = menuBar() -> addMenu( tr("File"));
	
	fileMenu -> addAction( openAct );
	fileMenu -> addSeparator();
	fileMenu -> addAction( quitAct );
}