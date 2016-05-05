
#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "typedefs.h"

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>
#include <QFrame>
#include <QCheckBox>

#include <vector>
#include <string>

class regDisplay : public QFrame
{	// a regiszterek kijelzeseert felelos, fix meretu
public:
	regDisplay(int _meret, QWidget *parent = 0);
	~regDisplay();
	
	int size() const;
	
	void setName(std::string _name);
	void setValues(const std::vector<AP_UC> &val);
	
private:
	QLabel* nameLabel;
	QGridLayout* gridLayout;
	
	std::string name;
	int meret;
	
	std::vector<AP_UC> valueVec;
	std::vector<QLabel*> valueLabel;
};


class veremDisplay : public QFrame
{	// a verem illetve a valtozok kijelzeseert felelos, valtoztathato meretu, gorditosavval ellatott
public:
	veremDisplay( const std::string &nev, QWidget *parent );
	~veremDisplay();
	
	
	int size() const;
	
	void updateValues(const std::vector<AP_UC> &vals);
	void updateKieg(const std::vector<std::string> &kiegs);
	
private:
	const std::string name;
	QLabel* nameLabel;
	
	int meret;
	
	QScrollArea *scrollArea;
	QWidget *scrollWidget;
	QGridLayout* gridLayout;
	
	
	// byteertekek
	std::vector<AP_UC> valueVec;
	std::vector<QLabel*> valueLabel;
	// kiegeszito szovegek: valtozo nevek, verem pointer cimkek
	std::vector<std::string> kiegVec;
	std::vector<QLabel*> kiegLabel;
};

class flagDisplay : public QFrame
{
public:
	flagDisplay( const std::string &nev, QWidget* parent );
	~flagDisplay();
	
	bool getFlag() const;
	void setFlag( bool b );
private:
	const std::string name;
	QLabel* nameLabel;
	QCheckBox* checkBox;
	
	bool flag;
};

#endif	// UI_H_INCLUDED