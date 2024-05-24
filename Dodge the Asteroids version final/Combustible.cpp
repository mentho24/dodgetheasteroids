#include "Combustible.h"
#include <iostream>
#include "Config.cpp"
using namespace std;
Texture Combustible::t;

Combustible::Combustible() {
	if(!cargada){
		if(!t.loadFromFile("Sprites/Combustible.png"))
			cerr<<"No se pudo cargar la textura del Combustible"<<endl;	
		cargada=true;
	}
	setTexture(t);
}

Combustible::~Combustible() {
	
}

