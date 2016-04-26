
#ifndef ELSOPARSEPARSER_H_INCLUDED
#define ELSOPARSEPARSER_H_INCLUDED

#include "elsoparseParserbase.h"
#include "FlexLexer.h"

#include <map>

#undef elsoparseParser
class elsoparseParser : public elsoparseParserBase
{
public:
	elsoparseParser( std::istream &in);
	~elsoparseParser();
	
	int parse();
private:
	yyFlexLexer lexer;
	void error(char const *msg);
	int lex();
	void print();
	
	int utasitasszam;
	int getRegSize(std::string s);
	
	std::map<int, utasitas_data> utasitas_gyujto;
	
	std::map<std::string, int> ugrocimke_kovutasitas;
	
	void executeAction(int ruleNr);
	void errorRecovery();
	int lookup(bool recovery);
	void nextToken();
	void print__();
	void exceptionHandler__(std::exception const &exc);
	
	
};

#endif