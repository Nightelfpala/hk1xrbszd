
#include <fstream>

#include "elsoparseParser.h"
#include "ui_parts.h"
#include "ui_main.h"

#include <wx/gbsizer.h>
#include <wx/event.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/filefn.h>	// wxGetCwd()

mainDisplay::mainDisplay( const wxString &title ) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600) )
{
	wxPanel *mainPanel = new wxPanel( this, wxID_ANY  );
	mainPanel -> 
		SetAutoLayout( true );
	//mainPanel -> 
		SetMinSize( wxSize(900, 600) );
	
	menuBar = new wxMenuBar;
	file = new wxMenu;
	
	file -> Append( UI_MAIN_FILE_OPEN_EVENT, wxString::FromUTF8("Fájl megnyitása") );
	file -> Append( wxID_ANY, wxEmptyString, wxEmptyString, wxITEM_SEPARATOR );
	file -> Append( wxID_EXIT, wxString::FromUTF8("Kilépés") );
	menuBar -> Append( file, "File" );
	
	SetMenuBar( menuBar );
	
	//Connect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainDisplay::OnQuit ));
	//file -> Bind( wxEVT_COMMAND_MENU_SELECTED, &mainDisplay::OnQuit, this );
	
	sizer = new wxGridBagSizer( 1, 1 );
	eax = new regDisplay( mainPanel, 4, "EAX" );
	ebx = new regDisplay( mainPanel, 4, "EBX" );
	ecx = new regDisplay( mainPanel, 4, "ECX" );
	edx = new regDisplay( mainPanel, 4, "EDX" );
	
	valtozok = new varDisplay( mainPanel, wxString::FromUTF8("Változók") );
	verem = new varDisplay( mainPanel, "Verem" );
	
	sign = new flagDisplay( mainPanel, "SIGN" );
	zero = new flagDisplay( mainPanel, "ZERO" );
	
	sizer -> Add( eax, wxGBPosition(0, 0) );
	sizer -> Add( ebx, wxGBPosition(0, 1) );
	sizer -> Add( ecx, wxGBPosition(1, 0) );
	sizer -> Add( edx, wxGBPosition(1, 1) );
	sizer -> Add( sign, wxGBPosition(0, 2) );
	sizer -> Add( zero, wxGBPosition(1, 2) );
	sizer -> Add( valtozok, wxGBPosition(2, 0), wxGBSpan( 1, 3) );
	sizer -> Add( verem, wxGBPosition(3, 0), wxGBSpan( 1, 3) );

#if 1
	mainPanel -> SetSizer( sizer );
	sizer -> Layout();
	mainPanel -> Fit();
#else
	SetSizer( sizer );
	sizer -> Layout();
	Fit();
#endif
	
	Centre();
	
	displayRefresh();
}

mainDisplay::~mainDisplay()
{
	//if (menuBar) delete menuBar;
	//if (file) delete file;
}

void mainDisplay::OnQuit( wxCommandEvent& event)
{
	Close( true );
}

void mainDisplay::OpenFile( wxCommandEvent& event)
{
	wxFileDialog dialog( this, wxString::FromUTF8("Assembly kódfájl megnyitása"), wxGetCwd(), "", wxString::FromUTF8("Assembly fájlok (*.asm)|*.asm"), wxFD_OPEN | wxFD_FILE_MUST_EXIST );
	
	if ( dialog.ShowModal() == wxID_CANCEL)
	{	// nem tortent file megnyitas
		return;
	}
	
	wxMessageDialog msg( this, dialog.GetPath(), "eredmeny:");
	msg.ShowModal();
	//ifstream infile( dialog.GetPath().ToStdString() );
}

void mainDisplay::displayRefresh()
{
	std::vector<unsigned char> vec;
	std::vector<std::string> labels;
	
	allapot.get_reg( "eax", vec );
	eax -> updateValues( vec );
	
	/*
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
	*/
	sizer -> Layout();
	Fit();
}

wxDEFINE_EVENT( UI_MAIN_FILE_OPEN_EVENT, wxCommandEvent );

wxBEGIN_EVENT_TABLE(mainDisplay, wxFrame)
	EVT_MENU( UI_MAIN_FILE_OPEN_EVENT, mainDisplay::OpenFile )
	EVT_MENU( wxID_EXIT, mainDisplay::OnQuit )
wxEND_EVENT_TABLE()
