#!/bin/bash

cd "$(dirname "$0")/.." # this moves to the folder tasosh (root of project)

mkdir -p bin

if ! make tasosh; then
    echo "ERROR USING MAKEFILE"
    make clean
    exit 1
fi

mv ./tasosh bin
make clean

mkdir -p ~/.config/tasosh/
mkdir -p ~/.config/tasosh/plugins/
touch ~/.config/tasosh/logs.log
cp ./etc/tasosh.conf ~/.config/tasosh/tasosh.conf


if sudo -v 2>/dev/null; then
    echo "You have sudo privileges."
    sudo cp bin/tasosh /usr/bin
    if [ "$1" == "-dbg" ]; then
        tasosh
        echo "tasosh returned with code $?"
    fi
else
    echo "You do not have sudo privileges."
    if [ "$1" == "-dbg" ]; then
        bin/tasosh
        echo "tasosh returned with code $?"
    fi
fi
