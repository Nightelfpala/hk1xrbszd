
#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "typedefs.h"

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

#include <vector>
#include <string>

class vectorDisplay : public QWidget
{
public:
	vectorDisplay(int _meret, QWidget *parent = 0, bool kiegSzoveg = false );
	~vectorDisplay();
	
	int size() const;
	
	void setName(std::string _name);
	void setValues(std::vector<AP_UC> val);
	void setKieg(std::vector<std::string> kieg);
	
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






#endif	// UI_H_INCLUDED