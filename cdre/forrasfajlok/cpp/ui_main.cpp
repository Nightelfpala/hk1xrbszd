
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

#include <iostream>

using namespace std;

//mainDisplay::mainDisplay( const wxString &title ) 
mainDisplay::mainDisplay() 
	: wxFrame(NULL, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(800, 600) ), isloaded ( false ), iParser( NULL ), prev( -1 )
{
	wxFont displayFont(wxFontInfo( 12 ) );
	
	wxPanel *mainPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxBORDER_SIMPLE );
	mainPanel -> SetAutoLayout( true );
	SetMinSize( wxSize(820, 370) );
	SetMaxSize( wxSize(820, 370) );
		
	SetTitle( wxString::FromUTF8("Szimuláció") );
		
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
	prevButton = new wxButton( this, UI_MAIN_PREV_INSTRUCTION_EVENT, wxString::FromUTF8("Visszavon"));
	prevButton -> Enable( false );
	
	nextInstruction = new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition, wxSize( 250, 30), wxTE_READONLY | wxTE_RIGHT | wxBORDER_SIMPLE );
	nextInstruction -> SetFont( displayFont );
	nextInstruction -> SetBackgroundColour( wxColour( *wxWHITE ) );
	nextRow = new wxTextCtrl( this, wxID_ANY, " ", wxDefaultPosition, wxSize( 60, 30), wxTE_READONLY | wxTE_RIGHT | wxBORDER_SIMPLE );
	nextRow -> SetFont( displayFont );
	//nextRow -> SetBackgroundColour( wxColour( *wxWHITE ) );
	
	prevInstruction = new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition, wxSize( 250, 30), wxTE_READONLY | wxTE_RIGHT | wxBORDER_SIMPLE );
	prevInstruction -> SetFont( displayFont );
	prevInstruction -> SetBackgroundColour( wxColour( *wxWHITE ) );
	
	wxTextCtrl *prevText = new wxTextCtrl( this, wxID_ANY, " ", wxDefaultPosition, wxSize( 60, 30), wxTE_READONLY | wxTE_RIGHT );
	prevText -> SetFont( displayFont );
	prevText -> SetValue( wxString::FromUTF8("Előző:") );
	
	controlSizer -> Add( nextButton, wxGBPosition( 1, 2), wxDefaultSpan, wxALIGN_RIGHT );
	controlSizer -> Add( prevButton, wxGBPosition( 1, 1), wxDefaultSpan, wxALIGN_LEFT );
	controlSizer -> Add( nextInstruction, wxGBPosition( 0, 1), wxGBSpan(1, 3) );
	controlSizer -> Add( prevText, wxGBPosition( 2, 0) );
	controlSizer -> Add( prevInstruction, wxGBPosition( 2, 1), wxGBSpan(1, 3) );
	controlSizer -> Add( nextRow, wxGBPosition( 0, 0) );
	
	controlSizer -> Layout();
	
	sizer -> Add( controlSizer, wxGBPosition( 0, 3), wxGBSpan( 2, 1) );
	
	mainPanel -> SetSizer( sizer );
	sizer -> Layout();
	mainPanel -> Fit();

	prevButton -> Raise();
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

void mainDisplay::OnQuit( wxCommandEvent& event )
{
	Close( true );
}

void mainDisplay::OpenFile( wxCommandEvent& event )
{
	// nem ismetelheto, fura segfaultok
	wxFileDialog dialog( this, wxString::FromUTF8("Assembly kódfájl megnyitása"), wxGetCwd(), "", wxString::FromUTF8("Assembly fájlok (*.asm)|*.asm"), wxFD_OPEN | wxFD_FILE_MUST_EXIST );
	
	if ( dialog.ShowModal() == wxID_CANCEL)
	{	// nem tortent file megnyitas
		return;
	}
	
	SetTitle( wxString::FromUTF8("Szimuláció: ") + dialog.GetFilename() );
	
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
		
		while ( korabbiak.size() > 0 )
		{
			korabbiak.pop();
		}
		prevButton -> Enable( false );
		
		if ( vege > kezdet )
		{
			isloaded = true;
			nextButton -> Enable( true );
		}
		
		prev = -1;
		
		displayRefresh();
		
	} catch ( elsoparseParser::Exceptions ex)
	{
		infile.close();
		wxMessageDialog msg( this, eParser.get_error(), wxString::FromUTF8("Hiba történt a kezdeti elemzés során"));
		msg.ShowModal();
	}
}

