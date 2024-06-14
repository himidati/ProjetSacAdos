#include<string>
#include <chrono>
#include <iostream>
#include <future>
#include <chrono>
#include "selectionFile.hpp"


/**
 * prend un fichier .in et retourne un couple de valeur (N,M) N=nb item et M=capacité sac à dos
*/
pair<int, int> getN_M(string const & filePath){
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Erreur d'ouverture du fichier : " << filePath << endl;
        return make_pair(0, 0); // Retourne (0, 0) en cas d'erreur
    }

    int numElements;
    int capacity;

    // lit nb éléments
    string line;
    getline(file, line);
    numElements = stoi(line);

    // Ignore les deux lignes suivantes (poids et valeurs)
    getline(file, line);
    getline(file, line);

    // Lit la capacité du sac
    getline(file, line);
    capacity = stoi(line);

    file.close();
    return make_pair(numElements, capacity);
}

/**
 * fonction qui permet de sauvegarder les caractéristiques des instances dans un .csv
 * elle prend en paramètre un dossier contenant les instances .in et le fochier qui enregistrera les lignes
*/void savecaracteristique(const string &folder, const string &file) {
    ofstream output;
    try {
        output.open(file, ios::app);
        if (!output.is_open()) {
            throw ios_base::failure("Erreur: Impossible d'ouvrir le fichier de sortie.");
        }

        // On récupère tous les fichiers du dossier
        vector<string> listFiles = recupererTousFichier(folder);
        if (listFiles.empty()) {
            throw ios_base::failure("Erreur: Aucun fichier trouvé dans le dossier spécifié.");
        }

        output << "filename;N;M;N*M;OPT" << endl; // Entête

        for (const auto &filePath : listFiles) {
            fs::path nameInstance = filePath;
            try {
                pair<int, int> result = getN_M(filePath);
                long long int produit = result.first * result.second;

                if(produit>1000000 || produit<0){
                    continue;
                }
                else
                {
                    KpSolverBB kpBB(filePath);
                    BranchingStrategies b = BranchingStrategies::BestBound;

                    kpBB.setBranchingStrategy(b);
                    kpBB.setNbMaxNodeBb(10000);
                    kpBB.setSizeDPheur(100);
                    kpBB.setWithDPinitPrimalHeuristic(true);
                    kpBB.solve();

                    int solution = kpBB.getUpperBound();
                    output << filePath << ";" << result.first << ";" << result.second << ";" << produit << ";" << solution << endl;
                }
            } catch (const exception &e) {
                cerr << "Erreur lors du traitement du fichier " << filePath << ": " << e.what() << endl;
            }
        }

    } catch (const ios_base::failure &e) {
        cerr << e.what() << endl;
    } catch (const exception &e) {
        cerr << "Erreur inattendue: " << e.what() << endl;
    } catch (...) {
        cerr << "Erreur inconnue." << endl;
    }

    if (output.is_open()) {
        output.close();
    }
}



/***
 * retourne l'optimum d'une instance
*/
int getOptimum(string const & fileInput){
    ifstream file(fileInput);

    if (!file.is_open()) {
        cerr << "Erreur d'ouverture du fichier : " << fileInput << endl;
        return -1;
    }

    int optimumValue;
    file >> optimumValue;

    file.close();
    return optimumValue;
}

/**
 * lit le fichier csv des caractéristiques
 * 
*/
vector<caracteristiqueInstance> loadInstancesFromCSV(const string& filePath) {
    vector<caracteristiqueInstance> instances;
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Erreur d'ouverture du fichier : " << filePath << endl;
        return instances; // Retourne un vecteur vide en cas d'erreur
    }

    string line;
    getline(file, line); // Ignore l'entête

    while (getline(file, line)) {
        istringstream iss(line);
        string filename;
        string N_str, M_str, NM_str,OPT;

        if (getline(iss, filename, ';') &&
            getline(iss, N_str, ';') &&
            getline(iss, M_str, ';') &&
            getline(iss, NM_str, ';') &&
            getline(iss, OPT, ';')) {

            int N = stoi(N_str);
            int M = stoi(M_str);
            int NM = stoi(NM_str);
            int opt = stoi(OPT);

            instances.push_back(caracteristiqueInstance{filename, N, M, NM, opt});
        } 
    }

    file.close();
    return instances;
}

/**
 * prend en paramètre le fichier .csv généré au début
 * suivant N*M on sélection les instances (on retire les trop petits)
*/
vector<caracteristiqueInstance> filterInstance(const vector<caracteristiqueInstance>& instances, int minNM, int maxNM) {
    vector<caracteristiqueInstance> filteredInstances;

    for (const auto& inst : instances) {
        if (inst.produit >= minNM && inst.produit <= maxNM) {
            filteredInstances.push_back(inst);
        }
    }

    return filteredInstances;
}




/**
 *  enregistre les temps de calcules pour le solver donné en paramètre 
*/
void tempsCalcules(KpSolverDP *kp)
{

    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    vector<caracteristiqueInstance>::iterator it;

    ofstream output("../results/temps_calcul.csv", ios::app);
    output << "filename" << ";" << "Temps-calculs(s)" << ";" << "OPT" << "N" << ";" << "M" << ";" << "N*M" << endl;

    start = chrono::steady_clock::now();
    kp->solve();
    end = chrono::steady_clock::now();
    elapsed_seconds = end - start;
    chrono::duration<double> temps = elapsed_seconds;

    output << (*it).filename << ";" << temps.count() << ";" << kp->getUpperBound() << ";" << (*it).N << ";" << (*it).M << ";" << (*it).produit << endl;
}

