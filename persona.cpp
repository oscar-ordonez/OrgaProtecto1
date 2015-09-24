#include "persona.h"
#include <iostream>
#include <string.h>
using namespace std;

persona::persona (string id, char nombre[], string genero, string idCiudad){
	
	this -> id = id;
	this -> nombre = nombre;
	this -> genero = genero;
	this -> idCiudad = idCiudad;

}
		
//get y set id
void persona::setId (string id){
	
	this -> id = id;

}
string persona::getId (){

	return id;

}
		
//get y set nombre
void persona::setNombre (char* nombre){

	this -> nombre = nombre;

}
char* persona::getNombre (){

	return nombre;

}

//get y set genero
void persona::setGenero (string generoo){

	this -> genero = genero;

}
string persona::getGenero (){

	return genero;

}

//get y set idCiudad
void persona::setIdCiudad (string idCiudad){

	this -> idCiudad = idCiudad;

}
string persona::getIdCuidad (){

	return idCiudad;
	
}