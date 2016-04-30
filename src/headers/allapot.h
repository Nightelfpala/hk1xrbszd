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
	int elso_byte( const std::string &valt_azon ) const;
	void get_var( const int &elso_byte, const int &hossz, std::vector<AP_UC> &to ) const;	// Exception: HATARON_KIVULI_VALTOZO ha az elmentett valtozo hatarokon kivulrol probal kivenni
	void set_var( const int &elso_byte, const std::vector<AP_UC> &from );	// Exception: HATARON_KIVULI_VALTOZO ha az elmentett valtozo hatarokon kivulre probal tarolni
	
	//verem muveletek
	void verem_push( const std::vector<AP_UC> &from );
	void verem_pop ( const int &hossz, std::vector<AP_UC> &to );	// Exception: URES_VEREM ha nincs annyi byte, amennyit ki akarunk venni
	AP_UI verem_teteje () const;	// nem a tenyleges veremteto, az esp pointer mutatasi helye
	
	//kovetkezo utasitas muveletek
	int get_kovetkezo() const;
	void set_kovetkezo( const int &kov );
	
	//lekerdezo muveletek -- kiirashoz hasznalhato interface
	void valtozo_vector( std::vector<AP_UC> &to ) const;
	void verem_vector( std::vector<AP_UC> &to ) const;	// az egesz vermet visszadja, nem csak az esp pointerig tarto reszet
	
	//hibakezeles
		// csak olyan hibak kerulnek lekezelesre, ami a szimulalt program futasabol szarmaznak - feltetelezzuk, hogy a szimulalo program kodja helyes
	enum Exceptions
	{
		URES_VEREM,
		HATARON_KIVULI_VALTOZO,
	};
private:
	//valtozok
	std::map<std::string, int> valtozo_elso;
	std::vector<AP_UC> valtozok_verem;	// a verem es a valtozok tarolasa
		// felepites:	eleje						verem alja
				//		valt1	valt2		valt3	PUSH1	PUSH2
	int max_valt;	// a valtozoknak hany byte van lefoglalva
	int max_verem;	// a verem jelenlegi helyzeteben max hany byteot hasznalhat
	int max_verem_elert;
	
	void veremNovel( int val );	// ha a verem teteje belelogna a valtozok koze, ezzel noveljuk a rendelkezesre allo helyet
	
	//regiszterek
	std::vector<AP_UC> eax;
	std::vector<AP_UC> ebx;
	std::vector<AP_UC> ecx;
	std::vector<AP_UC> edx;
	
		// a pointer regiszterek erteke nem egyeznek meg a szimulalt program futasanak kozbeni tenyleges ertekekkel
		//	csak funkcionalisan felelnek meg neki
			// azaz esp a verem tetejere mutat, ebp alprogram hivas eseten a visszateresi hely
	std::vector<AP_UC> ebp;
	std::vector<AP_UC> esp;
	
	bool zeroflag;
	bool signflag;
	
	//futasideju verem
	//std::vector<AP_UC> verem;	// nem tenyleges veremkent tarolva, szukseg van a belsejeben talalhato ertekekre is a folyamatos kiirashoz
	
	int kovetkezo_utasitas;
};

#endif	// ALLAPOT_H_INCLUDED 