/*##############################################################################

FUNNNELWEB COPYRIGHT
====================
FunnelWeb is a literate-programming macro preprocessor.
The FunnelWeb web is at http://www.ross.net/funnelweb/

Copyright (c) Ross N. Williams 1992. All rights reserved.
Copyright (c) X Caminhante 2025. All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of Version 2 of the GNU General Public License as
published by the Free Software Foundation (http://www.gnu.org/).

This program is distributed WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See Version 2 of the GNU General Public License for more details.

You should have received a copy of Version 2 of the GNU General Public
License along with this program. If not, you can obtain a copy as follows:
   ftp://prep.ai.mit.edu/pub/gnu/COPYING-2.0
or write to:
    Free Software Foundation, Inc.,
    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA

Section 2a of the license requires that all changes to this file be
recorded prominently in this file. Please record all changes here.

Programmers:
   RNW  Ross N. Williams (ross@ross.net)
   XCA  X Caminhante (xcaminhante@i2pmail.org)

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.
   08-May-1999  RNW  Renamed from weave.c to weavet.c
   08-May-1999  RNW  Modified diagnostic messages to mention "TeX".
   08-May-1999  RNW  Added typesetter check.
   09-May-1999  RNW  Added support for library macros.
   07-May-2025  XCA  Commented lines 127-131 so fw accepts any non-printable character (I want proper UTF-8 tho)

##############################################################################*/


/******************************************************************************/
/*                                   WEAVE.C                                  */
/******************************************************************************/

#include <ctype.h>
#include "style.h"

#include "as.h"
#include "data.h"
#include "lister.h"
#include "machin.h"
#include "misc.h"
#include "table.h"
#include "texhead.h"
#include "weavet.h"

/* IMPORTANT WARNING: The Macintosh THINK C compiler sets up strings that     */
/* start with \p or \P as PASCAL strings rather than C strings. So be very    */
/* careful not to start any strings with \p or \P.                            */

/******************************************************************************/

LOCVAR wf_t f_t;          /* Variable representing documentation file.        */
LOCVAR bool literal;      /* True if we are inside a literal @{.              */

/******************************************************************************/

LOCAL void wv_ex P_((p_ells_t));

/******************************************************************************/

LOCAL char * fn_nodir P_((char *));
LOCAL char * fn_nodir (p)
/* Given a pointer to a string, returns a pointer to the character just past  */
/* the last occurrance of FN_DELIM, or a pointer to the start of the string   */
/* if it does not occur. In other words, given a filename, return a pointer   */
/* to the start of the name field.                                            */
char *p;
{
 char *q = strrchr(p,FN_DELIM);
 if (q==NULL)
    return p;
 else
    return q+1;
}

/******************************************************************************/

LOCAL void wf_dec P_((p_wf_t,ulong));
LOCAL void wf_dec(p_wf,n)
/* Writes the unsigned number n to the specified output stream as a decimal.  */
/* This function has been named wf_dec so that it can be moved to the wf      */
/* package if it turns out to be popular.                                     */
p_wf_t p_wf;
ulong  n;
{
 char t[20];
 sprintf(t,"%lu",n);
 wf_wr(p_wf,t);
}

/******************************************************************************/

