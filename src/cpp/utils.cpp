
#include <iostream>

#include "utils.h"

using namespace std;

void Utils::vec_cout(const std::vector<AP_UC> &ki, std::string pre)
{
	if (pre != "")
	{
		cout << pre << endl;
	}
	for (int i = 0; i < ki.size(); ++i)
	{
		cout << (int)ki[i] << "\t";
	}
	cout << endl;
}

AP_UI Utils::vecc2uint( const std::vector<AP_UC> &from)
{
	AP_UI result = 0;
	for (AP_UI i = 0; i < from.size(); ++i)
	{
		result *= 256;
		result += from[(from.size() - 1 - i)];	// tarolas: legkisebb helyierteku bit van elol
	}
	return result;
}

AP_UI Utils::vecc2revuint( const std::vector<AP_UC> &from)
{
	return ~(vecc2uint(from));
}

void Utils::uint2vecc ( const AP_UI &from, std::vector<AP_UC> &to )
{
	AP_UI akt = from;
	for (AP_UI i = 0; i < to.size(); ++i)
	{
		to[i] = akt % 256;
		akt /= 256;
	}
}

void Utils::revuint2vecc ( const AP_UI &from, std::vector<AP_UC> &to )
{
	AP_UI akt = ~0 - from;
	for (AP_UI i = 0; i < to.size(); ++i)
	{
		to[i] = akt % 256;
		akt /= 256;
	}
}