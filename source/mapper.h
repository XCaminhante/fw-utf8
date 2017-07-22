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
/*                                  MAPPER.H                                  */
/******************************************************************************/
/*                                                                            */
/* The mapper is the first of FunnelWeb's four front end processors: (mapper, */
/* scanner, parser, analyser). The sole task of the mapper is, given the      */
/* name of a file, to create an image of that file in memory. This approach   */
/* is not wasteful of memory at all because FunnelWeb requires random access  */
/* to each input file at all times anyway so it can scramble the text around. */
/*                                                                            */
/******************************************************************************/

#include "style.h"

/******************************************************************************/

EXPORT char *map_file P_((char *,char **,ulong *));
/* Allocates a block of memory and places a Unix text stream representation   */
/* (with EOL marking end of line and no character marking end of file) of the */
/* file 'p_name' in the block of memory. Returns a pointer to the address and */
/* len of the file in the mem block in the parameters (pp_mem and p_length).  */
/* Returns NULL upon success or a pointer to an error message string upon     */
/* failure. Note: Parameters are: p_name, pp_mem, p_length.                   */
/* Note: Allocates enough memory so that there is guaranteed to be at least   */
/* two extra bytes of spare memory at the end of the mapped file. The         */
/* scanner uses this space to put EOL and EOF characters.                     */
/* Note: The mapper grabs its memory using mm_temp, so it can be recycled     */
/* as part of a call to mm_zapt.                                              */

/******************************************************************************/
/*                               End of MAPPER.H                              */
/******************************************************************************/
