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
	kifejezes_ertek* kif;
	elso_argumentum* earg;
	masodik_argumentum* marg;
}

%type <kif> ertek
%type <earg> elsoarg
%type <marg> masodarg

%%

start:
	utasitas
;

utasitas:
	MOV elsoarg VESSZO masodarg
	{
		AP_UI val = ( $4 -> value );
		std::vector<AP_UC> vec(argmeret);
		bool b = $2->isverem;
		if ( $2->isvalt )
		{
			Utils::uint2vecc( val, vec );
			allapot->set_var( ($2->elsobyte), vec, b );
		} else
		{
			bool b = ( $2->reg == "esp" || $2->reg == "ebp" || $2->reg == "sp" || $2->reg == "bp");
			if ( b )
			{
				Utils::sint2vecc( val, vec );
				allapot->set_reg( ($2->reg), vec );
			} else
			{
				Utils::uint2vecc( val, vec );
				allapot->set_reg( ($2->reg), vec );
			}
		}
		
		delete $2;
		delete $4;
	}
|
	ADD elsoarg VESSZO masodarg
	{
		AP_UI val = ( $4 -> value );
		std::vector<AP_UC> vec(argmeret);
		bool b = $2->isverem;
		AP_UI plusz;
		if ( $2->isvalt )
		{
			allapot->get_var( ($2->elsobyte), argmeret, vec, b );
			plusz = Utils::vecc2uint( vec );
			val += plusz;
			Utils::uint2vecc( val, vec );
			allapot->set_var( ($2->elsobyte), vec, b );
		} else
		{
			allapot->get_reg( ($2->reg), vec );
			bool b = ( $2->reg == "esp" || $2->reg == "ebp" || $2->reg == "sp" || $2->reg == "bp");
			if ( b )
			{
				plusz = Utils::vecc2sint( vec );
			} else
			{
				plusz = Utils::vecc2uint( vec );
			}
			val += plusz;
			if ( b )
			{
				Utils::sint2vecc( val, vec );
			} else
			{
				Utils::uint2vecc( val, vec );
			}
			allapot->set_reg( ($2->reg), vec );
		}
		allapot->set_zero( val == 0 );
		
		delete $2;
		delete $4;
	}
	
|
	SUB elsoarg VESSZO masodarg
	{
		AP_UI minusz = ( $4 -> value);
		std::vector<AP_UC> vec(argmeret);
		bool b = $2->isverem;
		AP_UI val;
		if ( $2->isvalt )
		{
			allapot->get_var( ($2->elsobyte), argmeret, vec, b );
			val = Utils::vecc2uint( vec );
			allapot->set_sign( val < minusz );
			val -= minusz;
			Utils::uint2vecc( val, vec );
			allapot->set_var( ($2->elsobyte), vec, b );
		} else
		{
			allapot->get_reg( ($2->reg), vec );
			bool b = ( $2->reg == "esp" || $2->reg == "ebp" || $2->reg == "sp" || $2->reg == "bp");
			if ( b )
			{
				val = Utils::vecc2sint( vec );
			} else
			{
				val = Utils::vecc2uint( vec );
			}
			allapot->set_sign( val < minusz );
			val -= minusz;
			if ( b )
			{
				Utils::sint2vecc( val, vec );
			} else
			{
				Utils::uint2vecc( val, vec );
			}
			allapot->set_reg( ($2->reg), vec );
		}
		allapot->set_zero( val == 0 );
		
		delete $2;
		delete $4;
	}
|
	CMP masodarg VESSZO masodarg
	{
		std::vector<AP_UC> vec;
		AP_UI val1 = ( $2 -> value);
		AP_UI val2 = ( $4 -> value);
		
		allapot->set_sign( val1 < val2 );
		allapot->set_zero( (val1 - val2) == 0 );
		
		
		delete $2;
		delete $4;
	}