LOCAL void wv_ugch P_((int));
LOCAL void wv_ugch(ch)
/* WeaVe UGly CHaracter.                                                      */
/* Sometimes it is necessary to output text without causing the typesetting   */
/* program (TeX) to interpret it as control sequences and generate errors.    */
/* There are two ways of doing this. First, we can get the typesetter to do   */
/* the work by making it less sensitive. This has been done with the          */
/* typesetting of the main macro text. The other approach is to convert each  */
/* offending character into the typesetter control sequence that will simply  */
/* output the character. For example, in TeX, "$" becomes "\$". This function */
/* accepts a single character and writes out its safe equivalent.             */
/* The term "ugly" is used to describe potentially harmful text/characters.   */
int ch;
{
 /* End of lines are the only non-printable allowed. */
 if (ch==EOL) {wf_chr(&f_t,EOL); return;}

 /* All other non-printables result in a bullet. In the absence of bugs, the  */
 /* only way a non-printable can get to us here is as a result of the user    */
 /* explicitly inserting one using the scanner's @^ control sequence.         */
 /*if (!isascprn(ch))
    {
     wf_wr(&f_t,"$\\bullet$");
     return;
    }*/
 /* If it IS printable, then print it ... carefully! */
 switch (ch)
   {
    /* Go through the printables in ASCII order. */
    /*   ' ':  is an ordinary character. */
    /*   '!':  is an ordinary character. */
    case '\"':  wf_wr(&f_t,"\\char`\\\"");  break;
    case '#':  wf_wr(&f_t,"\\#");  break;
    case '$':  wf_wr(&f_t,"\\$");  break;
    /* Note: The string "\\%" triggers a unknown sequence "\%" in GNUC.       */
    case '%':  wf_chr(&f_t,'\\'); wf_chr(&f_t,'%'); break;
    case '&':  wf_wr(&f_t,"\\&");  break;
    /*   ''': is an ordinary character. */
    /*   '(': is an ordinary character. */
    /*   ')': is an ordinary character. */
    /*   '*': is an ordinary character. */
    /*   '+': is an ordinary character. */
    /*   ',': is an ordinary character. */
    /*   '-': is an ordinary character. */
    /*   '.': is an ordinary character. */
    /*   '/': is an ordinary character. */
    /* '0-9': are   ordinary characters.*/
    /*   ':': is an ordinary character. */
    /*   ';': is an ordinary character. */
              /* Note: Some \chars work well in roman. Others don't. */
    case '<': if (literal)
                 wf_wr(&f_t,"\\char`\\<");
              else
                 wf_wr(&f_t,"$<$");
              break;
    /*   '=': is an ordinary character. */
    case '>': if (literal)
                 wf_wr(&f_t,"\\char`\\>");
              else
                 wf_wr(&f_t,"$>$");
              break;
    /*   '?': is an ordinary character. */
    /*   '@': is an ordinary character. */
    /* 'A-Z': are   ordinary characters.*/
    /*   '[': is an ordinary character. */
    case '\\': if (literal)
                  wf_wr(&f_t,"\\char`\\\\");
               else
                  wf_wr(&f_t,"$\\backslash$");
               break;
    /*   ']': is an ordinary character. */
    case '^':  wf_wr(&f_t,"\\char`\\^");  break;
    case '_':  wf_wr(&f_t,"\\_");  break;
    /*   '`': is an ordinary character. */
    /* 'a-z': are   ordinary characters.*/
    case '{':  if (literal)
                  wf_wr(&f_t,"\\char`\\{");
               else
                  wf_wr(&f_t,"$\\{$");
               break;
    case '|':  if (literal)
                  wf_wr(&f_t,"\\char`\\|");
               else
                  wf_wr(&f_t,"$|$");
               break;
    case '}':  if (literal)
                  wf_wr(&f_t,"\\char`\\}");
               else
                  wf_wr(&f_t,"$\\}$");
               break;
    case '~':  wf_wr(&f_t,"\\char`\\~");  break;
    default:   wf_chr(&f_t,ch);    break;
   }
}

/******************************************************************************/

LOCAL void wv_ugstr P_((char *));
LOCAL void wv_ugstr(s)
/* Writes out a potentially ugly string. */
char *s;
{
 while (*s != EOS)
    wv_ugch(*s++);
}

/******************************************************************************/

LOCAL void wv_ugsc P_((p_sc_t));
LOCAL void wv_ugsc(p_sc)
/* Writes out a potentially ugly text scrap. */
p_sc_t p_sc;
{
 char *p      = p_sc->sc_first;
 char *p_last = p_sc->sc_last;

 while (p<=p_last)
    wv_ugch(*p++);
}

/******************************************************************************/

LOCAL void wv_ugscls P_((p_scls_t));
LOCAL void wv_ugscls(p_scls)
/* This function writes the specified text list to the output stream. It      */
/* writes it cleaning up all ugly characters.                                 */
p_scls_t p_scls;
{
 ls_fir(p_scls);
 while (TRUE)
   {
    p_sc_t p_sc;
    ls_nxt(p_scls,PPV &p_sc);
    if (p_sc==NULL) break;
    wv_ugsc(p_sc);
   }
}

/******************************************************************************/

LOCAL void wv_manm P_((p_ma_t,ulong));
LOCAL void wv_manm(p_ma,part)
/* This function writes the specified macro name and number. */
/* The part number is the part to write out.                 */
p_ma_t p_ma;
ulong part;
{
 p_bp_t p_bp;
 p_md_t p_md = &p_ma->ma_defn[p_ma->ma_minlev];

 if (p_md->md_isfil)
    wf_wr(&f_t,"\\fwfilename{");
 else
    wf_wr(&f_t,"\\fwmacroname{");
 wv_ugstr(p_ma->ma_name);
 wf_wr(&f_t,"}{");
 ls_loo(p_md->md_body,part,PPV &p_bp);
 wf_dec(&f_t,(ulong) p_bp->bp_seq);
 wf_wr(&f_t,"}");
}

/******************************************************************************/

