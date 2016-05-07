// Generated by Bisonc++ V4.09.02 on Sat, 07 May 2016 19:58:46 +0200

#ifndef elsoparseParserBase_h_included
#define elsoparseParserBase_h_included

#include <exception>
#include <vector>
#include <iostream>

// $insert preincludes
#include "semantics.h"

namespace // anonymous
{
    struct PI__;
}



class elsoparseParserBase
{
    public:
// $insert tokens

    // Symbolic tokens:
    enum Tokens__
    {
        SZAM = 257,
        AZONOSITO,
        GLOBAL,
        SECTION,
        TEXT,
        BSS,
        DATA,
        RESB,
        RESW,
        RESD,
        DB,
        DW,
        DD,
        BYTE,
        WORD,
        DWORD,
        NYITOZAROJEL,
        CSUKOZAROJEL,
        NYITOSZOGZAROJEL,
        CSUKOSZOGZAROJEL,
        KETARGUMENTUMOS,
        EGYARGUMENTUMOS,
        UGROUTAS,
        RET,
        NEAR,
        REGISZTER,
        VESSZO,
        KETTOSPONT,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        LEXERROR,
    };

// $insert LTYPE
    struct LTYPE__
    {
        int timestamp;
        int first_line;
        int first_column;
        int last_line;
        int last_column;
        char *text;
    };
    
// $insert STYPE
union STYPE__
{
 std::string* szoveg;
 utasitas_data* utas;
 kifejezes_data* kif;
 int* szam;
 std::vector<int>* intvec;
};


    private:
        int d_stackIdx__;
        std::vector<size_t>   d_stateStack__;
        std::vector<STYPE__>  d_valueStack__;
// $insert LTYPEstack
        std::vector<LTYPE__>      d_locationStack__;

    protected:
        enum Return__
        {
            PARSE_ACCEPT__ = 0,   // values used as parse()'s return values
            PARSE_ABORT__  = 1
        };
        enum ErrorRecovery__
        {
            DEFAULT_RECOVERY_MODE__,
            UNEXPECTED_TOKEN__,
        };
        bool        d_debug__;
        size_t      d_nErrors__;
        size_t      d_requiredTokens__;
        size_t      d_acceptedTokens__;
        int         d_token__;
        int         d_nextToken__;
        size_t      d_state__;
        STYPE__    *d_vsp__;
        STYPE__     d_val__;
        STYPE__     d_nextVal__;
// $insert LTYPEdata
        LTYPE__   d_loc__;
        LTYPE__  *d_lsp__;

        elsoparseParserBase();

        void ABORT() const;
        void ACCEPT() const;
        void ERROR() const;
        void clearin();
        bool debug() const;
        void pop__(size_t count = 1);
        void push__(size_t nextState);
        void popToken__();
        void pushToken__(int token);
        void reduce__(PI__ const &productionInfo);
        void errorVerbose__();
        size_t top__() const;

    public:
        void setDebug(bool mode);
}; 

inline bool elsoparseParserBase::debug() const
{
    return d_debug__;
}

inline void elsoparseParserBase::setDebug(bool mode)
{
    d_debug__ = mode;
}

inline void elsoparseParserBase::ABORT() const
{
    throw PARSE_ABORT__;
}

inline void elsoparseParserBase::ACCEPT() const
{
    throw PARSE_ACCEPT__;
}

inline void elsoparseParserBase::ERROR() const
{
    throw UNEXPECTED_TOKEN__;
}


// As a convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define elsoparseParser elsoparseParserBase


#endif


