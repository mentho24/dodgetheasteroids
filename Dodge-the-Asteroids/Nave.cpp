#include "Nave.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Config.cpp"
using namespace sf;

Nave::Nave() {
	t.loadFromFile("Sprites/nave.png");
	exp.loadFromFile("Sprites/explosion.png");
	setTexture(t);
	combustible=100;
	setScale(1.7f,1.7f);
	setPosition(175, 130);
}

void Nave::SetSpeed(float hor,float ver){
	speed.x=hor;
	if(getPosition().x>0 && speed.x==0 && !exploto){
		speed.x=-100;
	}
	if(speed.x==0 && combustible==0)
		speed.x=-100;
	speed.y=ver;
}
void Nave::Mover(float dt){
	move(speed  * dt);
	
	if(exploto){
		setTexture(exp);
		if(Explosion.getElapsedTime().asSeconds()>0.0f && Explosion.getElapsedTime().asSeconds()<0.2f){
			setTextureRect(IntRect(0,0,30,18));
			
		}
		
		if(Explosion.getElapsedTime().asSeconds()>0.2f && Explosion.getElapsedTime().asSeconds()<0.4f){
			setTextureRect(IntRect(30,0,30,18));
			
		}
		
		if(Explosion.getElapsedTime().asSeconds()>0.4f && Explosion.getElapsedTime().asSeconds()<0.6f){
			setTextureRect(IntRect(60,0,30,18));
			
		}
		
		if(Explosion.getElapsedTime().asSeconds()>0.6f && Explosion.getElapsedTime().asSeconds()<0.8f){
			setTextureRect(IntRect(90,0,30,18));
			
		}
		
		if(Explosion.getElapsedTime().asSeconds()>1.0f && Explosion.getElapsedTime().asSeconds()<1.2f){
			setTextureRect(IntRect(120,0,30,18));
			
		}
		if(Explosion.getElapsedTime().asSeconds()>1.2f) explosionT=true;
	}
	
	speed.x = 0;
	speed.y = 0;
}
void Nave::QuitarVida(){
	vida-=25;
	if(vida==0){
		exploto=true;
		Explosion.restart();
	}
}
int  Nave::GetVida(){
	return vida;
}
void Nave::SetCombustible(int x){
	combustible=x;
}
int Nave::GetCombustible(){
	return combustible;
}
void Nave::SetVida(int x){
	vida=x;
	exploto=false;
	explosionT=false;
	setTexture(t);
}
void Nave::AddCombustible(){
	if(combustible<100)
		combustible+=5;
}
void Nave::BurnCombustible(){
	if(combustible>=10)
		combustible-=10;
	if(combustible>0 && combustible<=5)
		combustible=0;
	
}


bool Nave::TerminoExplosion(){
	return explosionT;
}
Nave::~Nave() {
	
}