LOCAL void wv_secnn P_((p_ty_t));
LOCAL void wv_secnn(p_ty)
/* Write out the section number and name, each in curly braces. */
p_ty_t p_ty;
{
 /* Write as arguments the section number and name. */
 wf_chr(&f_t,'{');
 sn_str(&p_ty->ty_sn,linet1);
 wf_wr(&f_t,linet1);
 wf_wr(&f_t,"}{");
 wv_ugstr((string) p_ty->ty_pname);
 wf_chr(&f_t,'}');
}

/******************************************************************************/

LOCAL void wv_echo P_((p_scls_t));
LOCAL void wv_echo(p_scls)
/* This function writes the specified text list to the output stream. It      */
/* writes it just as it is, with no modifications whatsoever.                 */
p_scls_t p_scls;
{
 ls_fir(p_scls);
 while (TRUE)
   {
    p_sc_t p_sc;
    ls_nxt(p_scls,PPV &p_sc);
    if (p_sc==NULL) break;
    wf_blk(&f_t,p_sc->sc_first,(size_t)
   (p_sc->sc_last-p_sc->sc_first+1));
   }
}

/******************************************************************************/

LOCAL void wv_verb P_((p_scls_t));
LOCAL void wv_verb(p_scls)
/* Writes a text list verbetim, but brackets it with sequences that instruct  */
/* the typesetter not to interpret the text in any special way.               */
p_scls_t p_scls;
{
 if (ls_len(p_scls) > 0)
   {
    wf_wr(&f_t,"\\fwbtx[");
    wv_echo(p_scls);
    wf_wl(&f_t,"]fwetx=%");
   }
}

/******************************************************************************/

LOCAL void wv_head P_((void));
LOCAL void wv_head()
{
 wf_wl(&f_t,"");
 wf_wl(&f_t,"%*******************************************************************************");
 wf_wl(&f_t,"%*                    START OF AUTOMATICALLY GENERATED TEX FILE                *");
 wf_wl(&f_t,"%*******************************************************************************");
 wf_wl(&f_t,"%*                                                                             *");
 wf_wl(&f_t,"%* This TeX file was automatically generated by the FunnelWeb preprocessor.    *");
 wf_wl(&f_t,"%* You can typeset this file to produce printed documentation by running it    *");
 wf_wl(&f_t,"%* through the TeX typesetter using a command such as:                         *");
 wf_wl(&f_t,"%*    tex thisfilename                                                         *");
 wf_wl(&f_t,"%* The resultant file thisfilename.dvi can be printed using a command such as: *");
 wf_wl(&f_t,"%*    lpr -Plaser -d thisfilename.dvi                                          *");
 wf_wl(&f_t,"%*                                                                             *");
 wf_wl(&f_t,"%* FunnelWeb is a preprocessor that allows programmers to weave programs and   *");
 wf_wl(&f_t,"%* their documentation together in a single document. The FunnelWeb program    *");
 wf_wl(&f_t,"%* analyses such documents producing both program files and typeset            *");
 wf_wl(&f_t,"%* documentation such as this TeX file.                                        *");
 wf_wl(&f_t,"%* FunnelWeb was created by Ross N. Williams.                                  *");
 wf_wl(&f_t,"%*                                                                             *");
 wf_wl(&f_t,"%* For more information on FunnelWeb see http://www.ross.net/funnelweb/        *");
 wf_wl(&f_t,"%*                                                                             *");
 wf_wl(&f_t,"%*******************************************************************************");
 wf_wl(&f_t,"");
 wf_wl(&f_t,"");
}

/******************************************************************************/

LOCAL void wv_tail P_((void));
LOCAL void wv_tail()
{
 wf_wl(&f_t,"");
 wf_wl(&f_t,"");
 wf_wl(&f_t,"%*******************************************************************************");
 wf_wl(&f_t,"%*                    END OF AUTOMATICALLY GENERATED TEX FILE                  *");
 wf_wl(&f_t,"%*******************************************************************************");
 wf_wl(&f_t,"");
}

/******************************************************************************/

LOCAL void wv_nsec P_((p_ty_t));
LOCAL void wv_nsec(p_ty)
/* Weaves the start of a new section. */
p_ty_t p_ty;
{
 as_cold(p_ty->ty_kind==TY_NSEC,"wv_nsec: Not a section!");

 /* Work out what kind of section macro should be used. */
 switch (sn_lev(&p_ty->ty_sn))
   {
    case 1: wf_wr(&f_t,"\\fwseca"); break;
    case 2: wf_wr(&f_t,"\\fwsecb"); break;
    case 3: wf_wr(&f_t,"\\fwsecc"); break;
    case 4: wf_wr(&f_t,"\\fwsecd"); break;
    case 5: wf_wr(&f_t,"\\fwsece"); break;
    default: as_bomb("wv_nsec:case defaulted.");
   }

 /* Write out the section number and name. */
 wv_secnn(p_ty);
}

