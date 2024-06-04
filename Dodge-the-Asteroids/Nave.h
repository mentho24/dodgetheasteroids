#ifndef NAVE_H
#define NAVE_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Nave: public Sprite {
private:
	Texture t;
	Texture exp;
	bool exploto,explosionT;
	Clock Explosion;
	Vector2f speed; //La velocidad de la Nave
	int combustible; //El combustible de la Nave
	int vida; //La "vida" de la nave
public:
	Nave();
	void Mover(float dt); //Mueve la Nave
	int GetCombustible(); //Obtiene el Combustible de la nave
	int GetVida();//Obtiene la vida de la nave
	void QuitarVida(); //Quita la vida de la nave;
	void SetVida(int x); //Valor inicial de la vida
	void AddCombustible(); //Agrega combustible a la nave 
	void BurnCombustible(); //"Quema" el combustible
	void SetCombustible(int x); //valor inicial del combustible
	void SetSpeed(float hor,float ver); //Setea la velocidad de la nave
	bool NaveExploto(){
		return exploto;
	}
	bool TerminoExplosion();
	~Nave();
};

#endif
