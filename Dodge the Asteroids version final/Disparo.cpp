#include "Disparo.h"
Texture Disparo::shot;
Disparo::Disparo(Vector2f pos) {
	if(!cargada2){
		shot.loadFromFile("Sprites/misil.png");
		cargada2=true;
	}
	setScale(3.0f,3.0f);
	pos.x+=40;
	pos.y+=10;
	setTexture(shot);
	setPosition(pos);
}
void Disparo::Actualizar(float dt){
	move(Vector2f(350*dt,0.0f));
}
Disparo::~Disparo() {
	
}

