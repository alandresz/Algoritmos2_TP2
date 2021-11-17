#ifndef TABLERO_H
#define TABLERO_H
#include <fstream>
#include <iostream>
#include <cstdlib>
// using namespace std;
//#include "allSame.h"

class Tablero
{
    public:
        Tablero();
        Tablero(int rows, int columns, int checkers);         // constructor con dimensiones de board
        ~Tablero();
        bool state;                             // 0 = open (partida en juego) , 1 = closed (partida terminada)
        int winner;                             // 0 = sin definicion , 1 = gano jugador 1 , 2 = gano jugador 2
        int rows;                               // cantida de filas del tablero
        int columns;                            // cantidad de columnas del tablero
        int checkers;                           // cantidad de fichas por jugador
        char **board;                           // variable que contiene al tablero
        void initBoard(int, int);               // inicia la variable board con un tablero con dimensiones igual a los dos argumentos
        void addChecker(int, int, int);         // agrega ficha en casillero con coordenadas (x,y) = a los argumentos
        void moveChecker(int, int, int, int);   // mueve ficha del casillero con (x,y) = a los primero dos argunmentos a casillero con (x,y) = a los segundos dos argumentos
        void printState();                      // imprime estado del tablero
        void printFile(int, int, std::ofstream &);                // imprime el estado actual del tablero a un archivo de texto
        bool checkIfEmpty(int, int);            // chequea si casillero esta vacio para colocar o  mover
        bool validateMove(int , int , int , int);
        bool validateOwnership(int, int, int);  // chequea si una ficha pertenece al jugador en cuestion
        //bool allSame(std::string);                   // chequea si todos los elementos de un array(fila, columna o diagonal) son iguales
        bool checkIfWinner();                   // chequea si hay alguna linea de elementos iguales


    protected:

    private:
};

#endif // TABLERO_H
