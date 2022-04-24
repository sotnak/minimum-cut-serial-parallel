!/bin/sh

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
$ -S /bin/sh

# Execute the job from the current working directory.
$ -cwd

# Defines  or  redefines  the  path used for the standard error stream of the job.
$ -e ./err.log

# The path used for the standard output stream of the job.
$ -o ./out.log

# Do not change.
$ -pe ompi 1

echo 'graf_20_17:'
./app --source ./IN/graf_20_17.txt --out ./OUT/graf_20_17.txt

echo 'graf_30_10:'
./app --source ./IN/graf_30_10.txt --out ./OUT/graf_30_10.txt

echo 'graf_30_20:'
./app --source ./IN/graf_30_20.txt --out ./OUT/graf_30_20.txt
