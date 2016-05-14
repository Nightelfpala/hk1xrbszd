
#include <QVBoxLayout>

#include <iostream>

#include "ui_parts.h"

#define UI_REG_HEIGHT 60

using namespace std;

regDisplay::regDisplay(int _meret, const std::string &nev, QWidget *parent) : QFrame(parent), name(nev), meret(_meret)
{
	setFixedSize(  200, UI_REG_HEIGHT );
	valueVec.resize(meret, 0);
	valueLabel.resize(meret, NULL);
	//valueLabel.resize(meret);
	
	QFont nameFont( "Arial", 16);
	QFont displayFont( "Arial", 12);
	
	gridLayout = new QGridLayout(this);
	nameLabel = new QLabel(this);
	
	nameLabel -> setFont(nameFont);
	//nameLabel -> setGeometry(20, 20, 400, 200);
	nameLabel -> setFixedSize( 80, 20 );
	nameLabel -> setAlignment(Qt::AlignCenter);
	nameLabel -> setText( QString::fromStdString( name ));
	
	gridLayout -> addWidget(nameLabel, 0, 0, 0, -1, Qt::AlignTop);
	//gridLayout -> addWidget(nameLabel, 0, 0, meret, 0);
	
	for (int i = 0; i < meret; ++i)
	{
		valueLabel[i] = new QLabel(this);
		
		valueLabel[i] -> setStyleSheet("QLabel { background-color : white; color : black; }");
		valueLabel[i] -> setTextInteractionFlags(Qt::TextSelectableByMouse);	// kijelolhetove (masolhatova) teszi a szoveget
		valueLabel[i] -> setFont(displayFont);
		
		//valueLabel[i] -> setGeometry(20, 20, 360, 120);
		valueLabel[i] -> setFixedSize( 40, 20 );
		valueLabel[i] -> setAlignment(Qt::AlignCenter);
		
		//gridLayout -> addWidget( valueLabel[i], disRow, i);
		gridLayout -> addWidget( valueLabel[i], 1, i);
	}
	
	setLayout(gridLayout);
	setFrameShape( QFrame::Box );	// fekete keret
}

regDisplay::~regDisplay()
{
	// null
}

int regDisplay::size() const
{
	return meret;
}

void regDisplay::setValues(const std::vector<AP_UC> &val)
{
	//cout << "vL.size(): " << valueLabel.size() << endl;
	unsigned int to = ( meret < val.size() ? meret : val.size() );
	for (int i = 0; i < to; ++i)
	{
		//cout << i << " / " << meret <<  endl;
		valueVec[i] = val[i];
		
		/*
		//cout << i << "-" << (int)val[i] << "xx" << endl;
		cout << (int)valueVec[i] << "\t" << (QString::number( (int)valueVec[i] )).toStdString() << endl;
		cout << "ptr: " << (valueLabel[i]) << endl;
		if ( valueLabel[i] == NULL )
		{
			cout << "NULL POINTER? WTF " << i << endl;
		} else
		{
			cout << "not null pointer " << i << endl;
		}
		//cout << "kek" << endl;
		*/
		valueLabel[i] -> setText( QString::number( (int)valueVec[i] ));
		//valueLabel[i] -> setText( "12");
		//cout << i << "+" << endl;
	}
}

// -----------------------------------------------

veremDisplay::veremDisplay( const std::string &nev, QWidget *parent = 0 ) : QFrame(parent), name(nev)
{
	setFixedSize( 800, 110 );
	
	QFont nameFont( "Arial", 16);
	//QFont displayFont( "Arial", 12);
	
	nameLabel = new QLabel( this );
	scrollArea = new QScrollArea( this);
	scrollWidget = new QWidget( scrollArea );
	gridLayout = new QGridLayout( this );
	QVBoxLayout *mainLayout = new QVBoxLayout( this );
	
	nameLabel -> setFont( nameFont );
	nameLabel -> setFixedSize( 80, 20 );
	nameLabel -> setAlignment(Qt::AlignCenter);
	nameLabel -> setText( QString::fromStdString( name ));
	
	mainLayout -> addWidget( nameLabel, Qt::AlignTop );
	
	mainLayout -> addWidget( scrollArea );
	scrollArea -> setWidget( scrollWidget );
	scrollArea -> setFrameShape(QFrame::NoFrame);
	
	scrollWidget -> setLayout( gridLayout );
//	scrollWidget -> setFixedSize( 780, 50 );
	
	setLayout( mainLayout );
	setFrameShape( QFrame::Box );	// fekete keret
	
	valueVec.resize(0);
	valueLabel.resize(0);
	kiegVec.resize(0);
	kiegLabel.resize(0);
}

veremDisplay::~veremDisplay()
{
	// null
}

int veremDisplay::size() const
{
	return valueVec.size();
}

