#include "KpSolver.hpp"
#include <chrono>
#include "KpSolverDP.hpp"


void testDP(std::string const &instanceFile, bool verboseMode)
{
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    KpSolverDPv2 kp(instanceFile,false,MatDPType::MatDPtabTab);
    kp.printKnapsackInstance();
    cout << endl
         << "Dynamic Programming iterative version without parallelization  :" << endl
         << endl;
    start = std::chrono::steady_clock::now();
    kp.solve();
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

    kp.printKnapsackSolution(verboseMode);
    
}

int main(int argc, char** argv){
    if (argc < 2) {
        cerr << "Usage: knapsack inputFile [heuristicMode] [verbosity]" << endl;
        cerr << "Usage: a heuristic/exactMode implies comparisons of exact methods (for small instances), whereas no parameter implies heuristic search" << endl;
        cerr << "A third parameter enable verbosity, useful for debugging" << endl;
        return 1;
    }

    bool verboseMode = true;
    //if (argc < 3) verboseMode = false;
    const char* instanceFile = argv[1];

    testDP(instanceFile, verboseMode);

    return 0;
}