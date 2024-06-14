//********* nodeBB.cpp *********

#include "nodeBB.hpp"


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


void NodeBB::primalHeuristic(uint kpBound, uint nbItems, vector<uint> & weights,  vector<uint> & values) {

	uint poidsDansSac = 0;

	localLowerBound = 0;
	primalSolution.resize(nbItems);

	for(uint i=0; i < nbItems; i++) {
		uint placeRestante = kpBound - poidsDansSac;
		if (weights[i] <= placeRestante) {
			localLowerBound += values[i];
			poidsDansSac += weights[i];
			primalSolution[i] = 1;
		} else {
			primalSolution[i] = 0;
		}
	}
 }



void NodeBB::solveUpperBound(uint kpBound, uint nbItems, vector<uint> & weights,  vector<uint> & values) {

	double poidsDansSac = 0;

	localUpperBound=0;


	double poidsObjetsFixes = 0;
	for (uint i=0; i < nbItems; i++) {
		if (isFixed[i]) {
			poidsObjetsFixes += weights[i];
			localUpperBound += values[i];
		}
	}

	poidsDansSac = poidsObjetsFixes;

	if (poidsObjetsFixes > kpBound) overCapacitated = true;
	else {
		for (uint i=0; i < nbItems; i++) {
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


