#include <iostream>
#include <iomanip>
#include <cstring>
#include <typeinfo>
#include <algorithm>
#include <fstream>
//#include <chrono>
//#include <ctime>

#include "Tablero.h"
using namespace std;

#define MAX_LEN 6
#define MAX_WID 6
#define MIN_DIM 3

/*=====================================================================================*/
// 				  PROTOTIPOS DE FUNCIONES UTILIZADAS EN EL MAIN
/*=====================================================================================*/

bool startup();
void setGame(int &, int &, int &);
void Game(Tablero &, int, int, int, ofstream &);
void placePiece(Tablero &, int, int);
void movePiece(Tablero &, int, int);
bool validateInputPosition(std::string ,Tablero &, int &, int &);
bool validateMovePosition(std::string, std::string, Tablero &, int &, int &, int &, int &, int);

/*====================================================================================*/
//									MAIN
/*====================================================================================*/


int main(void){
std::cout << " TaTeTi V1.0 - Alan Dreszman" << std::endl;
ofstream jugadas;


jugadas.open ("historial_de_jugadas.txt");

jugadas << "Inicio de partida: \n";



// INICIO
bool start = startup();
if(start){
    return 0;
}
//--------------------------------//

// Setear juego
int largo,alto;
int cant_fichas=0;
setGame(largo,alto,cant_fichas);
//-------------------------------//

// Inicializar Tablero
Tablero tab(largo,alto, cant_fichas);
//-------------------------------//

// Comenzar Juego
//bool a = Game(tab, cant_fichas, largo, alto);
Game(tab, cant_fichas, largo, alto, jugadas);
//-----------------------------------//

// endGame() "gano jugador x"


    for(int i=0 ; i < largo ; i++ ){
        for(int j=0 ; j < alto ; j++ ){
           std::cout << tab.board[i][j] << std::ends;
        }
        std::cout << ' ' << std::endl;
    }
    jugadas.close();
    return 0;
}

/*====================================================================================*/
// 						FUNCIONES INVOCADAS EN EL MAIN
/*====================================================================================*/

 bool startup(){

    char yes_no;
    std::string answer;
    int cuenta = 0;

    while(yes_no != 'Y' && yes_no != 'N'){
        if(cuenta!=0){
             std::cout << "RESPONDA 'Y' (SI) o 'N' (NO)" << std::endl;
        }
        std::cout << "Desea jugar al TATETI? (Y/N)" << std::endl;
        std::cin >> answer;
        if(answer.length() != 1){
            yes_no = 'X';
            continue;
        }
        else{
            yes_no = answer[0];
        }
        cuenta+=1;
    }
    if (yes_no == 'N'){
        std:: cout << "BUUU, AMARGO!" << std::endl;
        return 1;
    }

 return 0;
}


void setGame(int &largo, int &alto, int &cant_fichas){

    largo=0;
    alto=0;
    std::string input;
    std::string input_2;

    int cuenta=0;
    cant_fichas = 0;
    int min_dim;

    while( (largo<MIN_DIM) || (largo > MAX_LEN) || (alto < MIN_DIM) || (alto > MAX_WID) || (input.length() !=3 ) ){
        if(cuenta!=0){
            largo=0;
            alto=0;
            std::cout << "Los valores ingresados son invalidos o estan fuera de rango. Debe seleccionar valores NUMERICOS y dentro del rango ("<< MIN_DIM <<"<largo<" <<MAX_LEN<<", "<< MIN_DIM<< "<alto<" << MAX_WID <<")" <<std::endl;
            std::cout << "El formato de ingreso es 'AxB' donde 'A' es la contidad de filas y 'B' la cantidad de columnas" << std::endl;
            cuenta = 0;
            //break;
        }
        std::cout << "Seleccione las dimensiones del tablero (por defecto 3x3): " << std::endl;
        std::cout << "Dimensiones: " << std::ends;
        std::cin >> input;
        largo = input[0] - '0';
        alto = input[2] - '0';
        if(  (largo<MIN_DIM) || (largo > MAX_LEN) || (alto < MIN_DIM) || (alto > MAX_WID) || (input.length() !=3 ) ){
            cuenta=1;
        }
    }

    min_dim = std::min(largo,alto);
    while(cant_fichas == 0 || cant_fichas > min_dim)
    {
        if( (cant_fichas>min_dim) || cant_fichas<0 ){
            std::cout << "Cantidad de fichas o formato incorrecto. Ingrese un unico valor numerico" << std::endl;
            std::cout << "La cantidad de fichas debe ser igual o menor a la minima dimension del tablero" << std::endl;
            std::cout << "Menor dimension: " << min_dim <<std::endl;
            std::cout << "Cantidad de fichas: " << cant_fichas << std::endl;
            cant_fichas=0;
        }
        std::cout << "Seleccion la cantidad de fichas por jugador (por defecto 3): " << std::endl;
        std::cin >> input_2;
        cant_fichas = input_2[0] - '0';
    }

}


