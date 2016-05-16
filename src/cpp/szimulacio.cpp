

#include <fstream>
#include <sstream>

#include "szimulacio.h"
#include "elsoparseParser.h"

using namespace std;



Szimulacio::Szimulacio() : vantovabb( false )
{
	// null
}

Szimulacio::~Szimulacio()
{
	// null
}

void Szimulacio::run()
{
	string fnev;
	cout << "Adja meg a szimulalando file nevet!" << endl;
	//getline( cin, fnev );
	
	//ifstream file( fnev.c_str() );
	//ifstream file( "../testfiles/teszt1.asm" );
	ifstream file( "../testfiles/sokinc.asm" );
	if ( !file )
	{
		cout << "A megadott file nem talalhato!" << endl;
		return;
	}
	elsoparseParser eParser( file );
	
	map<string, int> valt_kezd;
	vector<AP_UC> valtozok;
	int kezdet;
	
	try
	{
		cout << "Kezdeti elemzes" << endl;
		eParser.completeParse();
		
		utas_data = eParser.get_utasitasok();
		valt_kezd = eParser.get_valtozokezdet();
		ugro_cimkek = eParser.get_ugrocimke();
		valtozok = eParser.get_valtozok();
		kezdet = eParser.get_elsoutasitas();
		vege = eParser.get_utolsoutasitas();
		cout << "Adatok atvetele megtortent" << endl;
		
		allapot.init( valt_kezd, valtozok );
		allapot.set_kovetkezo( kezdet );
		cout << "Allapot inicializalva" << endl;
		
		allapot.print_allapot();
		
		file.close();
	} catch ( elsoparseParser::Exceptions ex)
	{
		cout << "Hiba tortent a kezdeti elemzes kozben!" << endl;
		cout << eParser.get_error();
		file.close();
		return;
	}
	
	iParser.initAp( &allapot, &ugro_cimkek );
	vantovabb = true;
	
	cout << "A tovabblepeshez nyomjon Entert, a visszalepeshez a \'v\' betut irja be, majd nyomjon Entert! (Visszalepni csak akkor lehet, ha mar legalabb 1 utasitas vegre lett hajtva.)" << endl;
	
	receive();
}

void Szimulacio::receive()
{
	volatile int array[500000];
	while (1)
	{
		array[499999]++;
		cout << "Kovetkezo utasitas:" << endl;
		cout << "\t" << utas_data[ allapot.get_kovetkezo() ].eredetisorszam << ". sor:\t" << utas_data[ allapot.get_kovetkezo() ].sor << endl;
		string str("");
	
		getline( cin, str );
	
		if ( str.size() == 0 || str[0] != 'v' )
		{
			if ( !vantovabb )
			{
				cout << "Ez volt az utolso utasitas, nincs lehetoseg tovabblepesre, a program leall." << endl;
				getline( cin, str );
				break;
			} else
			{
				next();
			}
		} else
		{
			if ( korabbi_allapotok.size() > 0 )
			{
				prev();
			} else
			{
				cout << "Nincs lehetoseg visszalepesre, helyette tovabblepes." << endl;
				next();
			}
		}
	}
}

void Szimulacio::next()
{
	korabbi_allapotok.push( allapot );
	
	istringstream iss( utas_data[ allapot.get_kovetkezo() ].sor );
	try
	{
		cout << "parsing" << endl;
		iParser.completeParse( iss, utas_data[ allapot.get_kovetkezo() ].argmeret );
		cout << "parsedone" << endl;
		allapot.kov_utasitas();
		allapot.print_allapot();
		if ( allapot.get_kovetkezo() >= vege )
		{
			cout << "Ez volt az utolso utasitas, nincs lehetoseg tovabblepesre." << endl;
			vantovabb = false;
		}
	} catch ( interpretParser::Exceptions ex)
	{
		cout << "Interpretalassal hiba tortent: " << endl;
		cout << "\t" << iParser.get_error() << endl;
		vantovabb = false;
	} catch ( Allapot::Exceptions ex)
	{
		cout << "Allapot hiba!" << endl;
		switch (ex)
		{
		case Allapot::URES_VEREM:
			cout << "Ures a verem!" << endl;
			break;
		case Allapot::TELE_VEREM:
			cout << "Megtelt a verem!" << endl;
			break;
		case Allapot::HATARON_KIVULI_VALTOZO:
			cout << "Ervenytelen valtozo hivatkozas!" << endl;
			break;
		case Allapot::HATARON_KIVULI_VEREM:
			cout << "Ervenytelen verem hivatkozas!" << endl;
			break;
		case Allapot::NEGATIV_VEREM_MERET:
			cout << "Az esp regiszter ervenytelen erteket kapott!" << endl;
			break;
		}
		vantovabb = false;
	}
}

void Szimulacio::prev()
{
	allapot = korabbi_allapotok.top();
	korabbi_allapotok.pop();
	
	cout << "Visszalepes vegrehajtva." << endl;
	vantovabb = true;
	
	allapot.print_allapot();
}
	