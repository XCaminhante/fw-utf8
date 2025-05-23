/*##############################################################################

FUNNNELWEB COPYRIGHT
====================
FunnelWeb is a literate-programming macro preprocessor.
The FunnelWeb web is at http://www.ross.net/funnelweb/

Copyright (c) Ross N. Williams 1992. All rights reserved.

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

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.

##############################################################################*/


/******************************************************************************/
/*                                   HELP.C                                   */
/******************************************************************************/
/*                                                                            */
/* REPRESENTING MESSAGES AS C CODE                                            */
/* ===============================                                            */
/* Experience has shown that it is much more reliable to code text messages   */
/* into a program than to expect the program to track down text files         */
/* containing the messages at run time. Worthwhile for smallish files (such   */
/* as these help messages) at least. For this reason, most the messages in    */
/* this module are represented by code (e.g. as in printf statements).        */
/*                                                                            */
/* The only exception is the 18K Gnu license message which is a bit too big   */
/* to be done by hand. It has been moved to the help_gnu module.              */
/*                                                                            */
/******************************************************************************/

#include <ctype.h>
#include "style.h"

#include "as.h"
#include "help.h"
#include "help_gnu.h"
#include "misc.h"
#include "option.h"

/******************************************************************************/

/* This module contains many many output statements that call an output       */
/* function. To neaten up all these calls, we define a global variable to     */
/* hold a pointer to the function and simple macro to write output using      */
/* the function.                                                              */
LOCVAR void (*pf) P_((char *));

#define WX(STR) (*pf)(STR)

/******************************************************************************/

LOCAL void hel_men P_((void));
LOCAL void hel_men ()
{
 WX("\n");
 WX("FunnelWeb Help Messages\n");
 WX("-----------------------\n");
 WX("Introduction  - Introduction to FunnelWeb.\n");
 WX("DOcumentation - How to obtain FunnelWeb documentation.\n");
 WX("Options       - Command line options.\n");
 WX("DEfoptions    - Default command line options.\n");
 WX("COMmands      - Interactive commands.\n");
 WX("COPyright     - Copyright notice.\n");
 WX("License       - The license under which this software is distributed (long).\n");
 WX("Nowarranty    - Extract from the GNU license concerning lack of warranty.\n");
 WX("DIstribution  - Extract from the GNU license concerning distribution.\n");
 WX("MOdification  - Read this message if you intend to modify FunnelWeb.\n");
 WX("Versions      - A list of existing versions of FunnelWeb.\n");
 WX("Acknowledge   - Thanks to people who helped with FunnelWeb development.\n");
 WX("MEnu          - The message you are reading (the default help message).\n");
 WX("\n");
 WX("To display a message, give its (optionally abbreviated) name in a help command.\n");
 WX("To capture a message to a file, add +J<filename> to the fw command. Examples:\n");
 WX("\n");
 WX("          fw +Hintroduction +Jintro.txt   -- From the operating system level.\n");
 WX("          help introduction               -- From FunnelWeb interactive mode.\n");
}

/******************************************************************************/

LOCAL void hel_int P_((void));
LOCAL void hel_int ()
{
 WX("\n");
 WX("FunnelWeb Introduction\n");
 WX("----------------------\n");
 WX("Welcome to FunnelWeb, a literate-programming macro preprocessor.\n");
 WX("\n");
 WX("Traditional computer programs are primarily written for computers and consist\n");
 WX("of code laced with comments. In contrast, literate programs are primarily\n");
 WX("written for humans and consist of comments laced with code.  While simple, the\n");
 WX("effect of this inversion can change one's whole approach to programming.\n");
 WX("The literate programmer focuses on conveying meaning to other intelligent\n");
 WX("beings rather than merely convincing the computer to behave in a particular\n");
 WX("way. It is the difference between performing and exposing a magic trick.\n");
 WX("\n");
 WX("FunnelWeb is a production-quality literate-programming tool that emphasises\n");
 WX("simplicity and reliability. It provides a macro facility, and assists in the\n");
 WX("production of typeset documentation. FunnelWeb is available for most popular\n");
 WX("platforms and its highly portable source code in C is freely available under\n");
 WX("a GNU license.\n");
 WX("\n");
 WX("To get started with FunnelWeb, visit these webs:\n");
 WX("   http://www.ross.net/funnelweb/\n");
 WX("   http://www.ross.net/funnelweb/tutorial/\n");
}

/******************************************************************************/

