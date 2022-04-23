#!/bin/bash

make
 
./app --source ./IN/graf_10_7.txt --out ./OUT/graf_10_7_t2.txt --threads 2
./app --source ./IN/graf_20_7.txt --out ./OUT/graf_20_7_t2.txt --threads 2
./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t2.txt --threads 2

./app --source ./IN/graf_10_7.txt --out ./OUT/graf_10_7_t4.txt --threads 4
./app --source ./IN/graf_20_7.txt --out ./OUT/graf_20_7_t4.txt --threads 4
./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t4.txt --threads 4

./app --source ./IN/graf_10_7.txt --out ./OUT/graf_10_7_t8.txt --threads 8
./app --source ./IN/graf_20_7.txt --out ./OUT/graf_20_7_t8.txt --threads 8
./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t8.txt --threads 8

./app --source ./IN/graf_10_7.txt --out ./OUT/graf_10_7_t16.txt --threads 16
./app --source ./IN/graf_20_7.txt --out ./OUT/graf_20_7_t16.txt --threads 16
./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t16.txt --threads 16

./app --source ./IN/graf_10_7.txt --out ./OUT/graf_10_7_t20.txt --threads 20
./app --source ./IN/graf_20_7.txt --out ./OUT/graf_20_7_t20.txt --threads 20
./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t20.txt --threads 20
