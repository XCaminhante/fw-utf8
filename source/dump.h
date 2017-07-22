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
/*                                     DUMP.H                                 */
/******************************************************************************/
/*                                                                            */
/* This package contains functions that dump text representations of          */
/* FunnelWeb data structures. Each function accepts a wf stream on which it   */
/* writes its text representation. These functions are used in testing and    */
/* debugging only and are not used ordinarily in the program.                 */
/*                                                                            */
/******************************************************************************/

#include "style.h"

#include "clock.h"
#include "writfile.h"

/******************************************************************************/

EXPORT void dm_mem P_((p_wf_t,char *,ulong));
/* Writes a hex and ascii dump of the specified block of memory to the        */
/* specified stream.                                                          */

EXPORT void dm_lnls P_((p_wf_t));
/* Dumps a text representation of the global line list to the given stream.   */

EXPORT void dm_tkls P_((p_wf_t));
/* Dumps a text representation of the global token list to the given stream.  */

EXPORT void dm_matb P_((p_wf_t));
/* Dumps a text representation of the macro table to the given stream.        */

EXPORT void dm_dcls P_((p_wf_t));
/* Dumps a text representation of the document list to the given stream.      */

EXPORT void dm_times P_((p_wf_t,p_ck_t,p_ck_t,p_ck_t,p_ck_t,
                         p_ck_t,p_ck_t,p_ck_t,p_ck_t,p_ck_t));
/* Dumps a text representation of the execution times to the given stream.    */

/******************************************************************************/
/*                                 End of DUMP.H                              */
/******************************************************************************/
