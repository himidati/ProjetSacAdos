//********* kpSolver.hpp *********

#ifndef KPSOLVER_HPP
#define KPSOLVER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class KpSolver {

private:

    void sortKnapsack();
        // Reads instance data. 
    void importInstance(const string& fileName);

protected:
    // Items and knapsack properties.
    uint nbItems; // Number of items.
    vector<uint> weights; //weights of items
    vector<uint> values; //values of items
    unsigned long knapsackBound;     // Knapsack bound

    // Solution (items in the knapsack).
    vector<bool> solution;
    unsigned long costSolution;
    double upperBoundOPT;
    std::string _filename;

public:

    KpSolver(std::string const & filename) : _filename(filename) {importInstance(filename);}

    ~KpSolver()=default;

    void printKnapsackInstance();
    void printKnapsackSolution(bool printSol);
    void reindexMemo(bool sortMode);

	int getUpperBound(){return upperBoundOPT;};
	int getSolutionCost(){return costSolution;};
	bool isSelected(int item){return solution[item];};

	//void exportSubInstance(string& fileName, int id1, int id2, float propFactor);
	void extractSubInstance(int idMin, int idMax);

    void clearInstance();

	int getNbItems() const {return nbItems;	};
};

#endif

