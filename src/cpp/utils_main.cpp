#include <iostream>
#include <sstream>

#include "utils.h"

using namespace std;
using namespace Utils;

int main()
{
	// elsosorban sint konverziok ellenorzese
	vector<AP_UC> vec(4);
	stringstream ss;
	
	vec[0] = 255;
	vec[1] = 255;
	vec[2] = 255;
	vec[3] = 15;
	cout << "[255, 255, 255, 15] == " << vecc2sint(vec) << endl;
	
	sint2vecc( 0, vec );
	vec_cout(vec, "sint2vecc 0:");
	cout << "visszakonvertalva:\t" << vecc2sint(vec) << endl;
	
	sint2vecc( -1, vec );
	vec_cout(vec, "sint2vecc -1:");
	cout << "visszakonvertalva:\t" << vecc2sint(vec) << endl;
	
	sint2vecc( -10, vec );
	vec_cout(vec, "sint2vecc -10:");
	cout << "visszakonvertalva:\t" << vecc2sint(vec) << endl;
	
	sint2vecc( UTILS_SIGNED_ZERO, vec);
	ss << "sint2vecc UTILS_SIGNED_ZERO(" << UTILS_SIGNED_ZERO << "):";
	vec_cout(vec, ss.str());
	cout << "visszakonvertalva:\t" << vecc2sint(vec) << endl;
	
	sint2vecc( -UTILS_SIGNED_ZERO, vec);
	ss.str("");
	ss << "sint2vecc -UTILS_SIGNED_ZERO(" << -UTILS_SIGNED_ZERO << "):";
	vec_cout(vec, ss.str());
	cout << "visszakonvertalva:\t" << vecc2sint(vec) << endl;
	
	int a = 5;
	sint2vecc( a, vec );
	sint2vecc( vecc2sint( vec ) - 8, vec);
	cout << a << "\tkonvertalas, -8, visszakonvertalas:\t" << vecc2sint( vec ) << endl;
	
	return 0;
}