/*
 * TaskStruct.h
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "Bot.h"

#ifndef MANUPCBOT_H_
#define MANUPCBOT_H_
#include<iostream>
using namespace std;




struct Nodo{
	int nivel;				//Nivel del nodo
	Nodo *padre;			//Padre del nodo
	int mejorHijo;  //Mejor hijo de la lista de hijos
	GameState juego;	//Juego en este nodo del arbol
	Move accion;   //Acción que realizó el padre para llegar a este estado
	int valor;       //No sé pero sirve


	Nodo(GameState jueg, Nodo *papi, Move hacer, int level){
		juego=jueg;
		padre=papi;
		accion=hacer;
		nivel=level;
	}

	//Creamos así la raíz
	Nodo(GameState actual){
		padre=NULL;
		mejorHijo=-1;
		accion=(Move) -1;
		nivel=0;
		juego=actual;

	}

	friend ostream& operator <<(ostream &os,const Nodo &p){

	    os << "Otro nodo , NIVEL: " << p.nivel << endl;

	    return os;
		}



};

/*
Nodo generarRaiz(GameState actual){

	Nodo nuevo;
	nuevo.padre=NULL;
	nuevo.mejorHijo=NULL;
	nuevo.accion=(Move) -1;
	nuevo.nivel=0;
	nuevo.juego=actual;

	return nuevo;
}
*/

class TaskStruct:Bot {
	public:

		TaskStruct();
		~TaskStruct();

		int valorCasilla(int jugador, const GameState &state);

		void initialize();
		string getName();
		Move nextMove(const vector<Move> &adversary, const GameState &state);
		double PodaAlfaBeta(vector<Nodo> &arbol, int nodoActual, Player jugador, int alfa, int beta, int profundidad);

	private:

		const int NIVEL=10;


};

#endif /* MANUPCBOT_H_ */
