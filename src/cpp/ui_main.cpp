
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
	//openFile();
	
	QPushButton *btn = new QPushButton(this);
	connect( btn, SIGNAL( clicked() ), this, SLOT(openFile()));
}

mainDisplay::~mainDisplay( )
{
	
}

void mainDisplay::openFile()
{
	QString fileName = QFileDialog::getOpenFileName( this, ".asm file megnyitasa" );
	
	ifstream infile;
	infile.open( fileName.toStdString().c_str() );
	
	while (infile)
	{
		string s;
		getline(infile, s);
		cout << s << endl;
	}
	
	infile.close();
}