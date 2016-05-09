
#include <QFileDialog>
#include <QMessageBox>

#include "ui_main.h"
#include "utils.h"

#include "elsoparseParser.h"

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
	nextInstruction = new QLabel(this);
	nextButton = new QPushButton( QString::fromUtf8("Végrehajtás"), controlWidget);
	
	createWidgets();
	{
		openAct = new QAction( QString::fromUtf8("File megnyitása"), this);
		quitAct = new QAction( QString::fromUtf8("Kilépés"), this);
		
		//connect( openAct, SIGNAL( triggered() ), this, SLOT( openFile() ));
		connect( quitAct, SIGNAL( triggered() ), this, SLOT( close() ));
		connect( nextButton, SIGNAL( clicked() ), this, SLOT( interpretNext() ));
		
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
	
	layout -> addWidget(controlWidget, 0, 3, 2, 2);
	
	controlLayout -> addWidget( nextInstruction, 0, 0, 1, 3);
	controlLayout -> addWidget( nextButton, 1, 2, 1, 1);
	
	mainWidget -> setLayout(layout);
	controlWidget -> setLayout(controlLayout);
	
	displayAllapot();
	
	
	openFile();
}

mainDisplay::~mainDisplay( )
{
	
}

void mainDisplay::openFile()
{
	QString fileName = QFileDialog::getOpenFileName( this, tr("File megnyitasa") );
	
	ifstream infile;
	infile.open( fileName.toStdString().c_str() );
	
	cout << "opening file" << endl;
	elsoparseParser elsoParser( infile );
	
	try
	{
		cout << "yep" << endl;
		elsoParser.completeParse();
		cout << "parse done" << endl;
		
		vector<AP_UC> valtozok;
		map<std::string, int> valtozo_kezdetek;
		
		utasitasok = elsoParser.get_utasitasok();
		ugrocimkek = elsoParser.get_ugrocimke();
		valtozo_kezdetek = elsoParser.get_valtozokezdet();
		valtozok = elsoParser.get_valtozok();
		cout << "req done" << endl;
		
		allapot.init( valtozo_kezdetek, valtozok );
		iParser.initAp( &allapot, &ugrocimkek );
		
		allapot.set_kovetkezo( elsoParser.get_elsoutasitas() );
		displayAllapot();
		cout << "done?######################x" << endl;
	} catch ( elsoparseParser::Exceptions ex )
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle( QString::fromUtf8( "Hiba!" ));
		msgBox.setText( QString::fromUtf8("Hiba történt a kezdeti elemzés közben") );
		msgBox.setInformativeText( QString::fromStdString( elsoParser.get_error() ));
		msgBox.exec();
	}
	infile.close();
}

void mainDisplay::interpretNext()
{
	int kov = allapot.get_kovetkezo();
	string kovStr = utasitasok[kov].sor;
	istringstream iStream( kovStr );
	
	try
	{
		iParser.completeParse( iStream, utasitasok[kov].argmeret );
		displayAllapot();
	} catch ( interpretParser::Exceptions ex )
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle( QString::fromUtf8( "Hiba!" ));
		msgBox.setText( QString::fromUtf8("Hiba történt a muvelet vegrehajtasa kozben") );
		msgBox.setInformativeText( QString::fromStdString( iParser.get_error() ));
		msgBox.exec();
	} catch ( Allapot::Exceptions ex)
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle( QString::fromUtf8( "Hiba!" ));
		msgBox.setText( QString::fromUtf8("Hiba történt a muvelet vegrehajtasa kozben") );
		string error;
		switch (ex)
		{
		case Allapot::URES_VEREM:
			error = "Üres veremből pop művelet végrehajtása sikertelen!";
			break;
		case Allapot::TELE_VEREM:
			error = "Nem fér a verembe több változó!";
			break;
		case Allapot::HATARON_KIVULI_VALTOZO:
			error = "Nem érvényes változó hivatkozás!";
			break;
		case Allapot::HATARON_KIVULI_VEREM:
			error = "Nem érvényes verem hivatkozás!";
			break;
		default:
			error = "Ismeretlen hiba történt!";
			break;
		}
		msgBox.setInformativeText( QString::fromStdString( error ));
		msgBox.exec();
	}
}

void mainDisplay::createWidgets()
{
	QFont displayFont( "Arial", 12);
	
	eax = new regDisplay(4, "eax", this );
	ebx = new regDisplay(4, "ebx", this );
	ecx = new regDisplay(4, "ecx", this );
	edx = new regDisplay(4, "edx", this );
	
	valtozok = new veremDisplay( "valtozok", this );
	verem = new veremDisplay( "verem", this );
	
	signFlag = new flagDisplay( "sign", this );
	zeroFlag = new flagDisplay( "zero", this );
	
	nextInstruction -> setStyleSheet( "QLabel { background-color : white; color : black; }" );
	nextInstruction -> setTextInteractionFlags( Qt::TextSelectableByMouse );
	nextInstruction -> setFont( displayFont );
}

void mainDisplay::displayAllapot()
{
	cout << endl << "displayAllapot()" << endl << endl;
	vector<AP_UC> vecUC(4);
	vector<std::string> vecStr;
	bool b;
	
	//cout << "1" << endl;
	
	allapot.get_reg("eax", vecUC);
	//Utils::vec_cout(vecUC, "eax");
	//cout << "a" << vecUC.size() << endl;
	eax -> setValues( vecUC );
	
	allapot.get_reg("ebx", vecUC);
	//Utils::vec_cout(vecUC, "ebx");
	ebx -> setValues( vecUC );
	//cout << "b" << endl;
	
	allapot.get_reg("ecx", vecUC);
	//Utils::vec_cout(vecUC, "ecx");
	ecx -> setValues( vecUC );
	//cout << "c" << endl;
	
	allapot.get_reg("edx", vecUC);
	//Utils::vec_cout(vecUC, "edx");
	edx -> setValues( vecUC );
	//cout << "d" << endl;
	
	allapot.valtozo_vector( vecUC );
	allapot.elso_valtozok( vecStr );
	Utils::vec_cout(vecUC, "valtozok:");
	valtozok -> updateValues( vecUC );
	cout << "valtkieg" << endl;
	valtozok -> updateKieg( vecStr );
	cout << "valt" << endl;
	
	allapot.verem_vector( vecUC );
	allapot.vec_pointerek( vecStr );
	Utils::vec_cout(vecUC, "verem:");
	verem -> updateValues( vecUC );
	verem -> updateKieg( vecStr );
	cout << "verem" << endl;
	
	b = allapot.get_sign();
	signFlag -> setFlag(b);
	cout << "sign" << endl;
	
	b = allapot.get_zero();
	zeroFlag -> setFlag(b);
	cout << "zero" << endl;
	
	if ( nextInstruction )
	{
		nextInstruction -> setText( QString::fromStdString( utasitasok[allapot.get_kovetkezo()].sor ) );
		cout << "NI text setup" << endl;
	} else 
	{
		cout << "NO NEXTINSTRUCTION" << endl;
	}
}

