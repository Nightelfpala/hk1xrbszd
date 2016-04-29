
#ifndef SEMANTICS_H_INCLUDED
#define SEMANTICS_H_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

#include "typedefs.h"

struct kifejezes_data
{
	std::string kif;
	int argmeret;
	kifejezes_data(){}
	kifejezes_data(const std::string &s, const int &ar) : kif(s), argmeret(ar){}
};

struct elso_argumentum
{
	bool isvalt;
	std::string reg;	// ha isvalt == 0 -> regiszter neve
	int elsobyte;		// ha isvalt == 1 -> a valtozo elso byteja
	elso_argumentum(){}
	elso_argumentum(const std::string &r) : isvalt(0), reg(r) {}
	elso_argumentum(const int& elso) : isvalt(1), elsobyte(elso) {}
};

#endif // SEMANTICS_H_INCLUDED