#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"
#include <queue>
#include <iostream>
#include <cmath>
#include <set>
#include <stack>






//FUNCIONES AUXILIARES
		//INICIO
//**************************************************************************************************************************************************************************************************
		//CASILLA TRANSITABLE
/**Develve si una ubicacion en el mapa es tramsitable pra el agente*/
bool CasillaTransitable(const ubicacion &x , const vector<vector<unsigned char>> &mapa){
	return (mapa[x.f][x.c] != 'P' and mapa[x.f][x.c] != 'M');	
}


//**************************************************************************************************************************************************************************************************
		//NEXT CASILLA
/**Devuelve la ubicacion siguiente según el avance del agente*/	
ubicacion NextCasilla(const ubicacion &pos){
	ubicacion next = pos;
	
	switch (pos.brujula){
	
		case norte:
			next.f = pos.f -1;
			break;
		case noreste:
			next.f = pos.f -1 ;
			next.c = pos.c +1;
			break;
		case este:
			next.c = pos.c +1;
			break;
		case sureste:
			next.f = pos.f +1;
			next.c = pos.c +1;
			break;
		case sur:
			next.f = pos.f +1;
			break;
		case suroeste:
			next.f = pos.f +1;
			next.c = pos.c -1;
			break;
		case oeste:
			next.c = pos.c -1;
			break;
		case noroeste:
			next.f = pos.f -1;
			next.c = pos.c -1;
			break;
		default:
			break;
	
	}
	return next;
}

//**************************************************************************************************************************************************************************************************
			//APPLY
/** Devuelve el estado que se genera si el agente puede avanzar.
*Si no puede avanzar , se devuelve como salida el mismo estado de entrada.
*/

stateNO apply(const Action &a , const stateNO &st , const vector<vector<unsigned char>> &mapa){
	stateNO st_result = st;
	ubicacion sig_ubicacion;
	switch (a){
		case actFORWARD: //si la casilla es tarnsitable y no esta ocupada por el sonambulo
			sig_ubicacion = NextCasilla(st.jugador);
			if(CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion.f == st.sonambulo.f and sig_ubicacion.c == st.sonambulo.c)){
				st_result.jugador = sig_ubicacion;
			}
			break;
			
		case actTURN_L:
			st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula +6) %8);
			break;
			
		case actTURN_R:
			st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula +2) %8);
			break;
	}
	return st_result;
}




//********************************************************************************************

stateNO applyparaSonambulo(const Action &a , const stateNO &st , const vector<vector<unsigned char>> &mapa){
	stateNO st_result = st;
	ubicacion sig_ubicacion;
	switch(a){
		case actSON_FORWARD: //si la casilla es tarnsitable y no esta ocupada por el sonambulo
			sig_ubicacion = NextCasilla(st.sonambulo);
			if(CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion.f == st.jugador.f and sig_ubicacion.c == st.jugador.c)){
				st_result.sonambulo = sig_ubicacion;
			}
			break;
			
		case actSON_TURN_SL:
			st_result.sonambulo.brujula = static_cast<Orientacion>((st_result.sonambulo.brujula +7) %8);
			break;
			
		case actSON_TURN_SR:
			st_result.sonambulo.brujula = static_cast<Orientacion>((st_result.sonambulo.brujula +1) %8);
			break;
	}
	return st_result;
}


//***************************************************************************************************************************************************************************************************
		//FIND
/** Encuentra si el elemento item está en lista */
bool Find(const stateNO &item , const list<nodeNO> &lista){
	auto it = lista.begin();
	while(it != lista.end() and !(it->st == item)){
		it++;
	}
	return (!(it == lista.end()));

}

//**************************************************************************************************************************************************************************************************
		//ANULAR MATRIZ
/**pone a cero todos los elementos de una matriz*/
void AnularMatriz(vector<vector<unsigned char>> &matriz){
	for(int i = 0 ; i<matriz.size() ; i++){
		for(int j = 0 ; j<matriz[0].size() ; j++){
			matriz[i][j] = 0;
		}
	}
}

//**************************************************************************************************************************************************************************************************
		//COMPROBAR SI ESTA EL SONAMBULO EN LA VISION
bool loVeo(vector<unsigned char> superficie){
	for(int i= 0 ; i<16 ; i++){
		if(superficie[i] == 's'){
			return true;	
		}
	}
	return false;
}

//**************************************************************************************************************************************************************************************************
		//VISUALIZAR PLAN
