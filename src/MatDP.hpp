#pragma once

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

using T=uint;

class MatDP {
    
protected:
    uint nbRows;
    uint nbColumns;

public:

    MatDP(uint nbRow, uint nbCol): nbRows(nbRow), nbColumns(nbCol) {};
    virtual ~MatDP(){};


	virtual T getElement(uint row, uint col)=0;
	virtual void setElement(uint row, uint col, double val)=0; //{matrix[nbColumns * row+col]=val;};
    virtual T* operator[](int row)=0;
    virtual void computeLineDP(uint row, T costItem, T weightItem)=0;
    //virtual void display()=0; // TODo: a l'ecran et sur un flux

};


class MatDPvectVect  : public MatDP  {
private:

    vector<vector<T>> _matrixDP;

public:
    MatDPvectVect(uint nbRow, uint nbCol)
        : MatDP(nbRow,nbCol), _matrixDP(nbRow, vector<T>(nbCol+1, 0)){}
    ~MatDPvectVect() = default;

    T *operator[](int row) override { return _matrixDP[row].data(); }; //transforme le vecteur en pointeur
    T getElement(uint row, uint col) override { return _matrixDP[row][col]; };
    void setElement(uint row, uint col, double val) override { _matrixDP[row][col] = val; };
    void computeLineDP(uint row, T costItem, T weightItem) override;
};

class MatDPvect : public MatDP  {

private:

    vector<T> _matrixDP;

public:
    MatDPvect(uint nbRow, uint nbCol)
        : MatDP(nbRow,nbCol), _matrixDP(nbColumns*nbRow, 0){}
    ~MatDPvect() = default;

    T *operator[](int row) override { return &_matrixDP[nbColumns * row]; };
    T getElement(uint row, uint col) override { return _matrixDP[nbColumns * row + col]; };
    void setElement(uint row, uint col, double val) override { _matrixDP[nbColumns * row + col] = val; };
    void computeLineDP(uint row, T costItem, T weightItem) override;
};

class MatDPtabTab  : public MatDP  {

private:
    T** _matrixDP;

public:
    MatDPtabTab(uint nbRow, uint nbCol);
    ~MatDPtabTab();                     

    T *operator[](int row) override { return _matrixDP[row]; };
    T getElement(uint row, uint col) override { return _matrixDP[row][col]; };
    void setElement(uint row, uint col, double val) override { _matrixDP[row][col] = val; };
    void computeLineDP(uint row, T costItem, T weightItem) override;
};

class MatDPtab : public MatDP  {
private:
    T* _matrixDP;

public:
    MatDPtab(uint nbRow, uint nbCol);
    ~MatDPtab();

    T *operator[](int row) override { return &_matrixDP[nbColumns * row]; };
    T getElement(uint row, uint col) override { return _matrixDP[nbColumns * row + col]; };
    void setElement(uint row, uint col, double val) override { _matrixDP[nbColumns * row + col] = val; };
    void computeLineDP(uint row, T costItem, T weightItem) override;
};