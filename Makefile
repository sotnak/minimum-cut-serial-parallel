CC	=	mpiCC      # for ethernet and infiniband networks

CFLAGS	=	-std=c++17 -fopenmp -Wall -pedantic
LIBS	=	-lm

default:	all

all: build build/ArgGetter.o build/Configuration.o build/Problem.o build/Solution.o build/Asolver.o build/MasterBBSolver.o build/SlaveBBSolver.o
	$(CC) -o app $(CFLAGS) src/main.cpp build/ArgGetter.o build/Configuration.o build/Problem.o build/Solution.o build/Asolver.o build/MasterBBSolver.o build/SlaveBBSolver.o $(LIBS)
	
build:
	mkdir build

#main.o: src/main.cpp ArgGetter.o Asolver.o Solution.o Problem.o MasterBBSolver.o SlaveBBSolver.o
#	$(CC) -c $(CFLAGS) -o main.o src/main.cpp $(LIBS)

build/ArgGetter.o: src/ArgGetter.cpp src/headers/ArgGetter.h
	$(CC) -c $(CFLAGS) -o build/ArgGetter.o src/ArgGetter.cpp $(LIBS)

build/Configuration.o: src/Configuration.cpp src/headers/Configuration.h
	$(CC) -c $(CFLAGS) -o build/Configuration.o src/Configuration.cpp $(LIBS)

build/Problem.o: src/Problem.cpp src/headers/Problem.h
	$(CC) -c $(CFLAGS) -o build/Problem.o src/Problem.cpp $(LIBS)

build/Solution.o: src/Solution.cpp src/headers/Solution.h
	$(CC) -c $(CFLAGS) -o build/Solution.o src/Solution.cpp $(LIBS)

build/Asolver.o: src/solvers/Asolver.cpp src/solvers/headers/ASolver.h
	$(CC) -c $(CFLAGS) -o build/Asolver.o src/solvers/Asolver.cpp $(LIBS)

build/MasterBBSolver.o: src/solvers/MasterBBSolver.cpp src/solvers/headers/MasterBBSolver.h
	$(CC) -c $(CFLAGS) -o build/MasterBBSolver.o src/solvers/MasterBBSolver.cpp $(LIBS)

build/SlaveBBSolver.o: src/solvers/SlaveBBSolver.cpp src/solvers/headers/SlaveBBSolver.h
	$(CC) -c $(CFLAGS) -o build/SlaveBBSolver.o src/solvers/SlaveBBSolver.cpp $(LIBS)

clear:
	rm -R build/*.o app build
