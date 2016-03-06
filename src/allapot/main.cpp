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
	vector<AP_UC> vec_AP_UC_1(8);
	
	vec_AP_UC_1[0] = 1;
	vec_AP_UC_1[1] = 3;
	vec_AP_UC_1[2] = 10;
	vec_AP_UC_1[3] = 50;
	vec_AP_UC_1[5] = 12;
	vec_AP_UC_1[6] = 1;
	vec_AP_UC_1[7] = 1;
	vector<AP_UC> eredeti = vec_AP_UC_1;
	vec_cout(vec_AP_UC_1, "eltarolt vector:");

	cout << "verem teteje pointerig byteok szama: " << ap.verem_teteje() << endl;
	
	ap.verem_push(vec_AP_UC_1);
	ap.verem_vector(vec_AP_UC_1);
	vec_cout(vec_AP_UC_1, "verem vector:");
	
	cout << "verem teteje pointerig byteok szama: " << ap.verem_teteje() << endl;
	
	ap.verem_pop( eredeti.size(), vec_AP_UC_1);
	cout << "pop vector (tarolt : eredeti):" << endl;
	for (unsigned int i = 0; i < vec_AP_UC_1.size(); ++i)
	{
		cout << (int)vec_AP_UC_1[i] << " : " << (int)eredeti[i] << " , ";
	}
	cout << endl;
	
	if (vec_AP_UC_1 == eredeti)
	{
		cout << "HELYES! push-pop utan az eredeti vektort kaptuk vissza" << endl;
	} else
	{
		cout << "HIBA! push-pop soran megvaltozott a vektor" << endl;
	}
	
	ap.verem_vector(vec_AP_UC_1);
	vec_cout(vec_AP_UC_1, "verem vector:");
	cout << "verem teteje pointerig byteok szama: " << ap.verem_teteje() << endl;
	
	try
	{
		ap.verem_pop(4, vec_AP_UC_1);
		cout << "HIBA ures verembol lehetett 4 byteot poppolni" << endl;
	} catch (Allapot::Exceptions ex)
	{
		if (ex == Allapot::URES_VEREM)
		{
			cout << "HELYES ures verembol poppolva URES_VEREM exceptiont dobott" << endl;
		} else
		{
			cout << "HIBA ures verembol poppolva exceptiont dobott, de nem URES_VEREM -t" << endl;
		}
	}
	
	vector<AP_UC> vec_AP_UC_2;
	ap.get_reg("esp", vec_AP_UC_2);
	vec_AP_UC_2[0] -= 8;
	vec_cout(vec_AP_UC_2);
	ap.set_reg("esp", vec_AP_UC_2);
	cout << "esp modositas (-8) utan a verem teteje pointerig byteok szama: " << ap.verem_teteje() << endl;
	try
	{
		ap.verem_pop(4, vec_AP_UC_2);
		vec_cout(vec_AP_UC_2, "esp modositasa utani elso 4 byte-os pop:");
		ap.verem_pop(4, vec_AP_UC_2);
		vec_cout(vec_AP_UC_2, "esp modositasa utani masodik 4 byte-os pop:");
		cout << "HELYES esp allitas utani pop sikeres" << endl;
	} catch (Allapot::Exceptions ex)
	{
		cout << "HIBA esp allitas utani pop sikertelen" << endl;
	}
	
	cout << endl;
}

void regiszter_teszt()
{
	// csak eax es reszeire, a tobbi kodja megegyezik
	cout << "REGISZTER TESZT:" << endl;
	Allapot ap;
	vector<AP_UC> vec_AP_UC_1(4);
	
	vec_AP_UC_1[0] = 5;
	vec_AP_UC_1[1] = 2;
	vec_AP_UC_1[2] = 1;
	vec_AP_UC_1[3] = 0;
	vector<AP_UC> eredeti = vec_AP_UC_1;
	vec_cout(vec_AP_UC_1, "eredeti vector:");
	
	ap.set_reg("eax", vec_AP_UC_1);
	
	vector<AP_UC> vec_AP_UC_2;
	ap.get_reg("eax", vec_AP_UC_2);
	vec_cout(vec_AP_UC_2, "eax-bol gettelve");
	ap.get_reg("ax", vec_AP_UC_2);
	vec_cout(vec_AP_UC_2, "ax-bol gettelve");
	ap.get_reg("ah", vec_AP_UC_2);
	vec_cout(vec_AP_UC_2, "ah-bol gettelve");
	ap.get_reg("al", vec_AP_UC_2);
	vec_cout(vec_AP_UC_2, "al-bol gettelve");
	
	ap.get_reg("eax", vec_AP_UC_1);
	vec_AP_UC_1[0] = 11;
	vec_AP_UC_1[1] = 13;
	vec_cout(vec_AP_UC_1, "eax-bol get es 1., 2. atirasa");
	vector<AP_UC> vec_AP_UC_3(1, vec_AP_UC_1[1]);
	ap.set_reg("ah", vec_AP_UC_3);
	ap.get_reg("eax", vec_AP_UC_2);
	vec_cout(vec_AP_UC_2, "atiras ah-ba bemasolasa majd eax-bol kiolvasas");
	
	cout << endl;
}