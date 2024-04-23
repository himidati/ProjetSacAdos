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

void MatDPtabTab::computeLineDP(uint row, T costItem, T weightItem){
	for(uint i=0; i<row; i++){
		
	}
}


void MatDPvectVect::computeLineDP(uint row, T costItem, T weightItem){
	for(uint i=0; i<row; i++){
		
	}
}

void MatDPtab::computeLineDP(uint row, T costItem, T weightItem){
	for(uint i=0; i<row; i++){
		
	}
}


void MatDPvect::computeLineDP(uint row, T costItem, T weightItem){
	for(uint i=0; i<row; i++){
		
	}
}