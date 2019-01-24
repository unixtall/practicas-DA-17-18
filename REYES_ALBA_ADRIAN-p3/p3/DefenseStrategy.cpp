// ###### Config options ################



// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1
#define e_abs 0.01
#define e_rel 0.001 
#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include "cronometro.h"
using namespace Asedio;         

class Cell {
	public:
		Cell():position(Vector3()){};
		Cell(int i, int v = 0, Vector3 p = Vector3()):id(i), value(v),position(Vector3(p.x, p.y)){}
		Vector3 idToPosition(int id, int CellWidth, int nCell) {
			Vector3 ResultPosition;
			int row =  id / nCell;
			int col = id % nCell;
			ResultPosition.x = col * CellWidth + (CellWidth / 2);
			ResultPosition.y = row * CellWidth + (CellWidth / 2);

			return ResultPosition;
		}
		
    	bool operator < (const Cell& c) { return value < c.value;}
		Cell operator = (const Cell &c){
			id = c.id;
			value = c.value;
			position.x = c.position.x;
			position.y = c.position.y;
			
			return *this;
		}

		int value;
		int id;
		Vector3 position;

};

//INICIO ALGORITMO SIN PRE-ORDENACION
void sinPreOrdenacion(Cell** mCell, int nCellsWidth,Cell& cell) {
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
}//FIN ALGORITMO SIN PRE-ORDENACION
float defaultCellValue(int row, int col, int nCellsWidth, int nCellsHeight
    , float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses) {
    	
    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;

    Vector3 cellPosition((col * cellWidth) + cellWidth * 0.5f, (row * cellHeight) + cellHeight * 0.5f, 0);
    	
    float val = 0;
    for (List<Object*>::iterator it=obstacles.begin(); it != obstacles.end(); ++it) {
	    val += _distance(cellPosition, (*it)->position);
    }

    return val;
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

		//if(defensa->id != (*currentDefense)->id){

			if(_distance((*currentDefense)->position, currentCell.position) <= (*currentDefense)->radio + defensa->radio) //Comprobamos con las defensas

				return false;

		currentDefense++;
		//}
	}

 while(currentObstacles != obstacles.end()){
		if(_distance((*currentObstacles)->position, currentCell.position) <= (*currentObstacles)->radio + defensa->radio) //Comprobamos con los obstaculos
			return false;
		currentObstacles++;
	}

	return true;
	
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

void DEF_LIB_EXPORTED placeDefenses3(bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight
              , List<Object*> obstacles, List<Defense*> defenses) {

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight; 
    List<Defense*> defensesPutted;
    List<Cell> listCells(nCellsWidth * nCellsHeight);
	rellenarCells(listCells,cellWidth,nCellsWidth);

	Cell** cell = new Cell*[nCellsWidth];

	for(int i=0; i<nCellsWidth; i++)
		cell[i] = new Cell[nCellsWidth];

	for(int i = 0; i < nCellsWidth; i++)
			for(int j = 0; j < nCellsWidth; j++)
				cell[i][j].value = (int)defaultCellValue(i,j,nCellsWidth,nCellsHeight,mapWidth,mapHeight,obstacles,defenses);
	
	rellenarPosition(cell, cellWidth, nCellsWidth);
	
    /*SIN PRE-ORDENACION*/

    	List<Cell>::iterator currentCell = listCells.begin();	
		List<Defense*>::iterator currentDefense = defenses.begin();

		while(currentDefense != defenses.end() && currentCell != listCells.end()) {
			sinPreOrdenacion(cell,nCellsWidth,(*currentCell));
			if(factible(mapWidth,mapHeight,obstacles,defenses,(*currentDefense),(*currentCell),defensesPutted)){

				(*currentDefense)->position.x = (*currentCell).position.x;
				(*currentDefense)->position.y = (*currentCell).position.y;
				(*currentDefense)->position.z = 0;
				defensesPutted.push_back((*currentDefense));
				++currentDefense;
			}
			++currentCell;
		}

}
