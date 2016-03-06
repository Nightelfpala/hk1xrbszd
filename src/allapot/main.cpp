#include <iostream>

#include "../allapot.h"

using namespace std;

void vec_cout(const vector<AP_UC> &ki, string pre = "");
void regiszter_teszt();
void verem_teszt();
void valtozo_teszt();

int main()
{
	regiszter_teszt();
	
	verem_teszt();
	
	valtozo_teszt();
	
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
		cout << "HELYES push-pop utan az eredeti vektort kaptuk vissza" << endl;
	} else
	{
		cout << "HIBA push-pop soran megvaltozott a vektor" << endl;
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
	
	cout << endl;
	vector<AP_UC> vec_AP_UC_2;
	ap.get_reg("esp", vec_AP_UC_2);
	vec_AP_UC_2[0] -= 8;
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
	
	vector<AP_UC> vec_AP_UC_3(2);
	vec_AP_UC_3[0] = vec_AP_UC_1[0];
	vec_AP_UC_3[1] = vec_AP_UC_1[1];
	ap.set_reg("ah", vec_AP_UC_3);
	ap.get_reg("eax", vec_AP_UC_2);
	vec_cout(vec_AP_UC_2, "atiras ah-ba bemasolasa majd eax-bol kiolvasas");
	
	vector<AP_UC> vec_ex(4, 1);
	vector<AP_UC> vec_x;
	
	ap.set_reg("ebx", vec_ex);
	ap.get_reg("bx", vec_x);
	vec_cout(vec_x, "ebx-be 4 db 1-es, bx:");
	
	vec_ex[0] = 2;
	ap.set_reg("ecx", vec_ex);
	ap.get_reg("cl", vec_x);
	vec_cout(vec_x, "ecx-be 2 1 1 1, cl:");
	
	vec_ex[1] = 3;
	ap.set_reg("edx", vec_ex);
	ap.get_reg("dh", vec_x);
	vec_cout(vec_x, "edx-be 2 3 1 1, dh:");
	
	vec_ex[2] = 4;
	ap.set_reg("ebp", vec_ex);
	ap.get_reg("bp", vec_x);
	vec_cout(vec_x, "ebp-be 2 3 4 1, bp:");
	
	ap.get_reg("ebx", vec_x);
	vec_cout(vec_x, "ekozben ebx nem valtozott, ugyanaz az 1 1 1 1, ebx:");
	
	cout << endl;
}

void valtozo_teszt()
{
	cout << "VALTOZO TESZT:" << endl;
	// x: 4 byteos, y: 2 byteos, z: 4 byteos
	map<string, int> valtozo_kezdetek;
	valtozo_kezdetek["x"] = 0;
	valtozo_kezdetek["y"] = 4;
	valtozo_kezdetek["z"] = 6;
	Allapot ap;
	ap.init(valtozo_kezdetek, 10);
	
	cout << "elso byte:" << endl << "x:\t" << ap.elso_byte("x") << endl << "y:\t" << ap.elso_byte("y") << endl << "z:\t" << ap.elso_byte("z") << endl;
	
	// [y] := 2 * 256 + 5
	vector<AP_UC> vy(2);
	vy[0] = 5; vy[1] = 2;
	ap.set_var(ap.elso_byte("y"), vy);
	cout << "[y] := 2 * 256 + 5" << endl;
	
	vector<AP_UC> vout;
	ap.get_var(ap.elso_byte("y"), 2, vout);
	vec_cout(vout, "y tartalma:");
	cout << endl;
	
	// [x + 2] := 7 * 256^3 + 9 * 256^2 + 11 * 256 + 13
	vector<AP_UC> vx_2(4);
	vx_2[0] = 13; vx_2[1] = 11;
	vx_2[2] = 9; vx_2[3] = 7;
	ap.set_var(ap.elso_byte("x") + 2, vx_2);
	cout << "[x + 2] := 7 * 256^3 + 9 * 256^2 + 11 * 256 + 13" << endl;
	
	ap.get_var(ap.elso_byte("x"), 4, vout);
	vec_cout(vout, "x tartalma:");
	ap.get_var(ap.elso_byte("y"), 2, vout);
	vec_cout(vout, "y tartalma:");
	
	cout << endl;
	
	vy.push_back(60); vy.push_back(40);
	ap.set_var(ap.elso_byte("y"), vy);
	cout << "vy vegehez 60, 40 hozzafuzve, y-ban eltarolva" << endl;
	ap.get_var(ap.elso_byte("y"), 2, vout);
	vec_cout(vout, "y tartalma:");
	ap.get_var(ap.elso_byte("z"), 4, vout);
	vec_cout(vout, "z tartalma:");
	
	cout << endl;
}