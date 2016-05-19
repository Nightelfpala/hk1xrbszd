
#include "appmain.h"

#include "ui_main.h"

IMPLEMENT_APP(App)

bool App::OnInit()
{
	mainDisplay* main = new mainDisplay();
	
	main -> Show( true );
	
	return true;
}
