%baseclass-preinclude "semantics.h"
%class-name elsoparseParser
%lsp-needed

%token <szoveg> SZAM
%token <szoveg> AZONOSITO

%token GLOBAL
%token SECTION
%token TEXT
%token BSS
%token DATA

%token RESB
%token RESW
%token RESD

%token DB
%token DW
%token DD

%token BYTE
%token WORD
%token DWORD

%token NYITOZAROJEL
%token CSUKOZAROJEL
%token NYITOSZOGZAROJEL
%token CSUKOSZOGZAROJEL

%token <szoveg> KETARGUMENTUMOS
%token <szoveg> EGYARGUMENTUMOS
%token <szoveg> UGROUTAS
%token NEAR

%token <szoveg> REGISZTER

%token NEWLINE
%token VESSZO
%token KETTOSPONT

%left PLUS MINUS
%left MULTIPLY DIVIDE

%union
{
	std::string* szoveg;
	utasitas_data* utas;
	kifejezes_data* kif;
}

%type <utas> utasitas
%type <kif> argumentum
%type <kif> kifejezes

%%

start:
	utasitasok
	{	// TODO
		
	}
;

utasitasok:
	utasitas uressor utasitasok
	{
		utasitas_gyujto[$1->utasitassorszam] = *$1;
		
		delete $1;
	}
|
	utasitas
	{
		utasitas_gyujto[$1->utasitassorszam] = *$1;
		
		delete $1;
	}
;

utasitas:
	KETARGUMENTUMOS argumentum VESSZO argumentum
	{
		int argm;
		if ($2->argmeret == -1 && $4->argmeret == -1)
		{
			// TODO error undefined arg size
		} else if ($2->argmeret != $4->argmeret)
		{
			// TODO error not equal arg size
		} else
		{
			argm = ($2->argmeret == -1) ? ($4->argmeret) : ($2->argmeret);
		}
		
		$$ = new utasitas_data( std::string("") + *$1 + " " + $2->kif + ", ", d_loc__.first_line, utasitasszam++, argm);
		
		delete $2;
		delete $4;
	}
|
	EGYARGUMENTUMOS argumentum
	{
		if ($2->argmeret == -1)
		{
			// TODO error undefined arg size
		}
		$$ = new utasitas_data( *$1 + " " + $2->kif, d_loc__.first_line, utasitasszam++, $2->argmeret);
		
		delete $2;
	}
|
	UGROUTAS AZONOSITO
	{
		$$ = new utasitas_data( *$1 + " " + *$2, d_loc__.first_line, utasitasszam++, 4);
		
		delete $1;
		delete $2;
	}
|
	UGROUTAS NEAR AZONOSITO
	{
		$$ = new utasitas_data( *$1 + " near " + *$3, d_loc__.first_line, utasitasszam++, 4);
		
		delete $1;
		delete $3;
	}
|
	cimke utasitas
	{
		$$ = $2;
	}
;

cimke:
	AZONOSITO KETTOSPONT
	{
		if ( ugrocimke_kovutasitas.count(*$1) > 0)
		{
			// TODO error ujradefinialt cimke
		}
		ugrocimke_kovutasitas[*$1] = utasitasszam;
	}
;

argumentum:
	kifejezes
	{
		$$ = $1;
	}
|
	NYITOSZOGZAROJEL kifejezes CSUKOSZOGZAROJEL
	{
		$$ = new kifejezes_data("[ " + $2->kif + " ]", -1);
		delete $2;
	}
|
	BYTE NYITOSZOGZAROJEL kifejezes CSUKOSZOGZAROJEL
	{
		$$ = new kifejezes_data("byte [ " + $3->kif + " ]", 1);
		delete $3;
	}
|
	WORD NYITOSZOGZAROJEL kifejezes CSUKOSZOGZAROJEL
	{
		$$ = new kifejezes_data("word [ " + $3->kif + " ]", 2);
		delete $3;
	}
|
	DWORD NYITOSZOGZAROJEL kifejezes CSUKOSZOGZAROJEL
	{
		$$ = new kifejezes_data("dword [ " + $3->kif + " ]", 4);
		delete $3;
	}
;

kifejezes:
	NYITOZAROJEL kifejezes CSUKOZAROJEL
	{
		$$ = new kifejezes_data("( " + $2->kif + " )", $2->argmeret);
		
		delete $2;
	}
|
	kifejezes MULTIPLY kifejezes
	{
		int argm;
		if ($1->argmeret != -1 && $3->argmeret != -1 && $1->argmeret != $3->argmeret)
		{
			// TODO error not equal arg size
		} else
		{
			argm = ($1->argmeret == -1) ? ($3->argmeret) : ($1->argmeret);
		}
		$$ = new kifejezes_data($1->kif + " * " + $3->kif, argm);
		
		delete $1;
		delete $3;
	}
|
	kifejezes DIVIDE kifejezes
	{
		int argm;
		if ($1->argmeret != -1 && $3->argmeret != -1 && $1->argmeret != $3->argmeret)
		{
			// TODO error not equal arg size
		} else
		{
			argm = ($1->argmeret == -1) ? ($3->argmeret) : ($1->argmeret);
		}
		$$ = new kifejezes_data($1->kif + " / " + $3->kif, argm);
		
		delete $1;
		delete $3;
	}
|
	kifejezes PLUS kifejezes
	{
		int argm;
		if ($1->argmeret != -1 && $3->argmeret != -1 && $1->argmeret != $3->argmeret)
		{
			// TODO error not equal arg size
		} else
		{
			argm = ($1->argmeret == -1) ? ($3->argmeret) : ($1->argmeret);
		}
		$$ = new kifejezes_data($1->kif + " + " + $3->kif, argm);
		
		delete $1;
		delete $3;
	}
|
	kifejezes MINUS kifejezes
	{
		int argm;
		if ($1->argmeret != -1 && $3->argmeret != -1 && $1->argmeret != $3->argmeret)
		{
			// TODO error not equal arg size
		} else
		{
			argm = ($1->argmeret == -1) ? ($3->argmeret) : ($1->argmeret);
		}
		$$ = new kifejezes_data($1->kif + " - " + $3->kif, argm);
		
		delete $1;
		delete $3;
	}
|
	REGISZTER
	{
		int argm;
		argm = getRegSize(*$1);
		
		$$ = new kifejezes_data(*$1, argm);
		delete $1;
	}
|
	AZONOSITO
	{
		$$ = new kifejezes_data(*$1, -1);
		delete $1;
	}
|
	SZAM
	{
		$$ = new kifejezes_data(*$1, -1);
		delete $1;
	}
;

uressor:
	uressor NEWLINE
|
	NEWLINE
;