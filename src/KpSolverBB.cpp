#include "KpSolverBB.hpp"
#include "KpSolverDP.hpp"
#include <math.h>
#include <stdlib.h>
#include <time.h>

std::unique_ptr<NodeBB> RandomBranchingStrategy::selectNode() {

	  srand (time(NULL));

	  int n = nodes.size() ;
	  int id= rand() % n ;

	  swap(nodes[0],nodes[id]);
	cout<<"node front: "<<nodes.front().get();
	std::unique_ptr<NodeBB> node = std::make_unique<NodeBB>();
	node=std::move(nodes.front());
	nodes.pop_front();
	return node;

}


std::unique_ptr<NodeBB> BestBoundBranchingStrategy::selectNode(){
	std::sort(nodes.begin(), nodes.end(),
			[](std::unique_ptr<NodeBB> & i, std::unique_ptr<NodeBB> & j) {return i->getNodeUpperBound() < j->getNodeUpperBound();}
	);
	std::unique_ptr<NodeBB> nod = std::move(nodes.back());
	nodes.pop_back();
	return nod;
}

std::unique_ptr<NodeBB> BFSBranchingStrategy::selectNode(){
	std::unique_ptr<NodeBB> node = std::move(nodes.front());
	nodes.pop_front();
	return node;
}


std::unique_ptr<NodeBB> EndBranchingStrategy::selectNode(){
	std::unique_ptr<NodeBB> nod = std::move(nodes.back());
	nodes.pop_back();
	return nod;
}

std::unique_ptr<NodeBB> DFSBranchingStrategy::selectNode(){
	std::unique_ptr<NodeBB> nod = std::move(nodes.back());
	nodes.pop_back();
	return nod;
}

void BranchingStrategy::init(){
    nbNodes= 0;
    nodes.clear();
    std::unique_ptr<NodeBB> node0 = std::make_unique<NodeBB>();
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

    nodes.push_back(std::move(node0));

    if(!withDPinitPrimalHeuristic) return;

}

void BranchingStrategy::solve(){
    init();
	
	while (!nodes.empty() && nbNodes < nbMaxNodeBB	) {
		nbNodes ++;

		std::unique_ptr<NodeBB> currentNode = std::move(selectNode());

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
			//delete currentNode;
			continue;
		}

		//verification de la borne sup
		if(currentNode->getNodeUpperBound() <= costSolution + 0.99) {
			//delete currentNode;
			continue;
		}

		int crit = currentNode->getCriticalIndex();//recupere l'index de la variable critique
		if(crit < nbItems) {
			std::unique_ptr<NodeBB> nod1 = std::make_unique<NodeBB>(*currentNode);//noeud 1 --> variable critique fixée
			nod1->fixVariable(crit, true);

			std::unique_ptr<NodeBB> nod2 = std::make_unique<NodeBB>(*currentNode);//noeud 2 --> variable critique removed
			nod2->fixVariable(crit, false);

			nod1->solveUpperBound(knapsackBound, nbItems, weights, values);
			nod2->solveUpperBound(knapsackBound, nbItems, weights, values);
			
			insertNodes(std::move(nod1), std::move(nod2));
		}
	}
	getUpperBound();

}

void BranchingStrategy::insertNode(std::unique_ptr<NodeBB> nod){
    if ((nod->canBeRemoved()) || nod->getNodeUpperBound()<costSolution + 1) {
		//delete nod;
	}
	else nodes.push_back(std::move(nod));
}

void BranchingStrategy::insertNodes(std::unique_ptr<NodeBB>nod1, std::unique_ptr<NodeBB>nod2){
	if(_type==BranchingStrategies::BFS){
		insertNode(std::move(nod1));
		insertNode(std::move(nod2));
	}else{
		insertNode(std::move(nod2));
		insertNode(std::move(nod1));
	}
}

void BranchingStrategy::reset(){
    switch (_type)
    {
    case  BranchingStrategies::BestBound : 
        _branchingStrategy=std::make_unique<BestBoundBranchingStrategy>(_filename);
        break;
    case BranchingStrategies::DFS01 :
        _branchingStrategy=std::make_unique<DFSBranchingStrategy>(_filename);
        break;
    case BranchingStrategies::BFS :
        _branchingStrategy=std::make_unique<BFSBranchingStrategy>(_filename);

    case BranchingStrategies::End :
       _branchingStrategy=std::make_unique<EndBranchingStrategy>(_filename);
        
    case BranchingStrategies::Random :
        _branchingStrategy=std::make_unique<RandomBranchingStrategy>(_filename);
        
    case BranchingStrategies::DFS10 :
        _branchingStrategy=std::make_unique<DFSBranchingStrategy>(_filename);       
    default :
        _branchingStrategy= std::make_unique<RandomBranchingStrategy>(_filename);
        break;
    }
}

double BranchingStrategy::getUpperBound() {
	upperBoundOPT=costSolution;
	for (std::deque<std::unique_ptr<NodeBB>>::iterator it = nodes.begin() ; it != nodes.end(); ++it)
		upperBoundOPT=max(upperBoundOPT,(*it)->getNodeUpperBound());
	return upperBoundOPT;
}


void BranchingStrategy::printStatus() {
	getUpperBound();
	cout  << "nbNodes: " << nbNodes;
	cout  << " remaining Nodes: " << nodes.size();
	cout  << " LB: " << costSolution;
	cout  << " UB: " << (long) floor(upperBoundOPT);
	cout << " gap : " << (floor(upperBoundOPT)- (double)costSolution) /( (double)costSolution) * 100 << "%" << endl;
}
