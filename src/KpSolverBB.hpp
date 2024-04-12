//********* kpSolverBB.hpp *********

#ifndef KPSOLVERBB_HPP
#define KPSOLVERBB_HPP

#include "KpSolver.hpp"
#include "nodeBB.hpp"
#include <deque>
#include<memory>

// Enumération pour les différentes stratégies de parcours de l'arbre
enum class BranchingStrategies { 
    BestBound, 
    DFS10, 
    DFS01, 
    BFS, 
    Random, 
    End 
    };
    
// Classe abstraite pour les différentes stratégies de parcours de l'arbre
class BranchingStrategy : public KpSolver{

private :
    int nbNodes; // nombre de noeuds visites, compte le nombre d'appeles a la relaxation continue
    int nbMaxNodeBB; // nombre maximal de noeuds a explorer, un critere d arret pour uen resolution approchee
    bool withPrimalHeuristics; // active les heuristiques gloutonnes discretes a chaque noeud
    bool verboseMode; // mode verbux pour deboguer le B&B
    bool withDPinitPrimalHeuristic; // pour initialiser avec une solution obtenue par Kernel Search
    int sizeDPheur; // parametre pour la Kernel Search: nombre maximale d'objets a considere dans l'optimisation locale

    std::unique_ptr<BranchingStrategy> _branchingStrategy; // un type de parcours d'arbre, grace au type enumere BranchingStrategies
    BranchingStrategies _type;

public:
    BranchingStrategy(std::string const & filename, BranchingStrategies strategy)  
        : KpSolver(filename),_type(strategy){}

    virtual ~BranchingStrategy() = default;
    virtual std::unique_ptr<NodeBB> selectNode() = 0;

    void solve() override;
    void init();

	void setNbMaxNodeBb(int nbMaxNodeBb) {	nbMaxNodeBB = nbMaxNodeBb;};
	void setVerboseMode(bool vMode){verboseMode = vMode;};
	void setWithPrimalHeuristics(bool withHeuristics) {withPrimalHeuristics = withHeuristics;};
	void setWithDPinitPrimalHeuristic(bool withHeuristic) {withDPinitPrimalHeuristic = withHeuristic;};
	void setSizeDPheur(int siz) {sizeDPheur = siz;};
	int getNbNodes() const {return nbNodes;};

    void printStatus();
    void removeNodes();

    double getUpperBound();
protected:
    std::deque<std::unique_ptr<NodeBB>> nodes; // liste des noeuds actifs de l'arbre de B&B
    void insertNode(std::unique_ptr<NodeBB>nod);
    void insertNodes(std::unique_ptr<NodeBB>nod1, std::unique_ptr<NodeBB>nod2);
    void reset();
};

// Implémentation de la stratégie BestBound
class BestBoundBranchingStrategy : public BranchingStrategy {
public:
    BestBoundBranchingStrategy(std::string const & filename)
        : BranchingStrategy(filename,BranchingStrategies::BestBound ){}

    std::unique_ptr<NodeBB> selectNode() override;
};

// Implémentation de la stratégie DFS 
class DFSBranchingStrategy : public BranchingStrategy {
public:
    DFSBranchingStrategy(std::string const & filename)
        : BranchingStrategy(filename,BranchingStrategies::BestBound ){}
    std::unique_ptr<NodeBB> selectNode() override;
};

// Implémentation de la stratégie random
class RandomBranchingStrategy : public BranchingStrategy {
public:
    RandomBranchingStrategy(std::string const & filename)
        : BranchingStrategy(filename,BranchingStrategies::BestBound ){}
    std::unique_ptr<NodeBB> selectNode() override;
};

// Implémentation de la stratégie BFS 
class BFSBranchingStrategy : public BranchingStrategy {
public:
 BFSBranchingStrategy(std::string const & filename)
        : BranchingStrategy(filename,BranchingStrategies::BestBound ){}
    std::unique_ptr<NodeBB> selectNode() override;
};

// Implémentation de la stratégie End
class EndBranchingStrategy : public BranchingStrategy {
public:
    EndBranchingStrategy(std::string const & filename)
        : BranchingStrategy(filename,BranchingStrategies::BestBound ){}
    std::unique_ptr<NodeBB> selectNode() override;
};

#endif