/******************************************************************************/

LOCAL void wv_olit P_((p_ty_t));
LOCAL void wv_olit(p_ty)
p_ty_t p_ty;
{
 as_cold(p_ty->ty_kind==TY_OLIT,"wv_olit: Not an open literal!");
 wf_wr(&f_t,"\\fwlit{");
 literal=TRUE;
}

/******************************************************************************/

LOCAL void wv_clit P_((p_ty_t));
LOCAL void wv_clit(p_ty)
p_ty_t p_ty;
{
 as_cold(p_ty->ty_kind==TY_CLIT,"wv_clit: Not a close literal!");
 wf_wr(&f_t,"}");
 literal=FALSE;
}

/******************************************************************************/

LOCAL void wv_oemp P_((p_ty_t));
LOCAL void wv_oemp(p_ty)
p_ty_t p_ty;
{
 as_cold(p_ty->ty_kind==TY_OEMP,"wv_oemp: Not an open emphasize!");
 wf_wr(&f_t,"\\fwemp{");
}

/******************************************************************************/

LOCAL void wv_cemp P_((p_ty_t));
LOCAL void wv_cemp(p_ty)
p_ty_t p_ty;
{
 as_cold(p_ty->ty_kind==TY_CEMP,"wv_cemp: Not a close emphasize!");
 wf_wr(&f_t,"}");
}

/******************************************************************************/

LOCAL void wv_npag P_((p_ty_t));
LOCAL void wv_npag(p_ty)
p_ty_t p_ty;
{
 as_cold(p_ty->ty_kind==TY_NPAG,"wv_npag: Not a new page!");
 wf_wl(&f_t,"");
 wf_wl(&f_t,"\\fwnewpage");
 wf_wl(&f_t,"");
}

/******************************************************************************/

LOCAL void wv_tocs P_((p_ty_t));
LOCAL void wv_tocs(p_ty)
/* Writes a table of contents to the weave output file. */
p_ty_t p_ty;
{
 /* We need to save the document list position as the rest of the weaver is   */
 /* in the process of traversing it!!!                                        */
 p_void p_mark = ls_mar(document_list);

 as_cold(p_ty->ty_kind==TY_TOCS,"wv_tocs: Not a table of contents!");

 wf_wl(&f_t,"");
 wf_wl(&f_t,"\\fwtocstart{}");
 ls_fir(document_list);
 while (TRUE)
   {
    p_dc_t p_dc;
    ls_nxt(document_list,PPV &p_dc);
    if (p_dc == NULL) break;
    if (p_dc->dc_kind==DC_TYPE && p_dc->dc_pty->ty_kind==TY_NSEC)
      {
       switch(sn_lev(&p_dc->dc_pty->ty_sn))
         {
          case 1: wf_wr(&f_t,"\\fwtoca"); break;
          case 2: wf_wr(&f_t,"\\fwtocb"); break;
          case 3: wf_wr(&f_t,"\\fwtocc"); break;
          case 4: wf_wr(&f_t,"\\fwtocd"); break;
          case 5: wf_wr(&f_t,"\\fwtoce"); break;
          default: as_bomb("wv_toc: switch defaulted.");
         }
       wv_secnn(p_dc->dc_pty);
       wf_wl(&f_t,"");
      }
   }
 wf_wl(&f_t,"\\fwtocfinish{}");
 wf_wl(&f_t,"");

 /* Restore the document list position. */
 ls_set(document_list,p_mark);
}

/******************************************************************************/

LOCAL void wv_skip P_((p_ty_t));
LOCAL void wv_skip(p_ty)
/* Writes a vertical space to the output file. */
p_ty_t p_ty;
{
 as_cold(p_ty->ty_kind==TY_SKIP,"wv_skip: Not a skip directive!");

 sprintf(linet1,"\\fwvskip{%lu}",(ulong) p_ty->ty_mm);
 wf_wl(&f_t,linet1);
}

/******************************************************************************/

