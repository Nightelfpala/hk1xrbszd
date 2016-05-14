
#include <fstream>

#include "elsoparseParser.h"
#include "interpretParser.h"
		// interpretParser.h -> ERROR() atirva IP_ERROR() -ra, hogy ne conflictolja a wxWidgets-szel
#include "ui_parts.h"
#include "ui_main.h"

#include <wx/gbsizer.h>
#include <wx/event.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/button.h>
#include <wx/filefn.h>	// wxGetCwd()

using namespace std;

mainDisplay::mainDisplay( const wxString &title ) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600) ), iParser( NULL )
{
	wxFont displayFont(wxFontInfo( 12 ) );
	
	wxPanel *mainPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxBORDER_SIMPLE );
	mainPanel -> 
		SetAutoLayout( true );
	//mainPanel -> 
		SetMinSize( wxSize(900, 600) );
		
	wxGridBagSizer *controlSizer = new wxGridBagSizer( 2, 2 );
	
	menuBar = new wxMenuBar;
	file = new wxMenu;
	
	file -> Append( UI_MAIN_FILE_OPEN_EVENT, wxString::FromUTF8("Fájl megnyitása") );
	file -> Append( wxID_ANY, wxEmptyString, wxEmptyString, wxITEM_SEPARATOR );
	file -> Append( wxID_EXIT, wxString::FromUTF8("Kilépés") );
	menuBar -> Append( file, "File" );
	
	SetMenuBar( menuBar );
	
	sizer = new wxGridBagSizer( 
	//1, 1
	);
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
	sizer -> Add( valtozok, wxGBPosition(2, 0), wxGBSpan( 1, 4) );
	sizer -> Add( verem, wxGBPosition(3, 0), wxGBSpan( 1, 4) );
	
	nextButton = new wxButton( this, UI_MAIN_NEXT_INSTRUCTION_EVENT, wxString::FromUTF8("Végrehajt"));
	//nextButton -> SetFocus();
	nextButton -> Enable( false );
	
	nextInstruction = new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition, wxSize( 200, 30), wxTE_READONLY | wxTE_RIGHT | wxBORDER_SIMPLE );
	nextInstruction -> SetFont( displayFont );
	nextInstruction -> SetBackgroundColour( wxColour( *wxWHITE ) );
	nextRow = new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition, wxSize( 30, 30), wxTE_READONLY | wxTE_RIGHT | wxBORDER_SIMPLE );
	nextRow -> SetFont( displayFont );
	//nextRow -> SetBackgroundColour( wxColour( *wxWHITE ) );
	
	controlSizer -> Add( nextButton, wxGBPosition( 1, 2), wxDefaultSpan, wxALIGN_RIGHT );
	controlSizer -> Add( nextInstruction, wxGBPosition( 0, 1), wxGBSpan(1, 3) );
	controlSizer -> Add( nextRow, wxGBPosition( 0, 0) );
	
	controlSizer -> Layout();
	
	sizer -> Add( controlSizer, wxGBPosition( 0, 3), wxGBSpan( 2, 1) );
	
#if 1
	mainPanel -> SetSizer( sizer );
	sizer -> Layout();
	mainPanel -> Fit();
#else
	SetSizer( sizer );
	sizer -> Layout();
	Fit();
#endif

	nextButton -> Raise();
	
	SetBackgroundColour( mainPanel -> GetBackgroundColour() );
	Centre();
	
	displayRefresh();
}

mainDisplay::~mainDisplay()
{
	if ( iParser )
	{
		delete iParser;
	}
}

void mainDisplay::OnQuit( wxCommandEvent& event)
{
	Close( true );
}

void mainDisplay::OpenFile( wxCommandEvent& event)
{
	// nem ismetelheto, fura segfaultok
	wxFileDialog dialog( this, wxString::FromUTF8("Assembly kódfájl megnyitása"), wxGetCwd(), "", wxString::FromUTF8("Assembly fájlok (*.asm)|*.asm"), wxFD_OPEN | wxFD_FILE_MUST_EXIST );
	
	if ( dialog.ShowModal() == wxID_CANCEL)
	{	// nem tortent file megnyitas
		return;
	}
	
	//wxMessageDialog msg( this, dialog.GetPath(), "eredmeny:");
	//msg.ShowModal();
	
	ifstream infile( dialog.GetPath().ToStdString().c_str() );
	
	map<string, int> valt_kezd;
	vector<AP_UC> valtozok;
	int kezdet;
	
	elsoparseParser eParser( infile );
	try
	{
		eParser.completeParse();
		
		infile.close();
		
		utas_data = eParser.get_utasitasok();
		valt_kezd = eParser.get_valtozokezdet();
		ugro_cimkek = eParser.get_ugrocimke();
		valtozok = eParser.get_valtozok();
		kezdet = eParser.get_elsoutasitas();
		vege = eParser.get_utolsoutasitas();
		
		allapot.init( valt_kezd, valtozok );
		allapot.set_kovetkezo( kezdet );
		
		if ( iParser )
		{
			delete iParser;
		}
		
		iParser = new interpretParser;
		iParser -> initAp( &allapot, &ugro_cimkek );
		
		displayRefresh();
		
		if ( vege > kezdet )
		{
			nextButton -> Enable( true );
			
			stringstream ss;
			ss << utas_data[ allapot.get_kovetkezo() ].eredetisorszam << ". sor:";
			nextRow -> SetValue( ss.str() );
			nextInstruction -> SetValue(utas_data[ allapot.get_kovetkezo() ].sor);
		}
		
	} catch ( elsoparseParser::Exceptions ex)
	{
		infile.close();
		wxMessageDialog msg( this, eParser.get_error(), wxString::FromUTF8("Hiba történt a kezdeti elemzés során"));
		msg.ShowModal();
	}
}

void mainDisplay::NextInstruction( wxCommandEvent& event)
{
	
}

void mainDisplay::displayRefresh()
{
	std::vector<unsigned char> vec;
	std::vector<std::string> labels;
	
	allapot.get_reg( "eax", vec );
	eax -> updateValues( vec );
	
	allapot.get_reg( "ebx", vec );
	ebx -> updateValues( vec );
	
	allapot.get_reg( "ecx", vec );
	ecx -> updateValues( vec );
	
	allapot.get_reg( "edx", vec );
	edx -> updateValues( vec );
	
	allapot.valtozo_vector( vec );
	allapot.elso_valtozok( labels );
	valtozok -> updateValues( vec );
	valtozok -> updateLabels( labels );
	
	allapot.verem_vector( vec );
	allapot.vec_pointerek( labels );
	verem -> updateValues( vec );
	verem -> updateLabels( labels );
	
	sign -> set(allapot.get_sign());
	zero -> set(allapot.get_zero());
	
	sizer -> Layout();
	Fit();
}

wxDEFINE_EVENT( UI_MAIN_FILE_OPEN_EVENT, wxCommandEvent );
wxDEFINE_EVENT( UI_MAIN_NEXT_INSTRUCTION_EVENT, wxCommandEvent );

wxBEGIN_EVENT_TABLE(mainDisplay, wxFrame)
	EVT_MENU( UI_MAIN_FILE_OPEN_EVENT, mainDisplay::OpenFile )
	EVT_MENU( wxID_EXIT, mainDisplay::OnQuit )
	EVT_BUTTON( UI_MAIN_NEXT_INSTRUCTION_EVENT, mainDisplay::NextInstruction )
wxEND_EVENT_TABLE()
