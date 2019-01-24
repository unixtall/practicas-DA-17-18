// ###### Config options ################


// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"

using namespace Asedio;



void getVectors(std::list<Defense*> defenses, unsigned int* costs, float* media) {
	std::list<Defense*>::iterator itDefenses = defenses.begin();
	int i = 0;

	while(itDefenses != defenses.end()){
			media[i] = (((*itDefenses)->range +(*itDefenses)->dispersion + (*itDefenses)->damage + (*itDefenses)->attacksPerSecond + (*itDefenses)->health) / 5);
			costs[i] = (*itDefenses)->cost;
			++itDefenses;
			++i;
	}
	
}


void DEF_LIB_EXPORTED selectDefenses(std::list<Defense*> defenses, unsigned int ases, std::list<int> &selectedIDs
            , float mapWidth, float mapHeight, std::list<Object*> obstacles) {
	
	std::list<Defense*>::iterator extractor = defenses.begin();
    selectedIDs.push_back((*extractor)->id);
    ases -= (*extractor)->cost;
    defenses.erase(extractor);
	
	float* media = new float[defenses.size()];
	unsigned int* costs = new unsigned int[defenses.size()];
	
	
    float** matriz = new float*[defenses.size()];
    for(int j = 0; j < defenses.size(); ++j)
    	matriz[j] = new float[ases];
   
   getVectors(defenses,costs,media);
   
   for(unsigned int j = 0; j < ases; j++) {
   		if(j < costs[0])
   			matriz[0][j] = 0;		
   		else
   			matriz[0][j] = media[0];
   	}
   	
   
	for(unsigned int i = 1; i < defenses.size(); ++i)
		for(unsigned int j = 0; j < ases; ++j){
			if(j < costs[i])
				matriz[i][j] = matriz[i-1][j];
			else
				matriz[i][j] = std::max(matriz[i-1][j], matriz[i-1][j - costs[i]] + media[i]);
		}	
	
	int i = defenses.size() - 1;
	unsigned int j = ases-1;
    std::list<Defense*>::iterator it = --defenses.end() ;
   
    while(i > 0 && j > 0) {

        if(matriz[i][j] != matriz[i-1][j]) {
            selectedIDs.push_back((*it)->id);
            j -= (*it)->cost;
            i--;
            it--; 
        }else{
            i--;
            it--;
        }
      
    }    
}
