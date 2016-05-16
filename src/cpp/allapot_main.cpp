#include <iostream>

#include "allapot.h"
#include "utils.h"

using namespace std;
using namespace Utils;

void flag_teszt();
void regiszter_teszt();
void verem_teszt();
void valtozo_teszt();
void verem_limit_teszt();

int main()
{
	flag_teszt();
	
	regiszter_teszt();
	
	verem_teszt();
	
	valtozo_teszt();
	
	verem_limit_teszt();
	
	return 0;
}

void flag_teszt()
{
	cout << "FLAG TESZT:" << endl;
	Allapot ap;
	cout << "zero flag alapallapot:\t" << ap.get_zero() << endl;
	ap.set_zero(true);
	cout << "zero flag atallitva igazra:\t" << ap.get_zero() << endl;
	
	cout << "sign flag alapallapot:\t" << ap.get_sign() << endl;
	ap.set_sign(true);
	cout << "sign flag atallitva igazra:\t" << ap.get_sign() << endl;
	
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
	vector<string> verem_nevek;
	
	vec_AP_UC_1[0] = 1;
	vec_AP_UC_1[1] = 3;
	vec_AP_UC_1[2] = 10;
	vec_AP_UC_1[3] = 50;
	vec_AP_UC_1[5] = 12;
	vec_AP_UC_1[6] = 1;
	vec_AP_UC_1[7] = 1;
	vector<AP_UC> eredeti = vec_AP_UC_1;
	vec_cout(vec_AP_UC_1, "eltarolando vector:");

	cout << "verem teteje pointerig byteok szama: " << ap.verem_teteje() << endl;
	
	ap.verem_push(vec_AP_UC_1);
	ap.verem_vector(vec_AP_UC_1);
	ap.vec_pointerek(verem_nevek);
	vec_cout(vec_AP_UC_1, "verem vector:");
	for (int i = 0; i < verem_nevek.size(); ++i)
	{
		cout << verem_nevek[i] << "\t";
	}
	cout << endl;
	
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
	ap.vec_pointerek(verem_nevek);
	vec_cout(vec_AP_UC_1, "verem vector:");
	for (int i = 0; i < verem_nevek.size(); ++i)
	{
		cout << verem_nevek[i] << "\t";
	}
	cout << endl;
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
	sint2vecc( vecc2sint(vec_AP_UC_2) - 8, vec_AP_UC_2);	// 8 byte-al megnoveli a verem melyseget	~	mov esp, esp - 8
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
	
	cout << "ezek utan a veremben " << ap.verem_teteje() << " byte van" << endl;
	vector<AP_UC> to(4);
	ap.get_reg("esp", to);
	ap.set_reg("ebp", to);
	cout << "mov ebp, esp	;	vegrehajtasa" << endl;
	to.resize(0);
	to.resize(4, 0);
	uint2vecc( 1, to );
	ap.verem_push(to);
	uint2vecc( 2, to );
	ap.verem_push(to);
	uint2vecc( 3, to );
	ap.verem_push(to);
	cout << "4 byte-os formaban 1, majd 2, majd 3 pusholva a verembe" << endl;
	try
	{
		ap.get_reg("ebp", to);
		int veremfele = vecc2sint ( to ) - 4;
		ap.get_var( veremfele, 4, to, 1);
		vec_cout( to, "[ebp - 4] lekerdezese:");
		
		ap.get_reg("ebp", to);
		veremfele = vecc2sint( to ) - 8;
		ap.get_var( veremfele, 4, to, 1);
		vec_cout( to, "[ebp - 8] lekerdezese:");
	} catch(Allapot::Exceptions ex)
	{
		cout << "HIBA [ebp - 4] vagy [ebp - 8] lekerdezese sikertelen" << endl;
	}
	ap.verem_vector( to );
	vec_cout(to, "verem vektor:");
	
	ap.vec_pointerek(verem_nevek);
	for (int i = 0; i < verem_nevek.size(); ++i)
	{
		cout << verem_nevek[i] << "\t";
	}
	cout << endl;
	cout << endl;
	
	try
	{
		ap.get_reg( "esp", vec_AP_UC_2 );
		sint2vecc( vecc2sint( vec_AP_UC_2 ) + 16, to );
		ap.set_reg( "esp", to );
		
		cout << "HIBA esp negativ szamra allitasa eseten nem dobott hibat" << endl;
		
		ap.print_allapot();
	} catch ( Allapot::Exceptions ex )
	{
		cout << "HELYES esp negativ szamra allitasa eseten NEGATIV_VEREM_MERET hibat dobott" << endl;
		ap.print_allapot();
		cout << endl;
		cout << "HELYES Az allapot nem modosult, a hibas erteket nem vette fel." << endl;
	}
	ap.verem_pop( 4, to );
	ap.verem_pop( 4, to );
	ap.verem_pop( 4, to );
	
	cout << "Mind a 12 byte poppolasa." << endl;
	cout << endl;
	try
	{
		ap.get_reg( "sp", vec_AP_UC_2 );
		vec_AP_UC_2[0] -= 1;
		ap.set_reg( "sp", to );
		
		cout << "HIBA sp-n keresztul esp negativ szamra allitasa eseten nem dobott hibat" << endl;
	} catch ( Allapot::Exceptions ex )
	{
		cout << "HELYES sp-n keresztul esp negativ szamra allitasa eseten NEGATIV_VEREM_MERET hibat dobott" << endl;
		ap.print_allapot();
		cout << "HELYES Az allapot nem modosult, a hibas erteket nem vette fel." << endl;
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
	
	ap.get_reg("ebx", vec_x);
	vec_cout(vec_x, "ekozben ebx nem valtozott, ugyanaz az 1 1 1 1, ebx:");
	
	ap.print_allapot();
	
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
	vector<AP_UC> init(10, 0);
	ap.init(valtozo_kezdetek, init);
	
	cout << "elso byte:" << endl << "x:\t" << (int)(ap.elso_byte("x")) << endl << "y:\t" << (int)(ap.elso_byte("y")) << endl << "z:\t" << (int)(ap.elso_byte("z")) << endl;
	
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
	
	cout << "Valtozok hibakezeles ellenorzese:" << endl;
	try
	{
		ap.get_var(-1, 2, vout);
		cout << "HIBA nem dobott -1 -tol kiolvasasra hibat" << endl;
		vec_cout(vout, "kiolvasott valtozok:");
		ap.valtozo_vector(vout);
		vec_cout(vout, "tarolt valtozok:");
	} catch (Allapot::Exceptions ex)
	{
		if (ex == Allapot::HATARON_KIVULI_VALTOZO)
		{
			cout << "HELYES -1 -tol kezdve a valtozobol kivetelt HATARON_KIVULI_VALTOZO -t dobott" << endl;
		} else
		{
			cout << "HIBA -1 -tol kezdve a kivetelt rossz hibat dobott" << endl;
		}
	}
	try
	{
		ap.get_var(7, 4, vout);
		cout << "HIBA nem dobott 7-11. byteok (10 bytenyi valtozobol) kiolvasasara hibat" << endl;
		vec_cout(vout, "kiolvasott valtozok:");
		ap.valtozo_vector(vout);
		vec_cout(vout, "tarolt valtozok:");
	} catch (Allapot::Exceptions ex)
	{
		if (ex == Allapot::HATARON_KIVULI_VALTOZO)
		{
			cout << "HELYES 7-11. byteok kivetele (10 bytenyi valtozobol) a valtozobol HATARON_KIVULI_VALTOZO -t dobott" << endl;
		} else
		{
			cout << "HIBA 7-11. byteok kivetele (10 bytenyi valtozobol) a valtozobol rossz hibat dobott" << endl;
		}
	}
	try
	{
		ap.set_var(-1, vx_2);
		cout << "HIBA nem dobott -1 -tol eltarolasra hibat" << endl;
		vec_cout(vx_2, "lementett valtozok:");
		ap.valtozo_vector(vout);
		vec_cout(vout, "tarolt valtozok:");
	} catch (Allapot::Exceptions ex)
	{
		if (ex == Allapot::HATARON_KIVULI_VALTOZO)
		{
			cout << "HELYES -1 -tol kezdve a valtozoba berakast HATARON_KIVULI_VALTOZO -t dobott" << endl;
		} else
		{
			cout << "HIBA -1 -tol kezdve a valtozoba berakast rossz hibat dobott" << endl;
		}
	}
	try
	{
		ap.set_var(7, vx_2);
		cout << "HIBA nem dobott 7-11. byteok (10 bytenyi valtozobol) eltarolasara hibat" << endl;
		vec_cout(vx_2, "lementett valtozok:");
		ap.valtozo_vector(vout);
		vec_cout(vout, "tarolt valtozok:");
	} catch (Allapot::Exceptions ex)
	{
		if (ex == Allapot::HATARON_KIVULI_VALTOZO)
		{
			cout << "HELYES 7-11. byteok berakasa (10 bytenyi valtozobol) a valtozoba HATARON_KIVULI_VALTOZO -t dobott" << endl;
		} else
		{
			cout << "HIBA 7-11. byteok berakasa (10 bytenyi valtozobol) a valtozoba rossz hibat dobott" << endl;
		}
	}
	
	ap.print_allapot();
	
	cout << endl;
}

void verem_limit_teszt()
{
	cout << "Verem limit teszt:" << endl;
	Allapot ap;
	
	vector<AP_UC> vec(4);
	for (int i = 0; i < 4; ++i)
	{
		vec[i] = i + 1;
	}
	
	AP_UI j = 0;
	try
	{
		while (1)
		{
			ap.verem_push( vec );
			++j;
		}
	} catch (Allapot::Exceptions ex)
	{
		if (ex == Allapot::TELE_VEREM)
		{
			cout << "A verem " << j << " db 4-byteos pusholas utan dobott TELE_VEREM hibat, osszesen " << (4 * j) << " byte kerult bele." << endl;
			cout << "Ekkor a verem teteje:\t" << ap.verem_teteje() << endl;
		} else
		{
			cout << "HIBA a verem tultoltes elott mas hibat dobott" << endl;
		}
	}
	
	cout << endl;
}