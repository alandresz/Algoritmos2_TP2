#include <cstring>
#include <typeinfo>
#include <algorithm>
#include "Tablero.h"

Tablero::Tablero()
{
    this->rows=0;
    this->columns=0;

    std::cout << "constructed [" << this << "] empty\n";
}

//Constructor de un tablero con las dimensiones especificadas
Tablero::Tablero(int n_rows, int n_columns, int n_checkers){
    this->rows=n_rows;
    this->columns=n_columns;
    this->state = 0;
    this->winner = 0;
    this->checkers = n_checkers;

    int i=0,j=0;

    board = new char*[this->columns];
    for(i = 0; i < this->columns; ++i){
        board[i] = new char[this->rows];
    }

    for(i=0 ; i < this->columns ; i++ ){
        for(j=0 ; j < this->rows ; j++){
            board[i][j] = ' ';
        }
    }
    std::cout << "constructed [" << this << "]\n";
}

Tablero::~Tablero()
{
    //std::cout << "DESTRUCTED [" << this << "]\n";
}


// addChecker() agrega una ficha en un lugar determinado del tablero
void Tablero::addChecker(int row, int column,int player){
    char mark;
    if(player==1)
        mark = 'X';
    if(player==2)
        mark = 'O';
    this->board[row][column] = mark;
}

// printState() imprime el estado actual del tablero
void Tablero::printState(){
    std::cout << "-------------" << std::endl;
    for(int i=0 ; i < this->rows ; i++ ){
        std::cout << "|" << std::ends;
        for(int j=0 ; j < this->columns ; j++ ){
           std::cout <<this->board[i][j]<<" |" << std::ends;
        }
        std::cout << "" << std::endl;
        std::cout << "-------------" << std::endl;
    }
}

// checkIfEmpty() revisa si un casillero se encuentra vacio tanto para colocar una ficha ahi como para moverla hacia ahi
bool Tablero::checkIfEmpty(int row, int column){
    if (this->board[row][column] == ' '){
        return 0;}
    else{
        std:: cout << "Movimiento prohibido. Solo puede colocar/mover su ficha en/a lugares vacios" << std::endl;
        return 1;}
}


// validateMove() valida que el movimiento de una pieza se realice hacia lugares adyacentes a donde se encuentra la misma actualmente
bool Tablero::validateMove(int row_act, int col_act, int row_to,int col_to){
    if(abs((row_act-row_to) + (col_act-col_to)) != 1 ){
        std:: cout << "Movimiento prohibido. Solo puede mover su ficha a lugares adyacentes" << std::endl;
        return 1;
    }
    return 0;
}


// moveChecker() mueve una pieza de una posicion de origen hacia una de destino
void Tablero::moveChecker(int row_act, int col_act, int row_to,int col_to){
    this->board[row_to][col_to] = this->board[row_act][col_act];
    this->board[row_act][col_act] = ' ';
}


// validateOwnership() valida si un jugador es duenio de la ficha que esta intentando mover
bool Tablero::validateOwnership(int row, int column, int player){
    char mark;
    if(player==1)
        mark = 'X';
    if(player==2)
        mark = 'O';
    if(this->board[row][column] != mark){
        std:: cout << "Esa ficha no le pertenece. Solo puede mover fichas suyas" << std::endl;
        return 1;
    }
    return 0;
}


// allSame() es una funcion auxiliar que verifica en forma recursiva si un string contiene valores identicos
bool allSame(const std::string&, int );

bool allSame(const std::string &str, int N){

    if(N==1){return true;}
    if(str[0] != str[N-1]){
        return false;}
    return allSame(str, N-1);
}


bool Tablero::checkIfWinner(){

    int min_dim = std::min(this->rows, this->columns);
    std::string aux;

    // chequeo filas
    for(int i=0; i<min_dim; i++){
        for(int j=0; j<min_dim; j++){
            aux[j]=(this->board[i][j]);
        }
        if(allSame(aux, min_dim)){
            std:: cout << "Hay ganador!(fila "<< i+1 << ")"<< std::endl;
            return 1;
        }
    }

    // chequeo columnas
    for(int i=0; i<min_dim; i++){
        for(int j=0; j<min_dim; j++){
            aux[j]=this->board[j][i];
        }
        if(allSame(aux, min_dim)){
            std:: cout << "Hay ganador!(columna "<< i+1 << ")" << std::endl;
            return 1;
        }
    }

    // chequeo diagonales
    for(int i=0; i<min_dim; i++){
        aux[i]=this->board[i][i];
    }
    if(allSame(aux, min_dim)){
        std:: cout << "Hay ganador!(diagonal)" << std::endl;
        return 1;
    }

    for(int i=0; i<min_dim; i++){
        aux[i]=this->board[i][min_dim-i-1];
    }
    if(allSame(aux, min_dim)){
        std:: cout << "Hay ganador!(antidiagonal)" << std::endl;
        return 1;
    }
    return 0;
}


void Tablero::printFile(int turno, int jugador, std::ofstream &archivo){
    archivo << "Turno "<< turno << " del Jugador "<< jugador << "\n";
    archivo << "------------- \n" ;
    for(int i=0 ; i < this->rows ; i++ ){
        archivo << "|" ;
        for(int j=0 ; j < this->columns ; j++ ){
           archivo << this->board[i][j] <<" |";
        }
        archivo << " \n" ;
        archivo << "------------- \n";
    }
}