LOCAL void wv_titl P_((p_ty_t));
LOCAL void wv_titl(p_ty)
/* Writes a title line to the output file. */
p_ty_t p_ty;
{
 as_cold(p_ty->ty_kind==TY_TITL,"wv_titl: Not a title!");

 switch(p_ty->ty_align)
   {
    case LR_LEFT: wf_wr(&f_t,"\\fwleftline{");   break;
    case LR_RIGH: wf_wr(&f_t,"\\fwrightline{");  break;
    case LR_CENT: wf_wr(&f_t,"\\fwcenterline{"); break;
    default: as_bomb("wv_title: Alignment switch defaulted.");
   }
 switch(p_ty->ty_font)
   {
    case FT_NORM: wf_wr(&f_t,"\\fwfontnormal{");     break;
    case FT_TITL: wf_wr(&f_t,"\\fwfonttitle{");      break;
    case FT_STIT: wf_wr(&f_t,"\\fwfontsmalltitle{"); break;
    default: as_bomb("wv_title: Font switch defaulted.");
   }
 wv_ugsc(&p_ty->ty_sc);
 wf_wl(&f_t,"}}");
}

/******************************************************************************/

LOCAL void wv_dcty P_((p_dc_t));
LOCAL void wv_dcty(p_dc)
/* Weaves a document typesetter element. */
p_dc_t p_dc;
{
 p_ty_t p_ty = p_dc->dc_pty;

 as_cold(p_dc->dc_kind==DC_TYPE,"wv_dcty: Not a typesetter component!");

 switch (p_ty->ty_kind)
   {
    case TY_NSEC: wv_nsec(p_ty); break;
    case TY_OLIT: wv_olit(p_ty); break;
    case TY_CLIT: wv_clit(p_ty); break;
    case TY_OEMP: wv_oemp(p_ty); break;
    case TY_CEMP: wv_cemp(p_ty); break;
    case TY_NPAG: wv_npag(p_ty); break;
    case TY_TOCS: wv_tocs(p_ty); break;
    case TY_SKIP: wv_skip(p_ty); break;
    case TY_TITL: wv_titl(p_ty); break;
    default     : as_bomb("wv_dcty: Switch defaulted.");
   }
}

/******************************************************************************/

LOCAL void wv_dctx P_((p_dc_t));
LOCAL void wv_dctx(p_dc)
/* Write out a document text item. */
p_dc_t p_dc;
{
 as_cold(p_dc->dc_kind==DC_TEXT,"wv_dctx: Not text.");

 if (literal || tr_codes==TR_NONE)
    wv_ugscls(p_dc->dc_text);
 else
    wv_echo(p_dc->dc_text);
}

/******************************************************************************/

LOCAL void wv_eltx P_((p_el_t));
LOCAL void wv_eltx(p_el)
/* Weaves a text element. */
p_el_t p_el;
{
 as_cold(p_el->el_kind==EL_TEXT,"wv_eltx: Not text.");
 wv_verb(p_el->el_text);
}

/******************************************************************************/

LOCAL void wv_elin P_((p_el_t));
LOCAL void wv_elin(p_el)
/* Weaves a invocation element. */
p_el_t p_el;
{
 as_cold(p_el->el_kind==EL_INVC,"wv_elin: Not an invocation.");

 /* Write out the macro call proper. */
 wv_manm(p_el->el_p_mac,1L);

 /* Write out the actual parameter list, if any. */
 if (ls_len(p_el->el_parls) > 0)
   {
    ulong    parnum;
    wf_wr(&f_t,"\\fwoparen ");
    ls_fir(p_el->el_parls);  /* List of actual parameter expressions. */
    ls_fir(p_el->el_pretx);  /* List of crud before each expression.  */
    ls_fir(p_el->el_postx);  /* List of crud after  each expression.  */
    parnum=1;
    while (TRUE)
      {
       p_ells_t *pp_exp;
       p_scls_t *pp_scls1;
       p_scls_t *pp_scls2;
       ls_nxt(p_el->el_parls,PPV &pp_exp);
       ls_nxt(p_el->el_pretx,PPV &pp_scls1);
       ls_nxt(p_el->el_postx,PPV &pp_scls2);
       if (pp_exp==NULL) break;
       if (parnum++>1) wf_wr(&f_t,"\\fwcomma ");
       wv_verb(*pp_scls1);
       wf_wr(&f_t,"\\fwoquote"); wv_ex(*pp_exp); wf_wr(&f_t,"\\fwcquote");
       wv_verb(*pp_scls2);
      }
    wf_wr(&f_t,"\\fwcparen ");
   }
}

/******************************************************************************/

LOCAL void wv_elpr P_((p_el_t));
LOCAL void wv_elpr(p_el)
/* Weaves a parameter element. */
p_el_t p_el;
{
 as_cold(p_el->el_kind==EL_PARM,"wv_elpr: Not a parameter.");
 wf_wr (&f_t,"\\fwparam{");
 wf_dec(&f_t,(ulong) p_el->el_parno);
 wf_wr (&f_t,"}");
}


