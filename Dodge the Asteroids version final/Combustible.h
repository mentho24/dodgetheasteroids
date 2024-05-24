#ifndef COMBUSTIBLE_H
#define COMBUSTIBLE_H
#include "Config.cpp"
#include "Objeto.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Combustible : public Objeto {
private:
	static Texture t;
public:
	Combustible();
	~Combustible();
};

#endif

