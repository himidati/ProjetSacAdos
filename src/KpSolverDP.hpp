//********* kpSolver.hpp *********

#ifndef KPSOLVERDP_HPP
#define KPSOLVERDP_HPP

#include "KpSolver.hpp"

class  KpSolverDP : public KpSolver {

private:

    //matrice de programmation dynamique
    int** matrixDP;

    //option pour appeler la memoisation
    bool memoizedVersion;
    //option pour appeler le mode verbeux du solveur, et afficher la matrice de programmation dynamique
    bool verboseMode;

    bool parallelizedVersion;
    //TODO: construction itérative de la matrice de prog dynamique
    void solveIter();

    // construction itérative de la matrice de prog dynamique
    int solveMemoized(int i , int m);

    //TODO: backtrack dans la matrice de prog dynamique pour récupérer une composition optimale du sac a dos, a ecrire dans le vector<bool> solution heritee de la classe mere
    void backtrack();

    // construction et destruction de la matrice de prog dynamique
    void createMatrixDP();
    void deleteMatrixDP();

    //affichage de la matrice de prog dynamique
    void printMatrixDP();

    // construction de la première ligne de la matrice de prog dynamique (relative au premier objet)
    void fillFirstColumnDP();


public:
    KpSolverDP(std::string const & filename) : KpSolver(filename){}
    void solve() override;

    void setMemoizedVersion(bool memoizedVersion);
    void setVerboseMode(bool verbosemode);
    void updateKpSolverDP(vector<int> & newWeights,	vector<int> & newValues, int newBound);
    void solveIterParallel();
    // update de la capacité du sac, des poids et values pour pouvoir utiliser la classe dans kpSolverHeurDP
    //void update(int newNbItems, vector<int> newWeights, vector<int> newValues, int newBound);

};

#endif

