#!/bin/bash

# Will compile and launch the program

# Usage:
# First time, do: `chmod +x compile.sh`
# Then just do: `./compile.sh YOUR_FILE_NAME YOUR_ARGUMENT_IF_ANY`
# You can use the file name with and without the extension

NAME_WITHOUT_EXT="${1%.*}"
ARGV1="$2"

gcc "$NAME_WITHOUT_EXT.c" -o "$NAME_WITHOUT_EXT"
"./$NAME_WITHOUT_EXT" "$ARGV1"
rm "$NAME_WITHOUT_EXT"
