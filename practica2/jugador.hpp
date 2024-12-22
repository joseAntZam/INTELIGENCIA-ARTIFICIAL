#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"


#include <list>
#include <algorithm>
using namespace std;


/*
struct ubicacion{
	int f; 
	int c;
	orientacion brujula;
	
	bool operator==(const ubicacion &ub)const{
		return (f == ub.f and c == ub.c and brujula == ub.brujula);
	}
	};
*/




struct stateNO{
	ubicacion jugador;
	ubicacion sonambulo;
	
	bool operator== (const stateNO &x) const{
		if(jugador==x.jugador and sonambulo.f == x.sonambulo.f and sonambulo.c == x.sonambulo.c){
		return true;
	}
	else{
		return false;
	}
	}

};




struct nodeNO
{

	stateNO st;
	list<Action> secuencia;
	
	bool operator == (const nodeNO &n) const{
		return (st == n.st);
	}
	
	bool operator<(const nodeNO &n) const{
		if(st.jugador.f < n.st.jugador.f){
			return true;
		}
		else if(st.jugador.f == n.st.jugador.f and st.jugador.c < n.st.jugador.c){
			return true;
		}
		else if(st.jugador.f == n.st.jugador.f and st.jugador.c == n.st.jugador.c and st.jugador.brujula < n.st.jugador.brujula){
			return true;
		}
		else if(st.jugador.f == n.st.jugador.f and st.jugador.c == n.st.jugador.c and st.jugador.brujula == n.st.jugador.brujula and st.sonambulo.f < n.st.sonambulo.f){
			return true;
		}
		else if( st.jugador.f == n.st.jugador.f and st.jugador.c == n.st.jugador.c and st.jugador.brujula == n.st.jugador.brujula and st.sonambulo.f == n.st.sonambulo.f and st.sonambulo.c < n.st.sonambulo.c){
			return true;
		}
		else if(st.jugador.f == n.st.jugador.f and st.jugador.c == n.st.jugador.c and st.jugador.brujula == n.st.jugador.brujula and st.sonambulo.f == n.st.sonambulo.f and st.sonambulo.c == n.st.sonambulo.c and st.sonambulo.brujula < n.st.sonambulo.brujula){
			return true;
		}
		else{
			return false;
		}
	}
};



struct nodeNObjects
{
	
	int consumoCasilla; 
	bool tienebikini = false , tienezapatillas = false;
	nodeNO nodeObj; //objeto del nodo anterior

	
	bool operator == (const nodeNObjects &n) const{
		return (nodeObj.st == n.nodeObj.st);
	}
	
	
	bool operator<(const nodeNObjects &n) const{
		if(nodeObj.st.jugador.f < n.nodeObj.st.jugador.f){
			return true;
		}
		else if(nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c < n.nodeObj.st.jugador.c){
			return true;
		}
		else if(nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c == n.nodeObj.st.jugador.c and nodeObj.st.jugador.brujula < n.nodeObj.st.jugador.brujula){
			return true;
		}
		else if(tienezapatillas < n.tienezapatillas and nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c == n.nodeObj.st.jugador.c and nodeObj.st.jugador.brujula == n.nodeObj.st.jugador.brujula){
			return true;
		}
		
		else if(tienebikini < n.tienebikini and tienezapatillas == n.tienezapatillas and nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c == n.nodeObj.st.jugador.c and nodeObj.st.jugador.brujula == n.nodeObj.st.jugador.brujula){
			return true;
		}

		else{
			return false;
		}
	}
};



struct nodeNObjectsSom
{
	
	int consumoCasilla; 
	bool tienebikini = false , tienezapatillas = false;
	bool tienebikiniSon = false , tienezapatillasSon = false;
	nodeNO nodeObj; //objeto del nodo anterior


