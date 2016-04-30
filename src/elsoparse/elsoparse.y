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
%token <szoveg> RET
%token NEAR

%token <szoveg> REGISZTER

%token VESSZO
%token KETTOSPONT

%left PLUS MINUS
%left MULTIPLY DIVIDE

%token LEXERROR

%union
{
	std::string* szoveg;
	utasitas_data* utas;
	kifejezes_data* kif;
	int* szam;
	std::vector<int>* intvec;
}

%type <utas> utasitas
%type <kif> argumentum
%type <kif> kifejezes

%type <szam> meretdata
%type <szam> meretbss
%type <intvec> szamok

%%

start:
	szekciok
;

szekciok:
	szekcio szekciok
|
	szekcio
;

szekcio:
	global
|
	SECTION DATA datadeklaraciok
|
	SECTION BSS bssdeklaraciok
|
	SECTION TEXT global utasitasok
;

global:
	GLOBAL AZONOSITO
	{
		if (elsoutasitas_cimke != "")
		{
			std::stringstream ss;
			ss << d_loc__.first_line << ". sor: " << "global belepesi pont ismetles" << std::endl
				<< "\telozo nev: " << elsoutasitas_cimke << std::endl
				<< "\tmost talalt nev: " << $2 << std::endl;
			errorMsg = ss.str();
			
			delete $2;
			throw HIBA;
		}
		elsoutasitas_cimke = *$2;
		delete $2;
	}
;

datadeklaraciok:
	datadecl datadeklaraciok
|
	datadecl
;

bssdeklaraciok:
	bssdecl bssdeklaraciok
|
	bssdecl
;

datadecl:
	AZONOSITO KETTOSPONT meretdata szamok
	{
		int meret = (*$3);
		int pluszhossz = meret * $4->size();
		int mosthossz = valtozok.size();
		
		std::vector<AP_UC> vec(meret);
		
		valtozok.resize(mosthossz + pluszhossz, 0);
		for (int i = 0; i < pluszhossz; ++i)
		{
			Utils::uint2vecc( (*$4)[i] , vec );
			for (int j = 0; j < meret; ++j)
			{
				valtozok[mosthossz + i * meret + j] = vec[j];
			}
		}
		valtozo_kezdetek[*$1] = mosthossz;
		
		delete $1;
		delete $3;
		delete $4;
	}
;

szamok:
	szamok VESSZO SZAM
	{
		$1->push_back(atoi($3->c_str()));
		$$ = $1;
		
		delete $3;
	}
|
	SZAM
	{
		$$ = new std::vector<int>(1, atoi($1->c_str()));
		
		delete $1;
	}
;

bssdecl:
	AZONOSITO KETTOSPONT meretbss SZAM
	{
		int pluszhossz = (*$3) * atoi($4->c_str());
		int mosthossz = valtozok.size();
		
		valtozok.resize(mosthossz + pluszhossz, 0);
		valtozo_kezdetek[*$1] = mosthossz;
		
		delete $1;
		delete $3;
		delete $4;
	}
;

meretdata:
	DB
	{
		$$ = new int(1);
	}
|
	DW
	{
		$$ = new int(2);
	}
|
	DD
	{
		$$ = new int(4);
	}
;

meretbss:
	RESB
	{
		$$ = new int(1);
	}
|
	RESW
	{
		$$ = new int(2);
	}
|
	RESD
	{
		$$ = new int(4);
	}
;

utasitasok:
	utasitas utasitasok
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
			std::stringstream ss;
			ss << d_loc__.first_line << ". sor: " << "muvelet meg nem adott argumentummerettel" << std::endl
				<< "\t" << (std::string("") + *$1 + " " + $2->kif + ", " + $4->kif) << std::endl;
			errorMsg = ss.str();
			
			delete $1;
			delete $2;
			delete $4;
			throw HIBA;
		} else if ($2->argmeret != $4->argmeret && $2->argmeret != -1 && $4->argmeret != -1)
		{
			std::stringstream ss;
			ss << d_loc__.first_line << ". sor: " << "muvelet eltero argumentummerettel" << std::endl
				<< "\t" << (std::string("") + toLower(*$1) + " " + $2->kif + ", " + $4->kif) << std::endl
				<< "\telso argumentum merete: " << $2->argmeret << " byte" << std::endl
				<< "\tmasodik argumentum merete: " << $4->argmeret << " byte" << std::endl;
			errorMsg = ss.str();
			
			delete $1;
			delete $2;
			delete $4;
			throw HIBA;
		} else
		{
			argm = ($2->argmeret == -1) ? ($4->argmeret) : ($2->argmeret);
		}
		
		$$ = new utasitas_data( std::string("") + *$1 + " " + $2->kif + ", " + $4->kif, d_loc__.first_line, utasitasszam++, argm);
		
		delete $1;
		delete $2;
		delete $4;
	}
