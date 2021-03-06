
#include "utils.h"
#include "ui_parts.h"

#include <sstream>
#include <wx/gbsizer.h>
#include <wx/font.h>
#include <wx/scrolwin.h>

#include <iostream>
#include <iomanip>

#define UI_LABEL_WIDTH 50

using namespace std;

regDisplay::regDisplay( wxPanel *parent, const int &size, const wxString &nev ) :
	wxPanel( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxBORDER_SIMPLE ), name(nev), meret(size)
{
	vecValue.resize( meret, 0 );
	vecLabel.resize( meret );
	
	wxFont nameFont(wxFontInfo( 16 ).Bold( true ) );
	wxFont displayFont(wxFontInfo( 12 ) );
	
	wxGridBagSizer *sizer = new wxGridBagSizer( 1, 1 );
	nameLabel = new wxTextCtrl( this, wxID_ANY, name, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_LEFT | wxBORDER_NONE );
	nameLabel -> SetMinSize( wxSize(100, 25) );
	nameLabel -> SetFont( nameFont );
	nameLabel -> SetDefaultStyle( wxTextAttr( *wxBLACK ));
	
	valueLabel = new wxTextCtrl( this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_LEFT | wxBORDER_NONE );
	valueLabel -> SetMinSize( wxSize(100, 20) );
	valueLabel -> SetFont( displayFont );
	valueLabel -> SetDefaultStyle( wxTextAttr( *wxBLACK ));
	
	sizer -> Add( nameLabel, wxGBPosition(0, 0), wxGBSpan( 1, meret - 2 ) );
	sizer -> Add( valueLabel, wxGBPosition(0, meret - 2), wxGBSpan( 1, 2) );
	
	for ( int i = 0; i < meret; ++i )
	{
		vecLabel[i] = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTRE | wxTE_RICH );
		//vecLabel[i] -> SetEditable( false );
		vecLabel[i] -> SetMinSize( wxSize(50, 20) );
		vecLabel[i] -> SetFont( displayFont );
		vecLabel[i] -> SetDefaultStyle( wxTextAttr( *wxBLACK ));
		
		sizer -> Add( vecLabel[i], wxGBPosition( 1, i), wxDefaultSpan, wxALIGN_CENTER );
		
		stringstream ss;
		ss << (int)vecValue[i];
		vecLabel[i] -> SetValue( ss.str() );
	}
	
	SetSizer( sizer );
	Fit();
}

void regDisplay::updateValues( const std::vector<AP_UC> &values )
{
	for ( int i = 0; i < meret; ++i)
	{
		if ( vecValue[i] != values[i] )
		{
			vecLabel[i] -> SetForegroundColour( *wxRED );
			vecValue[i] = values[i];
		} else
		{
			vecLabel[i] -> SetForegroundColour( *wxBLACK );
		}
		
		std::stringstream ss;
		ss << (int)vecValue[i];
		vecLabel[i] -> SetValue( ss.str() );
	}
	stringstream ss;
	ss << "0x" << std::hex << std::setfill('0') << std::setw( meret * 2) << (AP_UI)Utils::vecc2uint( vecValue );
	valueLabel -> SetValue( ss.str() );
}

// ---------------------------------------------------------

varDisplay::varDisplay( wxPanel *parent, const wxString &nev )
	: wxPanel( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxBORDER_SIMPLE ), name(nev)
{
	vecValue.resize(0);
	vecLabel.resize(0);
	
	
	wxFont nameFont(wxFontInfo( 16 ).Bold( true ) );
	
	scroll = new wxScrolledWindow( this );
	scroll -> EnableScrolling( true, false );
	scroll -> ShowScrollbars( wxSHOW_SB_ALWAYS, wxSHOW_SB_NEVER );
	scroll -> SetMinSize( wxSize(800, 80) );
	scroll -> SetMaxSize( wxSize(800, 80) );
	
	outSizer = new wxGridBagSizer( 1, 1 );
	
	inSizer = new wxGridBagSizer( 1, 1 );
	nameLabel = new wxTextCtrl( this, wxID_ANY, name, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_LEFT | wxBORDER_NONE );
	nameLabel -> SetMinSize( wxSize(140, 25) );
	nameLabel -> SetFont( nameFont );
	nameLabel -> SetDefaultStyle( wxTextAttr( *wxBLACK ));
	
	outSizer -> Add( nameLabel, wxGBPosition(0, 0), wxGBSpan( 1, 1 ) );
	outSizer -> Add( scroll, wxGBPosition(1, 0), wxGBSpan(1, 3));
	
	scroll -> SetSizer( inSizer );
	inSizer -> Layout();
	scroll -> FitInside();
	SetSizer( outSizer );
	outSizer -> Layout();
	Fit();
}

