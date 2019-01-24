 // ###### Config options ################

//#define PRINT_DEFENSE_STRATEGY 1    // generate map images

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"

#ifdef PRINT_DEFENSE_STRATEGY
#include "ppm.h"
#endif

#ifdef CUSTOM_RAND_GENERATOR
RAND_TYPE SimpleRandomGenerator::a;
#endif

using namespace Asedio;

class Cell {
	public:
		Cell():position(Vector3()){};
		Cell( int i, int v = 0, Vector3 p = Vector3()):id(i), value(v),position(Vector3(p.x, p.y)){}
		Vector3 idToPosition(int id, int CellWidth, int nCell) {
			Vector3 ResultPosition;
			int row =  id / nCell;
			int col = id % nCell;
			ResultPosition.x = col * CellWidth + (CellWidth / 2);
			ResultPosition.y = row * CellWidth + (CellWidth / 2);

			return ResultPosition;
		}

		int value;
		int id;
		Vector3 position;

};

void cellValueExtractora(Cell** cell, int nCells,int fil,int col) {
	
	int value = 0, value2 = 0, value3 = 0, value4 = 0;
	//Primer cuadrante
		for(int i = 0 ; i < nCells/2; ++i) {
			for(int j = 0; j <nCells/2;++j){
				cell[i][j].value = value;
				value++; 
			}
		value--;
		}

	//Segundo cuadrante
		for(int i = 0 ; i < nCells/2; ++i){
			for(int j = nCells ; j > nCells/2; --j) {
				cell[i][j-1].value = value2;
				value2++;
			}
		value2--;	
		} 
	//Tercer cuadrante
	for(int i = nCells ; i > nCells/2; i--) {
			for(int j = 0; j <nCells/2; j++){
				cell[i-1][j].value = value3;
				value3++; 
			}
		value3--;
	}

	//Cuarto cuadrante
	for(int i = nCells ; i > nCells/2; i--) {
			for(int j = nCells; j > nCells/2; j--){
				cell[i-1][j-1].value = value4;
				value4++; 
			}
		value4--;
	}
	

}
void cellValueDefenses(Cell** cell, int nCells, int fil, int col) {
	
	int value = 0, value2 = 0, value3 = 0, value4 = 0;
	//Primer cuadrante
		for(int i = 0 ; i < nCells/2; ++i) {
			for(int j = 0; j <nCells/2;++j){
				cell[i][j].value = value;
				value++; 
			}
		value--;
		}

	//Segundo cuadrante
		for(int i = 0 ; i < nCells/2; ++i){
			for(int j = nCells ; j > nCells/2; --j) {
				cell[i][j-1].value = value2;
				value2++;
			}
		value2--;	
		} 
	//Tercer cuadrante
	for(int i = nCells ; i > nCells/2; i--) {
			for(int j = 0; j <nCells/2; j++){
				cell[i-1][j].value = value3;
				value3++; 
			}
		value3--;
	}

	//Cuarto cuadrante
	for(int i = nCells ; i > nCells/2; i--) {
			for(int j = nCells; j > nCells/2; j--){
				cell[i-1][j-1].value = value4;
				value4++; 
			}
		value4--;
	}
	

	int cont=0;
	int z = 0;
	for(z=0; z<nCells; ++z){
		if(z == 1){
			cont=100;
			cell[fil][col-z].value = cell[fil][col].value+cont;	
			cell[fil][col+z].value = cell[fil][col].value+cont;
			cell[fil-z][col].value = cell[fil][col].value+cont;
			cell[fil+z][col].value = cell[fil][col].value+cont;
			cell[fil-z][col+z].value = cell[fil][col].value+cont;
			cell[fil-z][col-z].value = cell[fil][col].value+cont;
			cell[fil+z][col+z].value = cell[fil][col].value+cont;
			cell[fil+z][col-z].value = cell[fil][col].value+cont;
		}
		if(z==2){

			cont=80;
			cell[fil][col-z].value = cell[fil][col].value+cont;	
			cell[fil][col+z].value = cell[fil][col].value+cont;
			cell[fil-z][col].value = cell[fil][col].value+cont;
			cell[fil+z][col].value = cell[fil][col].value+cont;
			cell[fil-z][col+z].value = cell[fil][col].value+cont;
			cell[fil-z][col-z].value = cell[fil][col].value+cont;
			cell[fil+z][col+z].value = cell[fil][col].value+cont;
			cell[fil+z][col-z].value = cell[fil][col].value+cont;
			cell[fil-1][col+z].value = cell[fil][col].value+cont;
			cell[fil-1][col-z].value = cell[fil][col].value+cont;
			cell[fil+1][col+z].value = cell[fil][col].value+cont;
			cell[fil+1][col-z].value = cell[fil][col].value+cont;
			cell[fil-z][col+1].value = cell[fil][col].value+cont;
			cell[fil-z][col-1].value = cell[fil][col].value+cont;
			cell[fil+z][col+1].value = cell[fil][col].value+cont;
			cell[fil+z][col-1].value = cell[fil][col].value+cont;

		}
		if(z == 3){

			cont=70;
			cell[fil][col-z].value = cell[fil][col].value+cont;	
			cell[fil][col+z].value = cell[fil][col].value+cont;
			cell[fil-z][col].value = cell[fil][col].value+cont;
			cell[fil+z][col].value = cell[fil][col].value+cont;
			cell[fil-z][col+z].value = cell[fil][col].value+cont;
			cell[fil-z][col-z].value = cell[fil][col].value+cont;
			cell[fil+z][col+z].value = cell[fil][col].value+cont;
			cell[fil+z][col-z].value = cell[fil][col].value+cont;
			cell[fil-1][col+z].value = cell[fil][col].value+cont;
			cell[fil-1][col-z].value = cell[fil][col].value+cont;
			cell[fil+1][col+z].value = cell[fil][col].value+cont;
			cell[fil+1][col-z].value = cell[fil][col].value+cont;
			cell[fil-z][col+1].value = cell[fil][col].value+cont;
			cell[fil-z][col-1].value = cell[fil][col].value+cont;
			cell[fil+z][col+1].value = cell[fil][col].value+cont;
			cell[fil+z][col-1].value = cell[fil][col].value+cont;
			cell[fil-2][col+z].value = cell[fil][col].value+cont;
			cell[fil-2][col-z].value = cell[fil][col].value+cont;
			cell[fil+2][col+z].value = cell[fil][col].value+cont;
			cell[fil+2][col-z].value = cell[fil][col].value+cont;
			cell[fil-z][col+2].value = cell[fil][col].value+cont;
			cell[fil-z][col-2].value = cell[fil][col].value+cont;
			cell[fil+z][col+2].value = cell[fil][col].value+cont;
			cell[fil+z][col-2].value = cell[fil][col].value+cont;
		}
	}
	
}

