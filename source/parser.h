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
/*                                    PARSER.H                                */
/******************************************************************************/
/*                                                                            */
/* The FunnelWeb parser parses the tokens in the global token list and        */
/* constructs a macro table and a document list. These two data structures    */
/* give structured views of the input document which are used later by tangle */
/* and weave. If the parser detects any errors it sends them to the lister    */
/* package. If any errors have occurred, the output of the parser should not  */
/* be used.                                                                   */
/*                                                                            */
/* IN : token_list    - List of tokens to be parsed.                          */
/* OUT: macro_table   - Table of macros parsed.                               */
/*      file_table    - Table indicating which macros are attached to files.  */
/*      document_list - List giving a structured view of the document.        */
/*      Also sends diagnostic messages to the lister.                         */
/*                                                                            */
/******************************************************************************/

#include "style.h"

/******************************************************************************/

EXPORT void parser P_((void));

/******************************************************************************/
/*                                End of PARSER.H                             */
/******************************************************************************/
