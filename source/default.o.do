CFILE="$1.c"
DFILE="$1.d"

gcc -MD -MF "$DFILE" -c -o "$3" "$CFILE"
redo-ifchange "$DFILE"
cat <<EOF | sh
redo-ifchange $(sed -r 's_^.+--redoing: __' "$DFILE")
EOF
