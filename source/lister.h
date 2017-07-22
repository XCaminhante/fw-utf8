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
/*                                   LISTER.H                                 */
/******************************************************************************/

#include "style.h"

#include "data.h"

/******************************************************************************/

EXPORT void lr_ini P_((void));
/* Initialize the lister. Calling this function destroys all the lister       */
/* package's old internal data structures and sets them to a well-defined     */
/* initial state (empty) and prepares the lister for the incoming messages.   */
/* This function may be called at any time and many times.                    */

EXPORT void lr_mes P_((ps_t *,char *));
EXPORT void lr_war P_((ps_t *,char *));
EXPORT void lr_err P_((ps_t *,char *));
EXPORT void lr_sev P_((ps_t *,char *));
/* The functions above allow the user to record four different kinds of       */
/* messages and to specify exactly where in the listing each message is to    */
/* appear.                                                                    */

EXPORT void lr_gen P_((p_wf_t,uword));
/* Merges the global structure line_list with the message table stored by the */
/* lister package and writes the resultant listing to the p_wf_t stream.      */
/* The second parameter is the number of lines of context around each         */
/* diagnostic. The lister does not write the entire input file out. It only   */
/* writes input lines near a diagnostic. The context argument specifies the   */
/* number of lines that should be written around each diagnostic.             */
/* Note: A context of 100 is special and means that no lines should be        */
/*       omitted in between diagnostics.                                      */

/******************************************************************************/
/*                               End of LISTER.H                              */
/******************************************************************************/

