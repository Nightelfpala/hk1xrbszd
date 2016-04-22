

#include "ui.h"

using namespace std;

vectorDisplay::vectorDisplay(int _meret, QWidget *parent, bool kiegSzoveg) : QWidget(parent), meret(_meret), kiegeszitoSzoveg(kiegSzoveg)
{
	int disRow = 2;
	if (kiegeszitoSzoveg) ++disRow;
	
	valueVec.resize(meret);
	valueLabel.resize(meret);
	if (kiegeszitoSzoveg)
	{
		kiegVec.resize(meret);
		kiegLabel.resize(meret);
	}
	
	QFont nameFont( "Arial", 18);
	QFont displayFont( "Arial", 12);
	
	gridLayout = new QGridLayout(this);
	nameLabel = new QLabel(this);
	
	nameLabel -> setFont(nameFont);
	nameLabel -> setGeometry(20, 20, 400, 200);
	nameLabel -> setAlignment(Qt::AlignCenter);
	
	gridLayout -> addWidget(nameLabel, 0, 0, 0, meret);
	
	for (int i = 0; i < meret; ++i)
	{
		if (kiegeszitoSzoveg)
		{
			kiegLabel[i] = new QLabel(this);
			kiegLabel[i] -> setStyleSheet("QLabel { color : black; }");
			kiegLabel[i] -> setFont(displayFont);
			
			kiegLabel[i] -> setGeometry(20, 20, 360, 120);
			kiegLabel[i] -> setAlignment(Qt::AlignCenter);
			
			gridLayout -> addWidget( kiegLabel[i], disRow - 1, i);
		}
		
		
		valueLabel[i] = new QLabel(this);
		
		valueLabel[i] -> setStyleSheet("QLabel { background-color : white; color : black; }");
		valueLabel[i] -> setTextInteractionFlags(Qt::TextSelectableByMouse);	// kijelolhetove (masolhatova) teszi a szoveget
		valueLabel[i] -> setFont(displayFont);
		
		valueLabel[i] -> setGeometry(20, 20, 360, 120);
		valueLabel[i] -> setAlignment(Qt::AlignCenter);
		
		gridLayout -> addWidget( valueLabel[i], disRow, i);
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

void vectorDisplay::setValues(std::vector<AP_UC> val)
{
	for (int i = 0; i < meret; ++i)
	{
		valueVec[i] = val[i];
		
		valueLabel[i] -> setText( QString::number( valueVec[i] ));
	}
}

void vectorDisplay::setKieg( std::vector<std::string> kieg)
{
	for (int i = 0; i < meret; ++i)
	{
		kiegVec[i] = kieg[i];
		
		kiegLabel[i] -> setText( QString::fromStdString( kiegVec[i] ) );
	}
}