
#include <algorithm>
#include <iostream>
#include <sstream>

#include "allapot.h"
#include "utils.h"

#define REG_SIZE 4

using namespace std;
using namespace Utils;


Allapot::Allapot() : zeroflag(false), signflag(false), kovetkezo_utasitas(0), utasitasszam(0)
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

void Allapot::get_reg( const std::string &reg_azon, std::vector<AP_UC> &to ) const
{
	switch (reg_azon.size())
	{
	case 3:
		{
			to.resize(4);
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
					int tmp = -vecc2sint( from );
					if ( tmp < 0 )
					{	// hogyha a verem merete 0 ala csokkenne, hibat dobunk, es nem hajtjuk vegre
						throw NEGATIV_VEREM_MERET;
					}
					for (int i = 0; i < REG_SIZE; ++i)
					{
						esp[i] = from[i];
					}
					// amennyiben magasabb pontra mutat a verem teteje, mint amekkora a vektora, noveljuk meg a meretet
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
						if ( reg_azon == "bx" )
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
						vector<AP_UC> newfrom = from;
						newfrom.push_back( esp[2] );
						newfrom.push_back( esp[3] );
						int tmp = -vecc2sint( newfrom );
						if ( tmp < 0 )
						{	// nem engedjuk a verem melyseget negativra allitani
							throw NEGATIV_VEREM_MERET;
						}
						for (int i = 0; i < 2; ++i)
						{
							esp[i] = from[i];
						}
						// amennyiben magasabb pontra mutat a verem teteje, mint amekkora a vektora, noveljuk meg a meretet
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

void Allapot::get_var( const int &elso_byte, const AP_UI &hossz, std::vector<AP_UC> &to, bool verembol ) const
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
		if ( (elso > verem.size() ) || (elso < hossz ) )
			throw HATARON_KIVULI_VEREM;
		for ( int i = 0; i < hossz; ++i)
		{
			to[i] = verem[ elso - 1 - i ];
		}
	}
}

void Allapot::set_var( const int &elso_byte, const std::vector<AP_UC> &from, bool verembe )
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

void Allapot::verem_push( const std::vector<AP_UC> &from )
{
	int veremteto = verem_teteje();
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
}

void Allapot::verem_pop ( const AP_UI &meret, std::vector<AP_UC> &to )
{
	int veremteto = verem_teteje();
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

void Allapot::kov_utasitas()
{
	++utasitasszam;
}
int Allapot::get_utasitasszam() const
{
	return utasitasszam;
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
	int meret = verem_teteje();
	to.resize( meret );
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
	to.resize( 0 );
	to.resize( verem.size() + 1, "");
	to[ -vecc2sint(ebp) ] = "ebp";
	to[ -vecc2sint(esp) ] = "esp";
}

int Allapot::verem_teteje() const
{
	return -vecc2sint(esp);
}

void Allapot::print_allapot() const
{
	cout << endl << "Allapot:" << endl;
	cout << "kovetkezo utasitas szama: " << kovetkezo_utasitas << endl;
	cout << "osszesen a " << utasitasszam << ". vegrehajtott utasitas" << endl;
	
	cout << "Zero flag:\t" << zeroflag << endl;
	cout << "Sign flag:\t" << signflag << endl;
	
	stringstream ss;
	ss << "eax:\t\t\t\t" << vecc2uint( eax );
	vec_cout(eax, ss.str() );
	ss.str("");
	ss << "ebx:\t\t\t\t" << vecc2uint( ebx );
	vec_cout(ebx, ss.str() );
	ss.str("");
	ss << "ecx:\t\t\t\t" << vecc2uint( ecx );
	vec_cout(ecx, ss.str() );
	ss.str("");
	ss << "edx:\t\t\t\t" << vecc2uint( edx );
	vec_cout(edx, ss.str() );
	cout << "--------------------------" << endl;
	ss.str("");
	ss << "esp:\t\t\t\t" << -vecc2sint( esp );
	vec_cout(esp, ss.str() );
	ss.str("");
	ss << "ebp:\t\t\t\t" << -vecc2sint( ebp );
	vec_cout(ebp, ss.str() );
	
	vector<string> vecStr;
	elso_valtozok( vecStr );
	cout << "valtozok, hossza: " << valtozok.size() << endl;
	for (int i = 0; i < vecStr.size(); ++i )
	{
		cout << vecStr[i] << "\t";
	}
	cout << endl;
	vec_cout( valtozok );
	
	vec_pointerek( vecStr );
	cout << "verem, hossza: " << verem_teteje() << endl;
	for (int i = 0; i < vecStr.size(); ++i )
	{
		cout << vecStr[i] << "\t";
	}
	cout << endl;
	vector<AP_UC> veremp;
	verem_vector( veremp );
	vec_cout( veremp );
}
