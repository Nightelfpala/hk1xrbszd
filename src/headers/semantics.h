
#ifndef SEMANTICS_H_INCLUDED
#define SEMANTICS_H_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iostream>

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
	int elsobyte;		// ha isvalt == 1 -> get_var kell, ha isverem == 0 -> normalis valtozo lekerd
	bool isverem;		// ha isverem == 1 -> get_var kell, veremre utalva (negativ elsobyte es a plusz parameter (set: 3., get: 4.) 1)
	//elso_argumentum(){}
	elso_argumentum(const std::string &r) : isvalt(0), reg(r), isverem(0) {}
	elso_argumentum(const int& elso) : isvalt(1), elsobyte(elso), isverem(0) {}
	elso_argumentum(const int& elso, bool b) : isvalt(1), elsobyte(elso), isverem(b) {}
};

struct kifejezes_ertek
{
	int value;
	bool isverem;	// ha esp vagy ebp van a kifejezesben, akkor igaz, kulonben hamis
	//kifejezes_ertek(){}
	kifejezes_ertek( int v ) : value(v), isverem(0) {}
	kifejezes_ertek( int v, bool b ) : value(v), isverem(b) {}
};

struct masodik_argumentum
{
	int value;
	bool issigned;
	//masodik_argumentum(){ }
	masodik_argumentum( int ert ) : value(ert), issigned(ert < 0) {}
	masodik_argumentum( int ert, bool is ) : value(ert), issigned(is) {}
};

#endif // SEMANTICS_H_INCLUDED