|
	EGYARGUMENTUMOS argumentum
	{
		if ($2->argmeret == -1)
		{
			std::stringstream ss;
			ss << d_loc__.first_line << ". sor: " << "muvelet meg nem adott argumentummerettel" << std::endl
				<< "\t" <<(std::string("") + toLower(*$1) + " " + $2->kif) << std::endl;
			errorMsg = ss.str();
			
			delete $1;
			delete $2;
			throw HIBA;
		}
		$$ = new utasitas_data( *$1 + " " + $2->kif, d_loc__.first_line, utasitasszam++, $2->argmeret);
		
		delete $1;
		delete $2;
	}
|
	UGROUTAS AZONOSITO
	{
		if ( ugrocimke_kovutasitas.count(*$2) == 0 )
		{
			ugrocimke_kovutasitas[ *$2 ] = -1;
		}
		$$ = new utasitas_data( *$1 + " " + (*$2), d_loc__.first_line, utasitasszam++, 4);
		
		delete $1;
		delete $2;
	}
|
	UGROUTAS NEAR AZONOSITO
	{
		if ( ugrocimke_kovutasitas.count(*$3) == 0 )
		{
			ugrocimke_kovutasitas[ *$3 ] = -1;
		}
		$$ = new utasitas_data( toLower(*$1) + " near " + (*$3), d_loc__.first_line, utasitasszam++, 4);
		
		delete $1;
		delete $3;
	}
|
	RET
	{
		$$ = new utasitas_data( "ret", d_loc__.first_line, utasitasszam++, 0);
		
		delete $1;
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
			std::stringstream ss;
			ss << d_loc__.first_line << ". sor: " << "ujradefinialt ugras cimke" << std::endl
				<< "\t" << $1 << std::endl;
			errorMsg = ss.str();
			
			delete $1;
			throw HIBA;
		}
		ugrocimke_kovutasitas[*$1] = utasitasszam;
		
		delete $1;
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
			std::stringstream ss;
			ss << d_loc__.first_line << ". sor: " << "szorzas muvelet eltero argumentummerettel" << std::endl
				<< "\t" << (std::string("") + $1->kif + " * " + $3->kif) << std::endl
				<< "\telso argumentum merete: " << $1->argmeret << " byte" << std::endl
				<< "\tmasodik argumentum merete: " << $3->argmeret << " byte" << std::endl;
			errorMsg = ss.str();
			
			delete $1;
			delete $3;
			throw HIBA;
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
			std::stringstream ss;
			ss << d_loc__.first_line << ". sor: " << "osztas muvelet eltero argumentummerettel" << std::endl
				<< "\t" << (std::string("") + $1->kif + " / " + $3->kif) << std::endl
				<< "\telso argumentum merete: " << $1->argmeret << " byte" << std::endl
				<< "\tmasodik argumentum merete: " << $3->argmeret << " byte" << std::endl;
			errorMsg = ss.str();
			
			delete $1;
			delete $3;
			throw HIBA;
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
			std::stringstream ss;
			ss << d_loc__.first_line << ". sor: " << "osszeadas muvelet eltero argumentummerettel" << std::endl
				<< "\t" << (std::string("") + $1->kif + " + " + $3->kif) << std::endl
				<< "\telso argumentum merete: " << $1->argmeret << " byte" << std::endl
				<< "\tmasodik argumentum merete: " << $3->argmeret << " byte" << std::endl;
			errorMsg = ss.str();
			
			delete $1;
			delete $3;
			throw HIBA;
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
			std::stringstream ss;
			ss << d_loc__.first_line << ". sor: " << "kivonas muvelet eltero argumentummerettel" << std::endl
				<< "\t" << (std::string("") + $1->kif + " - " + $3->kif) << std::endl
				<< "\telso argumentum merete: " << $1->argmeret << " byte" << std::endl
				<< "\tmasodik argumentum merete: " << $3->argmeret << " byte" << std::endl;
			errorMsg = ss.str();
			
			delete $1;
			delete $3;
			throw HIBA;
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
		
		$$ = new kifejezes_data( toLower(*$1), argm);
		delete $1;
	}
|
	AZONOSITO
	{
		if ( valtozo_kezdetek.count(*$1) == 0)
		{
			valtozo_kezdetek[ *$1 ] = -1;
		}
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