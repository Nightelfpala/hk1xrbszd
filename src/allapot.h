#ifndef ALLAPOT_H_INCLUDED
#define ALLAPOT_H_INCLUDED

#include <string>
#include <map>
#include <vector>

typedef unsigned char AP_UC;
typedef unsigned int AP_UI;

class Allapot
{
public:
	Allapot();
	~Allapot();
	void init( const std::map<std::string, int> &valtozo_kezdetek, const int &valt_hossz);
	
	//regiszter muveletek
	void get_reg( const std::string &reg_azon, std::vector<AP_UC> &to ) const;
	void set_reg( const std::string &reg_azon, const std::vector<AP_UC> &from );	// mindig a megadott vector legelso elemetol kezdodik a masolas
																					// akkor is, ha pl. "ah"-ba masolunk egy 2 hosszu vectorbol
		// A regiszter muveleteknel nem feltetlenul szukseges a teljes egyezes a regiszterek nevevel
		//	eleg egy egyertelmu minta is: pl. 3 karakterbol all, a 2. karakter 'a' -> eax
	
	bool get_zero() const;
	void set_zero( bool b);
	
	bool get_sign() const;
	void set_sign( bool b);
	
	//valtozo muveletek
	int elso_byte( const std::string &valt_azon ) const;
	void get_var( const int &elso_byte, const int &hossz, std::vector<AP_UC> &to ) const;
	void set_var( const int &elso_byte, const std::vector<AP_UC> &from );
	
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
	enum Exceptions
	{
		URES_VEREM,
	};
private:
	//valtozok
	std::map<std::string, int> valtozo_elso;
	std::vector<AP_UC> valtozok;
	
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
	std::vector<AP_UC> verem;	// nem tenyleges veremkent tarolva, szukseg van a belsejeben talalhato ertekekre is a folyamatos kiirashoz
	
	int kovetkezo_utasitas;
	
	//segedmuvelet (veremkezeles)
	//	a rev elotagu muveletek a bitenkenti ellentettjet allitjak elo
	AP_UI vecc2uint( const std::vector<AP_UC> &from ) const;
	AP_UI vecc2revuint( const std::vector<AP_UC> &from ) const;
	void uint2vecc( const AP_UI &from, std::vector<AP_UC> &to ) const;
	void revuint2vecc( const AP_UI &from, std::vector<AP_UC> &to ) const;
};

#endif	// ALLAPOT_H_INCLUDED 