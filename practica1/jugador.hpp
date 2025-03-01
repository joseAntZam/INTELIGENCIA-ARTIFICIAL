#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H
#include "comportamientos/comportamiento.hpp"
using namespace std;

struct state{
	int fil;
	int col;
	Orientacion brujula;
};

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      current_state.fil = current_state.col = 99;
      current_state.brujula = norte;
      last_action = actIDLE;
      girar_derecha = false;
      bien_situado = false;
      tengozapatillas = false;
      tengobikini = false;
      posicionamiento = false;
      pasos = 0;
      
      
      
     
    }
     
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
  
  // Declarar aquí las variables de estado
  state current_state; //nos permite recordar donde estoy(cuando no hay sensores) y hacia donde voy
  Action last_action; //Ultima accion que ralicé.
  bool girar_derecha;
  bool bien_situado;
  bool tengozapatillas;
  bool tengobikini;
  bool posicionamiento;
  int pasos;
  
  
  
  
  
};

#endif
