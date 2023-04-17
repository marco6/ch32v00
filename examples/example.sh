#!/bin/bash

function print_help() {
    echo "Usage: $0 [OPTION]... EXAMPLE"
    echo "Prints the source of EXAMPLE from the original ch32V00x SDK, or compiles"
    echo "it if requested."
    echo ""
    echo "  -c                           Compiles the source instead of just printing"
    echo "                               the source. The output name is 'a.out' by"
    echo "                               default."
    echo "  -o <file>                    Save to <file> instead of using stdout. If"
    echo "                               compilation is requested (-c) <file> will be"
    echo "                               the name of the compilation output."
    echo "  -h, --help                   Display this help and exit."
    echo ""
    echo "Few environmental values can be used to influence how the compiler is executed."
    echo ""
    echo "    PREFIX  can be used to specify a different compiler chain prefix."
    echo "            The default is 'ch32v00x.' ."
    echo "    CFLAGS  can be used to specify additional compilation flags to the compiler."
    echo ""
    echo "All examples here come with the following copyright notice, which have been"
    echo "stripped from the original source:"
    echo ""
    echo "    Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd."
    echo "    "
    echo "    Attention: This software (modified or not) and binary are used for "
    echo "    microcontroller manufactured by Nanjing Qinheng Microelectronics."
    echo ""
    echo "Most of them have been modified by Marco Manino to take into account the "
    echo "structural changes applied to the original SDK to make it usable within"
    echo "this snap. Please note that the SDK will evolve indipendently from and in"
    echo "a probably different direction than the original one."
    echo ""
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
        flags="$CFLAGS -Os -Wall -pedantic -flto --specs=ch32v00x.specs"

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
