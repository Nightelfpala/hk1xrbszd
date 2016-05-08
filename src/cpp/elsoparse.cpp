#include <fstream>

#include "elsoparseParser.h"
#include "utils.h"

using namespace std;

int main(int argc, char* argv[])
{
	
	ifstream bef;
	bef.open("../testfiles/teszt1.asm");
	
	elsoparseParser epP(bef);
	int p;
	try
	{
		p = epP.completeParse();
		
		map<int, utasitas_data> utasitasok = epP.get_utasitasok();
		map<string, int> valtkezdet = epP.get_valtozokezdet();
		map<string, int> ugrocimkek = epP.get_ugrocimke();
		vector<AP_UC> valtozok = epP.get_valtozok();
		
		//cout << "Uresek? " << utasitasok.empty() << "\t" << valtkezdet.empty() << "\t" << ugrocimkek.empty() << "\t" << valtozok.empty() << endl;
		
		cout << "Utasitasok:" << endl;
		for (map<int, utasitas_data>::iterator it = utasitasok.begin(); it != utasitasok.end(); ++it)
		{
			
			cout << it->first << ". utasitas:" << endl
				<< "\t" << it->second.eredetisorszam << ". sorban eredetileg" << endl
				<< "\t" << it->second.utasitassorszam << ". utasitaskent eltarolt" << endl
				<< "\t" << it->second.argmeret << " byteos argumentumokkal" << endl
				<< "\t" << it->second.sor << endl;
			cout << endl;
		}
		cout << endl << endl;
		
		cout << "Valtozo kezdetek:" << endl;
		for (map<string, int>::iterator it = valtkezdet.begin(); it != valtkezdet.end(); ++it)
		{
			cout << it->first << " valtozonak elso byteja\t" << it->second << "." << endl;
		}
		cout << endl;
		
		cout << "Ugrocimkek:" << endl;
		for (map<string, int>::iterator it = ugrocimkek.begin(); it != ugrocimkek.end(); ++it)
		{
			cout << it->first << " cimket koveto utasitas\t" << it->second << "." << endl;
		}
		cout << endl;
		
		cout << "Valtozo vektor:" << endl;
		for (vector<AP_UC>::iterator it = valtozok.begin(); it != valtozok.end(); ++it)
		{
			cout << (int)*it << "\t";
		}
		cout << endl;
		
		cout << "Veget jelzo utasitasszam: " << epP.get_utolsoutasitas() << endl;
		cout << endl;
	} catch(elsoparseParser::Exceptions ex)
	{
		
		cout << "Hiba parse kozben:" << endl
			<< epP.get_error() << endl;
		
		return -1;
	}
	
	return 0;
};