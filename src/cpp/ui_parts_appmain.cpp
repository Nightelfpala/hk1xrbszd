
#include "appmain.h"

#include "ui_main.h"

IMPLEMENT_APP(App)

bool App::OnInit()
{
	mainDisplay* main = new mainDisplay( wxString::FromUTF8("Ablak cím") );
	//mainDisplay* main = new mainDisplay( "window" );
	
	main -> Show( true );
	
	return true;
}
