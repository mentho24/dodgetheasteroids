#include "Objeto.h"
#include "Config.cpp"
#include <cstdlib>
#include <ctime>

int aleatorio(int desde, int hasta) { return (desde+(rand()%(hasta-desde))); }
Objeto::Objeto() {
	Reset(0);
}

void Objeto::Reset(int dif){
	
	setPosition(WIDTH + 40,(rand()%HEIGHT)-32);
	switch(dif){
	case 0: velocidad=aleatorio(50,250);
	break;
	case 1: velocidad=aleatorio(150,400);
	break;
	case 2: velocidad=aleatorio(250,500);
	break;
	case 3: velocidad=aleatorio(400,600);
	}
	
}

void Objeto::Actualizar(float dt,int dif){
	move( - velocidad * dt , 0.0f); //solo se mueven en x
	
	if(getPosition().x < -40)
		Reset(dif);
}
Objeto::~Objeto() {
	
}

