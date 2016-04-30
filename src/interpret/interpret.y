%baseclass-preinclude "semantics.h"
%class-name interpretParser
%lsp-needed

%token <szoveg> SZAM
%token <szoveg> AZONOSITO

%token NYITOZAROJEL
%token CSUKOZAROJEL
%token NYITOSZOGZAROJEL
%token CSUKOSZOGZAROJEL

%token VESSZO

%token MOV
%token ADD
%token SUB
%token CMP
%token AND
%token OR
%token XOR
%token MUL
%token DIV
%token INC
%token DEC
%token NOT
%token PUSH
%token POP

%token JMP
%token JA
%token JB
%token JE
%token JZ
%token JNA
%token JNB
%token JNE
%token JNZ

%token CALL
%token RET

%left PLUS MINUS
%left MULTIPLY DIVIDE

%token <szoveg> REGISZTER

%token LEXERROR

%union
{
	std::string* szoveg;
	int* szam;
	elso_argumentum* earg;
}

%type <szam> ertek
%type <earg> elsoarg

%%

start:
	utasitas
;

utasitas:
	MOV elsoarg VESSZO ertek
	{
		int val = (*$4);
		std::vector<AP_UC> vec(argmeret);
		Utils::uint2vecc( val, vec );
		if ( $2->isvalt )
		{
			allapot->set_var( ($2->elsobyte), vec );
		} else
		{
			allapot->set_reg( ($2->reg), vec );
		}
		
		delete $2;
		delete $4;
	}
|
	ADD elsoarg VESSZO ertek
	{
		int val = (*$4);
		std::vector<AP_UC> vec(argmeret);
		if ( $2->isvalt )
		{
			allapot->get_var( ($2->elsobyte), argmeret, vec );
			val += Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_var( ($2->elsobyte), vec );
		} else
		{
			allapot->get_reg( ($2->reg), vec );
			val += Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_reg( ($2->reg), vec );
		}
		allapot->set_sign( val < 0 );
		allapot->set_zero( val == 0 );
		
		delete $2;
		delete $4;
	}
	
|
	SUB elsoarg VESSZO ertek
	{
		int val = (*$4);
		std::vector<AP_UC> vec(argmeret);
		if ( $2->isvalt )
		{
			allapot->get_var( ($2->elsobyte), argmeret, vec );
			val -= Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_var( ($2->elsobyte), vec );
		} else
		{
			allapot->get_reg( ($2->reg), vec );
			val -= Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_reg( ($2->reg), vec );
		}
		allapot->set_sign( val < 0 );
		allapot->set_zero( val == 0 );
		
		delete $2;
		delete $4;
	}
|
	CMP ertek VESSZO ertek
	{
		std::vector<AP_UC> vec;
		int val1 = (*$2);
		int val2 = (*$4);
		
		allapot->set_sign( (val1 - val2) < 0 );
		allapot->set_zero( (val1 - val2) == 0 );
		
		
		delete $2;
		delete $4;
	}
|
	AND elsoarg VESSZO ertek
	{
		int val = (*$4);
		std::vector<AP_UC> vec(argmeret);
		if ( $2->isvalt )
		{
			allapot->get_var( ($2->elsobyte), argmeret, vec );
			val &= Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_var( ($2->elsobyte), vec );
		} else
		{
			allapot->get_reg( ($2->reg), vec );
			val &= Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_reg( ($2->reg), vec );
		}
		allapot->set_zero( val == 0 );
		
		delete $2;
		delete $4;
	}
|
	OR elsoarg VESSZO ertek
	{
		int val = (*$4);
		std::vector<AP_UC> vec(argmeret);
		if ( $2->isvalt )
		{
			allapot->get_var( ($2->elsobyte), argmeret, vec );
			val |= Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_var( ($2->elsobyte), vec );
		} else
		{
			allapot->get_reg( ($2->reg), vec );
			val |= Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_reg( ($2->reg), vec );
		}
		allapot->set_zero( val == 0 );
		
		delete $2;
		delete $4;
	}
|
	XOR elsoarg VESSZO ertek
	{
		int val = (*$4);
		std::vector<AP_UC> vec(argmeret);
		if ( $2->isvalt )
		{
			allapot->get_var( ($2->elsobyte), argmeret, vec );
			val ^= Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_var( ($2->elsobyte), vec );
		} else
		{
			allapot->get_reg( ($2->reg), vec );
			val ^= Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_reg( ($2->reg), vec );
		}
		allapot->set_zero( val == 0 );
		
		delete $2;
		delete $4;
	}
|
	MUL elsoarg
	{
		std::vector<AP_UC> vec;
		AP_UI mulval;
		if ( argmeret == 4 )
		{
			allapot->get_reg( "eax" , vec );
		} else if ( argmeret == 2)
		{
			allapot->get_reg( "ax" , vec );
		} else	// argmeret == 1
		{
			allapot->get_reg( "al" , vec );
		}
		mulval = vecc2uint( vec );
		AP_UI baseval;
		if ( $2->isvalt )
		{
			allapot->get_var( ($2->elsobyte) , argmeret, vec );
			baseval = Utils::vecc2uint( vec );
			// TODO finish overflow
		} else
		{
			allapot->get_reg( ($2->reg), vec );
			baseval = Utils::vecc2uint( vec );
			// TODO
		}
		
		delete $2;
	}
|
	DIV elsoarg
	{
		// TODO
	}
