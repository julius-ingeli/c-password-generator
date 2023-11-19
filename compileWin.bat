@echo off
gcc -o pwgen pwgen.c -lssl -lcrypto
@echo Compilation completed.
