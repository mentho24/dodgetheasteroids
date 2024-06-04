#ifndef DISPARO_H
#define DISPARO_H
#include <SFML/Graphics.hpp>
#include "Config.cpp"
using namespace sf;
class Disparo : public Sprite {
private:
	static Texture shot;
public:
	Disparo(Vector2f pos);
	void Actualizar(float dt);
	/*void SetSize(float w);*/
	~Disparo();
};

#endif

