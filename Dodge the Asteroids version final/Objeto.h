#ifndef OBJETO_H
#define OBJETO_H
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;
class Objeto : public Sprite {
private:
	float velocidad;
public:
	Objeto();
	void Actualizar(float dt,int dif);
    void Reset(int dif);
	~Objeto();
};

#endif