LOCAL void hel_opt P_((void));
LOCAL void hel_opt ()
{
 WX("\n");
 WX("FunnelWeb Command Line Options\n");
 WX("------------------------------\n");
 WX("Options are of the form (\"+\" | \"=\" | \"-\") <letter> [<string>].\n");
 WX("+ turns on an option. - turns it off. = doesn't affect it's onoffedness.\n");
 WX("The case (e.g. upper or lower) of <letter> does not matter.\n");
 WX("<string> is usually a filename or directory, but sometimes a number.\n");
 WX("Convention: f=filename, n=decimal number, h=help message name.\n");
 WX("\n");
 WX("Example: fw sloth +L +Jaardvark.xxx +W80 -Q =Twalrus.tex\n");
 WX("\n");
 WX("Action options: (choose at least one when you invoke FunnelWeb from the OS).\n");
 WX("If you choose more than one, they will be executed in the order given here.\n");
 WX("   +Xf   Execute specified Funnelweb script.\n");
 WX("   +Ff   Process specified input file.\n");
 WX("   +Hh   Display specified help message.\n");
 WX("   +K    Invoke FunnelWeb's interative mode.\n");
 WX("\n");
 WX("Other options:\n");
 WX("   +B1   Diagnostic: Dump image of input file    to listing file.\n");
 WX("   +B2   Diagnostic: Dump scanner's line list    to listing file.\n");
 WX("   +B3   Diagnostic: Dump scanner's token list   to listing file.\n");
 WX("   +B4   Diagnostic: Dump parser's macro table   to listing file.\n");
 WX("   +B5   Diagnostic: Dump parser's document list to listing file.\n");
 WX("   +B6   Diagnostic: Dump time breakdown report  to listing file.\n");
 WX("   +B7   Diagnostic: Suppress non-deterministic output.\n");
 WX("   +Cn   Number of lines of context around diagnostics in listing file.\n");
 WX("   +D    Delete each output file identical to its previous version.\n");
 WX("   +If   Default file specification for include files.\n");
 WX("   +Jf   Generate journal file.  Default file specification.\n");
 WX("   +Lf   Generate listing file.  Default file specification.\n");
 WX("   +Of   Generate product files. Default file specification.\n");
 WX("   +Q    Quiet mode. Only really important messages displayed on console.\n");
 WX("   +Tf   Generate Tex documentation file. Default file specification.\n");
 WX("   +Uf   Generate HTML documentation file. Default file specification.\n");
 WX("   +Sn   Send errors to console with specified number of lines of context.\n");
 WX("   +Wn   Set maximum length of lines in product files.\n");
 WX("\n");
 WX("If an option appears more than once, the rightmost one dominates.\n");
 WX("For default values refer to the \"DEFOPTIONS\" help message.\n");
 WX("For more information, refer to the FunnelWeb Reference Manual at:\n");
 WX("   http://www.ross.net/funnelweb/reference/\n");
}

/******************************************************************************/

LOCAL void hel_dop P_((void));
LOCAL void hel_dop ()
{
 op_t defop;

 WX("\n");
 WX("FunnelWeb Default Option Settings\n");
 WX("---------------------------------\n");
 WX("These are the settings FunnelWeb STARTS UP with.\n");
 op_ini(&defop);
 WX("\n");
 op_wri(&defop,pf);
 WX("\n");
 WX("See the OPTIONS help message for a brief description of these options.\n");
 WX("For more information, refer to the FunnelWeb Reference Manual at:\n");
 WX("   http://www.ross.net/funnelweb/reference/\n");
}

/******************************************************************************/