/******************************************************************************/

LOCAL void wv_ex(p_exp)
/* Weaves a expression. */
p_ells_t p_exp;
{

 ls_fir(p_exp);
 while (TRUE)
   {
    p_el_t p_el;
    ls_nxt(p_exp,PPV &p_el);
    if (p_el==NULL) break;
    switch (p_el->el_kind)
      {
       case EL_TEXT: wv_eltx(p_el); break;
       case EL_INVC: wv_elin(p_el); break;
       case EL_PARM: wv_elpr(p_el); break;
       default: as_bomb("wv_ex: Case defaulted.");
      }
   }
}

/******************************************************************************/

LOCAL void wv_usage P_((p_ma_t,ulong));
LOCAL void wv_usage(p_ma,level)
/* Weaves a list of all the sections in which the specified macro is used. */
p_ma_t p_ma;
ulong  level;
{
 p_md_t p_md = &p_ma->ma_defn[p_ma->ma_minlev];

 ulong  no_calls = ls_len(p_ma->ma_calls);
 ulong  callno;

 /* If it is a file macro then it is not allowed to be called. */
 if (p_md->md_isfil)
   {
    wf_wl(&f_t,"\\fwisafile{This macro is attached to an output file.}");
    return;
   }

 if (p_ma->ma_minlev < level)
   {
    p_bp_t p_bp;
    p_md_t p_md2 = &p_ma->ma_defn[p_ma->ma_minlev];
    ls_loo(p_md2->md_body,1L,PPV &p_bp);
    wf_wl(&f_t,"\\fwusedin{This library macro was overruled by definition ");
    wf_dec(&f_t,(ulong) p_bp->bp_seq);
    wf_wl(&f_t," and is not active.}");
    return;
   }

 if (no_calls==0)
   {
    wf_wl(&f_t,"\\fwusedin{This macro is NEVER invoked.}");
    return;
   }

 wf_wr(&f_t,"\\fwusedin{This macro is invoked in definition");
 if (no_calls>1) wf_chr(&f_t,'s');
 wf_chr(&f_t,' ');
 ls_fir(p_ma->ma_calls);
 for (callno=1;callno<=no_calls;callno++)
   {
    p_mc_t p_mc;
    ls_nxt(p_ma->ma_calls,PPV &p_mc); as_cold(p_mc!=NULL,"wv_usage: Awk!");
    wf_dec(&f_t,(ulong) p_mc->mc_seq);
    if (callno < no_calls-1)
       wf_wr(&f_t,", ");
    else
       if (callno==no_calls-1)
           wf_wr(&f_t," and ");
   }
 wf_wl(&f_t,".}");
}

/******************************************************************************/

LOCAL void wv_defin P_((p_ma_t,ulong));
LOCAL void wv_defin(p_ma,level)
/* Just after each macro body part definition comes a note listing the        */
/* containing the macro's body parts. This function weaves that list.         */
p_ma_t p_ma;
ulong  level;
{
 p_md_t p_md = &p_ma->ma_defn[level];
 ulong  no_parts = ls_len(p_md->md_body);
 ulong  partno;

 /* If it's not an additive macro, we don't write anything. */
 if (!p_md->md_isadd) return;

 wf_wr(&f_t,"\\fwseealso{This macro is defined in definitions ");
 ls_fir(p_md->md_body);
 for (partno=1;partno<=no_parts;partno++)
   {
    p_bp_t p_bp;
    ls_nxt(p_md->md_body,PPV &p_bp);
    as_cold(p_bp!=NULL,"wv_defin: Awk!");
    wf_dec(&f_t,(ulong) p_bp->bp_seq);
    if (partno<no_parts-1)
       wf_wr(&f_t,", ");
    else
       if (partno==no_parts-1)
          wf_wr(&f_t," and ");
   }
 wf_wl(&f_t,".}");
}

/******************************************************************************/