/**Permite pintar sobre el mapa del simulador el plan partiendo desde el estado st*/

void ComportamientoJugador::VisualizaPlan(const stateNO &st , const list<Action> &plan){
	AnularMatriz(mapaConPlan);
	stateNO cst = st;
	
	auto it = plan.begin();
	while (it != plan.end()){
		switch (*it){
			case actFORWARD:
				cst.jugador = NextCasilla(cst.jugador);
				mapaConPlan[cst.jugador.f][cst.jugador.c] = 1;
			break;
			
			case actTURN_R:
				cst.jugador.brujula = (Orientacion)((cst.jugador.brujula+2)%8);
			break;
			
			case actTURN_L:
				cst.jugador.brujula = (Orientacion)((cst.jugador.brujula+6)%8);
			break;
			
			case actSON_FORWARD:
				cst.sonambulo = NextCasilla(cst.sonambulo);
				mapaConPlan[cst.sonambulo.f][cst.sonambulo.c] = 2;
			break;
			
			case actSON_TURN_SR:
				cst.sonambulo.brujula = (Orientacion)((cst.sonambulo.brujula+1)%8);
			break;
			
			case actSON_TURN_SL:
				cst.sonambulo.brujula = (Orientacion)((cst.sonambulo.brujula+7)%8);
			break;
		}
		it++;
	}
}
//**************************************************************************************************************************************************************************************************
			//REVISAR NODOS

bool revisonNodos( const vector<vector<unsigned char>> &mapa , const ubicacion &posicionJ, const ubicacion &posicionS){
	
	switch(posicionJ.brujula)
	{
	
	case norte:
		if((posicionJ.f -posicionS.f) == 1 and (posicionJ.c -posicionS.c) == 1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 1 and (posicionJ.c -posicionS.c) == 0 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 1 and (posicionJ.c -posicionS.c) == -1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 2 and (posicionJ.c -posicionS.c) == 2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 2 and (posicionJ.c -posicionS.c) == 1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 2 and (posicionJ.c -posicionS.c) == 0 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 2 and (posicionJ.c -posicionS.c) == -2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 2 and (posicionJ.c -posicionS.c) == -1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 3 and (posicionJ.c -posicionS.c) == 3 ){
			return true;
		}
				
		if((posicionJ.f -posicionS.f) == 3 and (posicionJ.c -posicionS.c) == 2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 3 and (posicionJ.c -posicionS.c) == 1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 3 and (posicionJ.c -posicionS.c) == 0 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 3 and (posicionJ.c -posicionS.c) == -2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 3 and (posicionJ.c -posicionS.c) == -1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 3 and (posicionJ.c -posicionS.c) == -3 ){
			return true;
		}
		
		return false;
		break;
		
	case este:
	
		if((posicionJ.f -posicionS.f) == 1 and (posicionJ.c -posicionS.c) == -1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 0 and (posicionJ.c -posicionS.c) == -1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -1 and (posicionJ.c -posicionS.c) == -1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 2 and (posicionJ.c -posicionS.c) == -2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 1 and (posicionJ.c -posicionS.c) == -2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 0 and (posicionJ.c -posicionS.c) == -2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -1 and (posicionJ.c -posicionS.c) == -2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -2 and (posicionJ.c -posicionS.c) == -2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 3 and (posicionJ.c -posicionS.c) == -3 ){
			return true;
		}
				
		if((posicionJ.f -posicionS.f) == 2 and (posicionJ.c -posicionS.c) == -3 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 1 and (posicionJ.c -posicionS.c) == -3 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 0 and (posicionJ.c -posicionS.c) == -3 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -1 and (posicionJ.c -posicionS.c) == -3 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -2 and (posicionJ.c -posicionS.c) == -3 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -3 and (posicionJ.c -posicionS.c) == -3 ){
			return true;
		}
	
		return false;
		break;
	
	case sur:
	
		if((posicionJ.f -posicionS.f) == -1 and (posicionJ.c -posicionS.c) == 1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -1 and (posicionJ.c -posicionS.c) == 0 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -1 and (posicionJ.c -posicionS.c) == -1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -2 and (posicionJ.c -posicionS.c) == 2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -2 and (posicionJ.c -posicionS.c) == 1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -2 and (posicionJ.c -posicionS.c) == 0 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -2 and (posicionJ.c -posicionS.c) == -2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -2 and (posicionJ.c -posicionS.c) == -1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -3 and (posicionJ.c -posicionS.c) == 3 ){
			return true;
		}
				
		if((posicionJ.f -posicionS.f) == -3 and (posicionJ.c -posicionS.c) == 2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -3 and (posicionJ.c -posicionS.c) == 1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -3 and (posicionJ.c -posicionS.c) == 0 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -3 and (posicionJ.c -posicionS.c) == -2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -3 and (posicionJ.c -posicionS.c) == -1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -3 and (posicionJ.c -posicionS.c) == -3 ){
			return true;
		}
	
		return false;
		break;
	case oeste:
	
		if((posicionJ.f -posicionS.f) == 1 and (posicionJ.c -posicionS.c) == 1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 0 and (posicionJ.c -posicionS.c) == 1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -1 and (posicionJ.c -posicionS.c) == 1 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 2 and (posicionJ.c -posicionS.c) == 2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 1 and (posicionJ.c -posicionS.c) == 2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 0 and (posicionJ.c -posicionS.c) == 2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -1 and (posicionJ.c -posicionS.c) == 2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -2 and (posicionJ.c -posicionS.c) == 2 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 3 and (posicionJ.c -posicionS.c) == 3 ){
			return true;
		}
				
		if((posicionJ.f -posicionS.f) == 2 and (posicionJ.c -posicionS.c) == 3 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 1 and (posicionJ.c -posicionS.c) == 3 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == 0 and (posicionJ.c -posicionS.c) == 3 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -1 and (posicionJ.c -posicionS.c) == 3 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -2 and (posicionJ.c -posicionS.c) == 3 ){
			return true;
		}
		
		if((posicionJ.f -posicionS.f) == -3 and (posicionJ.c -posicionS.c) == 3 ){
			return true;
		}
		return false;
		break;
	}
	
}
//*****************************************************************************************************************************************************************************************************
	//CALCULAR CONSUMO