LOCAL void hel_com P_((void));
LOCAL void hel_com ()
{
 WX("\n");
 WX("FunnelWeb Interactive Commands\n");
 WX("------------------------------\n");
 WX("   !                       - Comment. Ignores the whole line.             \n");
 WX("   ABSENT fn               - Aborts if specified file exists.             \n");
 WX("   CODIFY ftext fC         - Convert text file into C code to write text. \n");
 WX("   COMPARE f1 f2           - Aborts if two files are different.           \n");
 WX("   DEFINE n \"text\"         - Defines $n to translate to text.             \n");
 WX("   DIFF f1 f2 logf [ABORT] - Writes differences between f1 and f2 to logf.\n");
 WX("                           - Severe if different and ABORT is present.    \n");
 WX("   DIFFSUMMARY             - Summary of differences done since DIFFZERO.  \n");
 WX("   DIFFZERO                - Zeros differences counters.                  \n");
 WX("   ENEO fn                 - Establish Non Existence Of file.             \n");
 WX("   EXECUTE fn              - Execute commands in specified file.          \n");
 WX("   EXISTS fn               - Aborts if file does not exist.               \n");
 WX("   FIXEOLS fn [outf]       - Fixes up EOL markers in specified file.      \n");
 WX("   FW options              - Invoke FunnelWeb-proper once.                \n");
 WX("   HELP [name]             - Displays specified help message.             \n");
 WX("   HERE                    - Terminates effect of SKIPTO command.         \n");
 WX("   QUIT                    - Quits FunnelWeb.                             \n");
 WX("   SET options             - Sets options.                                \n");
 WX("   SHOW                    - Displays currently active options.           \n");
 WX("   SKIPTO                  - Ignore commands until HERE command.          \n");
 WX("   STATUS                  - Write out status and diagnostic counts.      \n");
 WX("   STATUS [Sn] [En] [Wn]   - Aborts if status is not as specified.        \n");
 WX("   TOLERATE                - Don't abort script if next commmand gens err.\n");
 WX("   TRACE ON | OFF          - Turns command tracing ON or OFF.             \n");
 WX("   WRITE \"text\"            - Writes specified text to screen and journal. \n");
 WX("   WRITEU \"text\"           - Same as WRITE but underlines text.           \n");
 WX("\n");
 WX("For more information, refer to the FunnelWeb Reference Manual at:\n");
 WX("   http://www.ross.net/funnelweb/reference/\n");
 WX("\n");
 WX("Most of these commands were created to support regression testing and\n");
 WX("can be ignored by most users. In fact most users will never need to invoke\n");
 WX("FunnelWeb's interactive mode at all. If you are just getting started\n");
 WX("with FunnelWeb, it's probably best to run FunnelWeb directly from your\n");
 WX("command interface and ignore the +K command line option for now.\n");
}

/******************************************************************************/

LOCAL void hel_doc P_((void));
LOCAL void hel_doc ()
{
 WX("\n");
 WX("FunnelWeb Documentation\n");
 WX("-----------------------\n");
 WX("The following FunnelWeb documentation is available:\n");
 WX("\n");
 WX("   http://www.ross.net/funnelweb/            - Main FunnelWeb web.\n");
 WX("   http://www.ross.net/funnelweb/reference/  - Reference manual.\n");
 WX("   http://www.ross.net/funnelweb/tutorial/   - Tutorial manual.\n");
 WX("   http://www.ross.net/funnelweb/developer/  - Developer manual.\n");
}

/******************************************************************************/

