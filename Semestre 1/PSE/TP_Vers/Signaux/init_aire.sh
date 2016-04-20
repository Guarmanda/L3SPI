#!/bin/bash


../Vers/init_fich_ver ver.bin
../Terrain/init_fich_terrain terrain.bin $2 $3

./aire ../Terrain/terrain.bin ../Vers/ver.bin $1
