%baseclass-preinclude "semantics.h"
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
	SZABALY1 SZABALY2 SZABALY3
	{	// TODO
		;
	}
|
	
;

utasitasok:
	utasitas NEWLINE utasitasok
	{
		// save line number, instruction number, instruction string
		
		delete $1;
	}
|
	utasitas
	{
		// save line number, instruction number, instruction string
		
		delete $1;
	}
;

utasitas:
	KETARGUMENTUMOS argumentum VESSZO argumentum
	{
		$$ = new utasitas_data;	// TODO
		
		if ($2->argmeret == -1 && $4->argmeret == -1)
		{
			// error undefined arg size
		}
		if ($2->argmeret != $4->argmeret)
		{
			// error not equal arg size
		}
		
		delete $2;
		delete $4;
	}
|
	EGYARGUMENTUMOS argumentum
	{
		$$ = new utasitas_data; // TODO
		if ($2->argmeret == -1)
		{
			// error undefined arg size
		}
		
		delete $2;
	}
|
	UGROUTAS AZONOSITO
	{
		$$ = new utasitas_data;	// TODO
		
		delete $1;
		delete $2;
	}
|
	UGROUTAS NEAR AZONOSITO
	{
		$$ = new utasitas_data; // TODO
		
		delete $1;
		delete $3;
	};
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
		$$ = new kifejezes_data("byte [ " + $2->kif + " ]", 1);
		delete $2;
	}
|
	WORD NYITOSZOGZAROJEL kifejezes CSUKOSZOGZAROJEL
	{
		$$ = new kifejezes_data("word [ " + $2->kif + " ]", 2);
		delete $2;
	}
|
	DWORD NYITOSZOGZAROJEL kifejezes CSUKOSZOGZAROJEL
	{
		$$ = new kifejezes_data("dword [ " + $2->kif + " ]", 4);
		delete $2;
	}
;

kifejezes:
	NYITOZAROJEL kifejezes CSUKOZAROJEL;
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
			// error not equal arg size
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
			// error not equal arg size
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
			// error not equal arg size
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
			// error not equal arg size
		} else
		{
			argm = ($1->argmeret == -1) ? ($3->argmeret) : ($1->argmeret);
		}
		$$ = new kifejezes_data($1->kif + " - " + $3->kif, argm);
		
		delete $1;
		delete $3;
	}
|
	REGISTER
	{
		int argm;
		// argm = getRegSize(*$1);
		/*	TODO move to Parser as private method
		int getRegSize(std::string reg)
		{	// undefined behaviour with flag registers
			if ($1[0] == "e")
			{
				return 4;
			} else if ($1[1] == "p" || $1[1] == "x")
			{
				return 2;
			} else
			{
				return 1;
			}
		}
		*/
		$$ = new kifejezes_data(*$1, -1);
		delete $1;
	}
|
	AZONOSITO
	{
		// TODO check reference - variable (not jump label)
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