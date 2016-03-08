
#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "typedefs.h"
#include <vector>

namespace Utils
{
	// vektor tartalmanak kilistazasa az elejetol kezdve
		// ha a 'pre' string nem ures, akkor eloszor kiirja annak a tartalmat es a kovetkezo sorba a vektoret
	void vec_cout(const std::vector<AP_UC> &ki, std::string pre = "");
	
	// vektor<unsigned char> <-> unsigned int konverzio
		// a rev elotag az unsigned int bitenkenti komplementeret hasznalja / allitja elo
	AP_UI vecc2uint( const std::vector<AP_UC> &from );
	AP_UI vecc2revuint( const std::vector<AP_UC> &from );
	void uint2vecc( const AP_UI &from, std::vector<AP_UC> &to );
	void revuint2vecc( const AP_UI &from, std::vector<AP_UC> &to );
}

#endif