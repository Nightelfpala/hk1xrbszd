#include <iostream>

#include "../allapot.h"

using namespace std;

void verem_teszt();

int main()
{
	verem_teszt();
	
	return 0;
}

void verem_teszt()
{
	// letrehoz egy vektort, rak bele nehany szamot
	//	pusholja a verembe, kiirja a verem tartalmat
	//	poppolja a verem tartalmat, osszehasonlitja az eredetivel
	//	kiirja a verem maradek tartalmat (az esp pointer ertekeig)
	Allapot ap;
	vector<AP_UC> abc(8);
	
	abc[0] = 1;
	abc[1] = 3;
	abc[2] = 10;
	abc[3] = 50;
	abc[5] = 12;
	abc[6] = 1;
	abc[7] = 1;
	vector<AP_UC> eredeti = abc;
	cout << "eltarolt vektor :\t";
	for (unsigned int i = 0; i < abc.size(); ++i)
	{
		cout << (int)abc[i] << "\t";
	}
	cout << endl;
	
	ap.verem_push(abc);
	ap.verem_vector(abc);
	cout << endl << "verem vector:\t";
	for (unsigned int i = 0; i < abc.size(); ++i)
	{
		cout << (int)abc[i] << "\t";
	}
	cout << endl;
	
	ap.verem_pop( eredeti.size(), abc);
	cout << endl << "pop vector (tarolt : eredeti):\t";
	for (unsigned int i = 0; i < abc.size(); ++i)
	{
		cout << (int)abc[i] << " : " << (int)eredeti[i] << "\t,\t";
	}
	cout << endl;
	
	if (abc == eredeti)
	{
		cout << endl << "HELYES! push-pop utan az eredeti vektort kaptuk vissza" << endl;
	} else
	{
		cout << endl << "HIBA! push-pop soran megvaltozott a vektor" << endl;
	}
	
	ap.verem_vector(abc);
	cout << endl << "verem vector:\t";
	for (unsigned int i = 0; i < abc.size(); ++i)
	{
		cout << (int)abc[i] << "\t";
	}
	cout << endl;
}