//********* kpSolverBB.cpp *********

#include "kpSolverBB.hpp"
#include "KpSolverDP.hpp"
#include <math.h>
#include <stdlib.h>
#include <time.h>


int KpSolverBB::getUpperBound() {
	upperBoundOPT=costSolution;
	for (std::deque<NodeBB*>::iterator it = nodes.begin() ; it != nodes.end(); ++it)
		upperBoundOPT=max(upperBoundOPT,(*it)->getNodeUpperBound());
	return upperBoundOPT;
}


void KpSolverBB::printStatus() {
	getUpperBound();
	cout  << "nbNodes: " << nbNodes;
	cout  << " remaining Nodes: " << nodes.size();
	cout  << " LB: " << costSolution;
	cout  << " UB: " << (long) floor(upperBoundOPT);
	cout << " gap : " << (floor(upperBoundOPT)- (double)costSolution) /( (double)costSolution) * 100 << "%" << endl;
}

void KpSolverBB::init() {
    nbNodes= 0;
    nodes.clear();
    NodeBB* node0 = new NodeBB();
    node0->init(nbItems);
    node0->solveUpperBound(knapsackBound, nbItems, weights, values);
	getUpperBound();
    if (withPrimalHeuristics) {
    	node0->primalHeuristic(knapsackBound, nbItems, weights, values);
    	costSolution=node0->getNodePrimalBound();
    	node0->copyPrimalSolution(&solution);
    }
    else {
    	costSolution=0;
    	solution.resize(nbItems);
    	for (int i = 0; i < nbItems; i++) solution[i]=false;
    }

    nodes.push_back(node0);

    if(!withDPinitPrimalHeuristic) return;


}

NodeBB* KpSolverBB::selectNodeRandom() {

	  srand (time(NULL));

	  int n = nodes.size() ;
	  int id= rand() % n ;

	  swap(nodes[0],nodes[id]);

	NodeBB* node = nodes.front();
	nodes.pop_front();
	return node;

}

NodeBB* KpSolverBB::selectNode() {

	if(branchingStrategy == Random) return selectNodeRandom();

	if(branchingStrategy == BestBound){
	std::sort(nodes.begin(), nodes.end(),
			[](NodeBB* i, NodeBB* j) {return i->getNodeUpperBound() < j->getNodeUpperBound();}
	);
	}

	if(branchingStrategy == BFS){ 	//parcours en largeur
		NodeBB* node = nodes.front();
		nodes.pop_front();
		return node;
	}

	NodeBB* nod = nodes.back();
	nodes.pop_back();
	return nod;
}

void KpSolverBB::insertNode(NodeBB *nod) {

	if ((nod->canBeRemoved()) || nod->getNodeUpperBound()<costSolution + 1) {
		delete nod;
	}
	else nodes.push_back(nod);
}

void KpSolverBB::insertNodes(NodeBB *nod1, NodeBB *nod2) {

	if(branchingStrategy == DFS01) {	//parcours en profondeur
		insertNode(nod1);
		insertNode(nod2);
	}
	else {
		insertNode(nod2);
		insertNode(nod1);
	}
}




void KpSolverBB::solve() {

	init();
	
	while (!nodes.empty() && nbNodes < nbMaxNodeBB	) {
		nbNodes ++;

		NodeBB* currentNode = selectNode();

		//primalHeuristics
		if(withPrimalHeuristics || currentNode->getFractionalVariable() == 0) {

			currentNode->primalHeuristic(knapsackBound, nbItems, weights, values);
			
			if (currentNode->getNodePrimalBound() > costSolution) {			
				costSolution = currentNode->getNodePrimalBound();															//remplacer le lowerbound
				currentNode->copyPrimalSolution(&solution);																	//remplacer la solution (composition du sac)
			}
		}

		//verification overCapacited
		if(currentNode->canBeRemoved()) {
			delete currentNode;
			continue;
		}

		//verification de la borne sup
		if(currentNode->getNodeUpperBound() <= costSolution + 0.99) {
			delete currentNode;
			continue;
		}


		int crit = currentNode->getCriticalIndex();																			//recupere l'index de la variable critique
		if(crit < nbItems) {
			NodeBB* nod1 = new NodeBB(*currentNode);																		//noeud 1 --> variable critique fixée
			nod1->fixVariable(crit, true);

			NodeBB* nod2 = new NodeBB(*currentNode);																		//noeud 2 --> variable critique removed
			nod2->fixVariable(crit, false);

			nod1->solveUpperBound(knapsackBound, nbItems, weights, values);
			nod2->solveUpperBound(knapsackBound, nbItems, weights, values);
			
			insertNodes(nod1, nod2);
		}

		delete currentNode;
	
	}
	getUpperBound();

}
