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
   15-May-1999  RNW  Modified STDC definition for Digital Unix.
   15-May-1999  RNW  Added support for FreeBSD.

##############################################################################*/


/******************************************************************************/
/*                                   ENVIRON.H                                */
/******************************************************************************/
/*                                                                            */
/* WARNING: DO NOT ADD ANY PROGRAM-DEPENDENT DEFINITIONS.                     */
/*                                                                            */
/* This header file environ.h contains definitions and objects whose values   */
/* depends directly on the compilation and execution environment, but are     */
/* otherwise independent of any particular computer program.                  */
/*                                                                            */
/* This is one of two machine-dependent, program-independent modules. The     */
/* other module is machin (machin.h,machin.c). This "environ" module contains */
/* definitions and objects that are considered essential. The "machin" module */
/* contains less essential definitions. Motivation for the division came from */
/* the fact that style.h (used by almost every module) includes environ.h     */
/* (this file), and from the need for the stuff in style.h by some            */
/* environment-dependent definitions.                                         */
/*                                                                            */
/* There seems to be two ways to organize a module such as this one. The      */
/* first is to have a different version of this module for each target        */
/* environment. The second is to have a single file that uses #defines and    */
/* #ifs to select between code for each target environment. I have chosen the */
/* latter method as this allows many different environments to share the same */
/* definitions.                                                               */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_ENVIRON
#define DONE_ENVIRON

/******************************************************************************/

/* Detecting The Environment                                                  */
/* -------------------------                                                  */
#define OS_MAC    0  /* Macintosh        */
#define OS_DOS    0  /* MS-DOS           */
#define OS_VMS    0  /* OpenVMS          */
#define OS_W32    0  /* Win32            */
#define OS_UNX    0  /* Unix             */
#define    OS_HPU 0  /*    HP/UX         */
#define    OS_OSF 0  /*    Digital Unix  */
#define    OS_SUN 0  /*    SunOS/Solaris */
#define    OS_IRX 0  /*    IRIX          */
#define    OS_B86 0  /*    BSDOS         */
#define    OS_L86 0  /*    Linux         */
#define    OS_AIX 0  /*    AIX           */
#define    OS_FBD 0  /*    FreeBSD       */


#ifdef  THINK_C      
#undef  OS_MAC 
#define  OS_MAC  1
#undef  OS_MAC 
#define  OS_MAC  1
#endif


#ifdef  __MWERKS__   
#undef  OS_MAC 
#define  OS_MAC  1
#undef  OS_MAC 
#define  OS_MAC  1
#endif


#ifdef  MSDOS        
#undef  OS_DOS 
#define  OS_DOS  1
#undef  OS_DOS 
#define  OS_DOS  1
#endif


#ifdef  __DOS__      
#undef  OS_DOS 
#define  OS_DOS  1
#undef  OS_DOS 
#define  OS_DOS  1
#endif


#ifdef  __BORLANDC__ 
#undef  OS_DOS 
#define  OS_DOS  1
#undef  OS_DOS 
#define  OS_DOS  1
#endif


#ifdef  VMS          
#undef  OS_VMS 
#define  OS_VMS  1
#undef  OS_VMS 
#define  OS_VMS  1
#endif


#ifdef  _WIN32       
#undef  OS_W32 
#define  OS_W32  1
#undef  OS_W32 
#define  OS_W32  1
#endif


#ifdef  __hpux       
#undef  OS_UNX 
#define  OS_UNX  1
#undef  OS_HPU 
#define  OS_HPU  1
#endif


#ifdef  __osf__      
#undef  OS_UNX 
#define  OS_UNX  1
#undef  OS_OSF 
#define  OS_OSF  1
#endif


#ifdef  sun          
#undef  OS_UNX 
#define  OS_UNX  1
#undef  OS_SUN 
#define  OS_SUN  1
#endif


#ifdef  __ultrix     
#undef  OS_UNX 
#define  OS_UNX  1
#undef  OS_ULT 
#define  OS_ULT  1
#endif


#ifdef  __sgi        
#undef  OS_UNX 
#define  OS_UNX  1
#undef  OS_IRX 
#define  OS_IRX  1
#endif


#ifdef  __386BSD__   
#undef  OS_UNX 
#define  OS_UNX  1
#undef  OS_B86 
#define  OS_B86  1
#endif


#ifdef  __linux__    
#undef  OS_UNX 
#define  OS_UNX  1
#undef  OS_L86 
#define  OS_L86  1
#endif


#ifdef  _AIX         
#undef  OS_UNX 
#define  OS_UNX  1
#undef  OS_AIX 
#define  OS_AIX  1
#endif

#ifdef  __FreeBSD__         
#undef  OS_UNX 
#define  OS_UNX  1
#undef  OS_FBD 
#define  OS_FBD  1
#endif

#if (OS_MAC + OS_UNX + OS_VMS + OS_DOS + OS_W32) == 0
   #error Error: No operating system class has been selected.
