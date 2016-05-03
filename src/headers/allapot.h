#ifndef ALLAPOT_H_INCLUDED
#define ALLAPOT_H_INCLUDED

#include <string>
#include <map>
#include <vector>

#include "typedefs.h"

class Allapot
{
public:
	Allapot();
	~Allapot();
	void init( const std::map<std::string, int> &valtozo_kezdetek, const std::vector<AP_UC> &valt_vector);
	
	//regiszter muveletek
	void get_reg( const std::string &reg_azon, std::vector<AP_UC> &to ) const;
	void set_reg( const std::string &reg_azon, const std::vector<AP_UC> &from );	// mindig a megadott vector legelso elemetol kezdodik a masolas
																					// akkor is, ha pl. "ah"-ba masolunk egy 2 hosszu vectorbol
		// A regiszter muveleteknel nem feltetlenul szukseges a teljes egyezes a regiszterek nevevel
		//	eleg egy egyertelmu minta is: pl. 3 karakterbol all, a 2. karakter 'a' -> eax
	
	bool get_zero() const;	// igaz akkor, ha "nulla" az eredmeny -- azaz az utolso muvelet vagy osszehasonlitaskor a ket argumentum megegyezik
	void set_zero( bool b);
	
	bool get_sign() const;	// igaz akkor, ha negativ az eredmeny -- azaz az utolso osszehasonlitaskor az elso (bal oldali) argumentum a kisebb
		// tehat a jb, jna ugrasok feltetele teljesul
	void set_sign( bool b);
	
	//valtozo muveletek
	AP_UI elso_byte( const std::string &valt_azon ) const;
	void get_var( const int &elso_byte, const AP_UI &hossz, std::vector<AP_UC> &to, bool verembol = 0 ) const;	// Exception: HATARON_KIVULI_VALTOZO vagy HATARON_KIVULI_VEREM ha az elmentett valtozo hatarokon kivulrol probal kivenni
	void set_var( const int &elso_byte, const std::vector<AP_UC> &from, bool verembe = 0 );	// Exception: HATARON_KIVULI_VALTOZO vagy HATARON_KIVULI_VEREM ha az elmentett valtozo hatarokon kivulre probal tarolni
	
	//verem muveletek
	void verem_push( const std::vector<AP_UC> &from );		// Exception: TELE_VEREM ha a veremben 0x0FFFFFFF (~26mio) byte talalhato
	void verem_pop ( const AP_UI &hossz, std::vector<AP_UC> &to );	// Exception: URES_VEREM ha nincs annyi byte, amennyit ki akarunk venni
	int verem_teteje () const;	// nem a tenyleges veremteto, az esp pointer mutatasi helye
	
	//kovetkezo utasitas muveletek
	AP_UI get_kovetkezo() const;
	void set_kovetkezo( const AP_UI &kov );
	
	//lekerdezo muveletek -- kiirashoz hasznalhato interface
	void valtozo_vector( std::vector<AP_UC> &to ) const;
	void verem_vector( std::vector<AP_UC> &to ) const;	// az egesz vermet visszadja, nem csak az esp pointerig tarto reszet
	void elso_valtozok( std::vector<std::string> &to ) const;	// ad egy vektort, amiben azokon az indexeken ahol valtozo kezdodik talalhato a valtozo neve, a tobbi ures string
	void vec_pointerek( std::vector<std::string> &to ) const;	// ad egy vektort, amiben az esp illetve ebp mutatasi helye be van jelolve (a tobbi ures string)
																	// ha ugyanoda mutatnak, akkor esp van kiirva
	
	//hibakezeles
		// csak olyan hibak kerulnek lekezelesre, ami a szimulalt program futasabol szarmaznak - feltetelezzuk, hogy a szimulalo program kodja helyes
	enum Exceptions
	{
		URES_VEREM,
		TELE_VEREM,
		HATARON_KIVULI_VALTOZO,
		HATARON_KIVULI_VEREM,
	};
private:
	//valtozok
	std::map<std::string, int> valtozo_elso;
	std::vector<AP_UC> valtozok;	// a verem es a valtozok tarolasa
		// felepites:	eleje						verem alja
				//		valt1	valt2		valt3	PUSH1	PUSH2	PUSH3
	
	//regiszterek
	std::vector<AP_UC> eax;
	std::vector<AP_UC> ebx;
	std::vector<AP_UC> ecx;
	std::vector<AP_UC> edx;
	
		// a pointer regiszterek erteke nem egyeznek meg a szimulalt program futasanak kozbeni tenyleges ertekekkel
		//	csak funkcionalisan felelnek meg neki
			// azaz esp a verem tetejere mutat, stack pointereket tarolhat
	std::vector<AP_UC> ebp;
	std::vector<AP_UC> esp;
	
	bool zeroflag;
	bool signflag;
	
	//futasideju verem
	std::vector<AP_UC> verem;	// nem tenyleges veremkent tarolva, szukseg van a belsejeben talalhato ertekekre is a folyamatos kiirashoz
	
	AP_UI kovetkezo_utasitas;
};

#endif	// ALLAPOT_H_INCLUDED 