int calcularConsumo( const Action &movimiento , const unsigned char &tipoCasilla, bool zapatillas , bool bikini){

//recto
if(movimiento == actFORWARD){
	
	if(tipoCasilla == 'A'){
		if(bikini){return 10;}
		if(!bikini){return 100;}
	}
	if(tipoCasilla == 'B'){
		if(zapatillas){return 15;}
		if(!zapatillas){return 50;}
	}
	if(tipoCasilla == 'T'){
		return 2;
	}
	return 1;
}
if(movimiento == actTURN_R){
	
	if(tipoCasilla == 'A'){
		if(bikini){return 5;}
		if(!bikini){return 25;}
	}
	if(tipoCasilla == 'B'){
		if(zapatillas){return 1;}
		if(!zapatillas){return 5;}
	}
	if(tipoCasilla == 'T'){
		return 2;
	}
	return 1;
}

if(movimiento == actTURN_L){
	
	if(tipoCasilla == 'A'){
		if(bikini){return 5;}
		if(!bikini){return 25;}
	}
	if(tipoCasilla == 'B'){
		if(zapatillas){return 1;}
		if(!zapatillas){return 5;}
	}
	if(tipoCasilla == 'T'){
		return 2;
	}
	return 1;
}



if(movimiento == actSON_FORWARD){
	
	if(tipoCasilla == 'A'){
		if(bikini){return 10;}
		if(!bikini){return 100;}
	}
	if(tipoCasilla == 'B'){
		if(zapatillas){return 15;}
		if(!zapatillas){return 50;}
	}
	if(tipoCasilla == 'T'){
		return 2;
	}
	return 1;
}
if(movimiento == actSON_TURN_SR){
	
	if(tipoCasilla == 'A'){
		if(bikini){return 2;}
		if(!bikini){return 7;}
	}
	if(tipoCasilla == 'B'){
		if(zapatillas){return 1;}
		if(!zapatillas){return 3;}
	}
	if(tipoCasilla == 'T'){
		return 1;
	}
	return 1;
}

if(movimiento == actSON_TURN_SL){
	
	if(tipoCasilla == 'A'){
		if(bikini){return 2;}
		if(!bikini){return 7;}
	}
	if(tipoCasilla == 'B'){
		if(zapatillas){return 1;}
		if(!zapatillas){return 3;}
	}
	if(tipoCasilla == 'T'){
		return 1;
	}
	return 1;
}
}
//FIN

//**************************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************************
            			//LEVEL0
