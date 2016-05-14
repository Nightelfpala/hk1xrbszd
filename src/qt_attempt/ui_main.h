#ifndef UI_MAIN_H_INCLUDED
#define UI_MAIN_H_INCLUDED

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QLabel>
#include <QPushbutton>

#include <vector>
#include <map>

#include "ui_parts.h"
#include "allapot.h"
#include "interpretParser.h"
#include "typedefs.h"

class elsoparseParser;

class mainDisplay : public QMainWindow
{
	Q_OBJECT
public:
	mainDisplay( QWidget *parent = 0 );
	~mainDisplay( );
private slots:
	void openFile();
	void interpretNext();
	
	void displayAllapot();
private:

	regDisplay* eax;
	regDisplay* ebx;
	regDisplay* ecx;
	regDisplay* edx;
	
	veremDisplay* valtozok;
	veremDisplay* verem;
	
	std::map<int, utasitas_data> utasitasok;
	std::map<std::string, int> ugrocimkek;
	
	Allapot allapot;
	
	elsoparseParser *eParser;
	
};



#endif	// UI_MAIN_H_INCLUDED
