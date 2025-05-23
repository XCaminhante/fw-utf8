/**
FUNNNELWEB COPYRIGHT
====================
FunnelWeb is a literate-programming macro preprocessor.
The original FunnelWeb web is at <http://www.ross.net/funnelweb/>.
This fork resides at <https://github.com/XCaminhante/fw-utf8>.

Copyright (c) Ross N. Williams 1992. All rights reserved.
Copyright (c) X Caminhante 2025. All rights reserved.

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <https://www.gnu.org/licenses>.

Linking funnelweb statically or dynamically with other modules is making a combined work based on funnelweb. Thus, the terms and conditions of the GNU General Public License cover the whole combination.

Section 2a of the version 2 license requires that all changes to this file be recorded prominently in this file. Please record all changes here.

Programmers:
  RNW  Ross N. Williams (ross@ross.net)
  XCA  X Caminhante (xcaminhante@i2pmail.org)

Changes:
  07-May-1992  RNW  Program prepared for release under GNU GPL V2.
  08-May-1999  RNW  Added code to set creator/type of output files on Mac.
  07-May-2025  XCA  Renewed GPL preamble, removed legacy I don't need/understand, also I heard you like FunnelWeb, so I'll put FunnelWeb on your FunnelWeb!
**/
#include "style.h"
#include "as.h"
#include "command.h"
#include "data.h"
#include "machin.h"
#include "memory.h"
int main (int argc, char** argv) {
  char  *p_comline;
  ulong sum_all;
  sum_fat =sum_sev=sum_err=sum_war =0;
  p_comline = (char*) mm_perm( (size_t) COMLINE_MAX+1 );
  getcline(argc, argv, p_comline);
  command(p_comline);
  sum_all = sum_war+sum_err+sum_sev+sum_fat;
  if (sum_all>0) { return EXIT_FAILURE; }
  return EXIT_SUCCESS;
}