//**************************************************************************************************************************************************************************************************


list<Action>AnchuraSoloJugador_V3(const stateNO &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa)
{
	nodeNO current_node;
	list<nodeNO> frontier;
	set<nodeNO> explored;
	list<Action> plan;
	current_node.st = inicio;
	bool SolutionFound = (current_node.st.jugador.f == final.f and current_node.st.jugador.c == final.c);
	
		frontier.push_back(current_node);
	
	while(!frontier.empty() and !SolutionFound) 
	{
		frontier.pop_front();
		explored.insert(current_node);
		
		nodeNO child_forward = current_node;
		child_forward.st = apply(actFORWARD, current_node.st,mapa);
		
		if(child_forward.st.jugador.f == final.f and child_forward.st.jugador.c == final.c)
		{
			child_forward.secuencia.push_back(actFORWARD);
			current_node = child_forward;
			SolutionFound = true;
		}
		else if(explored.find(child_forward) == explored.end())
		{
			child_forward.secuencia.push_back(actFORWARD);
			frontier.push_back(child_forward);
		}
		
		if(!SolutionFound)
		{
			nodeNO child_turnl = current_node;
			child_turnl.st = apply(actTURN_L, current_node.st, mapa);
			
			if(explored.find(child_turnl) == explored.end())
			{
				child_turnl.secuencia.push_back(actTURN_L);
				frontier.push_back(child_turnl);
			}
			
			
			nodeNO child_turnr = current_node;
			child_turnr.st = apply(actTURN_R, current_node.st, mapa);
			
			if(explored.find(child_turnr) == explored.end())
			{
				child_turnr.secuencia.push_back(actTURN_R);
				frontier.push_back(child_turnr);
			}
		}
		
		if(!SolutionFound and !frontier.empty())
		{
			current_node = frontier.front();
			while(!frontier.empty() and explored.find(current_node) != explored.end())
			{
				frontier.pop_front();
				if(!frontier.empty()){
				current_node = frontier.front();
				}
			}
		}
	}
	
	if(SolutionFound)
	{
		plan = current_node.secuencia;
	}
	
	
	return plan;
}

//**************************************************************************************************************************************************************************************************
							//LEVEL1
//**************************************************************************************************************************************************************************************************


list<Action>AnchuraSonambuloDestino(const stateNO &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa)
{
list<Action> plan;
bool SolutionFound;
nodeNO current_node;

list<nodeNO> frontier;
set<nodeNO> explored;
current_node.st = inicio;
//int iteracciones = 0 ;

SolutionFound = ((current_node.st.jugador.f == final.f) and (current_node.st.jugador.c == final.c));
			
				frontier.push_back(current_node);
			
			while(!frontier.empty() and !SolutionFound) 
			{
			//iteracciones ++;
			
				frontier.pop_front();
				explored.insert(current_node);
				
				nodeNO child_forward = current_node;
				child_forward.st = apply(actFORWARD, current_node.st,mapa);
				
				if(child_forward.st.jugador.f == final.f and child_forward.st.jugador.c == final.c)
				{
					child_forward.secuencia.push_back(actFORWARD);
					current_node = child_forward;
					//SolutionFound = true;
				}
				else if(explored.find(child_forward) == explored.end())
				{
					child_forward.secuencia.push_back(actFORWARD);
					frontier.push_back(child_forward);
				}
				
				//if(!SolutionFound)
				//{
					nodeNO child_turnl = current_node;
					child_turnl.st = apply(actTURN_L, current_node.st, mapa);
					
					if(explored.find(child_turnl) == explored.end())
					{
						child_turnl.secuencia.push_back(actTURN_L);
						frontier.push_back(child_turnl);
					}
					
					
					nodeNO child_turnr = current_node;
					child_turnr.st = apply(actTURN_R, current_node.st, mapa);
					
					if(explored.find(child_turnr) == explored.end())
					{
						child_turnr.secuencia.push_back(actTURN_R);
						frontier.push_back(child_turnr);
					}
				//}
				
				/*
				if(!SolutionFound and !frontier.empty())
				{
					current_node = frontier.front();
					while(!frontier.empty() and explored.find(current_node) != explored.end())
					{
						frontier.pop_front();
						if(!frontier.empty()){
						current_node = frontier.front();
						}
					}
				}
			}
		    */




if(revisonNodos( mapa , current_node.st.jugador, current_node.st.sonambulo)){

	
	
		   
		

					nodeNO child_forward = current_node;
					child_forward.st = applyparaSonambulo(actSON_FORWARD, current_node.st, mapa);
					
					
					

					if (child_forward.st.sonambulo.f == final.f and child_forward.st.sonambulo.c == final.c)
					{
					    
					    child_forward.secuencia.push_back(actSON_FORWARD);
					    current_node = child_forward;
					    SolutionFound = true;
					}
					
					
					
					
					else if (explored.find(child_forward) == explored.end())
					{
					    
					    child_forward.secuencia.push_back(actSON_FORWARD);
					    frontier.push_back(child_forward);
					}





					if (!SolutionFound)
					{
					    nodeNO child_turnl = current_node;
					    child_turnl.st = applyparaSonambulo(actSON_TURN_SL, current_node.st, mapa);
					    
					    if (explored.find(child_turnl) == explored.end())
					    {
						
						child_turnl.secuencia.push_back(actSON_TURN_SL);
						frontier.push_back(child_turnl);
					    }

					    nodeNO child_turnr = current_node;
					    child_turnr.st = applyparaSonambulo(actSON_TURN_SR, current_node.st, mapa);

					    if (explored.find(child_turnr) == explored.end())
					    {
						
						child_turnr.secuencia.push_back(actSON_TURN_SR);
						frontier.push_back(child_turnr);
					    }
					}
					}
					
					
					
					

					if (!SolutionFound and !frontier.empty())
					{
					    current_node = frontier.front();
					    while (!frontier.empty() and explored.find(current_node) != explored.end())
					    {
						frontier.pop_front();
						if (!frontier.empty())
						{
						    current_node = frontier.front();
						}
					    }
					}
					
				    }
		    
		   

		    
    if (SolutionFound)
    {
        plan = current_node.secuencia;
       // cout<<"Iteracciones: "<<iteracciones<<endl;
       // cout<<"Abiertos: "<<frontier.size()<<endl;
       // cout<<"Cerrados: "<<explored.size()<<endl;
    }


    return plan;
}
	
