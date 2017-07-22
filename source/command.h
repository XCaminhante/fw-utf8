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
/*                                   COMMAND.H                                */
/******************************************************************************/
/*                                                                            */
/* The command package is the mover and shaker of FunnelWeb. It exports a     */
/* single function, whose argument is the command line given to FunnelWeb     */
/* when it is invoked at the operating system level. The command package      */
/* routine examines the command line and executes it, possibly invoking a     */
/* mini-interpreter or calling the different component of FunnelWeb in turn   */
/* (e.g. the parser).                                                         */
/*                                                                            */
/******************************************************************************/

#include "style.h"
#include "machin.h"

/******************************************************************************/

void command P_((p_cl_t));
/* Executes the command line which is passed as the argument. */

/******************************************************************************/
/*                               End of COMMAND.H                             */
/******************************************************************************/
