
#ifndef UI_MAIN_H_INCLUDED
#define UI_MAIN_H_INCLUDED

#include "typedefs.h"
#include "allapot.h"
#include "interpretParser.h"
		// interpretParser.h -> ERROR() atirva IP_ERROR() -ra, hogy ne conflictolja a wxWidgets-szel

#include <wx/wx.h>
#include <wx/menu.h>

wxDECLARE_EVENT( UI_MAIN_FILE_OPEN_EVENT, wxCommandEvent );

class wxGridBagSizer;

class regDisplay;
class varDisplay;
class flagDisplay;

class mainDisplay : public wxFrame
{
public:
	mainDisplay( const wxString &title );
	~mainDisplay();

private:	
	void OnQuit( wxCommandEvent& event);
	void OpenFile( wxCommandEvent& event);
	
	Allapot allapot;

	regDisplay* eax;
	regDisplay* ebx;
	regDisplay* ecx;
	regDisplay* edx;
	
	varDisplay* valtozok;
	varDisplay* verem;
	
	flagDisplay* sign;
	flagDisplay* zero;
	
	wxMenuBar *menuBar;
	wxMenu *file;
	
	wxGridBagSizer *sizer;
	
	void displayRefresh();
	
	wxDECLARE_EVENT_TABLE();
};

#endif // UI_MAIN_H_INCLUDED

