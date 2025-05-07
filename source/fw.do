#!/bin/bash
#CFLAGS=""
SRC=( $(find . -name '*.c') )
OBJ=( $(for s in "${SRC[@]}"; do echo "${s/.c/.o}"; done) )
redo-ifchange "${OBJ[@]}"
gcc "${OBJ[@]}" -o "$3"
