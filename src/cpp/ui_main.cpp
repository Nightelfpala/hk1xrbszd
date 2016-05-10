
#include <QFileDialog>
#include <QMessageBox>

#include "ui_main.h"
#include "utils.h"

#include "elsoparseParser.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

mainDisplay::mainDisplay( QWidget *parent ) : QMainWindow(parent)
{
	setWindowTitle( QString::fromUtf8("Assembly szimuláció") );
	
	QWidget *mainWidget = new QWidget( this );
	setCentralWidget(mainWidget);
	//openFile();
	setFixedSize( 800, 600 );
	
	QGridLayout *mainLayout = new QGridLayout(this);
	QPushButton *btn = new QPushButton(this);
	
	eax = new regDisplay(4, "eax", this);
	ebx = new regDisplay(4, "ebx", this);
	ecx = new regDisplay(4, "ecx", this);
	edx = new regDisplay(4, "edx", this);
	
	connect( btn, SIGNAL( clicked() ), this, SLOT(openFile()));
	btn -> setFixedSize( 150, 150);
	
	mainLayout -> addWidget( eax, 0, 0);
	mainLayout -> addWidget( ebx, 0, 1);
	mainLayout -> addWidget( ecx, 1, 0);
	mainLayout -> addWidget( edx, 1, 1);
	
	mainLayout -> addWidget( btn, 2, 0);
	
	
	mainWidget -> setLayout( mainLayout );
	
	displayAllapot();
}

mainDisplay::~mainDisplay( )
{
	
}

void mainDisplay::openFile()
{
	QString fileName = QFileDialog::getOpenFileName( this, ".asm file megnyitasa" );
	
	if ( fileName.isEmpty() )
	{
		ifstream infile;
		infile.open( fileName.toStdString().c_str() );
		
		elsoparseParser eParser(infile);
		
		try
		{
			eParser.completeParse();
			
			
			displayAllapot();
			
		} catch (elsoparseParser::Exceptions ex)
		{
			QMessageBox msg;
			msg.setWindowTitle( QString::fromUtf8(" ") );
			msg.setText( QString::fromUtf8("Nem történt fájlmegnyitás"));
			msg.exec();
		}
		
		infile.close();
	}
}

void mainDisplay::interpretNext()
{
	
}

void mainDisplay::displayAllapot()
{
	vector<AP_UC> vecUC(4);
	
	allapot.get_reg("eax", vecUC);
	eax -> setValues( vecUC );
	
	allapot.get_reg("ebx", vecUC);
	ebx -> setValues( vecUC );
	
	allapot.get_reg("ecx", vecUC);
	ecx -> setValues( vecUC );
	
	allapot.get_reg("edx", vecUC);
	edx -> setValues( vecUC );
}