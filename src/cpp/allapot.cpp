
#include <algorithm>

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
	
	for (int i = 0; i < REG_SIZE; ++i)
	{
		eax[i] = 0;
		ebx[i] = 0;
		ecx[i] = 0;
		edx[i] = 0;
		esp[i] = 255;		// pointer ertek, igy a hozzaadas es a kivonas megfeleloen mukodik
		ebp[i] = 255;
	}
}

Allapot::~Allapot()
{
	//null
}

void Allapot::init( const std::map<std::string, int> &valtozo_kezdetek, const std::vector<AP_UC> &valt_vector)
{
	valtozo_elso = valtozo_kezdetek;
	valtozok_verem = valt_vector;
	max_valt = valtozok_verem.size();
	int szazasmeret = ((max_valt / 100) + 2) * 100;
	max_verem = szazasmeret - max_valt;
	max_verem_elert = 0;
	valtozok.resize(szazasmeret, 0);
}

void Allapot::veremNovel( int val = 100)
{
	vector<AP_UC> temp( valtozok_verem.size() + val, 0);
	for (int i = 0; i < max_valt; ++i)
	{
		temp[i] = valtozok_verem[i];
	}
	for (int i = 0; i < max_verem; ++i)
	{
		temp[ temp.size() - 1 - i] = valtozok_verem[ valtozok_verem.size() - 1 - i];
	}
	max_verem = temp.size() - max_valt;
	valtozok_verem = temp;
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
					int tmp = (vecc2revuint(esp) - max_verem);
					if ( tmp > 0 )
					{
						veremNovel( ((tmp * 3) > 100) ? (tmp * 3) : 100 );
						max_verem_elert = std::max(tmp, max_verem_elert);
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
						int tmp = (vecc2revuint(esp) - max_verem);
						if ( tmp > 0 )
						{
							veremNovel( ((tmp * 3) > 100) ? (tmp * 3) : 100 );
							max_verem_elert = std::max(tmp, max_verem_elert);
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

int Allapot::elso_byte( const std::string &valt_azon ) const
{
	return valtozo_elso.at(valt_azon);
}

void Allapot::get_var( const int &elso_byte, const int &hossz, std::vector<AP_UC> &to ) const	// TODO
{
	if ( (elso_byte < 0) || ((elso_byte + hossz) > max_valt ))
		throw HATARON_KIVULI_VALTOZO;
	to.resize(hossz);
	for (int i = 0; i < hossz; ++i)
	{
		to[i] = valtozok_verem[elso_byte + i];
	}
}

void Allapot::set_var( const int &elso_byte, const std::vector<AP_UC> &from )	// TODO
{
	int hossz = from.size();
	if ( (elso_byte < 0) || ( (elso_byte + hossz) > max_valt ))
		throw HATARON_KIVULI_VALTOZO;
	for (int i = 0; i < hossz; ++i)
	{
		valtozok_verem[elso_byte + i] = from[i];
	}
}

void Allapot::verem_push( const std::vector<AP_UC> &from )	// TODO
{
	AP_UI veremteto = verem_teteje();
	int meret = from.size();
	if ( max_verem < (veremteto + meret) )
	{
		veremNovel( ((veremteto + meret) > 100) ? (( veremteto + meret ) * 3 ) : 100 );
	}
	for (int i = 0; i < meret; ++i)
	{
		valtozok_verem[ valtozok_verem.size() - 1 - veremteto - i] = from[meret - 1 - i];
	}
	veremteto += meret;
	max_verem_elert = std::max(max_verem_elert, veremteto);
	revuint2vecc( veremteto, esp );
}

void Allapot::verem_pop ( const int &meret, std::vector<AP_UC> &to )	// TODO
{
	AP_UI veremteto = vecc2revuint(esp);
	if (veremteto < meret)
	{
		throw URES_VEREM;
	}
	to.resize(meret);
	for (int i = 0; i < meret; ++i)
	{
		to[i] = valtozok_verem[veremteto - 1 - i];	
	}
	veremteto -= meret;
	revuint2vecc( veremteto, esp);
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
	to.resize(verem_alja);
	for (int i = 0; i < to.size(); ++i)
	{
		to[i] = valtozok_verem[i];
	}
}

void Allapot::verem_vector( std::vector<AP_UC> &to ) const
{
	to.resize(valtozok_verem.size() - veremalja);
	for (int i = 0; i < to.size(); ++i)
	{
		to[i] = valtozok_verem[veremalja + i];
	}
}

AP_UI Allapot::verem_teteje() const
{
	return vecc2revuint(esp);
}
