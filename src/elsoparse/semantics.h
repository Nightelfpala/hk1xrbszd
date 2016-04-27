
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
	kifejezes_data(std::string s, int ar) : kif(s), argmeret(ar){}
};

#endif // SEMANTICS_H_INCLUDED