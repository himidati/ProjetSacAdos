//********* knapsackGreedy.cpp *********

#include "KpSolverGreedy.hpp"



void KpSolverGreedy::solve() {
	solveUpperBound();
	solveLowerBound();
}

//TODO: calcul de relaxation continue, c'est le glouton ou un objet peut etre fractionaire
// seule la valeur du sac a dos continu est gardee, sauvegardee dans upperBoundOPT, pas la composition du sac a dos continu

void KpSolverGreedy::solveUpperBound() {

	double poidsDansSac = 0;
	upperBoundOPT = 0;

	for (int i=0; i < nbItems; i++) {
		if (weights[i] <= (knapsackBound - poidsDansSac)) {
			upperBoundOPT += values[i];
			poidsDansSac += weights[i];
		} else {
			upperBoundOPT += ((float)(knapsackBound - poidsDansSac) / (float) weights[i]) * values[i];
			poidsDansSac += (knapsackBound - poidsDansSac);
			break;
		}
	}
 }

//TODO: resolution de borne inferieure: algorithme glouton "discret", qui donne une borne inferieure a mettre a jour dans costSolution
// et une composition du sac a dos a ecrire dans le vector<bool> solution heritee de la classe mere

void KpSolverGreedy::solveLowerBound() {

	int poidsDansSac = 0;
	costSolution = 0;

	solution.resize(nbItems);
	for (int i = 0; i < nbItems; i++) {
		if (weights[i] <= knapsackBound - poidsDansSac) {
			costSolution += values[i];
			poidsDansSac += weights[i];
			solution[i] = 1;
		} else {
			solution[i] = 0;
		}
	}
 }