/*
lit le fichier csv contenant le temps + caractéristiques des instances et renvoies ces résultats dans un vecteur
*/
vector<resultat> lireResultatFromCsv(const string& filePath) {
    vector<resultat> instances;
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Erreur d'ouverture du fichier : " << filePath << endl;
        return instances;
    }

    string line;
    getline(file, line); // Ignore l'entête

    while (getline(file, line)) {
        istringstream iss(line);
        string filename, time, nStr, mStr, nmStr;
        double temps;
        int N, M, NM;

        if (getline(iss, filename, ';') &&
            getline(iss, time, ';') &&
            getline(iss, nStr, ';') &&
            getline(iss, mStr, ';') &&
            getline(iss, nmStr, ';')) {
            temps = stod(time);
            N = stoi(nStr);
            M = stoi(mStr);
            NM = stoi(nmStr);

            instances.push_back(resultat{filename, chrono::duration<double>(temps), N, M, NM});
        }
    }

    file.close();
    return instances;
}

/**
 * fonction qui permet de grouper les instances en ngroupe 
*/
vector<resultat> selectInstances(const vector<resultat>& instances, int numGroups, int groupSize) {
    vector<resultat> selectedInstances;
    vector<resultat> sortedInstances = instances;

    //trie les instances par N*M
    sort(sortedInstances.begin(), sortedInstances.end(), [](const resultat& a, const resultat& b) {
        return a.NM < b.NM;
    });

    //sélection des groupes d'instances
    for (int i = 0; i < numGroups; ++i) {
        int startIdx = i * groupSize;
        int endIdx = startIdx + groupSize;
        if (endIdx > sortedInstances.size()) break;
        selectedInstances.insert(selectedInstances.end(), sortedInstances.begin() + startIdx, sortedInstances.begin() + endIdx);
    }

    return selectedInstances;
}


/**
 * fonction qui permet de préparer les fichiers .sol afin de procéder au tests booléen vérifiant la 
 * cohérence des valeur optimale 
*/
void readSolution(string const & txtFile){
    ifstream inputfile(txtFile);
    if (!inputfile)
    {
        cerr << "Impossible d'ouvrir le fichier \""<<txtFile<<"\" contenant les chemins des instances" << endl;
        return;
    }

    string directory;

    while (getline(inputfile, directory)) {
        if (!fs::is_directory(directory)) {
            cerr << directory << " n'est pas un dossier" << endl;
            continue;  // Passer à l'itération suivante si ce n'est pas un dossier
        }

        // On récupère tous les fichiers du dossier
        vector<string> listFiles = recupererTousFichier(directory);

        for (auto it = listFiles.begin(); it != listFiles.end(); ++it) {
            if (fs::path(*it).extension() == ".in") {
                string filename = fs::path(*it).replace_extension(".sol").string();
                fs::path directoryPath = "../../data";
                fs::path filePath = directoryPath / filename;

                if (!fs::exists(directoryPath)) {
                    if (!fs::create_directories(directoryPath)) {
                        cerr << "Impossible de créer le nouveau dossier " << directoryPath << endl;
                        continue;
                    }
                }

                ofstream outputSol(filename);
                if (!outputSol) {
                    cerr << "Erreur : Impossible de créer le fichier .sol pour l'instance " << *it << endl;
                    continue;
                }

                pair<int, int> nm = getN_M(*it); 
                if (nm.first * nm.second > 1000000)
                {
                    continue;
                }
                KpSolverBB kpBB(*it);
                BranchingStrategies b = BranchingStrategies::BestBound;
                kpBB.setBranchingStrategy(b);
                kpBB.solve();

                int solution = kpBB.getUpperBound();
                outputSol << solution;
                outputSol.close();

                estValide(*it, solution);

            } else if (fs::path(*it).extension() == ".csv") {
                convertInstanceType3(*it);
            }
        }
    }
}


/**
 * vérifie qur pour un solveur donné, on a toujours la même valeur peu importe le choix de la matrice
 * prends en entré l'instance
*/
bool estValide(const string& instance, int optimum) {
    bool sameValue = true;
    int aux = 0;
    MatDPType matrixType = MatDPType::MatDPvectVect;

    auto checkSolution = [&](auto* kp) {
        do {
            kp->solve();
            aux = kp->getUpperBound();
            
            if (aux != optimum) {
                cerr << "L'optimum obtenu n'est pas le même que celui attendu pour le fichier `" << instance << "`." << aux << " au lieu de " << optimum << endl;
                sameValue = false;
            }
            ++matrixType;
        } while (matrixType != MatDPType::MatDPvectVect && sameValue);
    };

    // vérifie avec KpSolverDPv0
    {
        MatDPType matrixType = MatDPType::MatDPvectVect;
        auto* kp0 = new KpSolverDPv0(instance, matrixType);
        checkSolution(kp0);
        delete kp0;
    }

    // vérifie avec  KpSolverDPv1
    {
        MatDPType matrixType = MatDPType::MatDPvectVect;
        auto* kp1 = new KpSolverDPv1(instance, matrixType);
        checkSolution(kp1);
        delete kp1;
    }

    // vérifie avec KpSolverDPv2
    {
        MatDPType matrixType = MatDPType::MatDPvectVect;
        auto* kp2 = new KpSolverDPv2(instance, matrixType);
        checkSolution(kp2);
        delete kp2;
    }

    return sameValue;
}