void Game(Tablero &tab, int cant_fichas, int largo, int alto, ofstream & archivo){
    // startGame()
    std::cout << "Ya puede comenzar a jugar!" << std::endl;
    std::cout << "Para jugar en su turno debera indicar la posicion en el tablero en la que desea colocar su ficha" << std::endl;
    std::cout << "El formato para hacerlo es x,y; donde 'x' es la posicion vertical e 'y' es la horizonal" << std::endl;
    std::cout << "El primer jugador comienza ubicando las fichas 'X', el segundo coloca las fichas 'O'" << std::endl;

    int placing_turns_count=1;
    int turn_number;

    while(placing_turns_count<cant_fichas+1){
        // Coloca Jugador 1
        placePiece(tab, 1, placing_turns_count);
        tab.printState();
        tab.printFile(placing_turns_count,1,archivo);
        // checkear si gano
        if(placing_turns_count>=cant_fichas){
        }

        // Coloca Jugador 2
        placePiece(tab, 2, placing_turns_count);
        tab.printState();
        tab.printFile(placing_turns_count,2,archivo);
        // checkear si gano
        if(placing_turns_count>=cant_fichas){
        }
        placing_turns_count++;
    }
    turn_number = placing_turns_count;

    bool win=1;


    while(win){
        // Mueve Jugador 1
        movePiece(tab, 1, turn_number);
        tab.printState();
        tab.printFile(placing_turns_count,1,archivo);
        if(tab.checkIfWinner()){
            win=0;
            std::cout << "Gana el Jugador 1!" << std::endl;
            system("pause");
            continue;
        }
        // Mueve Jugador 2
        movePiece(tab, 2, turn_number);
        tab.printState();
        tab.printFile(placing_turns_count,2,archivo);
        if(tab.checkIfWinner()){
            win=0;
            std::cout << "Gana el Jugador 2!" << std::endl;
            system("pause");
            continue;
        }
        turn_number++;
    }
    //return 0;
}


void placePiece(Tablero &tab, int player, int turno){

    std::string jugada;
    int pos_x=0;
    int pos_y=0;

    std::cout << "Turno "<< turno << " del Jugador "<< player << std::endl;
    std::cout << "Jugada: " << std::ends;
    std::cin >> jugada;

    while(validateInputPosition(jugada, tab, pos_x, pos_y)){
        std::cout << "Turno "<< turno << " del Jugador "<< player << std::endl;
        std::cout << "Jugada: " << std::ends;
        std::cin >> jugada;
    }
    tab.addChecker(pos_x,pos_y,player);
}