LOCAL void wv_dcma P_((p_dc_t));
LOCAL void wv_dcma(p_dc)
/* Weaves a macro definition. */
p_dc_t p_dc;
{
 p_bp_t p_bp;
 p_ma_t p_ma  = p_dc->dc_p_ma;
 ulong  level = p_dc->dc_mlev;
 p_md_t p_md  = &p_ma->ma_defn[level];

 /* Macro calls sandwich the definition itsef. */
 wf_wl(&f_t,"\\fwbeginmacro");

 /* Write out the macro's name. */
 wv_manm(p_ma,p_dc->dc_part);

 /* Write the formal parameter list. */
 if (p_md->md_npar>0)
   {
    wf_wr(&f_t,"\\fwparams{");
    wf_dec(&f_t,(ulong) p_md->md_npar);
    wf_wr(&f_t,"}");
   }

 /* Zero and many options are indicated by bold letters. */
 {
  ulong i;
  if (p_md->md_iszer) wf_wr(&f_t,"\\fwzero{}");
  if (p_md->md_isman) wf_wr(&f_t,"\\fwmany{}");
  for (i=0; i<level; i++) wf_wr(&f_t,"\\fwlib{}");
 }

 /* Write the "equals". */
 if (p_md->md_isadd)
    wf_wr(&f_t,"\\fwplusequals ");
 else
    wf_wr(&f_t,"\\fwequals ");

 /* Write out this particular body part. */
 ls_loo(p_md->md_body,p_dc->dc_part,PPV &p_bp);
 wf_wr(&f_t,"\\fwodef ");
 wv_ex(p_bp->bp_ex);
 wf_wl(&f_t,"\\fwcdef ");

 /* After the macro definition, write out notes on the macro. */
 wf_wl(&f_t,"\\fwbeginmacronotes");
 wv_defin(p_dc->dc_p_ma,level);       /* A list of the macro's body parts.  */
 wv_usage(p_dc->dc_p_ma,level);       /* A list of where the macro is used. */
 wf_wl(&f_t,"\\fwendmacronotes");

 /* The macro definition is sandwiched by macro calls. */
 wf_wl(&f_t,"\\fwendmacro");
}

/******************************************************************************/

LOCAL void wv_dc P_((p_dc_t));
LOCAL void wv_dc(p_dc)
/* Weaves a document component (p_dc). */
p_dc_t p_dc;
{
 switch (p_dc->dc_kind)
   {
    case DC_TEXT: wv_dctx(p_dc); break;
    case DC_TYPE: wv_dcty(p_dc); break;
    case DC_MACR: wv_dcma(p_dc); break;
    default     : as_bomb("wv_dc: Case defaulted.");
   }
}

/******************************************************************************/

LOCAL void wv_docnt P_((void));
LOCAL void wv_docnt()
/* Weaves the entire document. This functions and most functions above assume */
/* that the output stream f_t is prepared for writing.                        */
{
 /* Write the typeset header. */
 wv_head();

 /* Writes the library macros. */
 tex_head(&f_t);

 ls_fir(document_list);
 literal=FALSE;
 while (TRUE)
   {
    p_dc_t p_dc;
    ls_nxt(document_list,PPV &p_dc);
    if (p_dc == NULL) break;
    wv_dc(p_dc);
   }
 wf_wl(&f_t,"\\bye");

 /* Write the typeset trailer. */
 wv_tail();
}

/******************************************************************************/

