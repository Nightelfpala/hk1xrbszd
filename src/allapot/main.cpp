#include <iostream>

#include "../allapot.h"

using namespace std;

void vec_cout(const vector<AP_UC> &ki, string pre = "");
void verem_teszt();
void regiszter_teszt();

int main()
{
	
	regiszter_teszt();
	
	verem_teszt();
	
	return 0;
}

void vec_cout(const vector<AP_UC> &ki, string pre)
{
	if (pre != "")
	{
		cout << pre << endl;
	}
	for (int i = 0; i < ki.size(); ++i)
	{
		cout << (int)ki[i] << "\t";
	}
	cout << endl;
}

void verem_teszt()
{
	// letrehoz egy vektort, rak bele nehany szamot
	//	pusholja a verembe, kiirja a verem tartalmat
	//	poppolja a verem tartalmat, osszehasonlitja az eredetivel
	//	kiirja a verem maradek tartalmat (az esp pointer ertekeig)
	
	cout << "VEREM TESZT:" << endl;
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
	vec_cout(abc, "eltarolt vector:");

	cout << "verem teteje pointerig byteok szama: " << ap.verem_teteje() << endl;
	
	ap.verem_push(abc);
	ap.verem_vector(abc);
	vec_cout(abc, "verem vector:");
	
	cout << "verem teteje pointerig byteok szama: " << ap.verem_teteje() << endl;
	
	ap.verem_pop( eredeti.size(), abc);
	cout << "pop vector (tarolt : eredeti):" << endl;
	for (unsigned int i = 0; i < abc.size(); ++i)
	{
		cout << (int)abc[i] << " : " << (int)eredeti[i] << " , ";
	}
	cout << endl;
	
	if (abc == eredeti)
	{
		cout << "HELYES! push-pop utan az eredeti vektort kaptuk vissza" << endl;
	} else
	{
		cout << "HIBA! push-pop soran megvaltozott a vektor" << endl;
	}
	
	ap.verem_vector(abc);
	vec_cout(abc, "verem vector:");
	cout << "verem teteje pointerig byteok szama: " << ap.verem_teteje() << endl;
	cout << endl;
}

void regiszter_teszt()
{
	
	cout << "REGISZTER TESZT:" << endl;
	Allapot ap;
	vector<AP_UC> abc(4);
	
	abc[0] = 5;
	abc[1] = 2;
	abc[2] = 1;
	abc[3] = 0;
	vector<AP_UC> eredeti = abc;
	vec_cout(abc, "eredeti vector:");
}