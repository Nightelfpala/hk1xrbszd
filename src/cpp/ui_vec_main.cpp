
#include <QApplication>
#include <QVBoxLayout>

#include <iostream>

#include "ui_parts.h"

using namespace std;


int main( int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	QWidget display;
	
	QVBoxLayout *_layout = new QVBoxLayout;
	
	vectorDisplay v1(4, &display);
	vectorDisplay v2(4, &display);
	veremDisplay v3("verem", &display);
	
	_layout -> addWidget(&v1);
	_layout -> addWidget(&v2);
	_layout -> addWidget(&v3);
	
	v1.setName("v1 neve");
	v2.setName("v2 neve");
	
	vector<AP_UC> fill1(v1.size());
	for (unsigned int i = 0; i < v1.size(); ++i)
	{
		fill1[i] = 1 + i + i * i;
	}
	
	const int v3size = 46;
	
	vector<AP_UC> fill2(v3size);
	vector<string> strv(v3size);
	for (unsigned int i = 0; i < v3size; ++i)
	{
		fill2[i] = 1 + 3 * i * i ;
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
	v2.setValues(fill1);
	v3.updateValues(fill2);
	v3.updateKieg(strv);
	
	display.show();
	
	return app.exec();
}