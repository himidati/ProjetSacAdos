#include "KpSolver.hpp"
#include <chrono>
#include "KpSolverDP.hpp"
#include "versionSolver.hpp"
#include "parser.cpp"

void testDP(std::string const &instanceFile, bool verboseMode, MatDPType matrixType, KpSolverDP * kp){

    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    if (verboseMode) kp->printKnapsackInstance();
    cout << endl << "Dynamic Programming version: " << static_cast<int>(matrixType) << endl << endl;

    start = chrono::steady_clock::now();
    kp->solve();
    end = chrono::steady_clock::now();
    elapsed_seconds = end - start;
    cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

    kp->printKnapsackSolution(verboseMode);
    if (verboseMode) kp->printMatrixDP();

}


//TODO:1 sortie sur une instance tous les calculs possibles par matrice et solveur differents

void testAll(const string& instanceFile, bool verboseMode) {

    MatDPType matrixType = MatDPType::MatDPvectVect;

    cout<<"programmation dynamique "<<endl;
    do {
        cout<<"############################################################"<<endl;
        SolverVersion tempSolverVersion = SolverVersion::KpSolverDPv0;
        cout<<"matrix: "<<tostring(matrixType)<<endl;
        cout<<"############################################################"<<endl;
        do {
            unique_ptr<KpSolverDP> kp;
            switch (tempSolverVersion) {
                case SolverVersion::KpSolverDPv0:
                    kp = make_unique<KpSolverDPv0>(instanceFile, matrixType);
                    break;
                case SolverVersion::KpSolverDPv1:
                    kp = make_unique<KpSolverDPv1>(instanceFile, matrixType);
                    break;
                case SolverVersion::KpSolverDPv1bis:
                    kp = make_unique<KpSolverDPv1bis>(instanceFile, matrixType);
                    break;
                case SolverVersion::KpSolverDPv2:
                    kp = make_unique<KpSolverDPv2>(instanceFile, matrixType);
                    break;
            }
            cout<<"-----------------------------------------------------------"<<endl;

        auto start = chrono::steady_clock::now();
        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        /*if (verboseMode) cout << "type: " << static_cast<int>(matrixType) << endl;*/
        
        cout<<endl;
        cout<<"version: "<<toStringSolver(tempSolverVersion)<<endl;
        cout<<endl;

        start = chrono::steady_clock::now();
        kp->solve();
        end = chrono::steady_clock::now();
        elapsed_seconds = end - start;
        cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
        
        kp->printKnapsackSolution(verboseMode);
        if (verboseMode) kp->printMatrixDP();

        ++tempSolverVersion;

        } while (tempSolverVersion != SolverVersion::KpSolverDPv0);

        ++matrixType;

        cout<<endl;
    } while (matrixType != MatDPType::MatDPvectVect);
}

//TODO:calcul sur toutes les instances (sauf trop grandes), sortir tableau .csv avec temps de calculs et valeurs obtenues

// kp_10000_1_0.03.in a 10000 objets passe, pas l'instance originale

int main(int argc, char** argv){

    const char* instanceFile;
    string cheminDefaut =  "../instances/courseExample.in"; //"../instances/kp_100_1.in";
    
    /*string file=convertFile("../instances2/low-dimensional/f1_l-d_kp_10_269");

    string cheminDefaut =  "../outputs/"+file; //ne fonctionne pas encore*/

    if (argc < 2) {
        //cerr << "Usage: knapsack inputFile [heuristicMode] [verbosity]" << endl;
        //cerr << "Usage: a heuristic/exactMode implies comparisons of exact methods (for small instances), whereas no parameter implies heuristic search" << endl;
        //cerr << "A third parameter enable verbosity, useful for debugging" << endl;
        //return 1;

        instanceFile = cheminDefaut.c_str();

    }
    else     instanceFile = argv[1];


    bool verboseMode = true;
    if (argc < 3) verboseMode = false;

    MatDPType matrixType = MatDPType::MatDPtab;
    KpSolverDP* kp = new KpSolverDPv2(instanceFile, matrixType);

    //testDP(instanceFile, verboseMode, matrixType, kp);
    testAll(instanceFile, verboseMode);
    return 0;
}
