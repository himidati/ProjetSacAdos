#include "KpSolverDP.hpp"


#include <omp.h>
#include "KpSolver.hpp"

void KpSolverDP::backtrack(){
	solution.resize(nbItems, false);
    int m = knapsackBound;
    for (int i = nbItems; i >=1 ; i--){
    	if (m < weights[i]) 
			solution[i]=false;
    	else if (_matDP->getElement(i-1,m) > values[i] + _matDP->getElement(i-1,m - weights[i])) 
			solution[i]=false;
    	else {
    		solution[i]=true;
    		m = m-weights[i];
    	}
    }

	if (m < weights[0]) solution[0]=false;
	else solution[0]=true;
}


void KpSolverDPv0::solve(){
	for(int i=1; i < nbItems; i++) {
		for (int m=1; m < knapsackBound+1; m++) {
			(*_matDP)[i][m] = (*_matDP)[i-1][m];
			if (m >= weights[i]) {
				(*_matDP)[i][m] = max((*_matDP)[i-1][m], ((*_matDP)[i-1][m-weights[i]] + values[i]));
			}
		}
	}
	costSolution = (*_matDP)[nbItems-1][knapsackBound];
	upperBoundOPT=costSolution;
	KpSolverDP::backtrack();
}

void KpSolverDPv1::solve(){
	for(uint i=1; i < nbItems; i++) {
		for (uint m=1; m < knapsackBound+1; m++) {
			_matDP->setElement(i,m,_matDP->getElement(i-1,m));
			if (m >= weights[i]) {
				_matDP->setElement( i,m,max(_matDP->getElement(i-1,m), (_matDP->getElement(i-1,m-weights[i]) + values[i])));
			}
		}
	}
	costSolution = _matDP->getElement(nbItems-1,knapsackBound);
	upperBoundOPT=costSolution;
	KpSolverDP::backtrack();
}

void KpSolverDPv2::solve(){
	
}

void KpSolverDP::printMatrixDP() {

	cout << "print DP matrix : " << endl;

	for(int i = 1; i < nbItems; i++){
		for(int j = 0; j <= knapsackBound; j++) cout <<  _matDP->getElement(i,j) << " "  ;
		cout << endl;
	}
}