void mainDisplay::NextInstruction( wxCommandEvent& event )
{
	istringstream iss(utas_data[ allapot.get_kovetkezo() ].sor);
	
	try
	{
		korabbiak.push( allapot );
		iParser -> completeParse( iss, utas_data[ allapot.get_kovetkezo() ].argmeret );
		allapot.kov_utasitas();
		
		prevButton -> Enable( true );
		nextButton -> SetFocus();
		
		prev = korabbiak.top().get_kovetkezo();
		
		displayRefresh();
	} catch ( interpretParser::Exceptions ex )
	{
		korabbiak.pop();
		nextButton -> Enable( false );
		wxMessageDialog msg( this, iParser -> get_error(), wxString::FromUTF8("Hiba történt a művelet végrehajtása során"));
		msg.ShowModal();
	} catch ( Allapot::Exceptions ex )
	{
		wxString errorMsg;
		switch (ex)
		{
		case Allapot::URES_VEREM:
			errorMsg = wxString::FromUTF8("A veremben nincs annyi byte, amennyit a \"pop\" utasítás ki akart venni!");
			break;
		case Allapot::TELE_VEREM:
			errorMsg = wxString::FromUTF8("Megtelt a verem! A tartalom mérete túllépte a 268.435.455 byteot.");
			break;
		case Allapot::HATARON_KIVULI_VALTOZO:
			errorMsg = wxString::FromUTF8("Érvénytelen változó hivatkozás!");
			break;
		case Allapot::HATARON_KIVULI_VEREM:
			errorMsg = wxString::FromUTF8("Érvénytelen verem hivatkozás!");
			break;
		case Allapot::NEGATIV_VEREM_MERET:
			errorMsg = wxString::FromUTF8("Az esp regiszter érvénytelen értéket kapott!");
			break;
		}
		korabbiak.pop();
		nextButton -> Enable( false );
		wxMessageDialog msg( this, errorMsg, wxString::FromUTF8("Hiba történt a művelet végrehajtása során"));
		msg.ShowModal();
	}
	
	if ( nextButton -> IsEnabled() && allapot.get_kovetkezo() >= vege)
	{
		//nextInstruction -> SetValue( wxString::FromUTF8( " ; Nincs több utasítás" ));
		nextInstruction -> SetValue( wxString::FromUTF8( "" ));
		nextRow -> SetValue( "" );
		wxMessageDialog msg( this, wxString::FromUTF8("Nincs több utasítás"), wxString::FromUTF8("Futás vége"));
		msg.ShowModal();
		nextButton -> Enable( false );
	}
}

void mainDisplay::PrevInstruction( wxCommandEvent& event )
{
	allapot = korabbiak.top();
	korabbiak.pop();
	isloaded = true;
	
	nextButton -> Enable( true );
	if ( korabbiak.size() == 0 )
	{
		prev = -1;
		prevButton -> Enable( false );
	} else
	{
		prev = korabbiak.top().get_kovetkezo();
	}

	displayRefresh();
}

void mainDisplay::displayRefresh()
{
	std::vector<AP_UC> vec;
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
	
	sign -> set( allapot.get_sign() );
	zero -> set( allapot.get_zero() );
	
	if ( isloaded && vege >= allapot.get_kovetkezo() )
	{
		stringstream ss;
		ss << utas_data[ allapot.get_kovetkezo() ].eredetisorszam << ". sor:";
		nextRow -> SetValue( ss.str() );
		nextInstruction -> SetValue(utas_data[ allapot.get_kovetkezo() ].sor);
	} else
	{
		isloaded = false;
		nextRow -> SetValue( "" );
	}
	
	if ( prev != -1 )
	{
		prevInstruction -> SetValue( utas_data[ prev ].sor );
	} else
	{
		prevInstruction -> SetValue( "" );
	}
	
	sizer -> Layout();
	Fit();
}

wxDEFINE_EVENT( UI_MAIN_FILE_OPEN_EVENT, wxCommandEvent );
wxDEFINE_EVENT( UI_MAIN_NEXT_INSTRUCTION_EVENT, wxCommandEvent );
wxDEFINE_EVENT( UI_MAIN_PREV_INSTRUCTION_EVENT, wxCommandEvent );

wxBEGIN_EVENT_TABLE(mainDisplay, wxFrame)
	EVT_MENU( UI_MAIN_FILE_OPEN_EVENT, mainDisplay::OpenFile )
	EVT_MENU( wxID_EXIT, mainDisplay::OnQuit )
	EVT_BUTTON( UI_MAIN_NEXT_INSTRUCTION_EVENT, mainDisplay::NextInstruction )
	EVT_BUTTON( UI_MAIN_PREV_INSTRUCTION_EVENT, mainDisplay::PrevInstruction )
wxEND_EVENT_TABLE()
