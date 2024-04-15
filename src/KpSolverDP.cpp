//********* kpSolverDP.hpp *********

#include "KpSolverDP.hpp"


#include <omp.h>
#include "KpSolver.hpp"


void KpSolverDP::setMemoizedVersion(bool memoizedVersion) {
	this->memoizedVersion = memoizedVersion;
}


void KpSolverDP::setVerboseMode(bool verbosemode){
	this->verboseMode = verbosemode;
}

void KpSolverDP::solve() {
//	if (verboseMode) cout << "create  DP matrix " << endl;
	createMatrixDP();
//	if (verboseMode) cout << " DP matrix created " << endl;
//	if (verboseMode) cout << "fill first column DP matrix " << endl;
	fillFirstColumnDP();
//	if (verboseMode) cout << "first column DP matrix filled" << endl;

//	if (verboseMode) cout << "fill  DP matrix : " << endl;

	/*if (memoizedVersion) costSolution = solveMemoized(nbItems-1,knapsackBound);
	else*/ solveIter();

//	if (verboseMode) cout << " DP matrix filled: " << endl;
	upperBoundOPT = costSolution ;
	if (verboseMode) cout << "solution cost by DP: "  << costSolution << endl;
//	if (verboseMode) cout << "print DP matrix :" << endl;
	if (verboseMode) printMatrixDP();
//	if (verboseMode) cout << "backtrack operations:" << endl;
	backtrack();
//	if (verboseMode) cout << "backtrack operations achieved:" << endl;

//	if (verboseMode) cout << "delete DP matrix : " << endl;
	deleteMatrixDP();
//	if (verboseMode) cout << "DP matrix deleted: " << endl;
}

void TabDynDP::createMatrixDP(){
	_matrixDP = new T* [nbItems];
	for(int i = 0; i < nbItems; i++){
		_matrixDP[i] = new T [knapsackBound+1];
		for(int j = 0; j <= knapsackBound; j++)
			if (memoizedVersion)  _matrixDP[i][j] =-1;
			else _matrixDP[i][j] =0;
	}
}

void TabDynDP::deleteMatrixDP(){
	for(int i = 0; i < nbItems; i++){
		delete [] _matrixDP[i];
	}
	delete [] _matrixDP;

}

void TabDynDP::solveIter(){
	for(int i=1; i < nbItems; i++) {
		for (int m=1; m < knapsackBound+1; m++) {
			_matrixDP[i][m] = getValueAT(i-1,m);
			if (m >= weights[i]) {
				_matrixDP[i][m] = max(getValueAT(i,m), getValueAT(i-1,m-weights[i]) + values[i]);
			}
		}
	}

	costSolution = getValueAT(nbItems-1,knapsackBound);
}

void TabDynDP::printMatrixDP() {

	cout << "print DP matrix : " << endl;

	for(int i = 0; i < nbItems; i++){
		for(int j = 0; j <= knapsackBound; j++) cout <<  getValueAT(i,j) << " "  ;
		cout << endl;
	}
}

void TabDynDP::backtrack() {

	solution.resize(nbItems, false); //initialise tout le vecteur à "false" (ou 0)

	int m = knapsackBound;
	for (int n=nbItems-1; n > 0; n--) {
		if (getValueAT(n,m) != getValueAT(n-1,m)) {
			solution[n] = 1;
			m = m - weights[n];
		}
	}
}

void TabDynDP::fillFirstColumnDP(){
	for(int m = 0; m <= knapsackBound; m++) if (m <weights[0]) _matrixDP[0][m] =0; else _matrixDP[0][m] =values[0];
}

void TabDynDP::solveIterParallel(){
	for (int i = 1; i < nbItems; i++) {
		#pragma omp parallel for
	    for (int m = 1; m <= knapsackBound; m++) {
	    	_matrixDP[i][m] =  getValueAT(i-1,m);
	             if (weights[i] <= m){
	            	 _matrixDP[i][m] = max(values[i] + getValueAT(i-1,m - weights[i]),  getValueAT(i-1,m));
	             }
	        }

	    }

	costSolution = _matrixDP[nbItems-1][knapsackBound];
}


void MatCarreDP::createMatrixDP(){
	_matrixDP=vector<vector<T>>(nbItems,vector<T>(knapsackBound+1));
	for(int i = 0; i < nbItems; i++){
		for(int j = 0; j <= knapsackBound; j++)
			_matrixDP[i][j] =0;
	}
}


void KpSolverDP::updateKpSolverDP(vector<int> & newWeights,	vector<int> & newValues, int newBound) {

	this->parallelizedVersion = true;
	this->memoizedVersion = false;
	this->verboseMode=false;

	this->knapsackBound = newBound;

	weights.clear();
	values.clear();

	weights = newWeights;
	values = newValues;

    nbItems = weights.size();

}


