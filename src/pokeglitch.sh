#!/usr/bin/env bash

# compiling the proj 
gcc -Wall *.c -o main

# getting the old save
cp ../rom/pokemon_red.sav .

# applying new data to the save
./main pokemon_red.sav

# copying the modified save to rom dir
cp pokemon_red.sav ../rom/pokemon_red.sav

# initializing the emulator
mgba-qt ../rom/pokemon_red.gb
