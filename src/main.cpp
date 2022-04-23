#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <vector>
#include <mutex>

#include "headers/Problem.h"
#include "solvers/headers/ASolver.h"
#include "headers/ArgGetter.h"

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
    const string folders = sPath.substr(0,sPath.find_last_of('/'));

    if(!fs::is_directory(folders))
        fs::create_directories(folders);

    ofstream output;
    output.open(sPath);
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

int main(int argc, char *argv[])
{
    const char* path = ArgGetter::getSourcePath(argc, argv);
    const char* outPath = ArgGetter::getOutputPath(argc, argv);

    ifstream input = getInput(path);
    ofstream output = getOutput(outPath);
    ASolver* solver = ASolver::SolverFactory();

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

    //input.close();

    output.close();

    delete solver;

    return 0;
}
