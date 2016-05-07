
#ifndef ELSOPARSEPARSER_H_INCLUDED
#define ELSOPARSEPARSER_H_INCLUDED

#include "elsoparseParserbase.h"

#undef yyFlexLexer
#define yyFlexLexer elsoparseFlexLexer
	// forras: http://flex.sourceforge.net/manual/Cxx.html
		// ezen a modon a ket lexikalis elemzo (elsoparse, interpret) kulonbozo nevu lesz

#include <FlexLexer.h>

#include <map>
#include <vector>

#include "utils.h"

#undef elsoparseParser
class elsoparseParser : public elsoparseParserBase
{
public:
	elsoparseParser( std::istream &in) : lexer( &in, &std::cerr ), utasitasszam(0), elsoutasitas_cimke(""), errorMsg("") {}
	~elsoparseParser() {}
	
	int completeParse();
	
	std::map<int, utasitas_data> get_utasitasok() const;
	std::map<std::string, int> get_valtozokezdet() const;
	std::map<std::string, int> get_ugrocimke() const;
	std::vector<AP_UC> get_valtozok() const;
	int get_elsoutasitas() const;
	
	std::string get_error() const;
		// szintaktikus / szemantikus hiba eseten hibat dobunk, ez a fv megadja hogy milyen hiba tortent
	
	enum Exceptions
	{
		HIBA,	// a get_error() metodussal lekerdezheto a hibauzenet
	};
private:
	int parse();
	void postParse();	// szemantikus ellenorzesek: minden ugropontnak van vegpontja, minden hivatkozott valtozo deklaralva van-e
	
	elsoparseFlexLexer lexer;
	void error(char const *msg);
	int lex();
	void print();
	
	int utasitasszam;
	int getRegSize(const std::string &s) const;
	std::string toLower(const std::string &s) const;
	
	std::map<int, utasitas_data> utasitas_gyujto;
	std::map<std::string, int> ugrocimke_kovutasitas;
	std::string elsoutasitas_cimke;
	
	std::map<std::string, int> valtozo_kezdetek;
	std::vector<AP_UC> valtozok;
	
	std::string errorMsg;
	
	void executeAction(int ruleNr);
	void errorRecovery();
	int lookup(bool recovery);
	void nextToken();
	void print__();
	void exceptionHandler__(std::exception const &exc);
	
	
};

#endif