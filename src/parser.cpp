#include <iostream>
#include <fstream>
#include <vector>
#include"parser.hpp"

string convertFile(const string& inputFileName) {

    ifstream inputFile(inputFileName);
    if (!inputFile)
    {
        return "Erreur: Impossible d'ouvrir le fichier d'entrée." ;
    }

    // Extraire le nom du fichier du chemin d'entrée
    size_t lastSlashPos = inputFileName.find_last_of("/\\");
    string inputFileNameOnly = (lastSlashPos != string::npos) ? inputFileName.substr(lastSlashPos + 1) : inputFileName;

    string outputFileName = inputFileName+".in";
    
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
       return  "Erreur: Impossible de créer le fichier de sortie.";
    }

    int n, wmax;
    inputFile >> n >> wmax;

    vector<int> values(n); // Vecteur pour stocker les valeurs
    vector<int> weights(n); // Vecteur pour stocker les poids

    for (int i = 0; i < n; ++i) {
        inputFile >> values[i];
    }

    for (int i = 0; i < n; ++i) {
        inputFile >> weights[i];
    }

    // nb dans le sac
    outputFile << n << endl;

    // valeurs du sac
    for (int i = 0; i < n; ++i) {
        outputFile << values[i] << " ";
    }
    outputFile << endl;

    // poids correspondants
    for (int i = 0; i < n; ++i) {
        outputFile << weights[i] << " ";
    }
    outputFile << endl;

    // capacité max du sac
    outputFile << wmax << endl;

    return outputFileName;
}

bool toCSV(const string & inputFileName){
    return true;
}