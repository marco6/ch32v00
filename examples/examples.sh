#!/bin/bash

function print_help() {
    echo "THIS IS THE HELP"
    exit 0
}

PREFIX=${PREFIX:-ch32v00x.}
DIR="$( dirname -- "${BASH_SOURCE[0]}"; )"

name=
output=
compile=

while [ "$1" != "$EOL" ]; do
    opt="$1"; shift
    case $opt in
        -c          ) compile="yes";;
        -o          ) output=$1; shift;;
        -h  | --help) print_help;;
        *           ) name=$opt;;
    esac
done

if [ -z "$name" ]
then
    echo "missing example name"
    exit 1
fi

if [ -f "${DIR}/${name}.c" ]
then
    if [ "$compile" = "yes" ]
    then
        echo Compiling example $name...
        flags="-Os -flto --specs=ch32v00x.specs"

        if [ -z "$output" ]
        then
            ${PREFIX}gcc $flags "$DIR/$name.c"
        else
            ${PREFIX}gcc $flags "$DIR/$name.c" -o "$output"
        fi
    else
        if [ -z "$output" ]
        then
            cat "${DIR}/${name}.c"
        else
            cp "${DIR}/${name}.c" "$output"
        fi
    fi
else
    echo no example named $name >&2
    exit 1
fi
