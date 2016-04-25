
%option noyywrap c++ yylineno
%option yyclass="elsoparse_flex"

%{
#include "Parserbase.h"
%}

DIGIT   [0-9]
IDENTIFIER [a-zA-Z"."][a-zA-Z0-9_"."]*
WS  [ \t]

%%

";".*		// komment, nem kell semmit csinalni

{DIGIT}+	return Parser::SZAM;
/*'(\\.|[^\\'])'	return Parser::KONSTANS_CHAR;*/

(?i:section)	return Parser::SECTION;
(?i:\.text)	return Parser::TEXT;
(?i:\.bss)	return Parser::BSS;
(?i:\.data)	return Parser::DATA;
(?i:global)	return Parser::GLOBAL;

(?i:resb)	return Parser::RESB;
(?i:resw)	return Parser::RESW;
(?i:resd)	return Parser::RESD;

(?i:db)	return Parser::DB;
(?i:dw)	return Parser::DW;
(?i:dd)	return Parser::DD;

(?i:byte)	return Parser::BYTE;
(?i:word)	return Parser::WORD;
(?i:dword)	return Parser::DWORD;

"+"	return Parser::PLUS;
"-"	return Parser::MINUS;
"*"	return Parser::MULTIPLY;
"/"	return Parser::DIVIDE;
"," return Parser::VESSZO;
":" return Parser::KETTOSPONT;

"("	return Parser::NYITOZAROJEL;
")"	return Parser::CSUKOZAROJEL;
"["	return Parser::NYITOSZOGZAROJEL;
"]"	return Parser::CSUKOSZOGZAROJEL;

(?i:(mov|add|sub|cmp|and|or|xor))	return Parser::KETARGUMENTUMOS;
(?i:(mul|div|inc|dec|not|jmp|push|pop|ja|jb|je|jne|jna|jnb|jz|jnz))	return Parser::EGYARGUMENTUMOS;
(?i:(jmp|ja|jb|je|jz|jna|jnb|jne|jnz))	return Parser::UGROUTAS;
/* call, ret*/
(?i:near)	return Parser::NEAR;

[eE]?[abcdABCD][xX]|[eE]?[bsBS][pP]|[abcdABCD][hlHL]	return Parser::REGISTER;

\n	return Parser::NEWLINE;	// utasitasok elvalasztasa
{WS}+	// whitespace	-	nem kell semmit csinalni

{IDENTIFIER}	return Parser::AZONOSITO;

.	{
		// lexikalis hiba!
	}