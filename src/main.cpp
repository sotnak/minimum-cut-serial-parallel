#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <vector>
#include <mutex>
#include <mpi.h>

#include "headers/Problem.h"
#include "solvers/headers/ASolver.h"
#include "headers/ArgGetter.h"
#include "solvers/headers/MasterBBSolver.h"
#include "solvers/headers/SlaveBBSolver.h"

using namespace std;
namespace fs = std::filesystem;


chrono::steady_clock::time_point getTimePoint(){
    return chrono::steady_clock::now();
}

chrono::duration<double> getDuration(chrono::steady_clock::time_point t1, chrono::steady_clock::time_point t2){
    return chrono::duration_cast<chrono::duration<double>>(t2 - t1);
}

ifstream getInput(const char* path){
    ifstream sourceFile;
    sourceFile.open(path);
    if(!sourceFile.is_open()){
        throw invalid_argument("file not found");
    }

    return sourceFile;
}

ofstream getOutput(const char* path){
    const string sPath = string(path);
    const string outPath = "OUT/" + sPath.substr(sPath.find('/')+1).substr(sPath.find('/')+1);
    const string folders = outPath.substr(0,outPath.find_last_of('/'));

    if(!fs::is_directory(folders))
        fs::create_directories(folders);

    ofstream output;
    output.open(outPath);
    if(output.fail())
        throw exception();
    return output;
}

vector<string> splitString(const string& str, char delimiter = ' '){
    stringstream strS(str);
    vector<string> res;
    string tmp;

    while(getline(strS, tmp, delimiter))
        res.push_back(tmp);
    return res;
}

void master(int argc, char *argv[]){
    const char* path = ArgGetter::getSourcePath(argc, argv);

    ifstream input = getInput(path);
    ofstream output = getOutput(path);
    auto solver = new MasterBBSolver();

    chrono::steady_clock::time_point t1;
    chrono::steady_clock::time_point t2;
    chrono::duration<double> time_span{};

    stringstream strstr;
    strstr << input.rdbuf();
    input.close();

    Problem problem(Problem::ProblemFactory(strstr));

    t1 = getTimePoint();


    Solution solution = solver->solve(problem);


    t2=getTimePoint();
    time_span= getDuration(t1,t2);
    cout << "total time: " << time_span.count() << endl;


    output << solution.toString()
           << solver->getCounter() << " "
           << time_span.count() << endl;

    output.close();

    delete solver;

    //cout<<"master out"<<endl;
}

void slave(int argc, char *argv[]){


    const char* path = ArgGetter::getSourcePath(argc, argv);

    ifstream input = getInput(path);
    auto solver = new SlaveBBSolver();

    stringstream strstr;
    strstr << input.rdbuf();
    input.close();

    Problem problem(Problem::ProblemFactory(strstr));

    solver->solve(problem);

    delete solver;
    //cout<<"slave out"<<endl;
}

int main(int argc, char *argv[])
{
    int world_rank;

    MPI_Init(&argc, &argv);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if(world_rank == 0)
        master(argc,argv);
    else
        slave(argc,argv);

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}
