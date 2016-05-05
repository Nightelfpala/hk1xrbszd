
#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "typedefs.h"

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>

#include <vector>
#include <string>

class vectorDisplay : public QWidget
{	// a regiszterek kijelzeseert felelos, fix meretu
public:
	vectorDisplay(int _meret, QWidget *parent = 0, bool kiegSzoveg = false );
	~vectorDisplay();
	
	int size() const;
	
	void setName(std::string _name);
	void setValues(const std::vector<AP_UC> &val);
	void setKieg(const std::vector<std::string> &kieg);
	
private:
	QLabel* nameLabel;
	QGridLayout* gridLayout;
	
	std::string name;
	int meret;
	
	std::vector<AP_UC> valueVec;
	std::vector<QLabel*> valueLabel;
	
	bool kiegeszitoSzoveg;
	std::vector<QLabel*> kiegLabel;
	std::vector<std::string> kiegVec;
};


class veremDisplay : public QWidget
{	// a verem illetve a valtozok kijelzeseert felelos, valtoztathato meretu, gorditosavval ellatott
public:
	veremDisplay( std::string nev, QWidget *parent );
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

#endif	// UI_H_INCLUDED