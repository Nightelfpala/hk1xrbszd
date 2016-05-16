
#ifndef SZIMULACIO_H_INCLUDED
#define SZIMULACIO_H_INCLUDED

#include <map>
#include <stack>

#include "utils.h"
#include "allapot.h"
#include "interpretParser.h"

class Szimulacio
{
public:
	Szimulacio();
	~Szimulacio();
	void run();
private:
	void receive();
	void next();
	void prev();
	
	interpretParser iParser;
	Allapot allapot;
	
	std::map<int, utasitas_data> utas_data;
	std::map<std::string, int> ugro_cimkek;
	int vege;
	
	std::stack<Allapot> korabbi_allapotok;
	bool vantovabb;

};


#endif // SZIMULACIO_H_INCLUDED

