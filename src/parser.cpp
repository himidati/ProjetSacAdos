#include <iostream>
#include <fstream>
#include <vector>
#include<filesystem>
#include"parser.hpp"

namespace fs=std::filesystem;


void convertFile(const string &inputFileName)
{

    ifstream inputFile(inputFileName);
    if (!inputFile)
    {
        cerr << "Erreur: Impossible d'ouvrir le fichier d'entrée." << endl;
        return;
    }

    // Extrait le nom du fichier du chemin d'entrée
    fs::path inputPath(inputFileName);
    std::string outputFileName;

    if (inputPath.extension() == ".csv")
    {
        outputFileName = inputPath.replace_extension(".in").string();
    }
    else
    {
        outputFileName = inputFileName + ".in";
    }

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
        cerr << "Erreur: Impossible de créer le fichier de sortie." << endl;
        return;
    }

    if (inputPath.extension() == ".csv")
    {
        // Skip the first line
        std::string line;
        std::getline(inputFile, line);

        int n, wmax;
        std::getline(inputFile, line);
        std::istringstream issN(line);
        std::string temp;
        issN >> temp >> n;

        std::getline(inputFile, line);
        std::istringstream issW(line);
        issW >> temp >> wmax;

        // Skip the next two lines
        std::getline(inputFile, line);
        std::getline(inputFile, line);

        std::vector<int> values(n);
        std::vector<int> weights(n);

        for (int i = 0; i < n; ++i)
        {
            std::getline(inputFile, line);
            std::istringstream iss(line);
            int index, value, weight, taken;
            char comma;
            iss >> index >> comma >> value >> comma >> weight >> comma >> taken;
            values[i] = value;
            weights[i] = weight;
        }

        // Write to output file
        outputFile << n << std::endl;

        for (int i = 0; i < n; ++i)
        {
            outputFile << values[i] << " ";
        }
        outputFile << std::endl;

        for (int i = 0; i < n; ++i)
        {
            outputFile << weights[i] << " ";
        }
        outputFile << std::endl;

        outputFile << wmax << std::endl;
    }
    else
    {
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
    }
    inputFile.close();

    cout << "conversion terminé avec succès" << endl;
}



void test(string const & inputFileName) {

    std::string outputFileName = fs::path(inputFileName).replace_extension("in").string();
    std::ofstream outputFile((fs::path("../output") / outputFileName).string());

    std::ifstream inputFile(inputFileName);
    std::string line;

    if (!inputFile.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier d'entrée." << std::endl;
        return;
    }

    std::vector<Item> items;
    std::vector<int> listCapacite;
    std::vector<uint> values;
    std::vector<uint> weights;

    int n = 0;
    int wmax = 0;
    bool headerRead = false;

    Item fin={-1,-1};
    
    //on lit ligne par ligne
    while (std::getline(inputFile, line)) {
        
        if (line == "-----") {
            items.push_back(fin);
            headerRead=true;
            continue;
        }

        std::istringstream ss(line);

        if (headerRead) { // lit les valeurs des en-têtes
            
            // Lire les valeurs des en-têtes
            std::getline(inputFile, line);
            std::string temp;
            std::getline(inputFile, line); // Lire la ligne "n x"
            ss.str(line);
            ss.clear();
            ss >> temp >> n;

            std::getline(inputFile, line); // Lire la ligne "c wmax"
            ss.str(line);
            ss.clear();
            ss >> temp >> wmax;
            listCapacite.push_back(wmax);

            std::getline(inputFile, line); // Lire la ligne "z d" (ignorée)
            std::getline(inputFile, line);// Lit la ligne "time 0.00" (ignorée)
            headerRead=false;
        } 
            else {

            Item item;
            char comma;
            int ki, bi; 

            if (ss >> ki >> comma >> item.value >> comma >> item.weight >> comma >> bi) {
                //items.push_back(item);
                weights.push_back(item.weight);
                values.push_back(item.value);

            }
        }
    }

    inputFile.close();

    //transcription dans le nouveau format
    outputFile << n << " " << wmax << "\n";

    vector<int>::iterator it=listCapacite.begin();

    for (const auto &item : items)
    {
        if (item.value == -1 && item.weight == -1)
        {
            outputFile << "\n";
            if (it != listCapacite.end())
            {
                outputFile << n << " " << (*it)<<"\n";
                it++;
            }
        }
        else
            outputFile << item.value << " " << item.weight << "\n";
    }

    outputFile.close();

    std::cout << "Conversion terminée" << std::endl;

}