//**************************************************************************************************************************************************************************************************
									//LEVEL2
//**************************************************************************************************************************************************************************************************

 
list<Action>AnchuraJugadorEficiente(const stateNO &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa)
{
	nodeNObjects current_node;
	priority_queue<nodeNObjects,vector<nodeNObjects>,ordenarConsumosCP> frontier;
	set<nodeNObjects> explored;
	list<Action> plan;
	current_node.nodeObj.st = inicio;
	
	
	frontier.push(current_node);
	
	
	while(!frontier.empty() and !(current_node.nodeObj.st.jugador.f == final.f and current_node.nodeObj.st.jugador.c == final.c ) )
	{
		frontier.pop();
		explored.insert(current_node);
		
		//nodeNObjects child_forward = current_node;
		//child_forward.nodeObj.st = apply(actFORWARD, current_node.nodeObj.st,mapa);
		
		char objeto = mapa[current_node.nodeObj.st.jugador.f][current_node.nodeObj.st.jugador.c];
		
		if(objeto == 'D')
		{
			current_node.tienezapatillas = true;
			current_node.tienebikini = false;
		}
		if(objeto == 'K')
		{
			current_node.tienebikini = true;
			current_node.tienezapatillas = false;
		}
		
		
		
		
		nodeNObjects child_forward = current_node;
		child_forward.nodeObj.st = apply(actFORWARD, current_node.nodeObj.st,mapa);
		
		if(explored.find(child_forward) == explored.end())
			{
				child_forward.nodeObj.secuencia.push_back(actFORWARD);
				//consumo
				child_forward.consumoCasilla +=calcularConsumo(actFORWARD,objeto, current_node.tienezapatillas,current_node.tienebikini);
				frontier.push(child_forward);
			}
		
		
		
		
		
		nodeNObjects child_turnl = current_node;
		child_turnl.nodeObj.st = apply(actTURN_L, current_node.nodeObj.st,mapa);
		
		if(explored.find(child_turnl) == explored.end())
			{
				child_turnl.nodeObj.secuencia.push_back(actTURN_L);
				//consumo
				child_turnl.consumoCasilla +=calcularConsumo(actTURN_L,objeto, current_node.tienezapatillas,current_node.tienebikini);
				frontier.push(child_turnl);
			}
		
		
		
		nodeNObjects child_turnr = current_node;
		child_turnr.nodeObj.st = apply(actTURN_R, current_node.nodeObj.st,mapa);
		
		if(explored.find(child_turnr) == explored.end())
			{
				child_turnr.nodeObj.secuencia.push_back(actTURN_R);
				//consumo
				child_turnr.consumoCasilla +=calcularConsumo(actTURN_R,objeto, current_node.tienezapatillas,current_node.tienebikini);
				frontier.push(child_turnr);
			}
			
			
			
	
		
		if(!frontier.empty())
		{
			current_node = frontier.top();
			
			while(!frontier.empty() and explored.find(current_node)!= explored.end())
			{
				frontier.pop();
				if(!frontier.empty()){
				current_node = frontier.top();
				}
			}
		}
	}
	
	if((current_node.nodeObj.st.jugador.f == final.f and current_node.nodeObj.st.jugador.c == final.c ))
	{
		plan = current_node.nodeObj.secuencia;
	}
	
	
	return plan;
}

