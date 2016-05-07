#ifndef UI_MAIN_H_INCLUDED
#define UI_MAIN_H_INCLUDED

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QLabel>
#include <QPushbutton>

#include "ui_parts.h"
#include "allapot.h"

class mainDisplay : public QMainWindow
{
	Q_OBJECT
public:
	mainDisplay( );
	~mainDisplay( );
	
private slots:
    void openFile();
	
private:
	Allapot allapot;

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