|
	INC elsoarg
	{
		std::vector<AP_UC> vec;
		int val;
		if ( $2->isvalt )
		{
			allapot->get_var( $2->elsobyte, argmeret, vec );
			val = Utils::vecc2uint( vec );
			++val;
			Utils::uint2vecc( val, vec );
			allapot->set_var( $2->elsobyte, vec );
		} else
		{
			allapot->get_reg( $2->reg, vec );
			val = Utils::vecc2uint( vec );
			++val;
			Utils::uint2vecc( val, vec );
			allapot->set_reg( $2->reg, vec );
		}
		allapot->set_zero( val == 0 );
		
		delete $2;
	}
|
	DEC elsoarg
	{
		std::vector<AP_UC> vec;
		int val;
		if ( $2->isvalt )
		{
			allapot->get_var( $2->elsobyte, argmeret, vec );
			val = Utils::vecc2uint( vec );
			--val;
			Utils::uint2vecc( val, vec );
			allapot->set_var( $2->elsobyte, vec );
		} else
		{
			allapot->get_reg( $2->reg, vec );
			val = Utils::vecc2uint( vec );
			--val;
			Utils::uint2vecc( val, vec );
			allapot->set_reg( $2->reg, vec );
		}
		allapot->set_zero( val == 0 );
		
		delete $2;
	}
|
	NOT elsoarg
	{
		std::vector<AP_UC> vec;
		int val;
		if ( $2->isvalt )
		{
			allapot->get_var( $2->elsobyte, argmeret, vec );
			val = Utils::vecc2uint( vec );
			val = ~val;
			Utils::uint2vecc( val, vec );
			allapot->set_var( $2->elsobyte, vec );
		} else
		{
			allapot->get_reg( $2->reg, vec );
			val = Utils::vecc2uint( vec );
			val = ~val;
			Utils::uint2vecc( val, vec );
			allapot->set_reg( $2->reg, vec );
		}
		allapot->set_zero( val == 0 );
		
		delete $2;
	}
|
	PUSH elsoarg
	{
		std::vector<AP_UC> vec;
		if ( $2-> isvalt )
		{
			allapot->get_var( $2->elsobyte, argmeret, vec );
		} else
		{
			allapot->get_reg( $2->reg, vec );
		}
		allapot->verem_push( vec );
		delete $2;
	}
|
	POP elsoarg
	{
		std::vector<AP_UC> vec;
		allapot->verem_pop( argmeret, vec );
		if ( $2-> isvalt )
		{
			allapot->set_var( $2->elsobyte, vec );
		} else
		{
			allapot->set_reg( $2->reg, vec );
		}
		delete $2;
	}
|
	JMP AZONOSITO
	{
		int kov = (*ugrocimkek)[*$2];
		allapot->set_kovetkezo(kov);
		delete $2;
	}
|
	JA AZONOSITO
	{
		int kov = (*ugrocimkek)[*$2];
		if ( allapot->get_sign() == 0 && allapot->get_zero() == 0 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	JB AZONOSITO
	{
		int kov = (*ugrocimkek)[*$2];
		if ( allapot->get_sign() == 1 && allapot->get_zero() == 0 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	JE AZONOSITO
	{
		int kov = (*ugrocimkek)[*$2];
		if ( allapot->get_zero() == 1 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	JZ AZONOSITO
	{
		int kov = (*ugrocimkek)[*$2];
		if ( allapot->get_zero() == 1 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	JNA AZONOSITO
	{
		int kov = (*ugrocimkek)[*$2];
		if ( allapot->get_sign() == 1 || allapot->get_zero() == 1 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	JNB AZONOSITO
	{
		int kov = (*ugrocimkek)[*$2];
		if ( allapot->get_sign() == 0 || allapot->get_zero() == 1 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	JNE AZONOSITO
	{
		int kov = (*ugrocimkek)[*$2];
		if ( allapot->get_zero() == 0 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	JNZ AZONOSITO
	{
		int kov = (*ugrocimkek)[*$2];
		if ( allapot->get_zero() == 0 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	CALL AZONOSITO
	{
		int cel = (*ugrocimkek)[*$2];
		int kov = allapot->get_kovetkezo();
		std::vector<AP_UC> vec(4);
		Utils::uint2vecc( kov, vec );
		allapot->verem_push( vec );
		allapot->set_kovetkezo( cel );
		delete $2;
	}
|
	RET
	{
		std::vector<AP_UC> vec;
		allapot->verem_pop(4, vec);
		int kov = Utils::vecc2uint( vec );
		allapot->set_kovetkezo( kov );
	}
;

elsoarg:
	REGISZTER
	{
		$$ = new elso_argumentum( (*$1) );
		
		delete $1;
	}
|
	NYITOSZOGZAROJEL ertek CSUKOSZOGZAROJEL
	{
		$$ = new elso_argumentum( (*$2) );
		
		delete $2;
	}
;

ertek:
	NYITOZAROJEL ertek CSUKOZAROJEL
	{
		$$ = $2;
	}
|
	ertek MULTIPLY ertek
	{
		$$ = new int( (*$1) * (*$3));
		delete $1;
		delete $3;
	}
|
	ertek DIVIDE ertek
	{
		$$ = new int( (*$1) / (*$3));
		delete $1;
		delete $3;
	}
|
	ertek PLUS ertek
	{
		$$ = new int( (*$1) + (*$3));
		delete $1;
		delete $3;
	}
|
	ertek MINUS ertek
	{
		$$ = new int( (*$1) - (*$3));
		delete $1;
		delete $3;
	}
|
	REGISZTER
	{
		std::vector<AP_UC> reg;
		allapot->get_reg( (*$1), reg);
		$$ = new int( Utils::vecc2uint(reg) );
		delete $1;
	}
|
	AZONOSITO
	{
		$$ = new int( allapot->elso_byte( (*$1) ));
		delete $1;
	}
|
	SZAM
	{
		$$ = new int( atoi( $1->c_str() ) );
		delete $1;
	}
;