|
	AND elsoarg VESSZO masodarg
	{
		AP_UI val = ( $4 -> value);
		std::vector<AP_UC> vec(argmeret);
		bool b = $2->isverem;
		if ( $2->isvalt )
		{
			allapot->get_var( ($2->elsobyte), argmeret, vec, b );
			val &= Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_var( ($2->elsobyte), vec, b );
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
	OR elsoarg VESSZO masodarg
	{
		AP_UI val = ( $4 -> value);
		std::vector<AP_UC> vec(argmeret);
		bool b = $2->isverem;
		if ( $2->isvalt )
		{
			allapot->get_var( ($2->elsobyte), argmeret, vec, b );
			val |= Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_var( ($2->elsobyte), vec, b );
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
	XOR elsoarg VESSZO masodarg
	{
		AP_UI val = ( $4 -> value);
		std::vector<AP_UC> vec(argmeret);
		bool b = $2->isverem;
		if ( $2->isvalt )
		{
			allapot->get_var( ($2->elsobyte), argmeret, vec, b );
			val ^= Utils::vecc2uint( vec );
			Utils::uint2vecc( val, vec );
			allapot->set_var( ($2->elsobyte), vec, b );
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
	MUL masodarg
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
		mulval = Utils::vecc2uint( vec );
		
		AP_UI baseval = $2->value;
		
		AP_UI cut = 0;
		for ( int i = 0; i < argmeret; ++i)
		{
			cut <<= 8;
			cut |= 0xFF;
		}
		
		unsigned long long result = ((unsigned long long) baseval) * ((unsigned long long) mulval);
		allapot->set_zero( result == 0);
		AP_UI resH = ( (result >> argmeret * 8) & cut );
		AP_UI resL = ( result & cut );
		std::vector<AP_UC> vecH(argmeret), vecL(argmeret);
		Utils::uint2vecc( resH, vecH );
		Utils::uint2vecc( resL, vecL );
		
		// mukodes elve: https://en.wikibooks.org/wiki/X86_Assembly/Arithmetic
		if (argmeret == 4)
		{
			allapot->set_reg("eax", vecL);
			allapot->set_reg("edx", vecH);
		} else if (argmeret == 2)
		{
			allapot->set_reg("ax", vecL);
			allapot->set_reg("dx", vecH);
		} else	// argmeret == 1
		{
			allapot->set_reg("al", vecL);
			allapot->set_reg("ah", vecH);
		}
		
		delete $2;
	}
|
	DIV masodarg
	{
		std::vector<AP_UC> vecL;
		std::vector<AP_UC> vecH;
		unsigned long long divval;
		if ( argmeret == 4 )
		{
			allapot->get_reg( "edx" , vecH );
			allapot->get_reg( "eax" , vecL );
		} else if ( argmeret == 2)
		{
			allapot->get_reg( "dx" , vecH );
			allapot->get_reg( "ax" , vecL );
		} else	// argmeret == 1
		{
			allapot->get_reg( "ah" , vecH );
			allapot->get_reg( "al" , vecL );
		}
		divval = (( ((unsigned long long)Utils::vecc2uint( vecH )) << (argmeret * 8)) | ((unsigned long long)(Utils::vecc2uint(vecL))));
		
		AP_UI oszto = $2->value;
		if (oszto == 0)
		{
			std::stringstream ss;
			ss << "0-val torteno osztas!" << std::endl;
			errorMsg = ss.str();
			throw HIBA;
		}
		
		AP_UI res = divval / oszto;
		AP_UI rem = divval % oszto;
		
		Utils::uint2vecc( res, vecL );
		Utils::uint2vecc( rem, vecH );
		
		if ( argmeret == 4)
		{
			allapot->set_reg( "edx" , vecH );
			allapot->set_reg( "eax" , vecL );
		} else if (argmeret == 2)
		{
			allapot->set_reg( "dx" , vecH );
			allapot->set_reg( "ax" , vecL );
		} else	// argmeret == 1
		{
			allapot->set_reg( "ah" , vecH );
			allapot->set_reg( "al" , vecL );
		}
		
		delete $2;
	}
|
	INC elsoarg
	{
		std::vector<AP_UC> vec;
		AP_UI val;
		bool b = $2->isverem;
		if ( $2->isvalt )
		{
			allapot->get_var( $2->elsobyte, argmeret, vec, b);
			val = Utils::vecc2uint( vec );
			++val;
			Utils::uint2vecc( val, vec );
			allapot->set_var( $2->elsobyte, vec, b);
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
		AP_UI val;
		bool b = $2->isverem;
		if ( $2->isvalt )
		{
			allapot->get_var( $2->elsobyte, argmeret, vec, b);
			val = Utils::vecc2uint( vec );
			--val;
			Utils::uint2vecc( val, vec );
			allapot->set_var( $2->elsobyte, vec, b);
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
		AP_UI val;
		bool b = $2->isverem;
		if ( $2->isvalt )
		{
			allapot->get_var( $2->elsobyte, argmeret, vec, b);
			val = Utils::vecc2uint( vec );
			val = ~val;
			Utils::uint2vecc( val, vec );
			allapot->set_var( $2->elsobyte, vec, b);
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
	PUSH masodarg
	{
		std::vector<AP_UC> vec(argmeret);
		if ( $2 -> issigned )
		{
			Utils::sint2vecc( $2 -> value, vec );
		} else
		{
			Utils::uint2vecc( $2 -> value, vec );
		}
		allapot->verem_push( vec );
		delete $2;
	}
|
	POP elsoarg
	{
		std::vector<AP_UC> vec;
		bool b = $2->isverem;
		allapot->verem_pop( argmeret, vec );
		if ( $2->isvalt )
		{
			allapot->set_var( $2->elsobyte, vec, b);
		} else
		{
			/* TODO
			bool b = ( $2->reg == "esp" || $2->reg == "ebp" || $2->reg == "sp" || $2->reg == "bp");
			if ( b )
			{
				Utils::sint2vecc( val, vec );
				allapot->set_reg( ($2->reg), vec );
			} else
			{
				Utils::uint2vecc( val, vec );
				allapot->set_reg( ($2->reg), vec );
			}
			*/
			allapot->set_reg( $2->reg, vec );
		}
		delete $2;
	}
|
	JMP AZONOSITO
	{
		AP_UI kov = (*ugrocimkek)[*$2];
		allapot->set_kovetkezo(kov);
		delete $2;
	}
|
	JA AZONOSITO
	{
		AP_UI kov = (*ugrocimkek)[*$2];
		if ( allapot->get_sign() == 0 && allapot->get_zero() == 0 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	JB AZONOSITO
	{
		AP_UI kov = (*ugrocimkek)[*$2];
		if ( allapot->get_sign() == 1 && allapot->get_zero() == 0 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	JE AZONOSITO
	{
		AP_UI kov = (*ugrocimkek)[*$2];
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
		AP_UI kov = (*ugrocimkek)[*$2];
		if ( allapot->get_sign() == 1 || allapot->get_zero() == 1 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	JNB AZONOSITO
	{
		AP_UI kov = (*ugrocimkek)[*$2];
		if ( allapot->get_sign() == 0 || allapot->get_zero() == 1 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	JNE AZONOSITO
	{
		AP_UI kov = (*ugrocimkek)[*$2];
		if ( allapot->get_zero() == 0 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	JNZ AZONOSITO
	{
		AP_UI kov = (*ugrocimkek)[*$2];
		if ( allapot->get_zero() == 0 )
		{
			allapot->set_kovetkezo(kov);
		}
		delete $2;
	}
|
	CALL AZONOSITO
	{
		AP_UI cel = (*ugrocimkek)[*$2];
		AP_UI kov = allapot->get_kovetkezo();
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
		AP_UI kov = Utils::vecc2uint( vec );
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
		$$ = new elso_argumentum( $2->value, $2->isverem );
		
		delete $2;
	}
;

masodarg:
	ertek
	{
		$$ = new masodik_argumentum( $1->value, $1->isverem );
		
		delete $1;
	}
|
	NYITOSZOGZAROJEL ertek CSUKOSZOGZAROJEL
	{
		bool b = $2->isverem;
		std::vector<AP_UC> vec;
		
		allapot->get_var( $2->value, argmeret, vec, b );
		
		$$ = new masodik_argumentum( Utils::vecc2uint(vec) );
		
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
		$$ = new kifejezes_ertek( ($1->value) * ($3->value), $1->isverem || $3->isverem);
		delete $1;
		delete $3;
	}
|
	ertek DIVIDE ertek
	{
		$$ = new kifejezes_ertek( ($1->value) / ($3->value), $1->isverem || $3->isverem);
		delete $1;
		delete $3;
	}
|
	ertek PLUS ertek
	{
		$$ = new kifejezes_ertek( ($1->value) + ($3->value), $1->isverem || $3->isverem);
		delete $1;
		delete $3;
	}
|
	ertek MINUS ertek
	{
		$$ = new kifejezes_ertek( ($1->value) - ($3->value), $1->isverem || $3->isverem);
		delete $1;
		delete $3;
	}
|
	REGISZTER
	{
		std::vector<AP_UC> reg;
		allapot->get_reg( (*$1), reg);
		bool b = ( *$1 == "esp" || *$1 == "ebp" || *$1 == "sp" || *$1 == "bp");
		if (b)
		{
			$$ = new kifejezes_ertek( Utils::vecc2sint(reg), 1);
		} else
		{
			$$ = new kifejezes_ertek( Utils::vecc2uint(reg) );
		}
		delete $1;
	}
|
	AZONOSITO
	{
		$$ = new kifejezes_ertek( allapot->elso_byte( (*$1) ));
		delete $1;
	}
|
	SZAM
	{
		$$ = new kifejezes_ertek( atoi( $1->c_str() ) );
		delete $1;
	}
;