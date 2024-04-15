//********* kpSolver.hpp *********

#ifndef KPSOLVERDP_HPP
#define KPSOLVERDP_HPP

#include "KpSolver.hpp"

using T=uint;

class  KpSolverDP : public KpSolver {
protected:
    //option pour appeler la memoisation
    bool memoizedVersion;
private:    
    //option pour appeler le mode verbeux du solveur, et afficher la matrice de programmation dynamique
    bool verboseMode;
    bool parallelizedVersion;
    //TODO: construction itérative de la matrice de prog dynamique
    virtual void solveIter()=0;
    //TODO: backtrack dans la matrice de prog dynamique pour récupérer une composition optimale du sac a dos, a ecrire dans le vector<bool> solution heritee de la classe mere
    virtual void backtrack()=0;

    // construction et destruction de la matrice de prog dynamique
    virtual void createMatrixDP()=0;
    virtual void deleteMatrixDP()=0;

    //affichage de la matrice de prog dynamique
    virtual void printMatrixDP()=0;

    // construction de la première ligne de la matrice de prog dynamique (relative au premier objet)
    virtual void fillFirstColumnDP()=0;
    virtual T getValueAT(int i, int j)=0;

    void setMemoizedVersion(bool memoizedVersion);
public:
    KpSolverDP(std::string const & filename) : KpSolver(filename){}
    void solve() override;

    void setVerboseMode(bool verbosemode);
    void updateKpSolverDP(vector<int> & newWeights,	vector<int> & newValues, int newBound);
    virtual void solveIterParallel()=0;
    // update de la capacité du sac, des poids et values pour pouvoir utiliser la classe dans kpSolverHeurDP
    //void update(int newNbItems, vector<int> newWeights, vector<int> newValues, int newBound);
};

class MatCarreDP : public KpSolverDP{
private:
    //matrice de programmation dynamique
    vector<vector<T>> _matrixDP;
public:
    MatCarreDP(std::string const & filename)
        :KpSolverDP(filename){}
    void solveIter()override ;
    void backtrack() override;
    void createMatrixDP()override ;
    void deleteMatrixDP() override;
    void printMatrixDP()override ;
    void fillFirstColumnDP()override ;
    void solveIterParallel()override ;
    T getValueAT(int i, int j) override { return _matrixDP[i][j];}
};

class TabDynDP : public KpSolverDP{
private:
    T** _matrixDP;
public:
    TabDynDP(std::string const & filename)
        :KpSolverDP(filename){}
    void solveIter()override ;
    void backtrack() override;
    void createMatrixDP()override ;
    void deleteMatrixDP() override;
    void printMatrixDP()override ;
    void fillFirstColumnDP()override ;
    void solveIterParallel()override ;
    // construction itérative de la matrice de prog dynamique
    int solveMemoized(int i , int m);
    T getValueAT(int i, int j)override { return _matrixDP[i][j];}
};

class ListAdjtDP : public KpSolverDP{
private:
   vector<T> _matrixDP;
public:
    ListAdjtDP(std::string const & filename)
        :KpSolverDP(filename),_matrixDP(nbItems*(knapsackBound+1)) {}
    void solveIter()override ;
    void backtrack() override;
    void createMatrixDP()override ;
    void deleteMatrixDP() override;
    void printMatrixDP()override ;
    void fillFirstColumnDP()override ;
    void solveIterParallel()override ;
    T getValueAT(int i, int j)override { return _matrixDP[i*(knapsackBound+1)+j];}
    void setValue(int i, int j, const T& value) { int index = i * knapsackBound + j;    _matrixDP[index] = value;
}
};

#endif

