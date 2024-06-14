#pragma once
#include <filesystem>
#include "KpSolverDP.hpp"
#include "kpSolverBB.hpp"
#include "parser.hpp"

struct caracteristiqueInstance {
    string filename;
    int N;
    int M;
    int produit;
    int opt;
};


struct resultat {
    string filename;
    chrono::duration<double> time;
    int Opt;
    int N;
    int M;
    int NM;
};

void filtrerInstance(string const &file, KpSolverDP * kp);
void readSolution(string const & txtFile);
void savecaracteristique(string const & inputfile, string const & file);
int getOptimum(string const & fileInput);
pair<int, int> getN_M(string const & file);
vector<caracteristiqueInstance> loadInstancesFromCSV(const string& filePath);
vector<caracteristiqueInstance> filterInstance(const vector<caracteristiqueInstance>& instances, int minNM, int maxNM);
void tempsCalcules(KpSolverDP *kp);
vector<caracteristiqueInstance> selectInstances(const vector<caracteristiqueInstance>& instances, int numGroups, int groupSize);
vector<resultat> lireResultatFromCsv(const string& filePath);
bool estValide(string const & instance, int optimum);
