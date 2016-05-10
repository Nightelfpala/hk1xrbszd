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
	mainDisplay( QWidget *parent = 0 );
	~mainDisplay( );
private slots:
	void openFile();
private:

	regDisplay* eax;
	
	void displayAllapot();
};



#endif	// UI_MAIN_H_INCLUDED
