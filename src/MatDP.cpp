#include"MatDP.hpp"

MatDPtabTab::MatDPtabTab(uint nbRow, uint nbCol): MatDP(nbRow, nbCol) {
    _matrixDP = new T* [nbRow];
	for(uint i = 0; i < nbRow; i++){
		_matrixDP[i] = new T [nbCol+1];
		for(uint j = 0; j <= nbCol; j++)
			_matrixDP[i][j]=0;
	}
}

MatDPtabTab::~MatDPtabTab(){
    for(uint i = 0; i < nbRows; i++){
		delete [] _matrixDP[i];
	}
	delete [] _matrixDP;
}


MatDPtab::MatDPtab(uint nbRow, uint nbCol): MatDP(nbRow, nbCol){
    _matrixDP=new T[nbRow*nbCol];
    for(uint i=0;i<nbRow*nbCol; i++){
        _matrixDP[i]=0;
    }
}

MatDPtab::~MatDPtab(){
    delete[] _matrixDP;
}

void MatDPtabTab::computeLineDP(uint row, T costItem, T weightItem) {
    for (uint m = 1; m <= nbColumns; ++m) {
        _matrixDP[row][m] = _matrixDP[row-1][m];
        if (m >= weightItem) {
            _matrixDP[row][m] = max(_matrixDP[row-1][m], _matrixDP[row-1][m-weightItem] + costItem);
        }
    }
}

void MatDPvectVect::computeLineDP(uint row, T costItem, T weightItem){
	for (uint m = 1; m <= nbColumns; ++m) {
        _matrixDP[row][m] = _matrixDP[row-1][m];
        if (m >= weightItem) {
            _matrixDP[row][m] = max(_matrixDP[row-1][m], _matrixDP[row-1][m-weightItem] + costItem);
        }
    }
}

void MatDPtab::computeLineDP(uint row, T costItem, T weightItem){
	
}


void MatDPvect::computeLineDP(uint row, T costItem, T weightItem){
	
}