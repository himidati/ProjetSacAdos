//********* kpSolverHeurDP.hpp *********

#ifndef KPSOLVERHEURDP_HPP
#define KPSOLVERHEURDP_HPP

#include "KpSolver.hpp"

class  KpSolverHeurDP : public KpSolver {

protected:
	int nbSelectedReopt;
	int nbUnselectedReopt;

	int lastIndex;
	int fixedCost;

public:
    KpSolverHeurDP(std::string const & filename)
        : KpSolver(filename){}
    void solveUpperBound();

    void setNeighborhood(int nbSelectedOpt, int nbUnselectedOpt);
    void solve() override;
};


#endif
