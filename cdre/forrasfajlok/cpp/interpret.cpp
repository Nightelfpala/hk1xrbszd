
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include "allapot.h"
#include "utils.h"
#include "elsoparseParser.h"
#include "interpretParser.h"


using namespace std;

int main( int argc, char *argv[] )
{
	std::string infile;
	if (argc > 1 )
	{
		infile = argv[1];
	} else
	{
		infile = "../testfiles/teszt1.asm";
	}
	cout << "File megnyitasa: " << infile << endl;
	
	ifstream inf( infile.c_str() );
	if ( !inf )
	{
		cout << "A megadott file nem talalhato! A program kilep." << endl;
		return -1;
	}
	elsoparseParser eParser( inf );
	
	map<int, utasitas_data> utas_data;
	map<string, int> valt_kezd;
	map<string, int> ugro_cimkek;
	vector<AP_UC> valtozok;
	int kezdet;
	int vege;
	
	Allapot allapot;
	
	try
	{
		cout << "Kezdeti elemzes." << endl;
		eParser.completeParse();
		
		utas_data = eParser.get_utasitasok();
		valt_kezd = eParser.get_valtozokezdet();
		ugro_cimkek = eParser.get_ugrocimke();
		valtozok = eParser.get_valtozok();
		kezdet = eParser.get_elsoutasitas();
		vege = eParser.get_utolsoutasitas();
		cout << "Adatok atvetele megtortent." << endl;
		
		allapot.init( valt_kezd, valtozok );
		allapot.set_kovetkezo( kezdet );
		cout << "Allapot inicializalva." << endl;
		
		allapot.print_allapot();
		
		inf.close();
	} catch ( elsoparseParser::Exceptions ex )
	{
		cout << "Hiba tortent a kezdeti elemzes kozben!" << endl;
		cout << eParser.get_error();
		inf.close();
		return -1;
	}
	
	interpretParser iP;
	iP.initAp( &allapot, &ugro_cimkek );
	cout << "Interpreter inicializalva." << endl;
	
	while ( allapot.get_kovetkezo() != vege)
	{
		cout << "Kovetkezo utasitas:" << endl;
		cout << "\t" << utas_data[ allapot.get_kovetkezo() ].eredetisorszam << ". sor:\t" << utas_data[ allapot.get_kovetkezo() ].sor << endl;
		cout << "Nyomjon entert a vegrehajtashoz!" << endl;
		{
			string tmp;
			getline( std::cin, tmp);
		}
		cout << endl << "Kovetkezo utasitas vegrehajtasa:" << endl;
		
		istringstream iss( utas_data[ allapot.get_kovetkezo() ].sor );
		try
		{
			iP.completeParse( iss, utas_data[ allapot.get_kovetkezo() ].argmeret );
			allapot.kov_utasitas();
		} catch( interpretParser::Exceptions ex)
		{
			cout << "Interpretalassal hiba tortent: " << endl;
			cout << "\t" << iP.get_error() << endl;
			return -1;
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
			return -1;
		}
		cout << "Sikeres vegrehajtas!" << endl;
		allapot.print_allapot();
	}
	
	cout << "Nincs tobb vegrehajthato utasitas." << endl;
	allapot.print_allapot();
	
	cout << "Nyomjon entert a program bezarasahoz!" << endl;
	getline( cin, infile );
	
	return 0;
}