bool validateInputPosition(std::string jugada, Tablero &tab, int & pos_x, int & pos_y){

    if(jugada.length() != 3){
        std::cout << "Formato incorrecto" << std::endl;
        std::cout << "Recuerde, el formato para ubicar una posicion es x,y; donde 'x' es la posicion vertical e 'y' es la horizonal" << std::endl;
        return 1;
    }
    pos_x = jugada[0] - '0' - 1 ;
    pos_y = jugada[2] - '0' - 1 ;
    if( pos_x >= tab.rows || pos_y >= tab.columns || pos_x < 0 || pos_y < 0 || jugada[1] != ','){
        std::cout << "Posicion invalida o formato incorrecto" << std::endl;
        std::cout << "Recuerde, el formato para ubicar una posicion es x,y; donde 'x' es la posicion vertical e 'y' es la horizonal" << std::endl;
  //      std::cout << tab.rows << tab.columns << " Ckp 2" << std::endl;
        return 1;
    }
    if(tab.checkIfEmpty(pos_x,pos_y)){
 //       std::cout << pos_x << pos_y << " Ckp 4" << std::endl;
        return 1;
    }

    return 0;
}


void movePiece(Tablero &tab, int player, int turno){

    std::string origen;
    std::string destino;
    int from_x=0;
    int from_y=0;
    int to_x=0;
    int to_y=0;

    std::cout << "Turno "<< turno << " del Jugador "<< player << std::endl;
    std::cout << "Que ficha desea mover?: " << std::ends;
    std::cin >> origen;
    std::cout << "Hacia que posicion?: " << std::ends;
    std::cin >> destino;

    while(validateMovePosition(origen, destino, tab, from_x, from_y, to_x, to_y, player)){
        std::cout << "Turno "<< turno << " del Jugador "<< player << std::endl;
        std::cout << "Que ficha desea mover?: " << std::ends;
        std::cin >> origen;
        std::cout << "Hacia que posicion?: " << std::ends;
        std::cin >> destino;
    }
    tab.moveChecker(from_x, from_y, to_x, to_y);
}



bool validateMovePosition(std::string origen, std::string destino, Tablero &tab, int & from_x, int & from_y, int & to_x, int & to_y, int player){

// Chequeo ORIGEN
    if(origen.length() != 3){
        std::cout << "Formato de posicion de ORIGEN incorrecto" << std::endl;
        std::cout << "Recuerde, el formato para ubicar una posicion es x,y; donde 'x' es la posicion vertical e 'y' es la horizonal" << std::endl;
        return 1;
    }

    from_x = origen[0] - '0' - 1 ;
    from_y = origen[2] - '0' - 1 ;
    if( from_x >= tab.rows || from_y >= tab.columns || from_x < 0 || from_y < 0 || origen[1] != ','){
        std::cout << "Posicion invalida o formato incorrecto de posicion de ORIGEN" << std::endl;
        std::cout << "Recuerde, el formato para ubicar una posicion es x,y; donde 'x' es la posicion vertical e 'y' es la horizonal" << std::endl;
  //      std::cout << tab.rows << tab.columns << " Ckp 2" << std::endl;
        return 1;
    }
    if(tab.validateOwnership(from_x,from_y,player)){
        return 1;
    }

    std::cout << "Origen OK" << std::endl;

// Chequeo DESTINO
    if(destino.length() != 3){
        std::cout << "Formato de posicion de DESTINO incorrecto" << std::endl;
        std::cout << "Recuerde, el formato para ubicar una posicion es x,y; donde 'x' es la posicion vertical e 'y' es la horizonal" << std::endl;
        return 1;
    }
    to_x = destino[0] - '0' - 1 ;
    to_y = destino[2] - '0' - 1 ;
    if( to_x >= tab.rows || to_y >= tab.columns || to_x < 0 || to_y < 0 || destino[1] != ','){
        std::cout << "Posicion invalida o formato incorrecto de posicion de DESTINO" << std::endl;
        std::cout << "Recuerde, el formato para ubicar una posicion es x,y; donde 'x' es la posicion vertical e 'y' es la horizonal" << std::endl;
        return 1;
    }

    if(tab.checkIfEmpty(to_x,to_y)){
        return 1;
    }

    if(tab.validateMove(from_x, from_y, to_x,to_y)){
        return 1;
    }

    std::cout << "Destino OK" << std::endl;
    return 0;
}


//bool checkWin(){

//}


