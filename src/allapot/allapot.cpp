
#include "../allapot.h"

#define REG_SIZE 4

using namespace std;


Allapot::Allapot() : zeroflag(false), signflag(false), kovetkezo_utasitas(0)
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

Allapot::~Allapot()
{
	//null
}

void Allapot::init( const std::map<std::string, int> &valtozo_kezdetek, const int &valt_hossz)
{
	valtozo_elso = valtozo_kezdetek;
	valtozok.resize(valt_hossz);
}

void Allapot::get_reg( const std::string &reg_azon, std::vector<AP_UC> &to ) const
{
	
}

void Allapot::set_reg( const std::string &reg_azon, const std::vector<AP_UC> &from )
{
	
}

bool Allapot::get_zero() const
{
	return zeroflag;
}

void Allapot::set_zero( bool b)
{
	zeroflag = b;
}
	
bool Allapot::get_sign() const
{
	return signflag;
}

void Allapot::set_sign( bool b)
{
	signflag = b;
}

int Allapot::elso_byte( const std::string &valt_azon ) const
{
	return valtozo_elso.at(valt_azon);
}

void Allapot::get_var( const int &elso_byte, const int &hossz, std::vector<AP_UC> &to ) const
{
	to.resize(hossz);
	for (int i = 0; i < hossz; ++i)
	{
		to[i] = valtozok[elso_byte + i];
	}
}

void Allapot::set_var( const int &elso_byte, const std::vector<AP_UC> &from )
{
	
}

void Allapot::verem_push( const std::vector<AP_UC> &from )
{
	int veremteto = vecc2int(esp);
	int meret = from.size();
	if ( verem.size() < (veremteto + meret) )
	{
		verem.resize(veremteto + meret);
	}
	for (int i = 0; i < meret; ++i)
	{
		verem[veremteto + i] = from[meret - 1 - i];
	}
	veremteto += meret;
	int2vecc( veremteto, esp );
}

void Allapot::verem_pop ( const int &meret, std::vector<AP_UC> &to )
{
	to.resize(meret);
	int veremteto = vecc2int(esp);
	for (int i = 0; i < meret; ++i)
	{
		to[i] = verem[veremteto - 1 - i];	
	}
	veremteto -= meret;
	int2vecc( veremteto, esp);
}

int Allapot::get_kovetkezo() const
{
	return kovetkezo_utasitas;
}

void Allapot::set_kovetkezo( const int &kov )
{
	kovetkezo_utasitas = kov;
}

void Allapot::valtozo_vector( std::vector<AP_UC> &to ) const
{
	to = valtozok;
}

void Allapot::verem_vector( std::vector<AP_UC> &to ) const
{
	to = verem;
}

// segedmuveletek
int Allapot::vecc2int( const std::vector<AP_UC> &from) const
{
	int result = 0;
	for (unsigned int i = 0; i < from.size(); ++i)
	{
		result *= 256;
		result += from[(from.size() - 1 - i)];	// tarolas: legkisebb helyierteku bit van elol
	}
	return result;
}

void Allapot::int2vecc ( const int &from, std::vector<AP_UC> &to ) const
{
	int akt = from;
	for (unsigned int i = 0; i < to.size(); ++i)
	{
		to[i] = akt % 256;
		akt /= 256;
	}
}