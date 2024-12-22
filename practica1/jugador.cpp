


#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;





void Precipicios(vector<vector<unsigned char>> & matriz){
	
	for(int i=0;i<3;++i){
		for(int p=0;p<matriz.size();++p){
			matriz[i][p]='P';
		}
		
	
		for(int p=0;p<matriz.size();++p){
			matriz[matriz.size()-1-i][p]='P';
		}
		
	
		for(int p=0;p<matriz.size();++p){
			matriz[p][matriz.size()-1-i]='P';
		}
		
	
		for(int p=0;p<matriz.size();++p){
			matriz[p][i]='P';
		}
	}
	
}










void PonerTerrenoEnMatriz(const vector<unsigned char>&terreno , const state &st , vector<vector<unsigned char>> & matriz ){






	if(st.brujula == norte){
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil-1][st.col-1] = terreno[1];
		matriz[st.fil-1][st.col] = terreno[2];
		matriz[st.fil-1][st.col+1] = terreno[3];
		matriz[st.fil-2][st.col-2] = terreno[4];
		matriz[st.fil-2][st.col-1] = terreno[5];
		matriz[st.fil-2][st.col] = terreno[6];
		matriz[st.fil-2][st.col+1] = terreno[7];
		matriz[st.fil-2][st.col+2] = terreno[8];
		matriz[st.fil-3][st.col-3] = terreno[9];
		matriz[st.fil-3][st.col-2] = terreno[10];
		matriz[st.fil-3][st.col-1] = terreno[11];
		matriz[st.fil-3][st.col] = terreno[12];
		matriz[st.fil-3][st.col+1] = terreno[13];
		matriz[st.fil-3][st.col+2] = terreno[14];
		matriz[st.fil-3][st.col+3] = terreno[15];
	
	}
	
	if(st.brujula == noreste){
	
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil-1][st.col] = terreno[1];
		matriz[st.fil-1][st.col+1] = terreno[2];
		matriz[st.fil][st.col+1] = terreno[3];
		matriz[st.fil-2][st.col] = terreno[4];
		matriz[st.fil-2][st.col+1] = terreno[5];
		matriz[st.fil-2][st.col+2] = terreno[6];
		matriz[st.fil-1][st.col+2] = terreno[7];
		matriz[st.fil][st.col+2] = terreno[8];
		matriz[st.fil-3][st.col] = terreno[9];
		matriz[st.fil-3][st.col+1] = terreno[10];
		matriz[st.fil-3][st.col+2] = terreno[11];
		matriz[st.fil-3][st.col+3] = terreno[12];
		matriz[st.fil-2][st.col+3] = terreno[13];
		matriz[st.fil-1][st.col+3] = terreno[14];
		matriz[st.fil][st.col+3] = terreno[15];
		
	}
	if(st.brujula == este){
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil-1][st.col+1] = terreno[1];
		matriz[st.fil][st.col+1] = terreno[2];
		matriz[st.fil+1][st.col+1] = terreno[3];
		matriz[st.fil-2][st.col+2] = terreno[4];
		matriz[st.fil-1][st.col+2] = terreno[5];
		matriz[st.fil][st.col+2] = terreno[6];
		matriz[st.fil+1][st.col+2] = terreno[7];
		matriz[st.fil+2][st.col+2] = terreno[8];
		matriz[st.fil-3][st.col+3] = terreno[9];
		matriz[st.fil-2][st.col+3] = terreno[10];
		matriz[st.fil-1][st.col+3] = terreno[11];
		matriz[st.fil][st.col+3] = terreno[12];
		matriz[st.fil+1][st.col+3] = terreno[13];
		matriz[st.fil+2][st.col+3] = terreno[14];
		matriz[st.fil+3][st.col+3] = terreno[15];
	}
	if(st.brujula == sureste){
	
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil][st.col+1] = terreno[1];
		matriz[st.fil+1][st.col+1] = terreno[2];
		matriz[st.fil+1][st.col] = terreno[3];
		matriz[st.fil][st.col+2] = terreno[4];
		matriz[st.fil+1][st.col+2] = terreno[5];
		matriz[st.fil+2][st.col+2] = terreno[6];
		matriz[st.fil+2][st.col+1] = terreno[7];
		matriz[st.fil+2][st.col] = terreno[8];
		matriz[st.fil][st.col+3] = terreno[9];
		matriz[st.fil+1][st.col+3] = terreno[10];
		matriz[st.fil+2][st.col+3] = terreno[11];
		matriz[st.fil+3][st.col+3] = terreno[12];
		matriz[st.fil+3][st.col+2] = terreno[13];
		matriz[st.fil+3][st.col+1] = terreno[14];
		matriz[st.fil+3][st.col] = terreno[15];
		
	}
	if(st.brujula == sur){
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil+1][st.col+1] = terreno[1];
		matriz[st.fil+1][st.col] = terreno[2];
		matriz[st.fil+1][st.col-1] = terreno[3];
		matriz[st.fil+2][st.col+2] = terreno[4];
		matriz[st.fil+2][st.col+1] = terreno[5];
		matriz[st.fil+2][st.col] = terreno[6];
		matriz[st.fil+2][st.col-1] = terreno[7];
		matriz[st.fil+2][st.col-2] = terreno[8];
		matriz[st.fil+3][st.col+3] = terreno[9];
		matriz[st.fil+3][st.col+2] = terreno[10];
		matriz[st.fil+3][st.col+1] = terreno[11];
		matriz[st.fil+3][st.col] = terreno[12];
		matriz[st.fil+3][st.col-1] = terreno[13];
		matriz[st.fil+3][st.col-2] = terreno[14];
		matriz[st.fil+3][st.col-3] = terreno[15];
	}
	if(st.brujula == suroeste){
	
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil+1][st.col] = terreno[1];
		matriz[st.fil+1][st.col-1] = terreno[2];
		matriz[st.fil][st.col-1] = terreno[3];
		matriz[st.fil+2][st.col] = terreno[4];
		matriz[st.fil+2][st.col-1] = terreno[5];
		matriz[st.fil+2][st.col-2] = terreno[6];
		matriz[st.fil+1][st.col-2] = terreno[7];
		matriz[st.fil][st.col-2] = terreno[8];
		matriz[st.fil+3][st.col] = terreno[9];
		matriz[st.fil+3][st.col-1] = terreno[10];
		matriz[st.fil+3][st.col-2] = terreno[11];
		matriz[st.fil+3][st.col-3] = terreno[12];
		matriz[st.fil+2][st.col-3] = terreno[13];
		matriz[st.fil+1][st.col-3] = terreno[14];
		matriz[st.fil][st.col-3] = terreno[15];
		
	}
	if(st.brujula == oeste){
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil+1][st.col-1] = terreno[1];
		matriz[st.fil][st.col-1] = terreno[2];
		matriz[st.fil-1][st.col-1] = terreno[3];
		matriz[st.fil+2][st.col-2] = terreno[4];
		matriz[st.fil+1][st.col-2] = terreno[5];
		matriz[st.fil][st.col-2] = terreno[6];
		matriz[st.fil-1][st.col-2] = terreno[7];
		matriz[st.fil-2][st.col-2] = terreno[8];
		matriz[st.fil+3][st.col-3] = terreno[9];
		matriz[st.fil+2][st.col-3] = terreno[10];
		matriz[st.fil+1][st.col-3] = terreno[11];
		matriz[st.fil][st.col-3] = terreno[12];
		matriz[st.fil-1][st.col-3] = terreno[13];
		matriz[st.fil-2][st.col-3] = terreno[14];
		matriz[st.fil-3][st.col-3] = terreno[15];
	}
	if(st.brujula == noroeste){
	
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil][st.col-1] = terreno[1];
		matriz[st.fil-1][st.col-1] = terreno[2];
		matriz[st.fil-1][st.col] = terreno[3];
		matriz[st.fil][st.col-2] = terreno[4];
		matriz[st.fil-1][st.col-2] = terreno[5];
		matriz[st.fil-2][st.col-2] = terreno[6];
		matriz[st.fil-2][st.col-1] = terreno[7];
		matriz[st.fil-2][st.col] = terreno[8];
		matriz[st.fil][st.col-3] = terreno[9];
		matriz[st.fil-1][st.col-3] = terreno[10];
		matriz[st.fil-2][st.col-3] = terreno[11];
		matriz[st.fil-3][st.col-3] = terreno[12];
		matriz[st.fil-3][st.col-2] = terreno[13];
		matriz[st.fil-3][st.col-1] = terreno[14];
		matriz[st.fil-3][st.col] = terreno[15];
		
	}


}

