/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
Pattern in oddtest.pat
this is intended to be the pattern for:
	if (test) fexp 1 else fexp -1
to transform to:
	fexp ( (absbool(test) <<1) -1))
where f is any sequence of unary operators including identity
*/

#include <stddef.h>

#include <shared/bool.h>

#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/exp.h>

#include <construct/shape.h>

#include <refactor/refactor.h>

#include "comp_eq_exp.h"
#include "oddtest.h"


static int
oddunary(exp x, exp y, exp *v)
{
  exp z;
  *v = x;
  if (x->tag != val_tag) goto flab1;
  if (!(y->tag==val_tag && ((no(x)==1 && no(y)==-1) || (no(x)==-1 && no(y)==1) ))) goto flab1;
  goto tlab1;
  flab1:
  if (x->tag != y->tag) goto flab0;
  { exp xC = son(x);
    z = xC;
    if (!(z!=NULL && z->last && son(y) != NULL && oddunary(z, son(y),v))) goto flab0;
    if(!xC->last) goto flab0;
  }
  tlab1:
  return 1;
  flab0: return 0;
}

int
oddtest(exp x, exp *t, exp *f, exp *v)
{
  exp l, z, g;
  if (x->tag != cond_tag) goto flab0;
  { exp xC = son(x);
    if (xC->tag != seq_tag) goto flab0;
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (xCCC->tag != test_tag) goto flab0;
        l =pt(*t);
        if(!xCCC->last) goto flab0;
      }
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      *f = xCC;
      if(!xCC->last) goto flab0;
    }
    if (xC->last) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      g = xCC;
      if (!(oddunary(*f,g,v))) goto flab0;
      if(!xCC->last) goto flab0;
    }
    if(!xC->last) goto flab0;
  }
  return 1;
  flab0: return 0;
}

/* looks for things like
	(a ~ b) ? a: b
	puts test in t - can make use of delay-slot
*/
int
is_maxlike(exp x, exp *t)
{
  exp op1, op2, z, l, w;
  if (x->tag != cond_tag) goto flab0;
  { exp xC = son(x);
    if (xC->tag != seq_tag) goto flab0;
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (xCCC->tag != test_tag) goto flab0;
        l=pt(*t);
        { exp xCCCC = son(xCCC);
          op1 = xCCCC;
          if (!(!is_floating(sh(op1)->tag))) goto flab0;
          if (xCCCC->last) goto flab0;
          xCCCC = bro(xCCCC);
          op2 = xCCCC;
          if(!xCCCC->last) goto flab0;
        }
        if(!xCCC->last) goto flab0;
      }
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      z = xCC;
      if (!(comp_eq_exp(z, op1, NULL,NULL))) goto flab0;
      if(!xCC->last) goto flab0;
    }
    if (xC->last) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      w = xCC;
      if (!(comp_eq_exp(w, op2,NULL,NULL))) goto flab0;
      if(!xCC->last) goto flab0;
    }
    if(!xC->last) goto flab0;
  }
  return 1;
  flab0: return 0;
}

/* looks for things like
	(a ~ b) ? b: a
	puts test in t - can make use of delay-slot
*/
int
is_minlike(exp x, exp *t)
{
  exp op1, op2, z, l, w;
  if (x->tag != cond_tag) goto flab0;
  { exp xC = son(x);
    if (xC->tag != seq_tag) goto flab0;
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (xCCC->tag != test_tag) goto flab0;
        l=pt(*t);
        { exp xCCCC = son(xCCC);
          op1 = xCCCC;
          if (!(!is_floating(sh(op1)->tag))) goto flab0;
          if (xCCCC->last) goto flab0;
          xCCCC = bro(xCCCC);
          op2 = xCCCC;
          if(!xCCCC->last) goto flab0;
        }
        if(!xCCC->last) goto flab0;
      }
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      z = xCC;
      if (!(comp_eq_exp(z, op2,NULL,NULL))) goto flab0;
      if(!xCC->last) goto flab0;
    }
    if (xC->last) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      w = xCC;
      if (!(comp_eq_exp(w, op1,NULL,NULL))) goto flab0;
      if(!xCC->last) goto flab0;
    }
    if(!xC->last) goto flab0;
  }
  return 1;
  flab0: return 0;
}

/* looks for things like
	(a~0) ? a:-a
*/
int
is_abslike(exp x, exp *t)
{
  exp op, l, z, w;
  if (x->tag != cond_tag) goto flab0;
  { exp xC = son(x);
    if (xC->tag != seq_tag) goto flab0;
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (xCCC->tag != test_tag) goto flab0;
        l=pt(*t);
        { exp xCCCC = son(xCCC);
          op = xCCCC;
          if (xCCCC->last) goto flab0;
          xCCCC = bro(xCCCC);
          if (xCCCC->tag != val_tag || no(xCCCC) != 0) goto flab0;
          if(!xCCCC->last) goto flab0;
        }
        if(!xCCC->last) goto flab0;
      }
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      z = xCC;
      if (!(comp_eq_exp(z, op,NULL,NULL))) goto flab0;
      if(!xCC->last) goto flab0;
    }
    if (xC->last) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      if (xCC->tag != neg_tag) goto flab0;
      { exp xCCC = son(xCC);
        w = xCCC;
        if (!(comp_eq_exp(op, w,NULL,NULL))) goto flab0;
        if(!xCCC->last) goto flab0;
      }
      if(!xCC->last) goto flab0;
    }
    if(!xC->last) goto flab0;
  }
  return 1;
  flab0: return 0;
}

int
is_fabs(exp x, exp *t)
{
  exp op, l, z, w;
  if (x->tag != cond_tag) goto flab0;
  { exp xC = son(x);
    if (xC->tag != seq_tag) goto flab0;
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (xCCC->tag != test_tag) goto flab0;
        l=pt(*t);
        { exp xCCCC = son(xCCC);
          op = xCCCC;
          if (xCCCC->last) goto flab0;
          xCCCC = bro(xCCCC);
          if (xCCCC->tag != val_tag || no(xCCCC) != 0) goto flab0;
          if(!xCCCC->last) goto flab0;
        }
        if(!xCCC->last) goto flab0;
      }
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      z = xCC;
      if (!(eq_exp(z, op))) goto flab0;
      if(!xCC->last) goto flab0;
    }
    if (xC->last) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      if (xCC->tag != fneg_tag) goto flab0;
      { exp xCCC = son(xCC);
        w = xCCC;
        if (!(eq_exp(op, w))) goto flab0;
        if(!xCCC->last) goto flab0;
      }
      if(!xCC->last) goto flab0;
    }
    if(!xC->last) goto flab0;
  }
  return 1;
  flab0: return 0;
}
