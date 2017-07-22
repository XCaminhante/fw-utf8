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
   08-May-1999  RNW  Added code to set creator/type of output files on Mac.

##############################################################################*/


/******************************************************************************/
/*                                     MAIN.C                                 */
/******************************************************************************/

#include "style.h"

#include "as.h"
#include "command.h"
#include "data.h"
#include "machin.h"
#include "memory.h"

/* Allows us to set the creator and type of output files on Macintosh. */
#if OS_MAC
extern long _ftype;
extern long _fcreator;
#endif

/******************************************************************************/

/* The following variables should really be local to main. However, some      */
/* compilers have a problem with this and so it has been declared here.       */
LOCVAR char  *p_comline;
LOCVAR ulong sum_all;

/******************************************************************************/

LOCAL void minimain P_((int,char **));
LOCAL void minimain(argc,argv)
/* Some compilers generate buggy code for main() and so this minimain         */
/* function has been created to take the heat off main().                     */
int    argc;
char **argv;
{
 /* 08-May-1999 RNW: On the Macintosh, it's convenient if FunnelWeb output */
 /* files can be clicked on to invoke a text editor. This can be done by   */
 /* setting the creator and type of output files. CodeWarrior makes this   */
 /* very easy. All we have to do is set some global variables and from     */
 /* that point on, all output files will have the specified creator/type.  */
 /* I originally set the creator to TeachText (ttxt), but soon discovered  */
 /* that TeachText can't open files greater than 32K. I looked around for  */
 /* another text application that Apple provides as standard, but couldn't */
 /* find one. So I chose BBEdit, whose creator is "R*ch".                  */
#if OS_MAC
 _fcreator = 'R*ch';
 _ftype    = 'TEXT';
#endif

 /* The principal concern of this main() function is to execute FunnelWeb and */
 /* to ensure that the correct return status is returned to the OS. So it     */
 /* seems appropriate to zero all the global diagnostic counters here.        */
 sum_fat=sum_sev=sum_err=sum_war=0;

 /* Some compilers place a low limit on the total amount of statics. So we    */
 /* have to allocate space for a command line.                                */
 p_comline=(char *) mm_perm((size_t) COMLINE_MAX+1);

 /* Obtaining the command line is highly machine specific and so it has been  */
 /* delegated to a function in the non-portable "machin". Just in case argc   */
 /* and argv are to be used, we hand them in too. The result of all this is a */
 /* standard FunnelWeb command line string in the variable 'comline'.         */
 getcline(argc,argv,p_comline);

 /* Execute the command line. */
 command(p_comline);

 /* Exit to the operating system with an appropriate status code. */
 sum_all=sum_war+sum_err+sum_sev+sum_fat;
 if (sum_all>0)
    exit(EXIT_FAILURE);
 else
    exit(EXIT_SUCCESS);
}

/******************************************************************************/

int main(argc,argv)
int   argc;
char *argv[];
{
 /* We don't put anything into the function main() because some compilers     */
 /* generate incorrect code for main, especially with local variables.        */
 minimain(argc,argv);

 /* Keep GCC warnings happy. */
 as_bomb("Main program dropped through.");
 return 0;
}

/******************************************************************************/
/*                                End of MAIN.C                               */
/******************************************************************************/