//funcion externa para rellenar las celdas
void rellenarCells(List<Cell> &listCells, float CellWidth, int nCell) {
int identificador = 0;
	List<Cell>::iterator iCell = listCells.begin();
	while(iCell != listCells.end()) {
		(*iCell).id = identificador;
		(*iCell).position = (*iCell).idToPosition(identificador, CellWidth, nCell);

		iCell++;identificador++;
	}

}

//funcion externa para rellenar las posiciones de la matriz
void rellenarPosition(Cell** cell, int CellWidth, int nCell) {
int identificador = 0;
	for(int i = 0; i < nCell; i++)
		for(int j = 0; j < nCell; j++){
		cell[i][j].id = identificador;
		cell[i][j].position = cell[i][j].idToPosition(identificador, CellWidth, nCell);
	
	identificador++;
		}
}



//FUNCION SELECCION
void selectCell(Cell** mCell, int nCellsWidth,Cell& cell){
	int maximo = 0;
	int x,z;
	for(int i = 0; i < nCellsWidth; i++)
		for(int j = 0; j < nCellsWidth; j++){
			if(mCell[i][j].value > maximo){
				maximo = mCell[i][j].value;
				cell.id = mCell[i][j].id;
				cell.position = mCell[i][j].position;
				x = i;
				z = j;
			}
		}
	
			mCell[x][z].value = -1;
}

//FUNCION FACTIBILIDAD

