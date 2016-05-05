
#include <QVBoxLayout>

#include <iostream>

#include "ui_parts.h"

using namespace std;

vectorDisplay::vectorDisplay(int _meret, QWidget *parent, bool kiegSzoveg) : QWidget(parent), meret(_meret), kiegeszitoSzoveg(kiegSzoveg)
{
	int disRow = 2;
	if (kiegeszitoSzoveg) ++disRow;
	
	setFixedSize(  200, 80 );
	valueVec.resize(meret);
	valueLabel.resize(meret);
	if (kiegeszitoSzoveg)
	{
		kiegVec.resize(meret);
		kiegLabel.resize(meret);
	}
	
	QFont nameFont( "Arial", 16);
	QFont displayFont( "Arial", 12);
	
	gridLayout = new QGridLayout(this);
	nameLabel = new QLabel(this);
	
	nameLabel -> setFont(nameFont);
	//nameLabel -> setGeometry(20, 20, 400, 200);
	nameLabel -> setFixedSize( 80, 30 );
	nameLabel -> setAlignment(Qt::AlignCenter);
	
	gridLayout -> addWidget(nameLabel, 0, 0, 0, meret);
	//gridLayout -> addWidget(nameLabel, 0, 0, meret, 0);
	
	for (int i = 0; i < meret; ++i)
	{
		if (kiegeszitoSzoveg)
		{
			kiegLabel[i] = new QLabel(this);
			kiegLabel[i] -> setStyleSheet("QLabel { color : black; }");
			kiegLabel[i] -> setFont(displayFont);
			
			//kiegLabel[i] -> setGeometry(20, 20, 360, 120);
			kiegLabel[i] -> setFixedSize( 40, 20 );
			kiegLabel[i] -> setAlignment(Qt::AlignCenter);
			
			gridLayout -> addWidget( kiegLabel[i], disRow - 1, i);
		}
		
		
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
}

vectorDisplay::~vectorDisplay()
{
	// null
}

int vectorDisplay::size() const
{
	return meret;
}

void vectorDisplay::setName(std::string _name)
{
	name = _name;
	nameLabel -> setText( QString::fromStdString( name ));
}

void vectorDisplay::setValues(const std::vector<AP_UC> &val)
{
	for (int i = 0; i < meret; ++i)
	{
		valueVec[i] = val[i];
		
		valueLabel[i] -> setText( QString::number( valueVec[i] ));
	}
}

void vectorDisplay::setKieg(const std::vector<std::string> &kieg)
{
	for (int i = 0; i < meret; ++i)
	{
		kiegVec[i] = kieg[i];
		
		kiegLabel[i] -> setText( QString::fromStdString( kiegVec[i] ) );
	}
}

// -----------------------------------------------

veremDisplay::veremDisplay( std::string nev, QWidget *parent = 0 ) : QWidget(parent), name(nev)
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
	
	mainLayout -> addWidget( nameLabel );
	
	mainLayout -> addWidget( scrollArea );
	scrollArea -> setWidget( scrollWidget );
	scrollArea -> setFrameShape(QFrame::NoFrame);
	
	scrollWidget -> setLayout( gridLayout );
//	scrollWidget -> setFixedSize( 780, 50 );
	
	setLayout( mainLayout );
	
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
	int prevsize = valueLabel.size();
	//cout << prevsize << "\t" << vals.size() << endl;
	if ( vals.size() < valueLabel.size() )
	{
		for (int i = valueLabel.size() - 1; i >= vals.size(); --i)
		{
			gridLayout -> removeWidget( valueLabel[i] );
			delete valueLabel[i];
		}
	}
	valueLabel.resize( vals.size() );
	valueVec = vals;
	if (prevsize < vals.size() )
	{
		QFont displayFont( "Arial", 12);
		for (int i = prevsize; i < valueLabel.size(); ++i)
		{
			//cout << "new " << i << endl;
			valueLabel[i] = new QLabel( this );
			valueLabel[i] -> setStyleSheet( "QLabel { background-color : white; color : black; }" );
			valueLabel[i] -> setTextInteractionFlags( Qt::TextSelectableByMouse );	// kijelolhetove (masolhatova) teszi a szoveget
			valueLabel[i] -> setFont( displayFont );
			valueLabel[i] -> setFixedSize( 40, 20 );
			valueLabel[i] -> setAlignment(Qt::AlignCenter);
			
			gridLayout -> addWidget( valueLabel[i], 1, i);
		}
	}
	for (int i = 0; i < valueLabel.size(); ++i)
	{
		valueLabel[i] -> setText( QString::number( valueVec[i] ));
		//cout << i << ". val: " << valueVec[i] << endl;
	}
	scrollWidget -> setFixedSize( 45 * valueLabel.size(), 45 );
}

void veremDisplay::updateKieg(const std::vector<std::string> &kiegs)
{
	int prevsize = kiegLabel.size();
	if ( kiegs.size() < kiegLabel.size() )
	{
		for (int i = kiegLabel.size() - 1; i >= kiegs.size(); --i)
		{
			gridLayout -> removeWidget( kiegLabel[i] );
			delete kiegLabel[i];
		}
	}
	kiegLabel.resize( kiegs.size() );
	kiegVec = kiegs;
	if (prevsize < kiegs.size() )
	{
		QFont displayFont( "Arial", 12);
		for (int i = prevsize; i < kiegLabel.size(); ++i)
		{
			kiegLabel[i] = new QLabel( this );
			kiegLabel[i] -> setStyleSheet( "QLabel { color : black; }" );
			kiegLabel[i] -> setTextInteractionFlags( Qt::TextSelectableByMouse );	// kijelolhetove (masolhatova) teszi a szoveget
			kiegLabel[i] -> setFont( displayFont );
			kiegLabel[i] -> setFixedSize( 40, 20 );
			kiegLabel[i] -> setAlignment(Qt::AlignCenter);
			
			gridLayout -> addWidget( kiegLabel[i], 0, i);
		}
	}
	for (int i = 0; i < kiegLabel.size(); ++i)
	{
		kiegLabel[i] -> setText( QString::fromStdString( kiegVec[i] ));
	}
	scrollWidget -> setFixedSize( 45 * kiegLabel.size(), 45 );
}