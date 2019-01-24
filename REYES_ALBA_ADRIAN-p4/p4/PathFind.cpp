// ###### Config options ################

#define PRINT_PATHS 1

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"


#ifdef PRINT_PATHS
#include "ppm.h"
#endif

using namespace Asedio;


bool comparar(AStarNode* A, AStarNode* B){
    if(A->F < B->F)
		return true;
    else
		return false;
}

Vector3 cellCenterToPosition(int i, int j, float cellWidth, float cellHeight){ 
    return Vector3((j * cellWidth) + cellWidth * 0.5f, (i * cellHeight) + cellHeight * 0.5f, 0); 
}

void DEF_LIB_EXPORTED calculateAdditionalCost(float** additionalCost
                   , int cellsWidth, int cellsHeight, float mapWidth, float mapHeight
                   , List<Object*> obstacles, List<Defense*> defenses) {

    float cellWidth = mapWidth / cellsWidth;
    float cellHeight = mapHeight / cellsHeight;

    for(int i = 0 ; i < cellsHeight ; ++i) {
        for(int j = 0 ; j < cellsWidth ; ++j) {
            Vector3 cellPosition = cellCenterToPosition(i, j, cellWidth, cellHeight);
            float cost = 0;
            if( (i+j) % 2 == 0 ) {
                cost = cellWidth * 100;
            }
            
            additionalCost[i][j] = cost;
        }
    }
}

void DEF_LIB_EXPORTED calculatePath(AStarNode* originNode, AStarNode* targetNode
                   , int cellsWidth, int cellsHeight, float mapWidth, float mapHeight
                   , float** additionalCost, std::list<Vector3> &path) {
	float cellWidth = mapWidth / cellsWidth;
	float cellHeight = mapHeight / cellsHeight;
    std::vector<AStarNode*> abierto, cerrado;
    AStarNode* current = originNode;
    current->H = _sdistance(current->position,targetNode->position);
    current->F = current->G+current->H;
    abierto.push_back(current);
    std::make_heap(abierto.begin(),abierto.end(),comparar);
    bool found = false;

    while(!found && abierto.size() > 0){
        current=abierto.front();
        std::pop_heap(abierto.begin(),abierto.end(),comparar);
        abierto.pop_back();
        cerrado.push_back(current);
      
        if(current == targetNode)
            found = true;
        else{
            for(List<AStarNode*>::iterator it=current->adjacents.begin(); it != current->adjacents.end(); it++){
                if(cerrado.end()==std::find(cerrado.begin(),cerrado.end(),(*it))){
                    if(abierto.end()==std::find(abierto.begin(),abierto.end(),(*it))){
                        int cx = (*it)->position.x/cellWidth;
                        int cy = (*it)->position.y/cellHeight;
                        (*it)->parent = current;
                        (*it)->G = current->G + _distance(current->position,(*it)->position) + additionalCost[cx][cy];
                        (*it)->H = _sdistance((*it)->position,targetNode->position);
                        (*it)->F = (*it)->G + (*it)->H;
                        abierto.push_back(*it);
                        std::make_heap(abierto.begin(),abierto.end(),comparar);
                    }
                    else{
                        float d = _distance(current->position,(*it)->position);
                        if((*it)->G > current->G + d){
                            (*it)->parent = current;
                            (*it)->G = current->G + d;
                            (*it)->F = (*it)->G + (*it)->H;
                            std::sort_heap(abierto.begin(),abierto.end(),comparar);
                        }
                    }
                }
            }
        }
    }
    current = targetNode;
    path.push_front(current->position);

    while(current->parent != originNode){
        current = current->parent;
        path.push_front(current->position);
    }


}
