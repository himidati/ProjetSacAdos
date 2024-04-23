//********* kpSolver.hpp *********

#pragma once
#include"KpSolver.hpp"
#include "MatDP.hpp"
#include <memory>

enum class MatDPType { 
    MatDPvectVect, 
    MatDPvect, 
    MatDPtabTab,
    MatDPtab    
};



class  KpSolverDP : public KpSolver {

protected:    

    std::unique_ptr<MatDP> _matDP;
    MatDPType _type;
    bool verboseMode;
public:
    virtual ~KpSolverDP(){};

    virtual void solve() =0;

    // construction de la première ligne de la matrice de prog dynamique (relative au premier objet)
    void backtrack();

    //affichage de la matrice de prog dynamique
    void printMatrixDP(); 


    KpSolverDP(std::string const & filename, bool verb = false,  MatDPType type = MatDPType::MatDPvect) : KpSolver(filename), verboseMode(verb) , _type(type){
        switch(_type){

        case MatDPType::MatDPvectVect:
            _matDP = std::make_unique<MatDPvectVect>(nbItems, knapsackBound);     // Knapsack bound
                    break;
        case MatDPType::MatDPvect : 
            _matDP = std::make_unique<MatDPvect>(nbItems, knapsackBound);
            break;
        case MatDPType::MatDPtabTab:
            _matDP = std::make_unique<MatDPtabTab>(nbItems, knapsackBound);
            break;
        case MatDPType::MatDPtab :
            _matDP= std::make_unique<MatDPtab>(nbItems, knapsackBound);
            break;
    }

    };

};


//TODO: solve_v0 on utilise [][]
//TODO: solve_v1 on utilise getElement et setElementusing T=uint;
//TODO: solve_v2 on computeLineDP

class  KpSolverDPv0 : public KpSolverDP {
public:
    KpSolverDPv0(std::string const & filename, bool verb = false,  MatDPType type = MatDPType::MatDPvect) 
        : KpSolverDP(filename, verb, type){};

    virtual void solve() override;
};

class  KpSolverDPv1 : public KpSolverDP {
public:
    KpSolverDPv1(std::string const & filename, bool verb = false,  MatDPType type = MatDPType::MatDPvect) 
        : KpSolverDP(filename, verb, type){};

    virtual void solve() override;
};

class  KpSolverDPv2 : public KpSolverDP {
public:
    KpSolverDPv2(std::string const & filename, bool verb = false,  MatDPType type = MatDPType::MatDPvect) 
        : KpSolverDP(filename, verb, type){};

    virtual void solve() override;
};

