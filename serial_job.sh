#!/bin/sh

#  ===========================================================================
# |                                                                           |
# |             COMMAND FILE FOR SUBMITTING SGE JOBS                          |
# |                                                                           |
# |                                                                           |
# | SGE keyword statements begin with #$                                      |
# |                                                                           |
# | Comments begin with #                                                     |
# | Any line whose first non-blank character is a pound sign (#)              |
# | and is not a SGE keyword statement is regarded as a comment.              |
#  ===========================================================================

# Request Bourne shell as shell for job
#$ -S /bin/sh

# Execute the job from the current working directory.
#$ -cwd

# Defines  or  redefines  the  path used for the standard error stream of the job.
#$ -e ./err.log

# The path used for the standard output stream of the job.
#$ -o ./out.log

# Do not change.
#$ -pe ompi 1

# echo 'graf_20_17_t2:'
# ./app --source ./IN/graf_20_17.txt --out ./OUT/graf_20_17_t2.txt --threads 2

# echo 'graf_30_10_t2:'
# ./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t2.txt --threads 2

# echo 'graf_30_20_t2:'
# ./app --source ./IN/graf_30_20.txt --out ./OUT/graf_30_20_t2.txt --threads 2


# echo 'graf_20_17_t4:'
# ./app --source ./IN/graf_20_17.txt --out ./OUT/graf_20_17_t4.txt --threads 4

# echo 'graf_30_10_t4:'
# ./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t4.txt --threads 4

# echo 'graf_30_20_t4:'
# ./app --source ./IN/graf_30_20.txt --out ./OUT/graf_30_20_t4.txt --threads 4


# echo 'graf_20_17_t8:'
# ./app --source ./IN/graf_20_17.txt --out ./OUT/graf_20_17_t8.txt --threads 8

# echo 'graf_30_10_t8:'
# ./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t8.txt --threads 8

# echo 'graf_30_20_t8:'
# ./app --source ./IN/graf_30_20.txt --out ./OUT/graf_30_20_t8.txt --threads 8


# echo 'graf_20_17_t16:'
# ./app --source ./IN/graf_20_17.txt --out ./OUT/graf_20_17_t16.txt --threads 16

# echo 'graf_30_10_t16:'
# ./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t16.txt --threads 16

# echo 'graf_30_20_t16:'
# ./app --source ./IN/graf_30_20.txt --out ./OUT/graf_30_20_t16.txt --threads 16


# echo 'graf_20_17_t20:'
# ./app --source ./IN/graf_20_17.txt --out ./OUT/graf_20_17_t20.txt --threads 20

# echo 'graf_30_10_t20:'
# ./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10_t20.txt --threads 20

# echo 'graf_30_20_t20:'
# ./app --source ./IN/graf_30_20.txt --out ./OUT/graf_30_20_t20.txt --threads 20

echo 'graf_40_8_t20:'
./app --source ./IN/graf_40_8.txt --out ./OUT/graf_40_8_t20.txt --threads 20

echo 'graf_40_8_t16:'
./app --source ./IN/graf_40_8.txt --out ./OUT/graf_40_8_t16.txt --threads 16

echo 'graf_40_8_t8:'
./app --source ./IN/graf_40_8.txt --out ./OUT/graf_40_8_t8.txt --threads 8

echo 'graf_40_8_t4:'
./app --source ./IN/graf_40_8.txt --out ./OUT/graf_40_8_t4.txt --threads 4

echo 'graf_40_8_t2:'
./app --source ./IN/graf_40_8.txt --out ./OUT/graf_40_8_t2.txt --threads 2



echo 'graf_40_15_t20:'
./app --source ./IN/graf_40_15.txt --out ./OUT/graf_40_15_t20.txt --threads 20

echo 'graf_40_15_t16:'
./app --source ./IN/graf_40_15.txt --out ./OUT/graf_40_15_t16.txt --threads 16

echo 'graf_40_15_t8:'
./app --source ./IN/graf_40_15.txt --out ./OUT/graf_40_15_t8.txt --threads 8

echo 'graf_40_15_t4:'
./app --source ./IN/graf_40_15.txt --out ./OUT/graf_40_15_t4.txt --threads 4

echo 'graf_40_15_t2:'
./app --source ./IN/graf_40_15.txt --out ./OUT/graf_40_15_t2.txt --threads 2



echo 'graf_40_25_t20:'
./app --source ./IN/graf_40_25.txt --out ./OUT/graf_40_25_t20.txt --threads 20

echo 'graf_40_25_t16:'
./app --source ./IN/graf_40_25.txt --out ./OUT/graf_40_25_t16.txt --threads 16

echo 'graf_40_25_t8:'
./app --source ./IN/graf_40_25.txt --out ./OUT/graf_40_25_t8.txt --threads 8

echo 'graf_40_25_t4:'
./app --source ./IN/graf_40_25.txt --out ./OUT/graf_40_25_t4.txt --threads 4

echo 'graf_40_25_t2:'
./app --source ./IN/graf_40_25.txt --out ./OUT/graf_40_25_t2.txt --threads 2
