
#include <algorithm>
#include <iostream>

#include "allapot.h"
#include "utils.h"

#define REG_SIZE 4

using namespace std;
using namespace Utils;


Allapot::Allapot() : zeroflag(false), signflag(false), kovetkezo_utasitas(0)
{
	eax.resize(4);
	ebx.resize(4);
	ecx.resize(4);
	edx.resize(4);
	
	ebp.resize(4);
	esp.resize(4);
	
	uint2vecc( 0, eax);
	ebx = eax;
	ecx = eax;
	edx = eax;
	
	sint2vecc( 0, esp);
	ebp = esp;
	
	verem.resize(0);
}

Allapot::~Allapot()
{
	//null
}

void Allapot::init( const std::map<std::string, int> &valtozo_kezdetek, const std::vector<AP_UC> &valt_vector)
{
	valtozo_elso = valtozo_kezdetek;
	valtozok = valt_vector;
}

void Allapot::get_reg( const std::string &reg_azon, std::vector<AP_UC> &to ) const
{
	switch (reg_azon.size())
	{
	case 3:
		{
			switch (reg_azon[1])	// b-nel vigyazni : ebp, ebx
			{
			case 'a':
				{
					to = eax;
					break;
				}
			case 'b':
				{
					if ( reg_azon == "ebx" )
					{
						to = ebx;
					} else
					{
						to = ebp;
					}
					break;
				}
			case 'c':
				{
					to = ecx;
					break;
				}
			case 'd':
				{
					to = edx;
					break;
				}
			case 's':
				{
					to = esp;
					break;
				}
			}
			break;
		}
	case 2:
		{
		switch (reg_azon[1])
		{
		case 'x': case 'p':
			{
				to.resize(2);
				switch (reg_azon[0])
				{
				case 'a':
					{
						for (int i = 0; i < 2; ++i)
						{
							to[i] = eax[i];
						}
						break;
					}
				case 'b':
					{
						if ( reg_azon == "bx")
						{
							for (int i = 0; i < 2; ++i)
							{
								to[i] = ebx[i];
							}
						} else
						{
							for (int i = 0; i < 2; ++i)
							{
								to[i] = ebp[i];
							}
						}
						break;
					}
				case 'c':
					{
						for (int i = 0; i < 2; ++i)
						{
							to[i] = ecx[i];
						}
						break;
					}
				case 'd':
					{
						for (int i = 0; i < 2; ++i)
						{
							to[i] = edx[i];
						}
						break;
					}
				case 's':
					{
						for (int i = 0; i < 2; ++i)
						{
							to[i] = esp[i];
						}
						break;
					}
				}
				break;
			}
		case 'h':
			{
				to.resize(1);
				switch (reg_azon[0])
				{
				case 'a':
					{
						to[0] = eax[1];
						break;
					}
				case 'b':
					{
						to[0] = ebx[1];
						break;
					}
				case 'c':
					{
						to[0] = ecx[1];
						break;
					}
				case 'd':
					{
						to[0] = edx[1];
						break;
					}
				}
				break;
			}
		case 'l':
			{
				to.resize(1);
				switch (reg_azon[0])
				{
				case 'a':
					{
						to[0] = eax[0];
						break;
					}
				case 'b':
					{
						to[0] = ebx[0];
						break;
					}
				case 'c':
					{
						to[0] = ecx[0];
						break;
					}
				case 'd':
					{
						to[0] = edx[0];
						break;
					}
				}
				break;
			}
		}
		break;
		}
	}
}

