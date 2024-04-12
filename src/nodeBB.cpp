//********* nodeBB.cpp *********

#include "nodeBB.hpp"
//#include <iostream>
//#include <fstream>

bool NodeBB::canBeRemoved() {
	return overCapacitated;
}

void NodeBB::init(int size){
	overCapacitated= false;

	isFixed.resize(size);
	isRemoved.resize(size);

	for(int i=0; i<size;i++){
		isFixed[i] = false;
		isRemoved[i] = false;
	}


    criticalIndex=-1;
    fractionalVariable=0;
    localLowerBound=0;
}


void NodeBB::primalHeuristic(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values) {

	int poidsDansSac = 0;

	localLowerBound = 0;
	primalSolution.resize(nbItems);

	for(int i=0; i < nbItems; i++) {
		int placeRestante = kpBound - poidsDansSac;
		if (weights[i] <= placeRestante) {
			localLowerBound += values[i];
			poidsDansSac += weights[i];
			primalSolution[i] = 1;
		} else {
			primalSolution[i] = 0;
		}
	}
 }



void NodeBB::solveUpperBound(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values) {

	double poidsDansSac = 0;

	localUpperBound=0;


	double poidsObjetsFixes = 0;
	for (int i=0; i < nbItems; i++) {
		if (isFixed[i]) {
			poidsObjetsFixes += weights[i];
			localUpperBound += values[i];
		}
	}

	poidsDansSac = poidsObjetsFixes;

	if (poidsObjetsFixes > kpBound) overCapacitated = true;
	else {
		for (int i=0; i < nbItems; i++) {
			double placeRestante = kpBound - poidsDansSac;
			if (isFixed[i] or isRemoved[i]) {
				continue;
			} else if (weights[i] <= placeRestante) {
				localUpperBound += values[i];
				poidsDansSac += weights[i];
			} else {
				criticalIndex = i;
				fractionalVariable = ((float) placeRestante /  (float) weights[i]);

				localUpperBound += fractionalVariable * values[i];
				//poidsDansSac += placeRestante;
				break;
			}	
		}
	}
 }


