/*
 * Automatically generated from the files:
 *	lctsyntax.sid
 * and
 *	lctsyntax.act
 * by:
 *	/Users/kate/svn/tendra20/obj-regen/bin/sid
 */

/* BEGINNING OF HEADER */

#line 124 "lctsyntax.act"


/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

 #ifndef LCT_SYNTAX_HEADER_INCLUDED
 #define LCT_SYNTAX_HEADER_INCLUDED

#include "ccode.h"
#include "adt.h"

#include "adt/tree.h"

struct lxi_additional_argument {
       	char* name;
	char* ctype;

	struct lxi_additional_argument* next;
};

typedef struct lct_parse_tree_tag {
	int headersdefined;
	int trailersdefined;
	CcodeT hfileheader;
	CcodeT cfileheader;
	CcodeT hfiletrailer;
	CcodeT cfiletrailer;
	struct lxi_additional_argument* arg_head;
	struct lxi_additional_argument** arg_tail;
} lct_parse_tree;

extern lexer_parse_tree* lxi_top_level;
extern lct_parse_tree global_lct_parse_tree ;

extern void init_lct_parse_tree(lct_parse_tree*);
#line 54 "lctsyntax.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_lct_unit(void);

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lct_lex_lone_Hcode_Hat (15)
#define lct_lex_code_Hreference (21)
#define lct_lex_code_Hend (14)
#define lct_lex_code_Heof (17)
#define lct_lex_trailer_Hkw (1)
#define lct_lex_comma (10)
#define lct_lex_action_Hkw (3)
#define lct_lex_unknown (23)
#define lct_lex_close (12)
#define lct_lex_colon (6)
#define lct_lex_code_Hat (16)
#define lct_lex_identifier (19)
#define lct_lex_arrow (7)
#define lct_lex_open (11)
#define lct_lex_reference (5)
#define lct_lex_eof (18)
#define lct_lex_semicolon (9)
#define lct_lex_map_Hkw (2)
#define lct_lex_code_Hstring (22)
#define lct_lex_define (8)
#define lct_lex_code_Hidentifier (20)
#define lct_lex_argument_Hkw (4)
#define lct_lex_code_Hstart (13)
#define lct_lex_header_Hkw (0)

/* BEGINNING OF TRAILER */

#line 454 "lctsyntax.act"

#endif
#line 92 "lctsyntax.h"

/* END OF FILE */
