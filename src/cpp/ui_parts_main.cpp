
#include <fstream>

#include <wx/gbsizer.h>
#include <wx/event.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>

#include "ui_parts.h"
#include "ui_parts_main.h"

mainDisplay::mainDisplay( const wxString &title ) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600) )
{
	wxPanel *mainPanel = new wxPanel( this, wxID_ANY  );
	mainPanel -> SetAutoLayout( true );
	SetMinSize( wxSize(800, 600) );
	
	menuBar = new wxMenuBar;
	file = new wxMenu;
	
	file -> Append( UI_MAIN_FILE_OPEN_EVENT, wxString::FromUTF8("Fájl megnyitása") );
	file -> Append( wxID_EXIT, wxString::FromUTF8("Kilépés") );
	menuBar -> Append( file, "File" );
	
	SetMenuBar( menuBar );
	
	sizer = new wxGridBagSizer( 1, 1 );
	eax = new regDisplay( mainPanel, 4, "eax" );
	ebx = new regDisplay( mainPanel, 4, "ebx" );
	ecx = new regDisplay( mainPanel, 4, "ecx" );
	edx = new regDisplay( mainPanel, 4, "edx" );
	
	valtozok = new varDisplay( mainPanel, "valtozok" );
	verem = new varDisplay( mainPanel, "verem" );
	
	sign = new flagDisplay( mainPanel, "sign" );
	zero = new flagDisplay( mainPanel, "zero" );
	
	sizer -> Add( eax, wxGBPosition(0, 0) );
	sizer -> Add( ebx, wxGBPosition(0, 1) );
	sizer -> Add( ecx, wxGBPosition(1, 0) );
	sizer -> Add( edx, wxGBPosition(1, 1) );
	sizer -> Add( sign, wxGBPosition(0, 2) );
	sizer -> Add( zero, wxGBPosition(1, 2) );
	sizer -> Add( valtozok, wxGBPosition(2, 0), wxGBSpan( 1, 3) );
	sizer -> Add( verem, wxGBPosition(3, 0), wxGBSpan( 1, 3) );

	mainPanel -> SetSizer( sizer );
	sizer -> Layout();
	mainPanel -> Fit();
	
	Centre();
	
	displayRefresh();
}

mainDisplay::~mainDisplay()
{
	
}

void mainDisplay::OnQuit( wxCommandEvent& event)
{
	Close( true );
}

void mainDisplay::OpenFile( wxCommandEvent& event)
{
	wxFileDialog dialog( this, wxString::FromUTF8("Assembly kódfájl megnyitása"), "", "", wxString::FromUTF8("Assembly fájlok (*.asm)|*.asm"), wxFD_OPEN | wxFD_FILE_MUST_EXIST );
	
	if ( dialog.ShowModal() == wxID_CANCEL)
	{	// nem tortent file megnyitas
		return;
	}
	
	wxMessageDialog msg( this, dialog.GetPath(), "eredmeny:");
	msg.ShowModal();
}

void mainDisplay::displayRefresh()
{
	std::vector<unsigned char> vec(4);
	std::vector<std::string> labels(4);
	for (int i = 0; i < 4; ++i)
	{
		vec[i] = 3 - i + i * i * 2;
		if ( i == 2)
		{
			labels[i] = "itt";
		} else
		{
			labels[i] = "";
		}
	}
	
	eax -> updateValues( vec );
	
	vec[2] = 42;
	ebx -> updateValues( vec );
	
	vec[0] = 13;
	ecx -> updateValues( vec );
	
	vec[3] = 255;
	edx -> updateValues( vec );
	
	vec[1] = 0;
	edx -> updateValues( vec );
	
	valtozok -> updateValues( vec );
	valtozok -> updateLabels( labels );
	
	vec.push_back( 44 );
	valtozok -> updateValues( vec );
	verem -> updateValues( vec );
	
	vec.resize( 4 );
	vec[1] = 6;
	verem -> updateValues( vec );
	valtozok -> updateValues( vec );
	labels.resize( 3 );
	labels[2] = "esp";
	verem -> updateLabels( labels );
	
	vec.resize(39, 2);
	labels.resize( 40, "");
	labels[15] = "ebp";
	vec[21] = 100;
	verem -> updateValues( vec );
	verem -> updateLabels( labels );
	
	sign -> set( true );
	
	sizer -> Layout();
	Fit();
}

wxDEFINE_EVENT( UI_MAIN_FILE_OPEN_EVENT, wxCommandEvent );

wxBEGIN_EVENT_TABLE(mainDisplay, wxFrame)
	EVT_MENU( UI_MAIN_FILE_OPEN_EVENT, mainDisplay::OpenFile )
	EVT_MENU( wxID_EXIT, mainDisplay::OnQuit )
wxEND_EVENT_TABLE()