Action ComportamientoJugador::think(Sensores sensores){
if (sensores.nivel == 0){
posicionamiento = true;
}

	Action accion = actIDLE;
	int a;

	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC << " ";
	switch(sensores.sentido){
		case 0: cout << "Norte" << endl; break;
		case 1: cout << "Noreste" << endl; break;
		case 2: cout << "Este" << endl; break;
		case 3: cout << "Sureste" << endl; break;
		case 4: cout << "Sur " << endl; break;
		case 5: cout << "Suroeste" << endl; break;
		case 6: cout << "Oeste" << endl; break;
		case 7: cout << "Noroeste" << endl; break;
	}
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << endl;
	
	if(sensores.reset==true){
		bien_situado=false;
		posicionamiento = false;
		tengobikini = false;
		tengozapatillas = false;
	}
	
	switch (last_action){
	
		case actFORWARD:
			// Actualización en caso de avanzar
			switch (current_state.brujula){
				case norte: current_state.fil--; break;
				case noreste: current_state.fil--; current_state.col++; break;
				case este: current_state.col++; break;
				case sureste: current_state.fil++; current_state.col++; break;
				case sur: current_state.fil++; break;
				case suroeste: current_state.fil++; current_state.col--;break;
				case oeste: current_state.col--; break;
				case noroeste: current_state.fil--; current_state.col--; break;
			}
			break;
		case actTURN_SL:
			a = current_state.brujula;
			a = (a+7)%8;
			current_state.brujula = static_cast<Orientacion>(a);
			break;
		case actTURN_SR:
			a = current_state.brujula;
			a = (a+1)%8;
			current_state.brujula = static_cast<Orientacion>(a);
			break;
		case actTURN_BL:
			a = current_state.brujula;
			a = (a + 5)%8;
			current_state.brujula = static_cast<Orientacion>(a);
			// Actualización de girar 135º a la izquierda
			break;
		case actTURN_BR:
			a = current_state.brujula;
			a = (a + 3)%8;
			current_state.brujula = static_cast<Orientacion>(a);
			// Actualización en caso de girar 135º a la derecha
			break;
	}


	if (sensores.posF !=-1 && sensores.posC !=-1 && !bien_situado){
		current_state.fil = sensores.posF;
		current_state.col= sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
	}
	
	

	
	Precipicios(mapaResultado);
	
	
	
	if (bien_situado && posicionamiento){
		PonerTerrenoEnMatriz(sensores.terreno, current_state, mapaResultado);
	}


//Modificado

if(sensores.superficie[2] == 'l' && sensores.superficie[1] == 'l' && sensores.superficie[3] == 'l' && sensores.superficie[4] == 'l' && sensores.superficie[5] == 'l' && sensores.superficie[6] == 'l' && sensores.superficie[7] == 'l' && sensores.superficie[8] == 'l'  &&     sensores.superficie[9] == 'l' && sensores.superficie[10] == 'l' && sensores.superficie[11] == 'l' && sensores.superficie[12] == 'l' && sensores.superficie[13] == 'l' && sensores.superficie[14] == 'l' && sensores.superficie[15] == 'l' ){
   accion == actTURN_BR;
}



 else if(sensores.terreno[0] == 'X' && sensores.bateria<5000){
	accion == actIDLE;

}





/*

else if(((sensores.terreno[2] == 'K' && !tengobikini ) || (sensores.terreno[2] == 'D' && !tengozapatillas) || (sensores.terreno[2] == 'X'&& sensores.bateria<5000 )||
  	 (sensores.terreno[2] == 'G' && !posicionamiento ))  ){
  	 	
  	 		if(sensores.terreno[2] == 'K'){tengobikini = true;}
 			if(sensores.terreno[2] == 'D'){tengozapatillas = true;}
 			if(sensores.terreno[2] == 'G'){posicionamiento = true;}
 			accion = actFORWARD;
 			
 }
 else if(((sensores.terreno[6] == 'K' && !tengobikini ) || (sensores.terreno[6] == 'D' && !tengozapatillas) || (sensores.terreno[6] == 'X'&& sensores.bateria<5000 )||
  	 (sensores.terreno[6] == 'G' && !posicionamiento ))  ){
 	
 			accion = actFORWARD;
 			
 }
 else if(((sensores.terreno[12] == 'K' && !tengobikini ) || (sensores.terreno[12] == 'D' && !tengozapatillas) || (sensores.terreno[12] == 'X'&& sensores.bateria<5000 )||
  	 (sensores.terreno[12] == 'G' && !posicionamiento ))  ){
 	
 			accion = actFORWARD;
 			
 }
 



*/





else if(((sensores.terreno[1] == 'K' && !tengobikini ) || (sensores.terreno[1] == 'D' && !tengozapatillas) || (sensores.terreno[1] == 'X'&& sensores.bateria<5000 )||
  	 (sensores.terreno[1] == 'G' && !posicionamiento )) && last_action != actTURN_SR ){
 	
 			accion = actTURN_SL;
 			
 }
 
else if(((sensores.terreno[3] == 'K' && !tengobikini ) || (sensores.terreno[3] == 'D' && !tengozapatillas )||
	  (sensores.terreno[3] == 'X'&& sensores.bateria<5000) || (sensores.terreno[3] == 'G' && !posicionamiento)) && last_action != actTURN_SL){
 
 			accion = actTURN_SR;
 
 }
 
else if(((sensores.terreno[4] == 'K' && !tengobikini ) || (sensores.terreno[4] == 'D' && !tengozapatillas) || (sensores.terreno[4] == 'X'&& sensores.bateria<5000 )||
  	 (sensores.terreno[4] == 'G' && !posicionamiento )) && last_action != actTURN_SR ){
 	
 			accion = actTURN_SL;
 			
 }
 
 else if(((sensores.terreno[8] == 'K' && !tengobikini ) || (sensores.terreno[8] == 'D' && !tengozapatillas )||
	  (sensores.terreno[8] == 'X'&& sensores.bateria<5000) || (sensores.terreno[8] == 'G' && !posicionamiento)) && last_action != actTURN_SL){
 
 			accion = actTURN_SR;
 
 }
  
else if(((sensores.terreno[9] == 'K' && !tengobikini ) || (sensores.terreno[9] == 'D' && !tengozapatillas) || (sensores.terreno[9] == 'X'&& sensores.bateria<5000 )||
  	 (sensores.terreno[9] == 'G' && !posicionamiento )) && last_action != actTURN_SR ){
 	
 			accion = actTURN_SL;
 			
 }
 
 else if(((sensores.terreno[15] == 'K' && !tengobikini ) || (sensores.terreno[15] == 'D' && !tengozapatillas )||
	  (sensores.terreno[15] == 'X'&& sensores.bateria<5000) || (sensores.terreno[15] == 'G' && !posicionamiento)) && last_action != actTURN_SL){
 
 			accion = actTURN_SR;
 
 }

else if(pasos >= 100){
	pasos =0;
	int movimiento2 = rand() % 4;
		if(movimiento2==0){accion = actTURN_BL;}
		if(movimiento2==1){accion = actTURN_BR;}
		if(movimiento2==2){accion = actTURN_SL;}
		if(movimiento2==3){accion = actTURN_SR;}

}

 else{

	if (((sensores.terreno[2] == 'K' ) ||
	   (sensores.terreno[2] == 'D' ) ||
	   (sensores.terreno[2] =='A' && tengobikini) || 
	   (sensores.terreno[2] =='B'&& tengozapatillas) ||
	   sensores.terreno[2] =='T' || 
	   sensores.terreno[2] =='S' ||
	   sensores.terreno[2] =='X' || 
	   sensores.terreno[2] =='G' ||
	   (sensores.terreno[0] =='A' && sensores.terreno[2] != 'P' && !tengobikini) ||
	   (sensores.terreno[0] =='B' && sensores.terreno[2] != 'P'&& !tengozapatillas))
	   && sensores.superficie[2] =='_')	
	{	
	
		if(sensores.terreno[2] == 'K'){tengobikini = true;}
		if(sensores.terreno[2] == 'D'){tengozapatillas = true;}
		if(sensores.terreno[2] == 'G'){posicionamiento=true;}
		if(sensores.terreno[2] == 'X'){sensores.bateria = 5000;}
		
		accion = actFORWARD;
		
	}else {
		
		int movimiento = rand() % 4;
		if(movimiento==0){accion = actTURN_BL;}
		if(movimiento==1){accion = actTURN_BR;}
		if(movimiento==2){accion = actTURN_SL;}
		if(movimiento==3){accion = actTURN_SR;}
		
	}

}
	

	// Determinar el efecto de la ultima accion enviada

	pasos++;
	last_action = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