void veremDisplay::updateValues(const std::vector<AP_UC> &vals)
{
	unsigned int prevsize = valueLabel.size();
	//cout << "psize newsize: " << prevsize << "\t" << vals.size() << endl;
	if ( vals.size() < valueLabel.size() )
	{
		for (unsigned int i = valueLabel.size() - 1; i >= vals.size(); --i)
		{
			gridLayout -> removeWidget( valueLabel[i] );
			delete valueLabel[i];
		}
	}
	valueLabel.resize( vals.size(), NULL);
	valueVec = vals;
	if (prevsize < vals.size() )
	{
		//cout << "psize newsize: " << prevsize << "\t" << vals.size() << "\t" << valueLabel.size() << endl;
		QFont displayFont( "Arial", 12);
		for (unsigned int i = prevsize; i < valueLabel.size(); ++i)
		{
			//cout << "new " << i << endl;
			valueLabel[i] = new QLabel( this );
			if ( (valueLabel[i] == NULL) )
			{
				//cout << "miert nem new? rossz " << i << endl;
			}
			valueLabel[i] -> setStyleSheet( "QLabel { background-color : white; color : black; }" );
			valueLabel[i] -> setTextInteractionFlags( Qt::TextSelectableByMouse );	// kijelolhetove (masolhatova) teszi a szoveget
			valueLabel[i] -> setFont( displayFont );
			valueLabel[i] -> setFixedSize( 40, 20 );
			valueLabel[i] -> setAlignment(Qt::AlignCenter);
			
			//cout << "adding " << i << "\tptrval: " << (valueLabel[i] == NULL) << endl;
			gridLayout -> addWidget( valueLabel[i], 1, i, Qt::AlignBottom);
		}
	}
//	cout << endl << "feltolt" << endl;
	for (unsigned int i = 0; i < valueLabel.size(); ++i)
	{
		/*
//		cout << "pre:\t" << i << ". val: " << (int)valueVec[i] << "\t" << (QString::number( (int)valueVec[i] )).toStdString() << endl;
		if ( (valueLabel[i] == NULL) )
		{
			//cout << i << " veremDisplay:\tNULLPTR" << endl;
		} else
		{
			//cout << i << "\tveremDisplay:\t van ptr" << endl;
			valueLabel[i] -> setText( QString::number( (int)valueVec[i] ));
		}
		*/
		valueLabel[i] -> setText( QString::number( (int)valueVec[i] ));
		//valueLabel[i] -> setText( "abc");
		//cout << i << ". val: " << (int)valueVec[i] << endl;
	}
	//scrollWidget -> setFixedSize( 45 * valueLabel.size(), 45 );	// ezt eleg, ha a kiegeszitoszoveg csinalja, az nagyobbra allitja
}

void veremDisplay::updateKieg(const std::vector<std::string> &kiegs)
{
	unsigned int prevsize = kiegLabel.size();
	if ( kiegs.size() < kiegLabel.size() )
	{
		for (unsigned int i = kiegLabel.size() - 1; i >= kiegs.size(); --i)
		{
			gridLayout -> removeWidget( kiegLabel[i] );
			delete kiegLabel[i];
		}
	}
	kiegLabel.resize( kiegs.size(), NULL );
	kiegVec = kiegs;
	if (prevsize < kiegs.size() )
	{
		QFont displayFont( "Arial", 12);
		for (unsigned int i = prevsize; i < kiegLabel.size(); ++i)
		{
			kiegLabel[i] = new QLabel( this );
			kiegLabel[i] -> setStyleSheet( "QLabel { color : black; }" );
			kiegLabel[i] -> setFont( displayFont );
			kiegLabel[i] -> setFixedSize( 40, 20 );
			kiegLabel[i] -> setAlignment(Qt::AlignCenter);
			
			gridLayout -> addWidget( kiegLabel[i], 0, i, Qt::AlignTop);
		}
	}
	for (unsigned int i = 0; i < kiegLabel.size(); ++i)
	{
		kiegLabel[i] -> setText( QString::fromStdString( kiegVec[i] ));
	}
	scrollWidget -> setFixedSize( 45 * kiegLabel.size(), 45 );
}

// ------------------------

flagDisplay::flagDisplay( const std::string &nev, QWidget *parent = 0) : QFrame(parent), name(nev), flag(0)
{
	setFixedSize(UI_REG_HEIGHT, UI_REG_HEIGHT);
	setFrameShape( QFrame::Box );
	
	QFont nameFont( "Arial", 16);
	QFont displayFont( "Arial", 12);
	QVBoxLayout *mainLayout = new QVBoxLayout( this );
	nameLabel = new QLabel( this );
	valueLabel = new QLabel( this );
	
	nameLabel -> setFont( nameFont );
	nameLabel -> setFixedSize( 40, 20 );
	nameLabel -> setAlignment(Qt::AlignCenter);
	nameLabel -> setText( QString::fromStdString( name ));
	
	valueLabel -> setDisabled( true );
	valueLabel -> setStyleSheet( "QLabel { background-color : white; color : black; }" );
	valueLabel -> setTextInteractionFlags( Qt::TextSelectableByMouse );	// kijelolhetove (masolhatova) teszi a szoveget
	valueLabel -> setFont( displayFont );
	valueLabel -> setFixedSize( 40, 20 );
	valueLabel -> setAlignment(Qt::AlignCenter);
	
	mainLayout -> addWidget( nameLabel, Qt::AlignTop );
	mainLayout -> addWidget( valueLabel, Qt::AlignCenter );
}

flagDisplay::~flagDisplay()
{
	// null
}

bool flagDisplay::getFlag() const
{
	return flag;
}

void flagDisplay::setFlag(bool b)
{
	flag = b;
	valueLabel -> setText( QString::number( b ) );
}
