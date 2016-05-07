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

class mainDisplay : public QMainWindow
{
	Q_OBJECT
public:
	mainDisplay( );
	~mainDisplay( );
	
private slots:
    void openFile();
	void oF2();
	void interpretNext();
	
private:
	Allapot allapot;
	
	interpretParser iParser;
	
	std::map<int, utasitas_data> utasitasok;
	std::map<std::string, int> ugrocimkek;

	regDisplay *eax;
	regDisplay *ebx;
	regDisplay *ecx;
	regDisplay *edx;
	
	veremDisplay *valtozok;
	veremDisplay *verem;
	
	flagDisplay *signFlag;
	flagDisplay *zeroFlag;
	
	QLabel *nextInstruction;
	QPushButton *nextButton;
	
	QMenu *fileMenu;
	QAction *openAct;
	QAction *quitAct;
	
	void createWidgets();
	void displayAllapot();
};



#endif	// UI_MAIN_H_INCLUDED
