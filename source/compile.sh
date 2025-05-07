#!/bin/bash
cd "$(dirname "$0")"
SRC=( $(find ./ -name '*.c') )
OBJ=( $(for s in "${SRC[@]}"; do echo "${s/.c/.o}"; done) )

for i in ${!SRC[@]}; do
  gcc "${SRC[$i]}" -c -o "${OBJ[$i]}" &
done
wait
gcc "${OBJ[@]}" -o ./fw
