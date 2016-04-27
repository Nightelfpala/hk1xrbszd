
#ifndef TYPEDEFS_H_INCLUDED
#define TYPEDEFS_H_INCLUDED

typedef unsigned char AP_UC;
typedef unsigned int AP_UI;

struct utasitas_data
{
	std::string sor;		// a sor szovege (modositasokkal - azonositot leszamitva csak kisbetu, 1 db szokoz elvalasztokarakter, nincs komment)
	int eredetisorszam;		// az eredeti fajlban az utasitas hanyadik sorban van	-	csak ertelmezest segit
	int utasitassorszam;	// az utasitasok sorozataban hanyadik	-	ugro utasitasoknal hasznalt
	int argmeret;	//	argumentum meretee, byteokban vagy -1: meg nem hatarozott (a masik argumentum donti el)
	utasitas_data(){}
	utasitas_data(std::string s, int es, int us, int ar) : sor(s), eredetisorszam(es), utasitassorszam(us), argmeret(ar) {}
};

#endif