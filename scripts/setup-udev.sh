#!/bin/bash

NAME=ch32v00x.setup-udev

function print_help() {
    echo "Usage: $NAME [-h|--help]"
    echo "Outputs a script to setup udev rules. "
    echo ""
    echo "The only option avaliable is -h (or the equivalent --help)"
    echo "which displays this output."
    echo ""
    echo "As a rule, please always review the script you pipe to an sh."
    echo "Once reviewed, the script can be executed with a command like:"
    echo "  $NAME | sudo sh -"
}

while [ "$1" != "$EOL" ]; do
    opt="$1"; shift
    case $opt in
     -h  | --help)
        print_help
        exit 0
        ;;
     *           )
        echo "Unknown option $opt"
        echo ""
        print_help
        exit 1
        ;;
    esac
done

DIR="$( dirname -- "${BASH_SOURCE[0]}"; )"

cat <<EOF
cat <<RULE > /etc/udev/rules.d/50-wch.rules
SUBSYSTEM=="usb", ATTR{idVendor}="1a86", ATTR{idProduct}=="8010", GROUP="plugdev"

SUBSYSTEM=="usb", ATTR{idVendor}="4348", ATTR{idProduct}=="55e0", GROUP="plugdev"
RULE

udevadm control --reload-rules && udevadm trigger
EOF
