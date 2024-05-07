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


MatDPType& operator++(MatDPType& type);


string tostring(MatDPType);

class  KpSolverDP : public KpSolver {

protected:    

    std::unique_ptr<MatDP> _matDP;
    MatDPType _type;

    void backtrack();

public:
    virtual ~KpSolverDP(){};

    virtual void solve() =0;


    //affichage de la matrice de prog dynamique
    void printMatrixDP(); 

    KpSolverDP(std::string const & filename,  MatDPType type);

};


class  KpSolverDPv0 : public KpSolverDP {
public:
    KpSolverDPv0(std::string const & filename,  MatDPType type = MatDPType::MatDPvect)
        : KpSolverDP(filename, type){};

    void solve() override;
};

class  KpSolverDPv1 : public KpSolverDP {
public:
    KpSolverDPv1(std::string const & filename,  MatDPType type = MatDPType::MatDPvect)
        : KpSolverDP(filename, type){};

    void solve() override;
};

class  KpSolverDPv1bis : public KpSolverDP {
public:
    KpSolverDPv1bis(std::string const & filename,  MatDPType type = MatDPType::MatDPvect)
        : KpSolverDP(filename, type){};

    void solve() override;
};


class  KpSolverDPv2 : public KpSolverDP {
public:
    KpSolverDPv2(std::string const & filename, MatDPType type = MatDPType::MatDPvect)
        : KpSolverDP(filename, type){};

    void solve() override;
};

