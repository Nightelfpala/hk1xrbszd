
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
	setMinimumSize( 800, 600 );
	
	QGridLayout *mainLayout = new QGridLayout(this);
	QPushButton *btn = new QPushButton(this);
	
	eax = new regDisplay(4, "eax", this);
	ebx = new regDisplay(4, "ebx", this);
	ecx = new regDisplay(4, "ecx", this);
	edx = new regDisplay(4, "edx", this);
	
	valtozok = new veremDisplay("valtozok", this);
	verem = new veremDisplay("verem", this);
	
	//connect( btn, SIGNAL( clicked() ), this, SLOT(openFile()));
	connect( btn, SIGNAL( clicked() ), this, SLOT(displayAllapot()));
	btn -> setFixedSize( 100, 100);
	
	mainLayout -> addWidget( eax, 0, 0);
	mainLayout -> addWidget( ebx, 0, 1);
	mainLayout -> addWidget( ecx, 1, 0);
	mainLayout -> addWidget( edx, 1, 1);
	mainLayout -> addWidget( valtozok, 2, 0, 1, 4);
	mainLayout -> addWidget( verem, 3, 0, 1, 4);
	
	mainLayout -> addWidget( btn, 4, 0);
	
	
	mainWidget -> setLayout( mainLayout );
	
	displayAllapot();
	
	openFile();
	cout << "constr vege" << endl;
}

mainDisplay::~mainDisplay( )
{
	if ( eParser )
	{
		delete eParser;
	}
	cout << "destr vege" << endl;
}

void mainDisplay::openFile()
{
	QString fileName = QFileDialog::getOpenFileName( this, ".asm file megnyitasa" );
	
	if ( !fileName.isEmpty() )
	{
		ifstream infile;
		infile.open( fileName.toStdString().c_str() );
		
		if ( eParser )
		{
			delete eParser;
			cout << "removing" << endl;
		}
		eParser = new elsoparseParser(infile);
		
		try
		{
			cout << "1" << endl;
			eParser -> completeParse();
			cout << "2" << endl;
			
			/*
			utasitasok = eParser.get_utasitasok();
			map<string, int> valtkezdet = eParser.get_valtozokezdet();
			ugrocimkek = eParser.get_ugrocimke();
			vector<AP_UC> valtozok = eParser.get_valtozok();
			
			for ( map<string, int>::iterator it = valtkezdet.begin(); it != valtkezdet.end(); ++it)
			{
				cout << it->first << " " << it->second << endl;
			}
			*/
			
			//allapot.init(valtkezdet, valtozok);
			
			//displayAllapot();
			
		} catch (elsoparseParser::Exceptions ex)
		{
			QMessageBox msg;
			msg.setWindowTitle( QString::fromUtf8(" ") );
			msg.setText( QString::fromUtf8("Nem történt fájlmegnyitás"));
			msg.exec();
		} catch (...)
		{
			try
			{
				throw;
			} catch (std::exception ex)
			{
				cout << "std except: " << ex.what() << endl;
			} catch (...)
			{
				cout << "other exception" << endl;
			}
		}
		
		infile.close();
	}
	cout << "segfault nincs" << endl;
}

void mainDisplay::interpretNext()
{
	
}

void mainDisplay::displayAllapot()
{
	vector<AP_UC> vecUC(4);
	
	for ( int i = 0; i < 4; ++i)
	{
		vecUC[i] = 3 - i + i * i;
	}
	eax -> setValues( vecUC );
	
	/*
	allapot.get_reg("eax", vecUC);
	eax -> setValues( vecUC );
	
	
	allapot.get_reg("ebx", vecUC);
	ebx -> setValues( vecUC );
	
	allapot.get_reg("ecx", vecUC);
	ecx -> setValues( vecUC );
	
	allapot.get_reg("edx", vecUC);
	edx -> setValues( vecUC );
	
	
	
	vector<AP_UC> longVecUC;
	vector<string> vectorStr;
	
	allapot.valtozo_vector( longVecUC );
	allapot.elso_valtozok( vectorStr );
	valtozok -> updateValues( longVecUC );
	valtozok -> updateKieg( vectorStr);
	
	allapot.verem_vector( longVecUC );
	allapot.vec_pointerek( vectorStr );
	verem -> updateValues( longVecUC );
	verem -> updateKieg( vectorStr);
	*/
	
}