
#ifndef UI_MAIN_H_INCLUDED
#define UI_MAIN_H_INCLUDED

#include "typedefs.h"
#include "allapot.h"

#include <stack>
#include <map>

#include <wx/wx.h>
#include <wx/menu.h>

wxDECLARE_EVENT( UI_MAIN_FILE_OPEN_EVENT, wxCommandEvent );
wxDECLARE_EVENT( UI_MAIN_NEXT_INSTRUCTION_EVENT, wxCommandEvent );
wxDECLARE_EVENT( UI_MAIN_PREV_INSTRUCTION_EVENT, wxCommandEvent );

class wxGridBagSizer;
class wxButton;

class regDisplay;
class varDisplay;
class flagDisplay;

class interpretParser;

class mainDisplay : public wxFrame
{
public:
	//mainDisplay( const wxString &title );
	mainDisplay();
	~mainDisplay();

private:	
	void OnQuit( wxCommandEvent& event );
	void OpenFile( wxCommandEvent& event );
	void NextInstruction( wxCommandEvent& event );
	void PrevInstruction( wxCommandEvent& event );
	
	Allapot allapot;
	
	bool isloaded;
	
	std::stack<Allapot> korabbiak;
	std::map<int, utasitas_data> utas_data;
	std::map<std::string, int> ugro_cimkek;
	int vege;
	
	interpretParser *iParser;

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
	
	wxButton *nextButton;
	wxTextCtrl *nextInstruction;
	wxTextCtrl *nextRow;
	
	wxButton *prevButton;
	wxTextCtrl *prevInstruction;
	//wxTextCtrl *prevText;
	
	int prev;
	
	void displayRefresh();
	
	wxDECLARE_EVENT_TABLE();
};

#endif // UI_MAIN_H_INCLUDED