//**************************************************************************************************************************************************************************************************
		//LEVEL3
//**************************************************************************************************************************************************************************************************
list<Action>AnchuraSonambuloDestinoEficiente(const stateNO &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa)
{
nodeNObjectsSom current_node;
	priority_queue<nodeNObjectsSom,vector<nodeNObjectsSom>,ordenarConsumosCPSon> frontier;
	set<nodeNObjectsSom> explored;
	list<Action> plan;
	current_node.nodeObj.st = inicio;
	
	
	frontier.push(current_node);
	
	while(!frontier.empty() and !(current_node.nodeObj.st.sonambulo.f == final.f and current_node.nodeObj.st.sonambulo.c == final.c))
	{
		frontier.pop();
		explored.insert(current_node);
		
	
		
		char objeto = mapa[current_node.nodeObj.st.jugador.f][current_node.nodeObj.st.jugador.c];
		
		if(objeto == 'D')
		{
			current_node.tienezapatillas = true;
			current_node.tienebikini = false;
		}
		if(objeto == 'K')
		{
			current_node.tienebikini = true;
			current_node.tienezapatillas = false;
		}
		
		/*
		char objeto2 = mapa[current_node.nodeObj.st.sonambulo.f][current_node.nodeObj.st.sonambulo.c];
		
		if(objeto2 == 'D')
		{
			current_node.tienezapatillasSon = true;
			current_node.tienebikiniSon = false;
		}
		if(objeto2 == 'K')
		{
			current_node.tienebikiniSon = true;
			current_node.tienezapatillasSon = false;
		}
				
		*/
		
		nodeNObjectsSom child_forward = current_node;
		child_forward.nodeObj.st = apply(actFORWARD, current_node.nodeObj.st,mapa);
		
		if(explored.find(child_forward) == explored.end())
			{
				child_forward.nodeObj.secuencia.push_back(actFORWARD);
				//consumo
				child_forward.consumoCasilla +=calcularConsumo(actFORWARD,objeto, current_node.tienezapatillas,current_node.tienebikini);
				frontier.push(child_forward);
			}
		
		
		
		
		
		nodeNObjectsSom child_turnl = current_node;
		child_turnl.nodeObj.st = apply(actTURN_L, current_node.nodeObj.st,mapa);
		
		if(explored.find(child_turnl) == explored.end())
			{
				child_turnl.nodeObj.secuencia.push_back(actTURN_L);
				//consumo
				child_turnl.consumoCasilla +=calcularConsumo(actTURN_L,objeto, current_node.tienezapatillas,current_node.tienebikini);
				frontier.push(child_turnl);
			}
		
		
		
		nodeNObjectsSom child_turnr = current_node;
		child_turnr.nodeObj.st = apply(actTURN_R, current_node.nodeObj.st,mapa);
		
		if(explored.find(child_turnr) == explored.end())
			{
				child_turnr.nodeObj.secuencia.push_back(actTURN_R);
				//consumo
				child_turnr.consumoCasilla +=calcularConsumo(actTURN_R,objeto, current_node.tienezapatillas,current_node.tienebikini);
				frontier.push(child_turnr);
			}
			
	
	
	
	
			
			
	
if(revisonNodos(mapa,current_node.nodeObj.st.jugador, current_node.nodeObj.st.sonambulo)){ 


	
	
		char objeto3 = mapa[current_node.nodeObj.st.sonambulo.f][current_node.nodeObj.st.sonambulo.c];
		
		if(objeto3 == 'D')
		{
			current_node.tienezapatillasSon = true;
			current_node.tienebikiniSon = false;
		}
		if(objeto3 == 'K')
		{
			current_node.tienebikiniSon = true;
			current_node.tienezapatillasSon = false;
		}
		
	
		nodeNObjectsSom child_forward = current_node;
		child_forward.nodeObj.st = applyparaSonambulo(actSON_FORWARD, current_node.nodeObj.st,mapa);
		
		if(explored.find(child_forward) == explored.end())
			{
				child_forward.nodeObj.secuencia.push_back(actSON_FORWARD);
				//consumo
						child_forward.consumoCasilla+=calcularConsumo(actSON_FORWARD,objeto3,
						current_node.tienezapatillasSon,current_node.tienebikiniSon);
				frontier.push(child_forward);
			}
		
		
		
		
		
		nodeNObjectsSom child_turnl = current_node;
		child_turnl.nodeObj.st = applyparaSonambulo(actSON_TURN_SL, current_node.nodeObj.st,mapa);
		
		if(explored.find(child_turnl) == explored.end())
			{
				child_turnl.nodeObj.secuencia.push_back(actSON_TURN_SL);
				//consumo
				child_turnl.consumoCasilla+=calcularConsumo(actSON_TURN_SL,objeto3, current_node.tienezapatillasSon,current_node.tienebikiniSon);
				frontier.push(child_turnl);
			}
		
		
		
		nodeNObjectsSom child_turnr = current_node;
		child_turnr.nodeObj.st = applyparaSonambulo(actSON_TURN_SR, current_node.nodeObj.st,mapa);
		
		if(explored.find(child_turnr) == explored.end())
			{
				child_turnr.nodeObj.secuencia.push_back(actSON_TURN_SR);
				//consumo
				child_turnr.consumoCasilla +=calcularConsumo(actSON_TURN_SR,objeto3, current_node.tienezapatillasSon,current_node.tienebikiniSon);
				frontier.push(child_turnr);
			}
			


 }		
	
	
	
	
	
	
	
		if(!frontier.empty())
		{
			current_node = frontier.top();
			
			while(!frontier.empty() and explored.find(current_node)!= explored.end())
			{
				frontier.pop();
				if(!frontier.empty()){
				current_node = frontier.top();
				}
			}
		}
		
	}
	

		    
		   

		    
 	if((current_node.nodeObj.st.sonambulo.f == final.f and current_node.nodeObj.st.sonambulo.c == final.c ))
	{
		plan = current_node.nodeObj.secuencia;
	}
	

    return plan;
}
	

 
  
