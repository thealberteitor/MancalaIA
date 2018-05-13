/*
 * TaskStruct.cpp
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "TaskStruct.h"

#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;




TaskStruct::TaskStruct() {
	// Inicializar las variables necesarias para ejecutar la partida

}

TaskStruct::~TaskStruct() {
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void TaskStruct::initialize() {
	// Inicializar el bot antes de jugar una partida
}

string TaskStruct::getName() {
	return "TaskStruct"; // Sustituir por el nombre del bot
}
/*
void TaskStruct::valorCasilla(int jugador, const GameState &state, const int &valor){

	Player turno= this->getPlayer();

	GameState juego=state.simulateMove( (Move) valor);
	Move valor = juego.getScore(turno);

	return

	//Hacer el getSeed o algo así , mirar el guión

}
*/


double PodaAlfaBeta(vector<Nodo> &arbol, int nodoActual, Player jugador, int alfa, int beta, int profundidad){

	cerr << "Voy a crear el árbol, me meto en la función " << endl;


	if(profundidad==4 || arbol[nodoActual].juego.isFinalState()){
		GameState play;
		double minim=9999, maxim=-9999, valor;

		for(int i=1; i<=6; i++){
			if(arbol[nodoActual].juego.getSeedsAt(jugador, (Position) i)){	//Si hay semillas en la casilla i
				play = arbol[nodoActual].juego.simulateMove( (Move) i);
				valor=play.getScore(jugador);

				if(arbol[nodoActual].nivel%2==0){ //Si soy max

					if(valor>maxim)
						maxim=valor;
				}
				else{															//Si soy min
					if(valor<minim)
						minim=valor;
				}
			}
		}

		if(arbol[nodoActual].nivel%2==0)
			return maxim;
		else
			return minim;

	}


	int numHijos;
	Move accionAnterior;
	double valor;


	//GameState hijo; //= state.simulateMove( (Move) ultimaAccion);


	for(int i=1; i<=6; i++){
		if(arbol[nodoActual].juego.getSeedsAt(jugador, (Position) i)){  //Si hay semillas en i
			//Generamos el hijo
			GameState Jhijo= arbol[nodoActual].juego.simulateMove((Move) i);  //Genero juego

							//acción    //padre 										//Mov
			Nodo hijo(Jhijo, hijo.padre=&arbol[nodoActual], (Move) i);

			cerr << "Genero hijo " << hijo << "con padre " << hijo.padre << endl;


			arbol.push_back(hijo);

			int posHijo = arbol.size()-1;

			//Búsqueda en profundidad para saber el valor del hijo
			//Comprobar si roba porque si roba el prox turno es (jugador+1)%2
			int valorHijo= PodaAlfaBeta(arbol, posHijo, jugador, alfa, beta, profundidad+1);

			if(arbol[nodoActual].nivel%2==0){ //Si soy Max

				if(alfa<valorHijo){
					arbol[nodoActual].mejorHijo= posHijo;
					arbol[nodoActual].valor=alfa;
				}
				if(alfa>=beta)
					return beta;
			}
			else{   //Si soy Min
				if(beta>valorHijo){
					beta=valorHijo;
					arbol[nodoActual].mejorHijo= posHijo;
					arbol[nodoActual].valor=beta;

				}
				if(beta<=alfa)
					return alfa;
			}

		}
	}

	if(arbol[nodoActual].nivel%2 ==0)    //Si soy MAX
		return alfa;
	else																	//Si soy Min
		return beta;

}



/*

	if(MaxMin){ //Si soy un máximo{
		for(int i=1; i <=6; i++){
			if(state.getSeedsAt(jugador, (Position) i)){ //Si hay semillas en la casilla i del jugador
				GameState hijo=state.simulateMove( (Move) i);
				valor=PodaAlfaBeta(hijo, jugador, profundidad-1, alfa, beta,accionAnterior, false);
				if(valor>alfa){
					alfa=valor;
					accion= ((Move) ultimaAccion);
				}
				if(beta<=alfa)
					break;

				hijo=state.simulateMove(ultimaAccion);
			}
		}
		return alfa;
	}
	else if(!MaxMin){ //Si soy un mínimo
		for(int i=1; i<=6; i++){
			if(state.getSeedsAt(jugador, (Position) i)){  //Si hay semillas en la casilla i
				GameState hijo=state.simulateMove( (Move) i);
				valor=PodaAlfaBeta(hijo, jugador, profundidad-1, alfa, beta, accionAnterior, true);

				if(valor<beta){
					beta=valor;
					accion= ((Move) ultimaAccion);
				}
				if(beta<= alfa)
					break;

				hijo = state.simulateMove(ultimaAccion);
			}
		}
		return beta;
	}

	*/








Move TaskStruct::nextMove(const vector<Move> &adversary, const GameState &state) {



	cerr << "SIGUIENTE MOVIMIENTO " << endl;

	Player turno= this->getPlayer();
	long timeout= this->getTimeOut();

	Nodo raiz(state);  //Generamos la raíz, contiene el juego actual

	//Declaramos las variables
	double alfa=-9999, beta=9999;
	int profundidad=0;

	vector<Nodo> arbol;
	arbol.push_back(raiz);

	PodaAlfaBeta(arbol, 0, turno, alfa, beta, profundidad);

	return arbol[arbol[0].mejorHijo].accion;
}