EXPORT void weavet()
/* Writes out the documentation file. */
{
 fn_t  fn_tmp;   /* Name of temporary file.                                   */
 fn_t  fn_targ;  /* Name of documentation file.                               */
 bool  renfil;   /* Do we wish to rename output file?                         */
 bool  istarg;   /* Does a target file already exist?                         */

 /* Writing the documentation file differs from some other output files. With */
 /* non critical files such as the listing file that are really just logs,    */
 /* generation of half a listing file is acceptable if not desirable. However */
 /* in the case of the documentation file, it is very bad to generate half an */
 /* output file; far better to generate none at all. For this reason, and     */
 /* also because of the presence of the D option (which prevents the writing  */
 /* of output files identical to existing files (to prevent MAKE              */
 /* propagations)) it is best to write a temporary file and then rename it.   */

 /* We shouldn't be here if the weave option is off! */
 as_cold(option.op_t_b,"weave: option.op_t_b==FALSE!");

 /* Work out what the typeset file's name should be.                          */
 strcpy(fn_targ,"");              /* Start with an empty string.              */
 fn_ins(fn_targ,option.op_f_s);
 fn_ins(fn_targ,".tex");
 fn_ins(fn_targ,option.op_t_s);

 /* The temporary file has to inherit too, because the output directory may   */
 /* not be the default directory and some computers can't rename across       */
 /* directories (and we have to rename it later).                             */
 strcpy(fn_tmp,fn_targ);
 fn_ins(fn_tmp,fn_temp());

 /* Complain if the FunnelWeb file doesn't have typesetter = none or tex. */
 if ((tr_codes != TR_NONE) && (tr_codes != TR_TEX))
   {
    sprintf(linet1,"Error generating TeX documentation file \"%s\".",&fn_targ[0]);
    wl_sjl(linet1);
    wl_sjl("To generate a TeX documentation file, the FunnelWeb input file");
    wl_sjl("must either be typesetter-independent (the default) or TeX-dependent.");
    wl_sjl("However, this input file declares itself dependent on a non-TeX typesetter.");
    wl_sjl("See the \"@p typesetter\" pragma in the input file for more information.");
    goto severe;
   }

 /* Expand the macro to the temporary file. */
 wf_ini(&f_t,TRUE);
 wf_ope(&f_t,fn_tmp);
 if (wf_err(&f_t))
   {
    sprintf(linet1,"Error creating temporary TeX documentation file \"%s\".",&fn_tmp[0]);
    wl_sjl(linet1);
    (void) remove(fn_tmp);
    goto severe;
   }

 wv_docnt();

 /* Make sure that there weren't any errors writing to the temporary file. */
 if (wf_err(&f_t))
   {
    sprintf(linet1,"Error writing to temporary TeX documentation file \"%s\".",&fn_tmp[0]);
    wl_sjl(linet1);
    (void) remove(fn_tmp);
    goto severe;
   }

 /* Close the temporary file. */
 wf_clo(&f_t);
 if (wf_err(&f_t))
   {
    sprintf(linet1,"Error closing temporary TeX documentation file \"%s\".",&fn_tmp[0]);
    wl_sjl(linet1);
    remove(fn_tmp);
    goto severe;
   }

 /* The rest of the code in this function copes with the renaming. */

 /* By default, we wish to rename the temporary file. */
 renfil=TRUE;

 /* Deal with any existing file of the target name. */
 istarg=fexists(fn_targ);
 if (istarg && option.op_d_b)
   {
    /* A target already exists, and the D option is on. If the target is      */
    /* identical to the temporary, we can simply delete the temporary!        */
    char *errstr;
    bool  same;
    errstr=eq_files(fn_tmp,fn_targ,&same);
    if (errstr != NULL)
      {
       wl_sjl("Error comparing temporary TeX file with previous documentation file.");
       wl_sjl("(A comparison was attempted because the D option was turned on.)");
       wl_sjl("Error from comparison routine was as follows (first=temp):");
       wr_sjl("   ");wl_sjl(errstr);
       sprintf(linet1,"Temporary file name was \"%s\".",&fn_tmp[0]);
       wl_sjl(linet1);
       sprintf(linet1,"Output    file name was \"%s\".",&fn_targ[0]);
       wl_sjl(linet1);
       wl_sjl("FunnelWeb will leave both files intact so you can look at them.");
       goto severe;
      }
    /* If the two files are the same, we can simply delete the temporary. */
    if (same)
      {
       int status;
       status=remove(fn_tmp);
       if (status != REMOVE_S)
         {
          sprintf(linet1,"Error deleting (under +D option) temporary file \"%s\".",&fn_tmp[0]);
          wl_sjl(linet1);
          goto severe;
         }
       sprintf(linet1,"Deleted identical TeX documentation file \"%s\".",&fn_targ[0]);
       wl_sjl(linet1);
       renfil=FALSE;
      }
   }

 if (renfil)
   {
    int status;
    /* We need to delete any existing file of the target name. */
    if (istarg)
      {
       status=remove(fn_targ);
       if (status != REMOVE_S)
         {
          sprintf(linet1,"Error deleting existing TeX documentation file \"%s\".",&fn_targ[0]);
          wl_sjl(linet1);
          goto severe;
         }
      }
    /* Rename the temporary file to the output file. */
    status=rename(fn_tmp,fn_targ);
    if (status != RENAME_S)
      {
       wl_sjl("Error renaming temporary TeX documentation file to documentation file.");
       sprintf(linet1,"Temporary file name was \"%s\".",&fn_tmp[0]);
       wl_sjl(linet1);
       sprintf(linet1,"Output    file name was \"%s\".",&fn_targ[0]);
       wl_sjl(linet1);
       wl_sjl("FunnelWeb will leave both files intact so you can look at them.");
       goto severe;
      }
   }

 /* Tell everyone that we have written an output file. */
 sprintf(linet1,"Weave : Completed %s.",fn_nodir(&fn_targ[0]));
 wl_s(linet1);
 if (option.op_b7_b)
    sprintf(linet1,"Weave: Completed %s.",SUPPNAME);
 wl_j(linet1);
 wl_l(linet1);
 return;

 /* Jump here is a nasty file error occurs. */
 severe:
 sprintf(linet1,"A problem occurred during the generation of TeX documentation file \"%s\".",&fn_targ[0]);
 wl_sjl(linet1);
 wl_sjl("S: Aborting...");
 num_sev++;
 return;
}

/******************************************************************************/

