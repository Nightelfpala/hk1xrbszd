
#include <QFileDialog>
#include <QMessageBox>

#include "ui_main.h"
#include "utils.h"

//#include "elsoparseParser.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

mainDisplay::mainDisplay( )
{
	QWidget *mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);
	
	QFrame *controlWidget = new QFrame(this);
	controlWidget -> setFrameShape( QFrame::Box );
	
	QGridLayout *layout = new QGridLayout(this);
	QGridLayout *controlLayout = new QGridLayout(controlWidget);
	nextInstruction = new QLabel(controlWidget);
	nextButton = new QPushButton( QString::fromUtf8("Végrehajtás"), controlWidget);
	
	createWidgets();
	{
		openAct = new QAction( QString::fromUtf8("File megnyitása"), this);
		quitAct = new QAction( QString::fromUtf8("Kilépés"), this);
		
		//connect( openAct, SIGNAL( triggered() ), this, SLOT( openFile() ));
		connect( quitAct, SIGNAL( triggered() ), this, SLOT( close() ));
		connect( nextButton, SIGNAL( clicked() ), this, SLOT( openFile() ));
		
		fileMenu = menuBar() -> addMenu( tr("File"));
		
		fileMenu -> addAction( openAct );
		fileMenu -> addSeparator();
		fileMenu -> addAction( quitAct );
	}
	
	layout -> addWidget(eax, 0, 0);
	layout -> addWidget(ebx, 0, 1);
	layout -> addWidget(ecx, 1, 0);
	layout -> addWidget(edx, 1, 1);
	
	layout -> addWidget(valtozok, 2, 0, 1, 3);
	layout -> addWidget(verem, 3, 0, 1, 3);
	
	layout -> addWidget(zeroFlag, 0, 2);
	layout -> addWidget(signFlag, 1, 2);
	
	layout -> addWidget(controlWidget, 0, 3, 1, 2);
	
	controlLayout -> addWidget( nextInstruction, 0, 0, 1, 3);
	controlLayout -> addWidget( nextButton, 1, 2, 1, 1);
	
	mainWidget -> setLayout(layout);
	controlWidget -> setLayout(controlLayout);
	
	//displayAllapot();
}

mainDisplay::~mainDisplay( )
{
	
}

void mainDisplay::openFile()
{
	QString fileName = QFileDialog::getOpenFileName( this, tr("File megnyitasa") );
	
	ifstream infile;
	infile.open( fileName.toStdString().c_str() );
	/*
	elsoparseParser elsoParser( infile );
	
	try
	{
		elsoParser.completeParse();
	} catch (  )
	{
		
	}
	*/
	infile.close();
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
}

void mainDisplay::displayAllapot()
{
	vector<AP_UC> vecUC;
	vector<std::string> vecStr;
	bool b;
	
	allapot.get_reg("eax", vecUC);
	eax->setValues( vecUC );
	
	allapot.get_reg("ebx", vecUC);
	ebx->setValues( vecUC );
	
	allapot.get_reg("ecx", vecUC);
	ecx->setValues( vecUC );
	
	allapot.get_reg("edx", vecUC);
	edx->setValues( vecUC );
	
	allapot.valtozo_vector( vecUC );
	allapot.elso_valtozok( vecStr );
	valtozok->updateValues( vecUC );
	valtozok->updateKieg( vecStr );
	
	allapot.verem_vector( vecUC );
	allapot.vec_pointerek( vecStr );
	verem->updateValues( vecUC );
	verem->updateKieg( vecStr );
	
	b = allapot.get_sign();
	signFlag->setFlag(b);
	
	b = allapot.get_zero();
	zeroFlag->setFlag(b);
}
