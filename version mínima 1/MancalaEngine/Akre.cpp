/*
 * Akre.cpp
 *
 *   Author: Álvaro López Jiménez
 */

#include "Akre.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;


Akre::Akre() {
	// Inicializar las variables necesarias para ejecutar la partida
	mejorHijo = -1 ; // Inicialmente no lo sabemos
}

Akre::~Akre() {
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void Akre::initialize() {
	// Inicializar el bot antes de jugar una partida
}

string Akre::getName() {
	return "Akre"; // Sustituir por el nombre del bot
}

int Akre::AlfaBeta(const GameState &state, int alfa, int beta, int profundidad){

	if(profundidad==NIVEL || state.isFinalState()){

		if (state.isFinalState())
			return state.getScore(getPlayer());
		else { // HEURÍSTICA

			// ROBAR TURNO

			int mejorOpcion = 0 ;
			int valores[6] = {0,0,0,0,0,0};

			for (int i = 1 ; i <= 6 ; i++) {
				if (state.getSeedsAt(getPlayer(), (Position) i) == i)
					valores[i-1] = state.getScore(getPlayer()) + 1 + i;
		  }

			for (int i = 0 ; i < 6 ; i++) {
				if (valores[i] > mejorOpcion)
					mejorOpcion = valores[i];
			}

			if (mejorOpcion != 0)
				return mejorOpcion ;
			else
				return state.getScore(getPlayer());
			

		}



		/* ROBAR SEMILLAS

			bool puedoRobar[6] = {false} ;

			for (int i = 0 ; i <= 6 ; i++) {
				if()
		}

		*/
	}


	for(int i=1; i<=6; i++){
		if(state.getSeedsAt(state.getCurrentPlayer(), (Position) i)) {  //Si hay semillas en i

			GameState Jhijo= state.simulateMove((Move) i);  // Generamos el hijo

			int valorHijo= AlfaBeta(state, alfa, beta, profundidad+1); // Búsqueda en profundidad para saber el valor del hijo

			if(state.getCurrentPlayer()==getPlayer()){   // Nodo MAX

				if(alfa<valorHijo){
					alfa=valorHijo;
					mejorHijo= i;
				}
				if(alfa>=beta)
					return beta;
			}
			else{   																			// Nodo MIN
				if(beta>valorHijo){
					beta=valorHijo;
					mejorHijo= i;
				}
				if(beta<=alfa)
					return alfa;
			}

		}
	}


	if(state.getCurrentPlayer()==getPlayer())		// Nodo MAX
		return alfa;
	else																				// Nodo MIN
		return beta;



}


Move Akre::nextMove(const vector<Move> &adversary, const GameState &state) {

	//cerr << "SIGUIENTE MOVIMIENTO " << endl;

	//Player turno= this->getPlayer();
	//long timeout= this->getTimeOut();

	//Declaramos las variables
	int alfa = INT_MIN ;
	int beta = INT_MAX ;
	int profundidad = 0;

	AlfaBeta(state, alfa, beta, profundidad);

	return (Move) mejorHijo;
}
