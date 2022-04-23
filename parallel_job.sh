#!/bin/bash

make

echo 'graf_20_17:'
mpirun -np 4 ./app --source ./IN/graf_20_17.txt --out ./OUT/graf_20_17.txt

echo 'graf_30_10:'
mpirun -np 4 ./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10.txt

echo 'graf_30_20:'
mpirun -np 4 ./app --source ./IN/graf_30_20.txt --out ./OUT/graf_30_20.txt
