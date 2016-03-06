
#include "allapot.h"

#define REG_SIZE 4

using namespace std;


allapot::allapot() : zeroflag(false), signflag(false), kovetkezo_utasitas(0)
{
	eax.resize(4);	// TODO: add other registers once this works properly (also to get_reg and set_reg)
	
	
	//ebp.resize(4);
	esp.resize(4);
	
	for (int i = 0; i < REG_SIZE; ++i)
	{
		eax[i] = 0;
		esp[i] = 0;
	}
}

allapot::~allapot()
{
	//null
}

void allapot::init( const std::map<std::string, int> &valtozo_kezdetek, const int &valt_hossz)
{
	valtozo_elso = valtozo_kezdetek;
	valtozok.resize(valt_hossz);
}

void allapot::get_reg( const std::string &reg_azon, std::vector<char> &to )
{
	
}

void allapot::set_reg( const std::string &reg_azon, const std::vector<char> &from ) const
{
	
}

bool allapot::get_zero() const
{
	return zeroflag;
}

void allapot::set_zero( bool b)
{
	zeroflag = b;
}
	
bool allapot::get_sign() const
{
	return signflag;
}

void allapot::set_sign( bool b)
{
	signflag = b;
}
	

int allapot::elso_byte( const std::string &valt_azon ) const
{
	return valtozo_elso.at(valt_azon);
}

void allapot::get_var( const int &elso_byte, const int &hossz, std::vector<char> &to )
{
	
}

void allapot::set_var( const int &elso_byte, const std::vector<char> &from )
{
	
}

void allapot::verem_push( const std::vector<char> &from )
{
	
}

void allapot::verem_pop ( const int &hossz, std::vector<char> &to )
{
	to.resize(hossz);
	int veremteto = vecc2int(esp);
	for (int i = 0; i < hossz; ++i)
	{
		to[i] = verem[veremteto - i];
	}
}

int allapot::get_kovetkezo() const
{
	return kovetkezo_utasitas;
}

void allapot::set_kovetkezo( const int &kov )
{
	kovetkezo_utasitas = kov;
}

void allapot::valtozo_vector( std::vector<char> &to ) const
{
	to = valtozok;
}

void allapot::verem_vector( std::vector<char> &to ) const
{
	to = verem;
}

// segedmuveletek
int allapot::vecc2int( const std::vector<char> &from) const
{
	int result = 0;
	for (unsigned int i = 0; i < from.size(); ++i)
	{
		result *= 256;
		result += from[(from.size() - 1 - i)];	// tarolas: legkisebb helyierteku bit van elol
	}
	return result;
}