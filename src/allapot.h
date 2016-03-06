#ifndef ALLAPOT_H_INCLUDED
#define ALLAPOT_H_INCLUDED

#include <map>
#include <vector>

class allapot
{
public:
	allapot();
	~allapot();
	
	//regiszter muveletek
	void get_reg( const std::string &reg_azon, std::vector<char> &to );
	void set_reg( const std::string &reg_azon, const std::vector<char> &from ) const;
	
	bool get_zero() const;
	void set_zero( bool b);
	
	bool get_sign() const;
	void set_sign( bool b);
	
	//valtozo muveletek
	int elso_byte( const std::string &valt_azon ) const;
	void get_var( const int &elso_byte, const int &hossz, std::vector<char> &to );
	void set_var( const int &elso_byte, const std::vector<char> &from );
	
	//verem muveletek
	void verem_push( const std::vector<char> &from );
	void verem_pop ( const int &hossz, std::vector<char> &to );
	
	//kovetkezo utasitas muveletek
	int get_kovetkezo() const;
	void set_kovetkezo( const int &kov );
	
	
	//lekerdezo muveletek -- kiirashoz hasznalhato interface
	void valtozo_vector( std::vector<char> &to ) const;
	void verem_vector( std::vector<char> &to ) const;
	
private:
	//valtozok
	std::map<string, int> valtozo_elso;
	std::vector<char> valtozok;
	
	//regiszterek
	std::vector<char> eax;
	std::vector<char> ebx;
	std::vector<char> ecx;
	std::vector<char> edx;
	
	std::vector<char> ebp;
	std::vector<char> esp;
	
	bool zeroflag;
	bool signflag;
	
	//futasideju verem
	std::vector<char> verem;	// nem tenyleges veremkent tarolva, szukseg van a belsejeben talalhato ertekekre is a folyamatos kiirashoz
	
	int kovetkezo_utasitas;
};

#endif	// ALLAPOT_H_INCLUDED 