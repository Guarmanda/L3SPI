#!/bin/bash

if( test $# -ne 1 ) then 
    echo "Usage: $0 <taille>"
    exit 1
fi 

taille=$1


rm ../Fichiers/mer.bin
touch ../Fichiers/mer.bin

rm ../Fichiers/amiral.bin
touch ../Fichiers/amiral.bin

./amiral ../Fichiers/mer.bin ../Fichiers/bateau.bin ../Fichiers/amiral.bin $taille