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
/*                                   HELP.H                                   */
/******************************************************************************/
/*                                                                            */
/* HELP PACKAGE                                                               */
/* ============                                                               */
/* As I came closer and closer to completing the release version of           */
/* FunnelWeb, I noticed that the online help was a bit of a mess. I had       */
/* random commands and command line options here and there to provide bits of */
/* information. After a close look and some thought, I decided to centralize  */
/* all of FunnelWeb's help messages into one module, and provide a clean and  */
/* consistent interface to the help messages, both in the command line, and   */
/* in interactive mode.                                                       */
/*                                                                            */
/* The result is that all of the help messages have been  moved to            */
/* this module. Each help message has a name consisting of a string. One      */
/* particular message has the name "MENU" and is the root help message (the   */
/* "menu message"). It contains a list of all the help messages available and */
/* their names.                                                               */
/*                                                                            */
/* The command line connects to help by providing a single command line       */
/* option called +Hx which has the effect of displaying the help message      */
/* called x. The default is -Hmenu. The "-" means that help is not invoked by */
/* default, but that if the user specifies +H, the menu message will be       */
/* printed. If the user specifies (say) +Hsloth, message SLOTH will be        */
/* displayed. The menu message is printed if the user invokes FunnelWeb with  */
/* no actions. The +H option is classified as an action option.               */
/*                                                                            */
/* Interactive mode connects to help through the HELP command. In the spirit  */
/* of the command line interface, if no argument is given, the menu message   */
/* is displayed. If an argument is given, the specified message is written    */
/* out.                                                                       */
/*                                                                            */
/* This module contributes two things to this process:                        */
/*    1) Provides a mapping from message names to messages.                   */
/*    2) Acts as a repository for the messages themselves.                    */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_HELP
#define DONE_HELP

/******************************************************************************/

#include "style.h"

/******************************************************************************/

/* Place a bound on help name length, and define an array type to hold them.  */
#define HL_NMLEN 20
typedef char hn_t[HL_NMLEN+1];

/******************************************************************************/

/* Each of the messages has a unique symbol and number. The reason for        */
/* defining these symbols instead of just using the message names in the code */
/* is that doing it this way allows us to change the exact message names      */
/* without having to track down all their occurences in the code, or getting  */
/* nasty surprises later down the track at run time (the compiler will tell   */
/* you in a call containing HL_SLT that the symbol doesn't exist, but it      */
/* won't complain about a string argument that just happens not to be the     */
/* name of a message anymore).                                                */

/* HL_ERR is the non-existent message. */
#define HL_ERR 0

/* HL_MEN - Help messages.             */
/* HL_INT - Introduction to FunnelWeb. */
/* HL_OPT - Command line options.      */
/* HL_DOP - Option defaults.           */
/* HL_COM - Interactive commands.      */
/* HL_DOC - Documentation.             */
/* HL_LIC - The GNU License.           */
/* HL_COP - Copyright notice.          */
/* HL_NOW - No Warranty notice.        */
/* HL_DIS - Distribution notice.       */
/* HL_ACK - Acknowledgements.          */
/* HL_VER - Versions.                  */
/* HL_MOD - Modifications.             */
#define HL_MEN  1
#define HL_INT  2
#define HL_OPT  3
#define HL_DOP  4
#define HL_COM  5
#define HL_DOC  6
#define HL_GNU  7
#define HL_COP  8
#define HL_NOW  9
#define HL_DIS 10
#define HL_ACK 11
#define HL_VER 12
#define HL_MOD 13

/* The following symbol does not represent a message. It is the number of     */
/* messages. This is useful for range checking and possibly in for loops.     */
#define HL_MAX 13

/******************************************************************************/

EXPORT uword hel_num P_((char *));
/* Accepts a character string that is supposed to be the name of a message    */
/* and returns the number of the message, or HL_ERR if the string does not    */
/* correspond to any defined message. A match will occur if the argument      */
/* string is the same (with case independent matching) as the prefix (of      */
/* corresponding length) of exactly one message name.                         */

EXPORT void hel_wri P_((void (*)(char *),uword));
/* Accepts a message number and writes the message using the function         */
/* provided in the first argument. Bombs the program if the message number in */
/* the second argument is not in the range [1,HL_MAX].                        */

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                               End of HELP.H                                */
/******************************************************************************/
