
#ifndef SEMANTICS_H_INCLUDED
#define SEMANTICS_H_INCLUDED

#include <string>

#include "typedefs.h"

struct utasitas_data
{
	std::string sor;		// a sor szovege (modositasokkal - azonositot leszamitva csak kisbetu, 1 db szokoz elvalasztokarakter, nincs komment)
	int eredetisorszam;		// az eredeti fajlban az utasitas hanyadik sorban van	-	csak ertelmezest segit
	int utasitassorszam;	// az utasitasok sorozataban hanyadik	-	ugro utasitasoknal hasznalt
	int argmeret;	//	argumentum meretee, byteokban vagy -1: meg nem hatarozott (a masik argumentum donti el)
	utasitas_data(){}
	utasitas_data(std::string s, int es, int us, int ar) : sor(s), eredetisorszam(es), utasitassorszam(us), argmeret(ar) {}
};

struct kifejezes_data
{
	std::string kif;
	int argmeret;
	kifejezes_data(){}
	kifejezes_data(std::string s, int ar) : kif(s), argmeret(ar){}
};

#endif // SEMANTICS_H_INCLUDED