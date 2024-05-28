#include "KpSolver.hpp"
#include <chrono>
#include "KpSolverDP.hpp"
#include "parser.cpp"
#include <string.h>

void testSolver(std::string const &instanceFile, MatDPType matrixType, KpSolverDP * kp1, KpSolverDP * kp2){

    string fileName= "result.csv";

    string fichierSortie = (fs::path("../output") / fileName).string();

    ofstream outputFile(fichierSortie,  std::ios::app);
    if (!outputFile) {
        cout << "Erreur: Impossible de créer le fichier CSV pour l'instance : "<<instanceFile << endl;
        return;
    }

    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    start = chrono::steady_clock::now();
    kp1->solve();
    end = chrono::steady_clock::now();
    elapsed_seconds = end - start;
    chrono::duration<double> temp1=elapsed_seconds;
    cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

    outputFile << elapsed_seconds.count() <<";";

    start = chrono::steady_clock::now();
    kp2->solve();
    end = chrono::steady_clock::now();
    elapsed_seconds = end - start;
    chrono::duration<double> temp2=elapsed_seconds;
    cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
    
    outputFile << elapsed_seconds.count() <<";";

    if(temp1.count()<temp2.count())
        outputFile << temp2.count()/temp1.count() <<";";
    else 
        outputFile <<temp1.count()/temp2.count()<<";";

    outputFile<<endl;

    outputFile.close();

}

void testAllMatrix(const string& instanceFile,  KpSolverDP * kp) {

    string fileName= fs::path(instanceFile).filename().replace_extension(".csv").string();

    string fichierSortie = (fs::path("../output") / fileName).string();

    ofstream outputFile(fichierSortie);
    if (!outputFile) {
        cout << "Erreur: Impossible de créer le fichier CSV pour l'instance : "<<instanceFile << endl;
        return;
    }

    bool isSame=true;
    int value=0;
    int aux=0;
    double tempsMin= numeric_limits<double>::max();
    vector<chrono::duration<double>> temps;


    outputFile << ";" << "MatDPvectVect" << ";" << "MatDPvect" << ";"<< "MatDPtabTab" << ";" << "MatDPtab" << ";" << "coherence" << ";" << "tempsMin: " <<endl;
    outputFile << fs::path(instanceFile).filename() <<";";

    MatDPType matrixType = MatDPType::MatDPtab;

    cout<<"programmation dynamique "<<endl;

    do {
        cout<<"############################################################"<<endl;
        cout<<"matrix: "<<tostring(matrixType)<<endl;
        cout<<"############################################################"<<endl;
        
        auto start = chrono::steady_clock::now();
        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        start = chrono::steady_clock::now();
        kp->solve();
        value=kp->getUpperBound();

        if(aux!=0 && aux!=value) 
            isSame=false ; 

        aux=value;

        end = chrono::steady_clock::now();
        elapsed_seconds = end - start;
        cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
        
        temps.push_back(elapsed_seconds);

        if(elapsed_seconds.count() < tempsMin) 
            tempsMin=elapsed_seconds.count();

        outputFile << elapsed_seconds.count() << ";";

        ++matrixType;
        
        cout<<endl;
    } while (matrixType != MatDPType::MatDPvectVect);

    outputFile << isSame << ";" << tempsMin<<";" ;

    //calcule de l'écart
    for(auto const& t: temps){
        double r= ((t.count() /tempsMin)*100);
        outputFile<<r<<";";
    }

    outputFile<<endl;

    outputFile.close();
}



int main(int argc, char **argv)
{
    string instanceFile;

    vector<string> liste_low_dimentional = {"f1_l-d_kp_10_269", "f2_l-d_kp_20_878", "f3_l-d_kp_4_20", "f4_l-d_kp_4_11",
                                                  "f5_l-d_kp_15_375", "f6_l-d_kp_10_60", "f8_l-d_kp_23_10000", "f9_l-d_kp_5_80", "f10_l-d_kp_20_879"};

    vector<string> liste_large_scale = {"knapPI_1_100_1000_1", "knapPI_1_500_1000_1", "knapPI_1_1000_1000_1", "knapPI_1_2000_1000_1","knapPI_1_5000_1000_1", "knapPI_1_10000_1000_1",
                                             "knapPI_2_100_1000_1", "knapPI_2_200_1000_1", "knapPI_2_500_1000_1", "knapPI_2_1000_1000_1", "knapPI_2_2000_1000_1", "knapPI_2_5000_1000_1", 
                                             "knapPI_2_10000_1000_1", "knapPI_3_100_1000_1","knapPI_3_200_1000_1", "knapPI_3_500_1000_1", "knapPI_3_1000_1000_1", "knapPI_3_2000_1000_1",
                                              "knapPI_3_5000_1000_1", "knapPI_3_10000_1000_1"};

    bool verboseMode = true;
    if (argc < 3)
        verboseMode = false;

    if (argc < 2)
    {
        // cerr << "Usage: knapsack inputFile [heuristicMode] [verbosity]" << endl;
        // cerr << "Usage: a heuristic/exactMode implies comparisons of exact methods (for small instances), whereas no parameter implies heuristic search" << endl;
        // cerr << "A third parameter enable verbosity, useful for debugging" << endl;
        // return 1;

        //test("../nouveauInstance/hardinstances_pisinger/knapPI_11_20_1000.csv");
        //convertFile("../nouveauInstance/hardinstances_pisinger/knapPI_11_20_1000.in");
        
        string chemin="../instances2/large_scale/";

        instanceFile=chemin+"knapPI_2_10000_1000_1.in";

        MatDPType matrixType = MatDPType::MatDPtab;
        KpSolverDP *kpv0= new KpSolverDPv2(instanceFile, matrixType);
        KpSolverDP *kpv2= new KpSolverDPv2(instanceFile, matrixType);

        testSolver(instanceFile,matrixType, kpv0,kpv2 );

        delete kpv0;
        delete kpv2;
    }
    else
        instanceFile = argv[1];


    return 0;
}
