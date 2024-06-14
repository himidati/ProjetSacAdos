#include <chrono>
#include "KpSolverDP.hpp"
#include "selectionFile.hpp"



void testSolver(string const &instanceFile, MatDPType matrixType, KpSolverDP * kp1, KpSolverDP * kp2,string fileName){

    string fichierSortie = (fs::path("../results") / fileName).string();

    ofstream outputFile(fichierSortie,  ios::app);
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

template <typename KpSolverDP>

void generateCSV(const string& instanceFile, int version) {
    int i = version;
    double tempsMin = numeric_limits<double>::max();
    vector<chrono::duration<double>> temps;

    string fileName = "testV" + to_string(i) + ".csv";
    string fichierSortie = (fs::path("../results") / fileName).string();

    ofstream outputFile(fichierSortie, ios::app);
    if (!outputFile) {
        cerr << "Erreur: Impossible de créer le fichier CSV pour l'instance : " << instanceFile << endl;
        return;
    }

    outputFile << fs::path(instanceFile).filename() << ";";

    MatDPType matrixType = MatDPType::MatDPvectVect;
    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    auto startCreation = chrono::steady_clock::now();
    auto* kp = new KpSolverDP(instanceFile, matrixType);
    auto endCreation = chrono::steady_clock::now();
    auto creation_time = endCreation - startCreation;

    do {
        cout << "############################################################" << endl;
        cout << "matrix: " << tostring(matrixType) << endl;
        cout << "############################################################" << endl;

        start = chrono::steady_clock::now();
        kp->solve();
        end = chrono::steady_clock::now();
        elapsed_seconds = (end - start)+creation_time;

        cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
        temps.push_back(elapsed_seconds);

        if (elapsed_seconds.count() < tempsMin)
            tempsMin = elapsed_seconds.count();

        outputFile << elapsed_seconds.count() << ";";

        ++matrixType;

        cout << endl;

    } while (matrixType != MatDPType::MatDPvectVect);

    // Calcul des écarts
    for (const auto& t : temps) {
        double r = ((t.count() / tempsMin) * 100);
        outputFile << r << ";";
    }

    outputFile << endl;
    outputFile.close();
    delete kp;
}

void testAllMatrix(const string& instanceFile) {
    generateCSV<KpSolverDPv0>(instanceFile, 0);
    generateCSV<KpSolverDPv1>(instanceFile, 1);
    generateCSV<KpSolverDPv2>(instanceFile, 2);
}


int main()
{
    string textfile = "../cheminInstance.txt";
    string caracteristics="../results/caracteristics.csv";

    //parseInstances(textfile);

    int minNM=0;
    int maxNM=1000000;

    //savecaracteristique("../../data/allIns", caracteristics);
    vector<caracteristiqueInstance> allInstances=loadInstancesFromCSV(caracteristics);
    vector<caracteristiqueInstance>  kept=filterInstance(allInstances, minNM, maxNM); 
/*
    vector<string> insOpt = recupererTousFichier("../../data/allOpt"); //cdossier contenant tous les fichiers .sol

    bool valide=true;
    for(const auto & instance : kept){
       
        fs::path instancePath = instance.filename;
        string instanceStem = instancePath.stem().string();
        string solFileName = instanceStem + ".sol";
    
        // Chercher le fichier correspondant dans insOpt
        auto it = find_if(insOpt.begin(), insOpt.end(), [&solFileName](const string &filePath) {
            return fs::path(filePath).filename() == solFileName;
        });

        if (it != insOpt.end()) {

            int opt=getOptimum(*it);
            estValide(instance.filename, opt);

        } else {
            estValide(instance.filename, instance.opt);
        }        
    }*/

    // génération des fichiers .csv contenant les temps d'executions des différents matrix/solver
    for (const auto &instance : kept)
    {
        testAllMatrix(instance.filename);
    }

    vector<caracteristiqueInstance>::iterator it= kept.begin();
    MatDPType matrixType = MatDPType::MatDPtab;

    // Test comparaison matrices 2 à 2

    KpSolverDPv0 * kp0;
    KpSolverDPv1 * kp1;

    while (it != kept.end())
    {
        kp0 = new KpSolverDPv0((*it).filename, matrixType);
        kp1 = new KpSolverDPv1((*it).filename, matrixType);
        testSolver((*it).filename,matrixType, kp0,kp1, "v0V1.csv");
        it++;
    }
    
    delete kp0;

    KpSolverDPv1bis * kpbis;
    while (it != kept.end())
    {
        kp1 = new KpSolverDPv1((*it).filename, matrixType);
        kpbis = new KpSolverDPv1bis((*it).filename, matrixType);
        testSolver((*it).filename,matrixType, kp1,kpbis, "v1V1bis.csv");
        it++;
    }

    delete kpbis;
    
    KpSolverDPv2 * kp2;
    while (it != kept.end())
    {
        kp1 = new KpSolverDPv1((*it).filename, matrixType);
        kp2 = new KpSolverDPv2((*it).filename, matrixType);
        testSolver((*it).filename,matrixType, kp1,kp2, "v1V2.csv");
        tempsCalcules(kp2); //enregistrements des temps de calcules pour V2
        it++;
    }

    delete kp1;
    delete kp2;

    return 0;
}