#endif

#if (OS_MAC + OS_UNX + OS_VMS + OS_DOS + OS_W32) > 1
   #error Error: More than one operating system class has been selected.
#endif

#if OS_UNX
#define OS_UNXSUM1 (OS_HPU+OS_OSF+OS_SUN+OS_SOL+OS_ULT)
#define OS_UNXSUM2 (OS_IRX+OS_B86+OS_L86+OS_AIX+OS_FBD)
#if ((OS_UNXSUM1+OS_UNXSUM2) != 1)
   #error Error: Exactly one Unix operating system must be chosen.
#endif
#endif

#define BEGIN_OS
#define END_OS

/******************************************************************************/

/* Establish Presence or Absence of __STDC__                                  */
/* -----------------------------------------                                  */
/* The __STDC__ symbol is very useful for determining if the compiler is      */
/* ANSI. However, some "nearly ANSI" compilers don't set this symbol, and     */
/* experience shows that things turn out better if it is set.                 */
/* This section decides if __STDC__ should be defined.                        */

/* The Macintosh THINK C compiler seems to be ANSI standard but, strangely    */
/* does not define the standard preprocessor symbol __STDC__ that indicates   */
/* this. Instead it defines THINK_C. Here, we execute the link manually.      */
/* For more information see the THINK C User's Manual, Chapter 57: "Language  */
/* Reference", Section 12.10, p.442.                                          */
#if OS_VMS || OS_OSF
#define __STDC__ 1
#endif

#ifdef __VISUALC__
#define __STDC__ 1
#endif

#ifdef __MWERKS__
#undef __STDC__
#define __STDC__ 1
#endif

/******************************************************************************/

/* Switch From Definedness to Boolean Symbols                                 */
/* ------------------------------------------                                 */
/* Use of the definedness of a preprocessor symbol to detect a condition is   */
/* convenient if it is desired that only one condition be tested at a time.   */
/* However, if we want to OR conditions, it is more convenient to use defined */
/* symbols that are either 0 or 1. This section contains ifdefs that do this. */

#ifdef __STDC__
#define STDC 1
#else
#define STDC 0
#endif

/* Note: If THINK_C is predefined, it is predefined to be 1. */
#ifndef THINK_C
#define THINK_C 0
#endif

/******************************************************************************/

/* Void                                                                       */
/* ----                                                                       */
/* Define void if necessary and define pointer to void.                       */
/* This idea from the book "Portable C", p.41.                                */
/* If necessary, add a boolean condition to cover your environment.           */
/* Note: The "| OS_SUN" is a last minute desperate hack.                      */
#if STDC || OS_SUN || OS_AIX
#define p_void void *
#else
typedef int     void;
#define p_void char *
#endif

/* The following function is here solely to act as a first tripping point for */
/* environments with no "void" so that the users trying to port this code     */
/* will look here first instead of starting to delete voids in the program.   */
extern void test_void();

/******************************************************************************/

/* Const                                                                      */
/* -----                                                                      */
/* It's useful to be able to specify that certain objects are constants.      */
/* Unfortunately, the "const" construct is only available in ANSI C and so we */
/* have to have a macro so as to cope with non-ANSI compilers.                */
/* Note: THINK-C is nearly ANSI, but does not support "const".                */
#if STDC & !THINK_C
#define CONST const
#else
#define CONST
#endif

/******************************************************************************/

/* Prototypes                                                                 */
/* ----------                                                                 */
/* Define a macro to wrap around prototype parameter lists so as to support   */
/* compilers with and without prototypes.                                     */
/* This idea came from the book "Portable C", S3.1, p.32.                     */
#if STDC
#define P_(A) A
#else
#define P_(A) ()
#endif

/******************************************************************************/

/* Structure Assignments                                                      */
/* ---------------------                                                      */
/* Structure assignments are not supported on some of the older compilers and */
/* so we use a macro to perform such operations.                              */
/* This idea came from the book "Portable C", S8.2.2, p.184.                  */
#if STDC
#define ASSIGN(a,b) ((a)=(b))
#else
#define ASSIGN(a,b) (memcpy((char *)&(a),(char *)&(b),sizeof(a)))
#endif

/******************************************************************************/

/* VMS EXIT STATUS */
/* --------------- */
/* The VAX C compiler I used doesn't seem to be ANSI. This means that the    */
/* exit symbols aren't set up properly. Furthermore, the sensible defaults   */
/* in the style.h file don't work for VMS. The upshot is that we have to do  */
/* a special case. Note: The top bit set in a VMS exit status means suppress */
/* diagnostic message. Even status means failure. Odd means success.         */
#if OS_VMS
#undef  EXIT_SUCCESS
#undef  EXIT_FAILURE
#define EXIT_SUCCESS 1
#define EXIT_FAILURE (0x10000002)
#endif

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                                End of ENVIRON.H                            */
/******************************************************************************/
