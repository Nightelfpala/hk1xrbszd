
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
	
	QGridLayout *mainLayout = new QGridLayout(this);
	QPushButton *btn = new QPushButton(this);
	
	eax = new regDisplay(4, "eax", this);
	
	connect( btn, SIGNAL( clicked() ), this, SLOT(openFile()));
	btn -> setFixedSize( 150, 150);
	
	mainLayout -> addWidget( eax, 0, 0);
	mainLayout -> addWidget( btn, 0, 1);
	
	displayAllapot();
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

void mainDisplay::displayAllapot()
{
	vector<AP_UC> vecUC(4);
	allapot.get_reg("eax", vecUC);
	
	eax -> setValues( vecUC );
}