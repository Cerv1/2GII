#ifndef PLAYER_H
#define PLAYER_H

#include "environment.h"

class Player{
    public:
      Player(int jug);
      Environment::ActionType Think();
      void Perceive(const Environment &env);
      double Poda_AlfaBeta(const Environment & tablero, int jugador, int profundidad, const int MAX_PROFUNDIDAD, Environment::ActionType & accion, double alpha, double beta);
    private:
      int jugador_;
      Environment actual_;
};
#endif