bool factible(float mapWidth,float mapHeight, std::list<Object*> obstacles, std::list<Defense*> defenses,
                Defense* defensa,Cell currentCell, List<Defense*> defensesPutted) {
	List<Defense*>::iterator currentDefense = defensesPutted.begin();
	List<Object*>::iterator currentObstacles = obstacles.begin();
	//Comprobamos que no se salga del mapa
	if((currentCell.position.x - defensa->radio) < 0 || (currentCell.position.x + defensa->radio  >= mapWidth)||(currentCell.position.y - defensa->radio) < 0 || (currentCell.position.y + defensa->radio ) >= mapHeight)
				return false;

	while(currentDefense != defensesPutted.end()){

		if(defensa->id != (*currentDefense)->id){

			if(_distance((*currentDefense)->position, currentCell.position) <= (*currentDefense)->radio + defensa->radio) //Comprobamos con las defensas

				return false;

		currentDefense++;
		}
	}

 while(currentObstacles != obstacles.end()){
		if(_distance((*currentObstacles)->position, currentCell.position) <= (*currentObstacles)->radio + defensa->radio) //Comprobamos con los obstaculos
			return false;
		currentObstacles++;
	}

	return true;
	
}


void DEF_LIB_EXPORTED placeDefenses(bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight
              , std::list<Object*> obstacles, std::list<Defense*> defenses) {
	bool flag = false;
    float cellWidth = mapWidth / nCellsWidth;
   	List<Cell> listCells(nCellsWidth * nCellsHeight);
	List<Defense*> defensesPutted;
	List<Cell>::iterator currentCell = listCells.begin();
	List<Defense*>::iterator itDefensesPutted = defensesPutted.begin();
	List<Defense*>::iterator currentExtraction = defenses.begin();
	int col, fil;

	rellenarCells(listCells,cellWidth,nCellsWidth);

	Cell** cell = new Cell*[nCellsWidth];

	for(int i=0; i<nCellsWidth; i++)
		cell[i] = new Cell[nCellsWidth];
		
	rellenarPosition(cell, cellWidth, nCellsWidth);

/*PARA LA EXTRACTORA*/
	cellValueExtractora(cell, nCellsWidth,fil,col);
	while(currentCell != listCells.end() && flag == false) {
		selectCell(cell,nCellsWidth,(*currentCell));
		if(factible(mapWidth,mapHeight,obstacles,defenses,(*currentExtraction),(*currentCell),defensesPutted)) {

		    flag = true;
		    (*currentExtraction)->position.x = (*currentCell).position.x;
		    (*currentExtraction)->position.y = (*currentCell).position.y;
		    (*currentExtraction)->position.z = 0;
		   	fil = (*currentCell).id / nCellsWidth;
		   	col = (*currentCell).id % nCellsWidth;
		    defensesPutted.push_front(*currentExtraction);


		}

		++currentCell;
	}

/*PARA LAS DEFENSAS*/
	cellValueDefenses(cell, nCellsWidth,fil,col);
List<Defense*>::iterator currentDefense = ++defenses.begin();
	currentCell = listCells.begin();
    while(currentDefense != defenses.end() && currentCell != listCells.end()) {
    	selectCell(cell,nCellsWidth,(*currentCell));
		if(factible(mapWidth,mapHeight,obstacles,defenses,(*currentDefense),(*currentCell),defensesPutted)) {
		    (*currentDefense)->position.x = (*currentCell).position.x;
		    (*currentDefense)->position.y = (*currentCell).position.y;
		    (*currentDefense)->position.z = 0;
		    defensesPutted.push_back(*currentDefense);
			++currentDefense;

		}

		++currentCell;

    }


#ifdef PRINT_DEFENSE_STRATEGY

    float** cellValues = new float* [nCellsHeight]; 
    for(int i = 0; i < nCellsHeight; ++i) {
       cellValues[i] = new float[nCellsWidth];
       for(int j = 0; j < nCellsWidth; ++j) {
           cellValues[i][j] = ((int)(cellValue(i, j))) % 256;
       }
    }
    dPrintMap("strategy.ppm", nCellsHeight, nCellsWidth, cellHeight, cellWidth, freeCells
                         , cellValues, std::list<Defense*>(), true);

    for(int i = 0; i < nCellsHeight ; ++i)
        delete [] cellValues[i];
	delete [] cellValues;
	cellValues = NULL;

#endif
}
