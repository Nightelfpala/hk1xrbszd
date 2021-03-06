
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
	
	regDisplay v1(4, "v1", &display);
	regDisplay v2(4, "v2", &display);
	veremDisplay v3("valtozok", &display);
	veremDisplay v4("verem", &display);
	
	flagDisplay sf("sf", &display);
	flagDisplay zf("zf", &display);
	
	_layout -> addWidget(&v1);
	_layout -> addWidget(&v2);
	_layout -> addWidget(&v3);
	_layout -> addWidget(&v4);
	_layout -> addWidget(&sf);
	_layout -> addWidget(&zf);
	
	
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
	
	vector<AP_UC> fill3(0);
	vector<string> strV(0);
	v4.updateValues(fill3);
	v4.updateKieg(strV);
	
	display.setLayout(_layout);
	
	v1.setValues(fill1);
	v2.setValues(fill1);
	v3.updateValues(fill2);
	v3.updateKieg(strv);
	
	for (int i = 0; i < 10; ++i)
	{
		fill2.push_back( i );
		strv.push_back( "jozsi" );
	}
	v3.updateValues(fill2);
	v3.updateKieg(strv);
	
	fill3.resize(8);
	strV.resize(8);
	for (int i = 0; i < 8; ++i)
	{
		fill3[i] = i * i;
		if (i % 3 == 1)
		{
			strV[i] = "abc";
		}
	}
	v4.updateValues(fill3);
	v4.updateKieg(strV);
	
	fill3.resize(4);
	strV.resize(4);
	for (int i = 0; i < 4; ++i)
	{
		fill3[i] = i + 1;
		if (i % 3 == 2)
		{
			strV[i] = "cba";
		} else
		{
			strV[i] = "";
		}
	}
	v4.updateValues(fill3);
	v4.updateKieg(strV);
	
	/*
	// ez a teszt a memoria-szivargas ellenorzeset szolgalja
	for (int j = 0; j < 1e4; ++j)
	{
		for (int i = 0; i < 10; ++i)
		{
			fill2.push_back( i );
			strv.push_back( "b" );
		}
		v3.updateValues(fill2);
		v3.updateKieg(strv);
		
		fill2.resize(20);
		strv.resize(20);
		
		v3.updateValues(fill2);
		v3.updateKieg(strv);
		if (j % 100 == 0)
		{
			cout << j << endl;
		}
	}
	*/
	
	sf.setFlag( 0 );
	zf.setFlag( 1 );
	
	display.show();
	
	return app.exec();
}