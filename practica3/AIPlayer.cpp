# include "AIPlayer.h"
# include "Parchis.h"

const double masinf = 9999999999.0, menosinf = -9999999999.0;
const double gana = masinf - 1, pierde = menosinf + 1;
const int num_pieces = 3;
const int PROFUNDIDAD_MINIMAX = 4;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 6; // Umbral maximo de profundidad para la poda Alfa_Beta

bool AIPlayer::move(){
    cout << "Realizo un movimiento automatico" << endl;

    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    cout << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color & c_piece, int & id_piece, int & dice) const{
    // IMPLEMENTACIÓN INICIAL DEL AGENTE
    // Esta implementación realiza un movimiento aleatorio.
    // Se proporciona como ejemplo, pero se debe cambiar por una que realice un movimiento inteligente
    //como lo que se muestran al final de la función.

    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores,
    //respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.

    // El id de mi jugador actual.
   // int player = actual->getCurrentPlayerId();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    //vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
   // vector<tuple<color, int>> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
   // current_dices = actual->getAvailableNormalDices(player);
    // Elijo un dado de forma aleatoria.
   // dice = current_dices[rand() % current_dices.size()];

    // Se obtiene el vector de fichas que se pueden mover para el dado elegido
    //current_pieces = actual->getAvailablePieces(player, dice);

    // Si tengo fichas para el dado elegido muevo una al azar.
    /*
    if (current_pieces.size() > 0)
    {
        int random_id = rand() % current_pieces.size();
        id_piece = get<1>(current_pieces[random_id]); // get<i>(tuple<...>) me devuelve el i-ésimo
        c_piece = get<0>(current_pieces[random_id]);  // elemento de la tupla
    }
    
    else
    {
        // Si no tengo fichas para el dado elegido, pasa turno (la macro SKIP_TURN me permite no mover).
        id_piece = SKIP_TURN;
        c_piece = actual->getCurrentColor(); // Le tengo que indicar mi color actual al pasar turno.
    }
*/
  
    // El siguiente código se proporciona como sugerencia para iniciar la implementación del agente.

    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha = menosinf, beta = masinf; // Cotas iniciales de la poda AlfaBeta
    // Llamada a la función para la poda (los parámetros son solo una sugerencia, se pueden modificar).
    // valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
    // cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
  
    // ----------------------------------------------------------------- //

    // Si quiero poder manejar varias heurísticas, puedo usar la variable id del agente para usar una u otra.
    
    switch(id){
        case 0:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
            break;
        case 1:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest1);   
          
            break;
        case 2:
           valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest2);
            break;
    }
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    
}