//********************************************************************************************

 
 
Action ComportamientoJugador::think(Sensores sensores)
{
	int numero = 0;
	Action accion = actIDLE;
	
	
	
	
	
	if(sensores.nivel != 4)
	{
	
		if(!hayPlan )
			{
			cout << "Calculando un nuevo plan\n";
			c_state.jugador.f = sensores.posF;
			c_state.jugador.c = sensores.posC;
			c_state.jugador.brujula = sensores.sentido;
			c_state.sonambulo.f = sensores.SONposF;
			c_state.sonambulo.c = sensores.SONposC;
			c_state.sonambulo.brujula = sensores.SONsentido;
			goal.f = sensores.destinoF;
			goal.c = sensores.destinoC;
			
			

			
			switch(sensores.nivel)
			{
			case 0:
				plan = AnchuraSoloJugador_V3(c_state, goal, mapaResultado);
				break;
			case 1:
				plan = AnchuraSonambuloDestino(c_state, goal, mapaResultado);
				break;
			case 2:
				plan= AnchuraJugadorEficiente(c_state, goal, mapaResultado);
				//level2
				break;
			case 3:
			plan = AnchuraSonambuloDestinoEficiente(c_state, goal, mapaResultado);
				//level3
				break;
			}
		
			if(plan.size() > 0)
			{
				VisualizaPlan(c_state,plan);
				hayPlan = true;
			
				
			}
			
		}
		
		
		
		
		if(hayPlan and plan.size()>0)
		{
			cout << "Ejecutando la siguiente accion del plan\n";
			accion = plan.front();
			plan.pop_front();
		}
		if(plan.size() == 0 )
		{
			cout << "Se completó el plan\n";
			hayPlan = false;
		}
		
		
		
		
	}
	
	else
	{
	//level4
	}

	

	return accion;
}





int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}
