#include <iostream>
#include <fstream>
#include <vector>
#include"parser.hpp"
#include<algorithm>


/**
 * retourne tous les fichiers depuis un dossier donné en paramètre
*/
vector<string> recupererTousFichier(string const &folder)
{
    vector<string> listFiles;

    for (const auto &fichier : fs::directory_iterator(folder))
    {
        if (fs::is_regular_file(fichier.status()))
        {
            listFiles.push_back(fichier.path());
        }
    }

    return listFiles;
}


/**
 * met au même format tous les instances
 * prend en paramètre le txtfile contenant les chemins des instances
*/
void parseInstances(string const & txtfile){

    ifstream inputfile(txtfile);
    if (!inputfile.is_open())
    {
        cerr << "Impossible d'ouvrir le fichier \""<<txtfile<<"\" contenant les chemins des instances" << endl;
        return;
    }

    string directory;

    while (getline(inputfile, directory)) {
        directory.erase(directory.find_last_not_of(" \n\r\t") + 1);

        if (!fs::is_directory(directory)) {
            cerr << directory << " n'est pas un dossier" << endl;
            continue;  // itération suivante si ce n'est pas un dossier
        }

        // On récupère tous les fichiers du dossier
        vector<string> listFiles = recupererTousFichier(directory);

        for (const auto &file : listFiles) {
            convertFile(file);
        }

    }
}


void convertFile(const string &inputFileName)
{

    ifstream inputFile(inputFileName);
    if (!inputFile)
    {
        cerr << "Erreur: Impossible d'ouvrir le fichier d'entrée \""<<inputFileName<<"\"" << endl;
        return;
    }

    // Extrait le nom du fichier du chemin d'entrée
    fs::path inputPath(inputFileName);

    if (inputPath.extension() == ".csv")
    {
        convertInstanceType3(inputFileName);
        
    }

    else if(inputPath.extension()!=".in") //est au format 2
    {
        string outputFileName = inputPath.stem().string() + ".in";
        fs::path directoryPath = "../../data/allIns";
        fs::path filePath = directoryPath / outputFileName;

        ofstream outputFile(filePath.string());
        if (!outputFile.is_open())
        {
            cerr << "Erreur: Impossible de parser le fichier "<<inputFileName << endl;
            return;
        }

        int n, wmax;
        inputFile >> n >> wmax;

        vector<int> values(n);
        vector<int> weights(n);

        for (int i = 0; i < n; ++i)
        {
            inputFile >> values[i];
        }

        for (int i = 0; i < n; ++i)
        {
            inputFile >> weights[i];
        }

        // nb dans le sac
        outputFile << n << endl;

        // valeurs du sac
        for (int i = 0; i < n; ++i)
        {
            outputFile << values[i] << " ";
        }
        outputFile << endl;

        // poids correspondants
        for (int i = 0; i < n; ++i)
        {
            outputFile << weights[i] << " ";
        }
        outputFile << endl;

        // capacité max du sac
        outputFile << wmax << endl;
        
    }else if (inputPath.extension() == ".in"){
        try
        {
            fs::path destinationDir = "../../data/allIns";
            if (!fs::exists(destinationDir))
            {
                fs::create_directories(destinationDir);
            }
            fs::path destinationPath = destinationDir / inputPath.filename();
            fs::copy_file(inputPath, destinationPath, fs::copy_options::overwrite_existing);
        }
        catch (const fs::filesystem_error &e)
        {
            cerr << "Erreur: Impossible de copier le fichier \"" << inputFileName << "\" vers \"" << "../../data" << "\" : " << e.what() << endl;
        }
    }
    
    inputFile.close();
}