double AIPlayer::ValoracionTest(const Parchis &estado, int jugador)
{
    // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.


    int ganador = estado.getWinner();
    int oponente = (jugador+1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_jugador++;
                }
                else if (estado.getBoard().getPiece(c, j).get_box().type == goal)
                {
                    puntuacion_jugador += 5;
                }
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if (estado.isSafePiece(c, j))
                {
                    // Valoro negativamente que la ficha esté en casilla segura o meta.
                    puntuacion_oponente++;
                }
                else if (estado.getBoard().getPiece(c, j).get_box().type == goal)
                {
                    puntuacion_oponente += 5;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}


//*************************Poda-y-heurística*******************************************



double AIPlayer::Poda_AlfaBeta(const Parchis &actual, int id_jugador, int profundidad, int profundidad_max, color &c_piece,int &id_piece, int &dice, double alpha, double beta,double (*heuristic)(const Parchis &, int)) const {
	
	 if ((profundidad == profundidad_max) || actual.gameOver()) {
		return heuristic(actual, id_jugador);
	} else { 
		
		
		ParchisBros iterador = actual.getChildren();
		ParchisBros::Iterator it = iterador.begin();
		Parchis siguiente_hijo = *it;
		
		
		if (id_jugador == actual.getCurrentPlayerId()) {
			color color_alpha = c_piece;
			int pieza_alpha = id_piece;
			int dado_alpha = dice;
			double poda_actualizada_alpha;
			
			while (!(siguiente_hijo == actual)) {
			
				int profundidad_actualizada_alpha = profundidad + 1;
				poda_actualizada_alpha = Poda_AlfaBeta(siguiente_hijo, id_jugador, profundidad_actualizada_alpha,profundidad_max, c_piece, id_piece,dice, alpha,beta, *heuristic);
				
				if (alpha < poda_actualizada_alpha) {
					alpha = poda_actualizada_alpha;
					color_alpha = it.getMovedColor();
					pieza_alpha = it.getMovedPieceId();
					dado_alpha = it.getMovedDiceValue();
				}
				if (alpha >= beta) {
					break;
				}
				++it;
				siguiente_hijo = *it;
			}
			c_piece = color_alpha;
			id_piece = pieza_alpha;
			dice = dado_alpha;
			return alpha;
			
		} else {
		
			color color_beta = c_piece;
			int pieza_beta = id_piece;
			int dado_beta = dice;
			double poda_actualizada_beta;
			while (!(siguiente_hijo == actual)  ) {
				int profundidad_actualizada_beta = profundidad + 1;
				poda_actualizada_beta = Poda_AlfaBeta(siguiente_hijo, id_jugador, profundidad_actualizada_beta,profundidad_max, c_piece, id_piece,dice, alpha,beta, *heuristic);
				
				if (beta > poda_actualizada_beta) {
					beta = poda_actualizada_beta;
					color_beta = it.getMovedColor();
					pieza_beta = it.getMovedPieceId();
					dado_beta = it.getMovedDiceValue();
				}
				if (alpha >= beta) {
					break;
				}
				++it;
				siguiente_hijo = *it;
			}
			c_piece = color_beta;
			id_piece = pieza_beta;
			dice = dado_beta;
			return beta;
			
		}
	}
		
		
			
	}
	
	

//H1**********************

double AIPlayer::ValoracionTest1(const Parchis &estado, int jugador){
    // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.


    int ganador = estado.getWinner();
    int oponente = (jugador+1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        
        
        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                puntuacion_jugador += 100;
                Box casilla = estado.getBoard().getPiece(c, j).get_box();
		puntuacion_jugador -= (estado.distanceToGoal(c,casilla) + estado.piecesAtHome(c));
		
		
		if(estado.isGoalMove()){ 
			puntuacion_jugador +=50;
		}
		
		
		else if(estado.isEatingMove()){
			puntuacion_jugador +=25;
		}
		
		
		else if(estado.isSafePiece(c,j)){
		 	puntuacion_jugador +=10;
		 }
		 
            }
        }
        
        
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
               
		puntuacion_oponente += 100;
                Box casilla = estado.getBoard().getPiece(c, j).get_box();
		puntuacion_oponente -= (estado.distanceToGoal(c,casilla) + estado.piecesAtHome(c));
		

		 if(estado.isGoalMove()){
		 	puntuacion_oponente +=50;
		 }
		
		else if(estado.isEatingMove()){
		 	puntuacion_oponente +=25;
		 }
		
		else if(estado.isSafePiece(c,j)){
		 	puntuacion_oponente +=10;
		 }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}	

//H2**********************

double AIPlayer::ValoracionTest2(const Parchis &estado, int jugador)
{
    // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.


    int ganador = estado.getWinner();
    int oponente = (jugador+1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                
                
                if(estado.isGoalMove()){ 
			puntuacion_jugador +=50;
		}
		
		
		else if(estado.isEatingMove()){
			puntuacion_jugador +=25;
		}
		
		
		else if(estado.isSafePiece(c,j)){
		 	puntuacion_jugador +=10;
		 }
		 
                else if (estado.getBoard().getPiece(c, j).get_box().type == goal)
                {
                    	puntuacion_jugador += 5;
                }
                
                else if ( estado.distanceToGoal(c,j) <= 7){
                	puntuacion_jugador ++;
                }
              
        }
	}
        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
              	
              	
              	 if(estado.isGoalMove()){
		 	puntuacion_oponente +=50;
		 }
		
		else if(estado.isEatingMove()){
		 	puntuacion_oponente +=25;
		 }
		
		else if(estado.isSafePiece(c,j)){
		 	puntuacion_oponente +=10;
		}
		 
                else if (estado.getBoard().getPiece(c, j).get_box().type == goal)
                {
                    puntuacion_oponente  += 5;
                }
                
                else if ( estado.distanceToGoal(c,j) <= 7){
                	puntuacion_oponente ++;
                }
               
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    
}
}
