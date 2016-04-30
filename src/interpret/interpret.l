%option noyywrap c++ yylineno
%option prefix="interpret"

%{
#include "interpretParserbase.h"
%}

DIGIT   [0-9]
IDENTIFIER [a-zA-Z"."][a-zA-Z0-9_"."]*
WS  [ \t\n]

%%

{DIGIT}+	return interpretParser::SZAM;

byte|word|dword		// do nothing - az utasitas_data mar tartalmazza a meret informaciokat
near		// do nothing - a programban szukseg lehet erre, a szimulacioban nem fogja az ugrasok tavolsagat korlatozni a pointer merete

"+"	return interpretParser::PLUS;
"-"	return interpretParser::MINUS;
"*"	return interpretParser::MULTIPLY;
"/"	return interpretParser::DIVIDE;
"," return interpretParser::VESSZO;

"("	return interpretParser::NYITOZAROJEL;
")"	return interpretParser::CSUKOZAROJEL;
"["	return interpretParser::NYITOSZOGZAROJEL;
"]"	return interpretParser::CSUKOSZOGZAROJEL;

mov	return interpretParser::MOV;
add	return interpretParser::ADD;
sub	return interpretParser::SUB;
cmp	return interpretParser::CMP;
and	return interpretParser::AND;
or	return interpretParser::OR;
xor	return interpretParser::XOR;

mul	return interpretParser::MUL;
div	return interpretParser::DIV;
inc	return interpretParser::INC;
dec	return interpretParser::DEC;
not	return interpretParser::NOT;
push	return interpretParser::PUSH;
pop	return interpretParser::POP;

jmp	return interpretParser::JMP;
ja	return interpretParser::JA;
jb	return interpretParser::JB;
je	return interpretParser::JE;
jz	return interpretParser::JZ;
jna	return interpretParser::JNA;
jnb	return interpretParser::JNB;
jne	return interpretParser::JNE;
jnz	return interpretParser::JNZ;

call	return interpretParser::CALL;
ret	return interpretParser::RET;

e?[abcd]x|e?[bs]p|[abcd][hl]	return interpretParser::REGISZTER;

{WS}+	// whitespace	-	nem kell semmit csinalni

{IDENTIFIER}	return interpretParser::AZONOSITO;

.	return interpretParser::LEXERROR;	// csak lexikalis hibak kimutatasara van hasznalatban - ennek elvileg nem szabad elojonnie