LOCAL void hel_cop P_((void));
LOCAL void hel_cop ()
{
 WX("\n");
 WX("FunnelWeb Copyright\n");
 WX("-------------------\n");
 WX("Copyright (c) Ross N. Williams 1992. All rights reserved.\n");
 WX("\n");
 WX("However, FunnelWeb has been released by the author and copyright owner Ross\n");
 WX("N. Williams (ross@ross.net) under Version 2 of the GNU General Public\n");
 WX("License published by the Free Software Foundation. This means that you can\n");
 WX("redistribute FunnelWeb and/or modify it under the terms of the license.\n");
 WX("\n");
 WX("Note: This program is distributed WITHOUT ANY WARRANTY; without even the\n");
 WX("implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
 WX("\n");
 WX("The following help messages provide further information:\n");
 WX("\n");
 WX("   License       - The license under which this software is distributed (long).\n");
 WX("   DIstribution  - Extract from the GNU license concerning distribution.\n");
 WX("   Nowarranty    - Extract from the GNU license concerning lack of warranty.\n");
 WX("   MOdification  - Read this message if you intend to modify FunnelWeb.\n");
 WX("   Registration  - How to register as an \"official\" FunnelWeb user.\n");
 WX("\n");
}

/******************************************************************************/

LOCAL void hel_now P_((void));
LOCAL void hel_now ()
{
 WX("\n");
 WX("FunnelWeb Comes With No Warranty\n");
 WX("--------------------------------\n");
 WX("Here is an extract from the GNU General Public License Version 2, under which\n");
 WX("FunnelWeb is distributed. See help message \"LICENSE\" for the full license.\n");
 WX("\n");
 WX("   11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY\n");
 WX("   FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN\n");
 WX("   OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES\n");
 WX("   PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED\n");
 WX("   OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF\n");
 WX("   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS\n");
 WX("   TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE\n");
 WX("   PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,\n");
 WX("   REPAIR OR CORRECTION.\n");
 WX("\n");
 WX("   12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING\n");
 WX("   WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR\n");
 WX("   REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,\n");
 WX("   INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING\n");
 WX("   OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED\n");
 WX("   TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY\n");
 WX("   YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER\n");
 WX("   PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE\n");
 WX("   POSSIBILITY OF SUCH DAMAGES.\n");
}

/******************************************************************************/

LOCAL void hel_dis P_((void));
LOCAL void hel_dis ()
{
 WX("\n");
 WX("FunnelWeb Distribution\n");
 WX("----------------------\n");
 WX("The following is an extract from the GNU General Public License Version 2,\n");
 WX("under which FunnelWeb is distributed.\n");
 WX("\n");
 WX("   1. You may copy and distribute verbatim copies of the Program's\n");
 WX("   source code as you receive it, in any medium, provided that you\n");
 WX("   conspicuously and appropriately publish on each copy an appropriate\n");
 WX("   copyright notice and disclaimer of warranty; keep intact all the\n");
 WX("   notices that refer to this License and to the absence of any warranty;\n");
 WX("   and give any other recipients of the Program a copy of this License\n");
 WX("   along with the Program.\n");
 WX("\n");
 WX("   You may charge a fee for the physical act of transferring a copy, and\n");
 WX("   you may at your option offer warranty protection in exchange for a fee.\n");
 WX("\n");
 WX("The license also allows you other freedoms.  For more information refer\n");
 WX("to the full text of the license in the help message \"LICENSE\".\n");
}

/******************************************************************************/

LOCAL void hel_ack P_((void));
LOCAL void hel_ack ()
{
 WX("\n");
 WX("FunnelWeb Acknowledgements\n");
 WX("--------------------------\n");
 WX("The following people assisted with the preparation of FunnelWeb.\n");
 WX("\n");
 WX("Many thanks go to DAVID HULSE (dave@cs.adelaide.edu.au) who translated the 1986\n");
 WX("version of FunnelWeb (V1) written in Ada into a public domain C version (V2).\n");
 WX("\n");
 WX("Thanks go to SIMON HACKETT (simon@internode.com.au) of Internode Systems\n");
 WX("Pty Ltd for the use of his Sun, Mac, and PC, for assistance in porting\n");
 WX("FunnelWeb to the Sun and PC, and for helpful discussions.\n");
 WX("\n");
 WX("Thanks go to JEREMY BEGG (jeremy@vsm.com.au) of VSM Software Services\n");
 WX("for the use of his VAX, and for assistance with the VMS-specific code.\n");
 WX("\n");
 WX("Ross Williams (ross@ross.net), 12 May 1992.\n");
}

/******************************************************************************/

LOCAL void hel_ver P_((void));
LOCAL void hel_ver ()
{
 WX("\n");
 WX("FunnelWeb Versions\n");
 WX("------------------\n");
 WX("FunnelWeb was created in 1986 and was used extensively by Ross N. Williams\n");
 WX("(ross@ross.net) for three years. However, Version 1.0 was written\n");
 WX("in Ada and was not very portable (it was fairly VAX/VMS specific). David Hulse\n");
 WX("(dave@cs.adelaide.edu.au) took the first step towards a release by translating\n");
 WX("the Ada code into C. Ross N. Williams then extensively reworked the C code,\n");
 WX("making it robust and portable, adding new features, and polishing it to its\n");
 WX("1992 V3.0 release. In 1999 he released V3.2.\n");
 WX("A extensive revision of FunnelWeb is been made in 2025 by X Caminhante.\n");
 WX("\n");
 WX("Vers  Lang  Created  Released   Author          Copyright      Licensing      \n");
 WX("----  ----  -------  --------   --------------  -------------  ---------      \n");
 WX("V1.0  Ada   1986     Never      Ross  Williams  Ross Williams  Exe for Vax.   \n");
 WX("V2.0  C     1989     Never      David Hulse     Public domain  No restriction.\n");
 WX("V3.0  C     1992     May-1992   Ross  Williams  Ross Williams  GNU release.   \n");
 WX("V3.1  C     1993     Never      Ross  Williams  Ross Williams  Not released.  \n");
 WX("V3.2  C     1999     May-1999   Ross  Williams  Ross Williams  GNU release.   \n");
 WX("V3.3  C     2025     May-2025   X Caminhante    X Caminhante   GNU release.   \n");
 WX("\n");
 WX("This is FunnelWeb Version 3.3.");
 WX("For more information on versions, refer to the FunnelWeb Reference Manual at:\n");
 WX("   http://www.ross.net/funnelweb/reference/\n");
}

/******************************************************************************/

LOCAL void hel_mod P_((void));
LOCAL void hel_mod ()
{
 WX("\n");
 WX("FunnelWeb Modifications\n");
 WX("-----------------------\n");
 WX("FunnelWeb is distributed under a GNU license, and you are free to modify the\n");
 WX("source code and distribute modified copies (see the help message LICENSE).\n");
 WX("However, there are good reasons why you should be careful about this:\n");
 WX("\n");
 WX("   1) If you distribute modified versions of FunnelWeb, you run the risk of\n");
 WX("   creating a version that will diverge from the \"official\" version of\n");
 WX("   FunnelWeb which I intend to maintain.\n");
 WX("\n");
 WX("   2) If you release a version of FunnelWeb with a changed input language,\n");
 WX("   users of your modified version will create source files that will no\n");
 WX("   longer work on other versions of FunnelWeb. This will destroy\n");
 WX("   interoperability.\n");
 WX("\n");
 WX("For more information on these issues, see the FunnelWeb Developer Manual at:\n");
 WX("   http://www.ross.net/funnelweb/developer/\n");
 WX("\n");
 WX("Ross Williams (ross@ross.net), 8 May 1999.\n");
}

/******************************************************************************/

LOCAL bool prefeq P_((char *,char *));
LOCAL bool prefeq (p_pref,p_target)
/* Returns TRUE iff string p_pref is a case insensitive prefix of p_target.   */
char *p_pref;
char *p_target;
{
 char *p,*q;

 if (strlen(p_pref) > strlen(p_target))
    return FALSE;

 p=p_pref;
 q=p_target;
 while (*p != EOS)
   {
    if (toupper(*p) != toupper(*q)) return FALSE;
    p++;
    q++;
   }
 return TRUE;
}

/******************************************************************************/

EXPORT uword hel_num (p_name)
char *p_name;
{
 uword matches = 0;
 uword messnum;

 /* We want to be fairly lenient on the user here as the user is trying to    */
 /* obtain help and will probably get annoyed and give up if it doesn't work, */
 /* so we perform case insensitive prefix matching.  However, we don't want   */
 /* to match if the user inputs a prefix that matches two message names. This */
 /* means we can't just return when we find a match; we have to see if there  */
 /* are any others as well.                                                   */

 if (prefeq(p_name,"MENU"         )) {messnum=HL_MEN; matches++;}
 if (prefeq(p_name,"INTRODUCTION" )) {messnum=HL_INT; matches++;}
 if (prefeq(p_name,"OPTIONS"      )) {messnum=HL_OPT; matches++;}
 if (prefeq(p_name,"DEFOPTIONS"   )) {messnum=HL_DOP; matches++;}
 if (prefeq(p_name,"COMMANDS"     )) {messnum=HL_COM; matches++;}
 if (prefeq(p_name,"DOCUMENTATION")) {messnum=HL_DOC; matches++;}
 if (prefeq(p_name,"LICENSE"      )) {messnum=HL_GNU; matches++;}
 if (prefeq(p_name,"COPYRIGHT"    )) {messnum=HL_COP; matches++;}
 if (prefeq(p_name,"NOWARRANTY"   )) {messnum=HL_NOW; matches++;}
 if (prefeq(p_name,"DISTRIBUTION" )) {messnum=HL_DIS; matches++;}
 if (prefeq(p_name,"ACKNOWLEDGE"  )) {messnum=HL_ACK; matches++;}
 if (prefeq(p_name,"VERSIONS"     )) {messnum=HL_VER; matches++;}
 if (prefeq(p_name,"MODIFICATION" )) {messnum=HL_MOD; matches++;}

 if (matches != 1) return HL_ERR;

 return messnum;
}

/******************************************************************************/

EXPORT void hel_wri (p_outf,messno)
void (*p_outf) P_((char *));
uword messno;
{
 as_cold(     1 <= messno, "hel_wri: Message number is zero.");
 as_cold(messno <= HL_MAX, "hel_wri: Message number is greater than HL_MAX.");

 /* Set the global output function pointer. */
 pf=p_outf;

 switch(messno)
   {
    case HL_MEN: hel_men(); break;
    case HL_INT: hel_int(); break;
    case HL_OPT: hel_opt(); break;
    case HL_DOP: hel_dop(); break;
    case HL_COM: hel_com(); break;
    case HL_DOC: hel_doc(); break;
    case HL_GNU: hel_gnu(p_outf); break; /* Calling another module. */
    case HL_COP: hel_cop(); break;
    case HL_NOW: hel_now(); break;
    case HL_DIS: hel_dis(); break;
    case HL_ACK: hel_ack(); break;
    case HL_VER: hel_ver(); break;
    case HL_MOD: hel_mod(); break;
    default    : as_bomb("hel_wri: switch defaulted.");
   }
}

/******************************************************************************/
/*                               End of HELP.C                                */
/******************************************************************************/
