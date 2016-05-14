
#ifndef UI_PARTS_H_INCLUDED
#define UI_PARTS_H_INCLUDED

#include <wx/wx.h>

#include <vector>

class wxScrolledWindow;
class wxGridBagSizer;

class regDisplay : public wxPanel
{
public:
	regDisplay( wxPanel *parent, const int &size, const std::string &nev );
	
	void updateValues( const std::vector<unsigned char> &values );
private:
	const std::string name;
	const int meret;
	
	wxTextCtrl* nameLabel;
	
	std::vector< wxTextCtrl* > vecLabel;
	std::vector<unsigned char> vecValue;
};

class varDisplay : public wxPanel
{
public:
	varDisplay( wxPanel *parent, const std::string &nev );
	
	void updateValues( const std::vector<unsigned char> &values );
	void updateLabels( const std::vector< std::string > &values );
private:
	const std::string name;
	
	wxTextCtrl* nameLabel;
	
	wxScrolledWindow *scroll;
	wxGridBagSizer *inSizer;
	wxGridBagSizer *outSizer;
	
	std::vector< wxTextCtrl* > vecLabel;
	std::vector<unsigned char> vecValue;
	
	std::vector< wxTextCtrl* > nameLabels;
	std::vector< std::string > vecNames;
};

class flagDisplay : public wxPanel
{
public:
	flagDisplay( wxPanel *parent, const std::string &nev);
	
	void set( bool b);
private:
	const std::string name;
	
	bool value;
	
	wxTextCtrl* nameLabel;
	wxTextCtrl* valLabel;
};

#endif // UI_PARTS_H_INCLUDED