void varDisplay::updateValues( const std::vector<AP_UC> &values )
{
	int prevsize = vecLabel.size();
	int newsize = values.size();
	
	if ( newsize > prevsize )
	{
		wxFont displayFont(wxFontInfo( 12 ) );
		vecValue.resize( newsize );
		vecLabel.resize( newsize );
		
		for ( int i = prevsize; i < newsize; ++i)
		{
			vecValue[i] = values[i];
			vecLabel[i] = new wxTextCtrl( scroll, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTRE | wxTE_RICH );
			vecLabel[i] -> SetForegroundColour( *wxRED );
			vecLabel[i] -> SetMinSize( wxSize(50, 20) );
			vecLabel[i] -> SetFont( displayFont );
			
			inSizer -> Add( vecLabel[i], wxGBPosition( 2, i ), wxDefaultSpan, wxALIGN_CENTER );
			
			std::stringstream ss;
			ss << (int)vecValue[i];
			vecLabel[i] -> SetValue( ss.str() );
		}
	}
	if ( newsize < prevsize )
	{
		for (int i = newsize; i < prevsize; ++i)
		{
			inSizer -> Detach( vecLabel[i] );
			vecLabel[i] -> Destroy();
		}
		vecValue.resize( newsize );
		vecLabel.resize( newsize );
	}
	
	for ( int i = 0; i < ((prevsize < newsize) ? (prevsize) : (newsize)); ++i)
	{
		if ( vecValue[i] != values[i])
		{
			vecValue[i] = values[i];
			vecLabel[i] -> SetForegroundColour( *wxRED );
		} else
		{
			vecLabel[i] -> SetForegroundColour( *wxBLACK );
		}
		
		std::stringstream ss;
		ss << (int)vecValue[i];
		vecLabel[i] -> SetValue( ss.str() );
	}
	inSizer -> Layout();
	scroll -> FitInside();
	outSizer -> Layout();
	Fit();
}

void varDisplay::updateLabels( const std::vector< std::string > &values )
{
	int prevsize = nameLabels.size();
	int newsize = values.size();
	
	if ( newsize > prevsize )
	{
		wxFont displayFont(wxFontInfo( 12 ) );
		vecNames.resize( newsize );
		nameLabels.resize( newsize );
		
		for ( int i = prevsize; i < newsize; ++i)
		{
			vecNames[i] = values[i];
			nameLabels[i] = new wxTextCtrl( scroll, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTRE | wxTE_RICH | wxBORDER_NONE );
			nameLabels[i] -> SetMinSize( wxSize(50, 20) );
			nameLabels[i] -> SetFont( displayFont );
			nameLabels[i] -> SetBackgroundColour( GetBackgroundColour() );
			nameLabels[i] -> SetForegroundColour( *wxRED );
			
			inSizer -> Add( nameLabels[i], wxGBPosition( 1, i ), wxDefaultSpan, wxALIGN_CENTER );
			
			nameLabels[i] -> SetValue( vecNames[i] );
		}
	}
	
	if (newsize < prevsize)
	{
		for ( int i = newsize; i < prevsize; ++i)
		{
			inSizer -> Detach( nameLabels[i] );
			nameLabels[i] -> Destroy();
		}
		vecNames.resize( newsize );
		nameLabels.resize( newsize );
	}
	
	for ( int i = 0; i < ((prevsize < newsize) ? (prevsize) : (newsize)); ++i)
	{
		if ( vecNames[i] != values[i])
		{
			vecNames[i] = values[i];
			nameLabels[i] -> SetForegroundColour( *wxRED );
		} else
		{
			nameLabels[i] -> SetForegroundColour( *wxBLACK );
		}
		
		nameLabels[i] -> SetValue( vecNames[i] );
	}
	inSizer -> Layout();
	{
		int x, y;
		scroll -> GetViewStart( &x, &y );
		scroll -> SetScrollbars( UI_LABEL_WIDTH, 0, newsize, x, y );
		scroll -> Scroll( x, y );
	}
	scroll -> FitInside();
	outSizer -> Layout();
	Fit();
}

// ----------------------------------------

flagDisplay::flagDisplay( wxPanel *parent, const wxString &nev) :
	wxPanel( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxBORDER_SIMPLE ), name(nev), value(0)
{
	wxFont nameFont(wxFontInfo( 16 ).Bold( true ) );
	wxFont displayFont(wxFontInfo( 12 ) );
	
	wxGridBagSizer *sizer = new wxGridBagSizer(1,1);
	
	nameLabel = new wxTextCtrl( this, wxID_ANY, name, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_LEFT | wxBORDER_NONE );
	nameLabel -> SetMinSize( wxSize(80, 25) );
	nameLabel -> SetFont( nameFont );
	nameLabel -> SetDefaultStyle( wxTextAttr( *wxBLACK ));
	
	valLabel = new wxTextCtrl( this, wxID_ANY, name, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_LEFT | wxBORDER_NONE );
	valLabel -> SetMinSize( wxSize(25, 20) );
	valLabel -> SetFont( displayFont );
	valLabel -> SetDefaultStyle( wxTextAttr( *wxBLACK ));
	set( false );
	
	sizer -> Add( nameLabel, wxGBPosition(0, 0));
	sizer -> Add( valLabel, wxGBPosition(1, 0), wxDefaultSpan, wxALIGN_CENTER);
	
	SetSizer( sizer );
	Fit();
}

void flagDisplay::set( bool b )
{
	if ( value == b )
	{
		valLabel -> SetForegroundColour( *wxBLACK );
	} else
	{
		value = b;
		valLabel -> SetForegroundColour( *wxRED );
	}
	
	valLabel -> SetValue( "" );
	
	std::stringstream ss;
	ss << (value ? 1 : 0);
	valLabel -> SetValue( ss.str() );
}
