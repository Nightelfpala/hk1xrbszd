%option noyywrap c++ yylineno
%option prefix="elsoparse"

%{
#include "elsoparseParserbase.h"
%}

DIGIT   [0-9]
IDENTIFIER [a-zA-Z"."][a-zA-Z0-9_"."]*
WS  [ \t]

%%

";".*		// komment, nem kell semmit csinalni

{DIGIT}+	return elsoparseParser::SZAM;

(?i:section)	return elsoparseParser::SECTION;
(?i:\.text)	return elsoparseParser::TEXT;
(?i:\.bss)	return elsoparseParser::BSS;
(?i:\.data)	return elsoparseParser::DATA;
(?i:global)	return elsoparseParser::GLOBAL;

(?i:resb)	return elsoparseParser::RESB;
(?i:resw)	return elsoparseParser::RESW;
(?i:resd)	return elsoparseParser::RESD;

(?i:db)	return elsoparseParser::DB;
(?i:dw)	return elsoparseParser::DW;
(?i:dd)	return elsoparseParser::DD;

(?i:byte)	return elsoparseParser::BYTE;
(?i:word)	return elsoparseParser::WORD;
(?i:dword)	return elsoparseParser::DWORD;

"+"	return elsoparseParser::PLUS;
"-"	return elsoparseParser::MINUS;
"*"	return elsoparseParser::MULTIPLY;
"/"	return elsoparseParser::DIVIDE;
"," return elsoparseParser::VESSZO;
":" return elsoparseParser::KETTOSPONT;

"("	return elsoparseParser::NYITOZAROJEL;
")"	return elsoparseParser::CSUKOZAROJEL;
"["	return elsoparseParser::NYITOSZOGZAROJEL;
"]"	return elsoparseParser::CSUKOSZOGZAROJEL;

(?i:(mov|add|sub|cmp|and|or|xor))	return elsoparseParser::KETARGUMENTUMOS;
(?i:(mul|div|inc|dec|not|push|pop))	return elsoparseParser::EGYARGUMENTUMOS;
(?i:(jmp|ja|jb|je|jz|jna|jnb|jne|jnz))	return elsoparseParser::UGROUTAS;
(?i:near)	return elsoparseParser::NEAR;

[eE]?[abcdABCD][xX]|[eE]?[bsBS][pP]|[abcdABCD][hlHL]	return elsoparseParser::REGISZTER;

\n	return elsoparseParser::NEWLINE;	// utasitasok elvalasztasa
{WS}+	// whitespace	-	nem kell semmit csinalni

{IDENTIFIER}	return elsoparseParser::AZONOSITO;

.	{
		// lexikalis hiba!
	}

%%