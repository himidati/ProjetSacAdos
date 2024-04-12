#include "KpSolver.hpp"
#include <chrono>
#include "KpSolverGreedy.hpp"
#include "KpSolverDP.hpp"
#include "KpSolverHeurDP.cpp"

void testGreedy(std::string const & instanceFile, bool verboseMode){

    KpSolverGreedy kpGreedy(instanceFile);

    //if (verboseMode) 
    kpGreedy.printKnapsackInstance();

    cout  << endl << "Greedy bounds :"  << endl << endl;

    auto start = std::chrono::steady_clock::now();
    kpGreedy.solve();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl<< endl;
    kpGreedy.printKnapsackSolution(verboseMode);

    kpGreedy.extractSubInstance(0,10);
    //if (verboseMode) 
    kpGreedy.printKnapsackInstance();
}

void testDP(std::string const &instanceFile, bool verboseMode)
{
    KpSolverDP kp(instanceFile);

    KpSolverHeurDP kpHeurDP(instanceFile);
    
    cout << endl
         << "Dynamic Programming heuristic  with neighborhood 100,100 :" << endl
         << endl;
    kpHeurDP.setNeighborhood(100, 100);
    auto start = std::chrono::steady_clock::now();
    start = std::chrono::steady_clock::now();

    kpHeurDP.solve();
    auto end = std::chrono::steady_clock::now();
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
    kpHeurDP.printKnapsackSolution(verboseMode);

    cout << endl
         << "Dynamic Programming heuristic  with neighborhood 200,200 :" << endl
         << endl;
    kpHeurDP.setNeighborhood(200, 200);
    start = std::chrono::steady_clock::now();
    kpHeurDP.solve();
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
    kpHeurDP.printKnapsackSolution(verboseMode);
}

int main(int argc, char** argv){
    if (argc < 2) {
        cerr << "Usage: knapsack inputFile [heuristicMode] [verbosity]" << endl;
        cerr << "Usage: a heuristic/exactMode implies comparisons of exact methods (for small instances), whereas no parameter implies heuristic search" << endl;
        cerr << "A third parameter enable verbosity, useful for debugging" << endl;
        return 1;
    }

    bool verboseMode = true;
    bool HeuristicMode = false;
    if (argc < 3) HeuristicMode = true;
    if (argc < 4) verboseMode = false;
    const char* instanceFile = argv[1];

    testGreedy(instanceFile, verboseMode);
    if(HeuristicMode){
        testDP(instanceFile, verboseMode);
    }

    return 0;
}