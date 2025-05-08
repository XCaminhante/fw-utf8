#!/bin/bash

#CFLAGS=""
#SRC=( $(find . -name '*.c') )
SRC=(
./analyse.c
./as.c
./clock.c
./command.c
./data.c
./dump.c
./help.c
./help_gnu.c
./list.c
./lister.c
./machin.c
./main.c
./mapper.c
./memory.c
./misc.c
./option.c
./parser.c
./scanner.c
./section.c
./table.c
./tangle.c
./texhead.c
./weaveh.c
./weavet.c
./writfile.c
)
OBJ=( $(for s in "${SRC[@]}"; do echo "${s/.c/.o}"; done) )

redo-ifchange "${OBJ[@]}"
gcc "${OBJ[@]}" -o "$3"