	bool operator<(const nodeNObjectsSom &n) const{
		if(nodeObj.st.jugador.f < n.nodeObj.st.jugador.f){
			return true;
		}
		else if(nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c < n.nodeObj.st.jugador.c){
			return true;
		}
		else if(nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c == n.nodeObj.st.jugador.c and nodeObj.st.jugador.brujula < n.nodeObj.st.jugador.brujula){
			return true;
		}
		else if(tienezapatillas < n.tienezapatillas and nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c == n.nodeObj.st.jugador.c and nodeObj.st.jugador.brujula == n.nodeObj.st.jugador.brujula){
			return true;
		}
		
		else if(tienebikini < n.tienebikini and tienezapatillas == n.tienezapatillas and nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c == n.nodeObj.st.jugador.c and nodeObj.st.jugador.brujula == n.nodeObj.st.jugador.brujula){
			return true;
		}

		
		else if( tienebikini == n.tienebikini and tienezapatillas == n.tienezapatillas and nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c == n.nodeObj.st.jugador.c and nodeObj.st.jugador.brujula == n.nodeObj.st.jugador.brujula and nodeObj.st.sonambulo.f < n.nodeObj.st.sonambulo.f){
			return true;
		}
		else if(tienebikini == n.tienebikini and tienezapatillas == n.tienezapatillas and nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c == n.nodeObj.st.jugador.c and nodeObj.st.jugador.brujula == n.nodeObj.st.jugador.brujula and nodeObj.st.sonambulo.f == n.nodeObj.st.sonambulo.f and nodeObj.st.sonambulo.c < n.nodeObj.st.sonambulo.c){
			return true;
		}
		else if(tienebikini == n.tienebikini and tienezapatillas == n.tienezapatillas and nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c == n.nodeObj.st.jugador.c and nodeObj.st.jugador.brujula == n.nodeObj.st.jugador.brujula and nodeObj.st.sonambulo.f == n.nodeObj.st.sonambulo.f and nodeObj.st.sonambulo.c == n.nodeObj.st.sonambulo.c and nodeObj.st.sonambulo.brujula < n.nodeObj.st.sonambulo.brujula){
			return true;
		}
		else if(tienebikini == n.tienebikini and tienezapatillas == n.tienezapatillas and nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c == n.nodeObj.st.jugador.c and nodeObj.st.jugador.brujula == n.nodeObj.st.jugador.brujula and nodeObj.st.sonambulo.f == n.nodeObj.st.sonambulo.f and nodeObj.st.sonambulo.c == n.nodeObj.st.sonambulo.c and nodeObj.st.sonambulo.brujula == n.nodeObj.st.sonambulo.brujula and tienezapatillasSon < n.tienezapatillasSon){
			return true;
		}
		
		else if(tienebikini == n.tienebikini and tienezapatillas == n.tienezapatillas and nodeObj.st.jugador.f == n.nodeObj.st.jugador.f and nodeObj.st.jugador.c == n.nodeObj.st.jugador.c and nodeObj.st.jugador.brujula == n.nodeObj.st.jugador.brujula and nodeObj.st.sonambulo.f == n.nodeObj.st.sonambulo.f and nodeObj.st.sonambulo.c == n.nodeObj.st.sonambulo.c and nodeObj.st.sonambulo.brujula == n.nodeObj.st.sonambulo.brujula and tienezapatillasSon == n.tienezapatillasSon and tienebikiniSon < n.tienebikiniSon){
			return true;
		}
		else{
			return false;
		}
		
	}
	
};



struct ordenarConsumosCP{
	bool operator()( const nodeNObjects &n , const nodeNObjects &n2){
		return n.consumoCasilla > n2.consumoCasilla;
	}
};

struct ordenarConsumosCPSon{
	bool operator()( const nodeNObjectsSom &n , const nodeNObjectsSom &n2){
		return n.consumoCasilla > n2.consumoCasilla;
	}
};





class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      hayPlan = false;
      conseguido = false;
      conseguidoSonambulo = false;
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      hayPlan = false;
      conseguido = false;
      conseguidoSonambulo = false;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}
    void VisualizaPlan(const stateNO &st , const list<Action> &plan);
    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    


  private:
    // Declarar Variables de Estado

	list<Action>plan;
	bool hayPlan;
	stateNO c_state;
	ubicacion goal;
	bool conseguido;
	bool conseguidoSonambulo;
	Action last;



};

#endif
