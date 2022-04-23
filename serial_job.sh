#!/bin/bash

make
 
 echo 'graf_20_17_t2:'
./app --source ./IN/graf_20_17.txt --out ./OUT/graf_20_17_t2.txt --threads 2

echo 'graf_30_10_t2:'
./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t2.txt --threads 2

echo 'graf_30_20_t2:'
./app --source ./IN/graf_30_20.txt --out ./OUT/graf_30_20_t2.txt --threads 2


echo 'graf_20_17_t4:'
./app --source ./IN/graf_20_17.txt --out ./OUT/graf_20_17_t4.txt --threads 4

echo 'graf_30_10_t4:'
./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t4.txt --threads 4

echo 'graf_30_20_t4:'
./app --source ./IN/graf_30_20.txt --out ./OUT/graf_30_20_t4.txt --threads 4


echo 'graf_20_17_t8:'
./app --source ./IN/graf_20_17.txt --out ./OUT/graf_20_17_t8.txt --threads 8

echo 'graf_30_10_t8:'
./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t8.txt --threads 8

echo 'graf_30_20_t8:'
./app --source ./IN/graf_30_20.txt --out ./OUT/graf_30_20_t8.txt --threads 8


echo 'graf_20_17_t16:'
./app --source ./IN/graf_20_17.txt --out ./OUT/graf_20_17_t16.txt --threads 16

echo 'graf_30_10_t16:'
./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t16.txt --threads 16

echo 'graf_30_20_t16:'
./app --source ./IN/graf_30_20.txt --out ./OUT/graf_30_20_t16.txt --threads 16


echo 'graf_20_17_t20:'
./app --source ./IN/graf_20_17.txt --out ./OUT/graf_20_17_t20.txt --threads 20

echo 'graf_30_10_t20:'
./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t20.txt --threads 20

echo 'graf_30_20_t20:'
./app --source ./IN/graf_30_20.txt --out ./OUT/graf_30_20_t20.txt --threads 20