void MatCarreDP::solveIterParallel() {
/*
#pragma omp parallel for collapse(2)
for (int i = 1; i < nbItems; i++) {
    for (int m = 1; m <= knapsackBound; m++) {
    	matrixDP[i-1][m]=-1;
    }
}

	omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
	{
		int id, i;
		id = omp_get_thread_num();
		for (i = 1; i < nbItems; i++) {
		    for (int m = 1+id; m <= knapsackBound; m=m+NUM_THREADS) {
		    	while(matrixDP[i-1][m] <0) {};
		    	matrixDP[i][m] =  matrixDP[i-1][m];
		             if (weights[i] <= m){
		     	    	while(matrixDP[i-1][m - weights[i]] <0) {};
		            	 matrixDP[i][m] = max(values[i] + matrixDP[i-1][m - weights[i]],  matrixDP[i-1][m]);
		             }
		        }

		    }

	}
*/

	for (int i = 1; i < nbItems; i++) {
		#pragma omp parallel for
	    for (int m = 1; m <= knapsackBound; m++) {
	    	_matrixDP[i][m] =  getValueAT(i-1,m);
	             if (weights[i] <= m){
	            	 _matrixDP[i][m] = max(values[i] + getValueAT(i-1,m - weights[i]),  getValueAT(i-1,m));
	             }
	        }

	    }

	costSolution = _matrixDP[nbItems-1][knapsackBound];
}


void MatCarreDP::deleteMatrixDP(){
	for(int i=0; i<nbItems; i++){
		_matrixDP[i].pop_back();
	}
	_matrixDP.pop_back();
}

void MatCarreDP::fillFirstColumnDP(){
	for(int m = 0; m <= knapsackBound; m++) if (m <weights[0]) _matrixDP[0][m] =0; else _matrixDP[0][m] =values[0];
}

void MatCarreDP::solveIter() {

	for(int i=1; i < nbItems; i++) {
		for (int m=1; m < knapsackBound+1; m++) {
			_matrixDP[i][m] = getValueAT(i-1,m);
			if (m >= weights[i]) {
				_matrixDP[i][m] = max(getValueAT(i,m), getValueAT(i-1,m-weights[i]) + values[i]);
			}
		}
	}

	costSolution = _matrixDP[nbItems-1][knapsackBound];

}

void MatCarreDP::backtrack() {

	solution.resize(nbItems, false); //initialise tout le vecteur à "false" (ou 0)

	int m = knapsackBound;
	for (int n=nbItems-1; n > 0; n--) {
		if (_matrixDP[n][m] != _matrixDP[n-1][m]) {
			solution[n] = 1;
			m = m - weights[n];
		}
	}
}

void MatCarreDP::printMatrixDP() {

	cout << "print DP matrix : " << endl;

	for(int i = 0; i < nbItems; i++){
		for(int j = 0; j <= knapsackBound; j++) cout <<  _matrixDP[i][j] << " "  ;
		cout << endl;
	}
}


int TabDynDP::solveMemoized(int i , int m) {

	 if (_matrixDP[i][m] > -1)  return _matrixDP[i][m];

	 if (m < weights[i] ) _matrixDP[i][m] =  solveMemoized(i-1,m);
	 else _matrixDP[i][m] = max(solveMemoized(i-1,m), values[i] + solveMemoized(i-1,m - weights[i]));

     return _matrixDP[i][m];
}



void ListAdjtDP::solveIter(){
	for(int i=1; i < nbItems; i++) {
		for (int m=1; m < knapsackBound+1; m++) {
			_matrixDP[i*(knapsackBound+1)+m] = getValueAT(i-1,m);
			if (m >= weights[i]) {
				_matrixDP[i*(knapsackBound+1)+m] = max(getValueAT(i,m), getValueAT(i-1,m-weights[i]) + values[i]);
			}
		}
	}

	costSolution = getValueAT(nbItems-1,knapsackBound);
}

void ListAdjtDP::backtrack(){
	solution.resize(nbItems, false); //initialise tout le vecteur à "false" (ou 0)

	int m = knapsackBound;
	for (int n=nbItems-1; n > 0; n--) {
		if (_matrixDP[n*(knapsackBound+1)+m] != _matrixDP[(n-1)*(knapsackBound+1)+m]) {
			solution[n] = 1;
			m = m - weights[n];
		}
	}
}

void ListAdjtDP::printMatrixDP() {

	cout << "print DP matrix : " << endl;

	for(int i = 0; i < nbItems; i++){
		for(int j = 0; j <= knapsackBound; j++) cout << getValueAT(i,j) << " "  ;
		cout << endl;
	}
}

void ListAdjtDP::fillFirstColumnDP(){
	for(int m = 0; m <= knapsackBound; m++) 
		if (m <weights[0]) 
			setValue(0,m,0);
		else setValue(0,m,values[0]);
}

void ListAdjtDP::solveIterParallel(){
	for (int i = 1; i < nbItems; i++) {
		#pragma omp parallel for
	    for (int m = 1; m <= knapsackBound; m++) {
	    	_matrixDP[i*(knapsackBound+1)+m] =  getValueAT(i-1,m);
	             if (weights[i] <= m){
	            	 _matrixDP[i*(knapsackBound+1)+m] = max(values[i] + getValueAT(i-1,m - weights[i]),  getValueAT(i-1,m));
	             }
	        }
	    }
	costSolution = _matrixDP[(nbItems-1)+knapsackBound];
}

void ListAdjtDP::deleteMatrixDP(){
	_matrixDP.pop_back();
}

void ListAdjtDP::createMatrixDP(){

}