/*
 * Akre.h
 *
 *  Author: Álvaro López Jiménez
 */

#include "Bot.h"

#ifndef MANUPCBOT_H_
#define MANUPCBOT_H_
#include<iostream>
using namespace std;

class Akre:Bot {
	public:

		Akre();
		~Akre();

		void initialize();
		string getName();
		Move nextMove(const vector<Move> &adversary, const GameState &state);
		int AlfaBeta(const GameState &state, int alfa, int beta, int profundidad);

	private:

		const int NIVEL=7;
		int mejorHijo ;


};

#endif /* MANUPCBOT_H_ */
