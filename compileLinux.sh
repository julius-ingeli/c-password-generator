#!/bin/bash

mytitle="Compilation"
echo -e '\033]2; '$mytitle'\007'
echo -e '\033[33mCompiling...\033[0m'
gcc pwgen.c -o pwgen
