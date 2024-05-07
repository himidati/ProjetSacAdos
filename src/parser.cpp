#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


// Structure pour stocker les valeurs et les poids
struct Item {
    int value;
    int weight;
};


string convertFile(const string& inputFileName) {

    ifstream inputFile(inputFileName);
    if (!inputFile)
    {
        return "Erreur: Impossible d'ouvrir le fichier d'entrée." ;
    }

    string outputFileName = "xp_" + inputFileName;
    
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