void Allapot::set_reg( const std::string &reg_azon, const std::vector<AP_UC> &from )
{
	switch (reg_azon.size())
	{
	case 3:
		{
			switch (reg_azon[1])	// b-nel vigyazni : ebp, ebx
			{
			case 'a':
				{
					for (int i = 0; i < REG_SIZE; ++i)
					{
						eax[i] = from[i];
					}
					break;
				}
			case 'b':
				{
					if ( reg_azon == "ebx" )
					{
						for (int i = 0; i < REG_SIZE; ++i)
						{
							ebx[i] = from[i];
						}
					} else
					{
						for (int i = 0; i < REG_SIZE; ++i)
						{
							ebp[i] = from[i];
						}
					}
					break;
				}
			case 'c':
				{
					for (int i = 0; i < REG_SIZE; ++i)
					{
						ecx[i] = from[i];
					}
					break;
				}
			case 'd':
				{
					for (int i = 0; i < REG_SIZE; ++i)
					{
						edx[i] = from[i];
					}
					break;
				}
			case 's':
				{
					for (int i = 0; i < REG_SIZE; ++i)
					{
						esp[i] = from[i];
					}
					// amennyiben magasabb pontra mutat a verem teteje, mint amekkora a vektora, noveljuk meg a meretet
					int tmp = vecc2sint(esp);
					cout << "tmp:\t" << tmp << endl;
					if ( tmp > verem.size() )
					{
						verem.resize( tmp );
					}
					break;
				}
				
			}
			break;
		}
	case 2:
		{
			switch (reg_azon[1])
			{
			case 'x': case 'p':
				switch (reg_azon[0])
				{
				case 'a':
					{
						for (int i = 0; i < 2; ++i)
						{
							eax[i] = from[i];
						}
						break;
					}
				case 'b':
					{
						if ( reg_azon == "eb" )
						{
							for (int i = 0; i < 2; ++i)
							{
								ebx[i] = from[i];
							}
						} else
						{
							for (int i = 0; i < 2; ++i)
							{
								ebp[i] = from[i];
							}
						}
						break;
					}
				case 'c':
					{
						for (int i = 0; i < 2; ++i)
						{
							ecx[i] = from[i];
						}
						break;
					}
				case 'd':
					{
						for (int i = 0; i < 2; ++i)
						{
							edx[i] = from[i];
						}
						break;
					}
				case 's':
					{
						for (int i = 0; i < 2; ++i)
						{
							esp[i] = from[i];
						}
						// amennyiben magasabb pontra mutat a verem teteje, mint amekkora a vektora, noveljuk meg a meretet
						int tmp = vecc2sint(esp);
						if ( tmp > verem.size() )
						{
							verem.resize( tmp );
						}
						break;
					}
				}
				break;
			case 'h':
				{
					switch (reg_azon[0])
					{
					case 'a':
						{
							eax[1] = from[0];
							break;
						}
					case 'b':
						{
							ebx[1] = from[0];
							break;
						}
					case 'c':
						{
							ecx[1] = from[0];
							break;
						}
					case 'd':
						{
							edx[1] = from[0];
							break;
						}
					}
					break;
				}
			case 'l':
				{
					switch (reg_azon[0])
					{
					case 'a':
						{
							eax[0] = from[0];
							break;
						}
					case 'b':
						{
							ebx[0] = from[0];
							break;
						}
					case 'c':
						{
							ebx[0] = from[0];
							break;
						}
					case 'd':
						{
							ebx[0] = from[0];
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
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

AP_UI Allapot::elso_byte( const std::string &valt_azon ) const
{
	return valtozo_elso.at(valt_azon);
}

void Allapot::get_var( const int &elso_byte, const AP_UI &hossz, std::vector<AP_UC> &to, bool verembol ) const	// TODO
{
	int elso = elso_byte;
	to.resize( hossz );
	if (verembol == 0)
	{
		if ( (elso < 0) || (( elso + hossz ) > valtozok.size()) )
			throw HATARON_KIVULI_VALTOZO;
		for ( int i = 0; i < hossz; ++i)
		{
			to[i] = valtozok[ elso + i ];
		}
	} else	// verembol == 1, verembol veszunk ki
	{
		elso *= -1;
		if ( (elso > verem.size() ) || (( elso - hossz ) < 0) )
			throw HATARON_KIVULI_VEREM;
		for ( int i = 0; i < hossz; ++i)
		{
			to[i] = verem[ elso - 1 - i ];
		}
	}
}

void Allapot::set_var( const int &elso_byte, const std::vector<AP_UC> &from, bool verembe )	// TODO
{
	int elso = elso_byte;
	int hossz = from.size();
	if (verembe == 0)
	{
		if ( (elso < 0 ) || (( elso + hossz) > valtozok.size()) )
			throw HATARON_KIVULI_VALTOZO;
		for ( int i = 0; i < hossz; ++i)
		{
			valtozok[ elso + i ] = from[i];
		}
	} else	// verembe == 1, verembe irunk felul
	{
		elso *= -1;
		if ( (elso > verem.size() ) || (( elso - hossz ) < 0) )
			throw HATARON_KIVULI_VEREM;
		for ( int i = 0; i < hossz; ++i)
		{
			verem[ elso - 1 - i] = from[i];
		}
	}
}

void Allapot::verem_push( const std::vector<AP_UC> &from )	// TODO
{
	int veremteto = verem_teteje();
	//cout << "veremteto:\t" << veremteto << endl;
	int meret = from.size();
	if ( veremteto + meret > UTILS_SIGNED_ZERO )
		throw TELE_VEREM;
	if ( verem.size() < (veremteto + meret) )
	{
		verem.resize( veremteto + meret );
	}
	for (int i = 0; i < meret; ++i)
	{
		verem[ veremteto + i ] = from[meret - 1 - i];
	}
	veremteto += meret;
	sint2vecc( -veremteto, esp );
	cout << "push vege" << endl;
}

void Allapot::verem_pop ( const AP_UI &meret, std::vector<AP_UC> &to )	// TODO
{
	int veremteto = verem_teteje();
	cout << "veremteto:\t" << veremteto << endl;
	if ( veremteto < meret)
	{
		throw URES_VEREM;
	}
	to.resize(meret);
	for (int i = 0; i < meret; ++i)
	{
		to[i] = verem[veremteto - 1 - i];	
	}
	veremteto -= meret;
	sint2vecc( -veremteto, esp);
}

AP_UI Allapot::get_kovetkezo() const
{
	return kovetkezo_utasitas;
}

void Allapot::set_kovetkezo( const AP_UI &kov )
{
	kovetkezo_utasitas = kov;
}

void Allapot::valtozo_vector( std::vector<AP_UC> &to ) const
{
	to.resize( valtozok.size() );
	for (int i = 0; i < to.size(); ++i)
	{
		to[i] = valtozok[i];
	}
}

void Allapot::verem_vector( std::vector<AP_UC> &to ) const
{
	to.resize( verem.size() );
	for (int i = 0; i < to.size(); ++i)
	{
		to[i] = verem[i];
	}
}

void Allapot::elso_valtozok( std::vector<std::string> &to ) const
{
	to.resize( valtozok.size() , "");
	for ( map<string, int>::const_iterator it = valtozo_elso.begin(); it != valtozo_elso.end(); ++it)
	{
		to[ it->second ] = it->first;
	}
}

void Allapot::vec_pointerek( std::vector<std::string> &to ) const
{
	to.resize( verem.size() + 1, "");
	to[ -vecc2sint(ebp) ] = "ebp";
	to[ -vecc2sint(esp) ] = "esp";
}

int Allapot::verem_teteje() const
{
	return -vecc2sint(esp);
}
