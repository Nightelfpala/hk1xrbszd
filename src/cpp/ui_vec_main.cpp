
#include <QApplication>
#include <QVBoxLayout>

#include "ui.h"

using namespace std;


int main( int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	QWidget display;
	
	QVBoxLayout *_layout = new QVBoxLayout;
	
	vectorDisplay v1(4, &display);
	vectorDisplay v2(12, &display, true);
	
	_layout -> addWidget(&v1);
	_layout -> addWidget(&v2);
	
	v1.setName("v1 neve");
	v2.setName("v2 neve");
	
	vector<AP_UC> fill1(v1.size());
	for (unsigned int i = 0; i < v1.size(); ++i)
	{
		fill1[i] = 1 + i + i * i;
	}
	
	vector<AP_UC> fill2(v2.size());
	vector<string> strv(v2.size());
	for (unsigned int i = 0; i < v2.size(); ++i)
	{
		fill2[i] = 1 + 3 * i ;
		if (i % 4 == 0)
		{
			strv[i] = "a";
		} else
		{
			strv[i] = "";
		}
	}
	
	display.setLayout(_layout);
	
	v1.setValues(fill1);
	v2.setValues(fill2);
	v2.setKieg(strv);
	
	display.show();
	
	return app.exec();
}