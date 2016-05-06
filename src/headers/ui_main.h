#ifndef UI_MAIN_H_INCLUDED
#define UI_MAIN_H_INCLUDED

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>

#include "ui_parts.h"
#include "allapot.h"

class mainDisplay : public QMainWindow
{
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
	
	QMenu *fileMenu;
	QAction *openAct;
	QAction *quitAct;
	
	void createWidgets();
};



#endif	// UI_MAIN_H_INCLUDED