/**
 * génère l'instance au format .in 
 * génère la solution de l'instance dans un .sol
*/
void convertInstanceType3(const string& inputfile) {
    ifstream inputFile(inputfile);
    string line;

    if (!inputFile.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier d'entrée." << endl;
        return;
    }

    vector<string> listFileName;
    vector<int> listCapacite;
    vector<uint> values;
    vector<uint> weights;
    vector<uint> optimums;

    string filename;
    int n = 0;
    int wmax = 0;
    int z = 0;
    bool headerRead = true;

    while (getline(inputFile, line)) {
        istringstream ss(line);
        string temp;

        if (headerRead) {

            // Lire les valeurs des en-têtes
            getline(inputFile, line);
            ss.str(line);
            ss >> filename;
            ss.clear();
            listFileName.push_back(filename);

            getline(inputFile, line); // Lire la ligne "n x"
            ss.str(line);
            ss.clear();
            ss >> temp >> n;

            getline(inputFile, line); // Lire la ligne "c wmax"
            ss.str(line);
            ss.clear();
            ss >> temp >> wmax;
            listCapacite.push_back(wmax);

            getline(inputFile, line); // Lire la ligne "z d" (ignorée)
            ss.str(line);
            ss.clear();
            ss >> temp >> z;
            optimums.push_back(z);

            getline(inputFile, line); // Lit la ligne "time 0.00" (ignorée)
            headerRead = false;

        } else {
            Item item;
            char comma;
            int ki, bi;

            if (ss >> ki >> comma >> item.value >> comma >> item.weight >> comma >> bi) {
                weights.push_back(item.weight);
                values.push_back(item.value);
            }

            if (line == "-----") {
                values.push_back(-1);
                weights.push_back(-1);
                headerRead = true;
            }
        }
    }

    inputFile.close();

    // transcription dans le nouveau format
    size_t instanceStart = 0;
    for (size_t j = 0; j < listFileName.size(); ++j) {
       
        string fileName =fs::path(listFileName[j]).replace_extension(".in").string();
        fs::path directoryPath = "../../data/allIns";
        fs::path filePath = directoryPath / fileName;

        if (!fs::exists(directoryPath))
        {
            if (!fs::create_directories(directoryPath))
                cerr << "impossible de créer le nouveau dossier "<<directoryPath <<endl;
        }

        ofstream outputFile(filePath.string());

        if (!outputFile) {
            cerr << "Erreur: Impossible de créer le nouveau fichier .in pour l'instance : " << listFileName[j] << endl;
            return;
        }

        // écriture dans le fichier de sorti // génération du .in
        outputFile << n << endl;

        // écriture des valeurs
        for (size_t i = instanceStart; i < values.size() && values[i] != -1; ++i) {
            outputFile << values[i] << " ";
        }
        outputFile << endl;

        // écriture des poids
        for (size_t i = instanceStart; i < weights.size() && weights[i] != -1; ++i) {
            outputFile << weights[i] << " ";
        }
        outputFile << endl;

        outputFile << listCapacite[j] << endl;
        outputFile.close();

        string nomfichier = fs::path(listFileName[j]).replace_extension(".sol").string();
        fs::path repertoryPath = "../../data/allOpt";
        fs::path chemin = repertoryPath / nomfichier;

        if (!fs::exists(repertoryPath))
        {
            if (!fs::create_directories(repertoryPath))
                cerr << "impossible de créer le nouveau dossier" << repertoryPath <<endl;
        }
        ofstream outputSol(chemin);

        if (!outputSol) {
            cerr << "Erreur : impossible de créer le fichier .sol pour l'instance " << listFileName[j] << endl;
            return;
        }

        // génération .sol
        outputSol << optimums[j];
        outputSol.close();

        //position de la prochaine instance
        instanceStart += (find(weights.begin() + instanceStart, weights.end(), -1) - weights.begin() - instanceStart + 1);
    }
}


/**
 * fonction qui vérifie la cohérence en temps d'exécution suivant N*M
 * on suppose qu'il ne prend que des fichier sans l'extension .in
*/
void validationCoherence(string const & inputfile, chrono::duration<double> tmps){
    
    ifstream inputFile(inputfile);

    if(!inputFile.is_open()){
        cerr << " Impossible d'ouvrir le fichier \"" << inputfile << "\" " << endl;
        return ;
    }

    fs::path inputPath(inputfile);

    if (inputPath.extension() == ".in")
    {
        string line;
        int lineNumber = 0;
        string n;
        string value;
        
        ofstream output("validation.csv", ios::app);

        while (getline(inputFile, line))
        {    

            ++lineNumber;
            if (lineNumber == 1) // nb item
            { 
                n = line;
            }
            else if (lineNumber == 4) // capacité du sac à dos
            {
                value = line;
                break;
            }
        }
        inputFile.close();
        auto ratio=(tmps / (stoi(n) * stoi(value)));

        output << inputfile << ";" <<  ratio.count() << endl;

        output.close();
    }
}

