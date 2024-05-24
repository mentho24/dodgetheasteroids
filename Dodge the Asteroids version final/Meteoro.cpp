#include "Meteoro.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Config.cpp"
using namespace std;
using namespace sf;

vector<Texture> Meteoro::M_T;

Meteoro::Meteoro() {
	/*srand(time(0));*/
	if(M_T.size() == 0){
		M_T.resize(2);
		if(!M_T[0].loadFromFile("Sprites/meteoro1_8bits.png"))
			cerr<<"No se pudo cargar la textura de la victima 1"<<endl;
		if(!M_T[1].loadFromFile("Sprites/meteoro2_8bits.png"))
			cerr<<"No se pudo cargar la textura de la victima 2"<<endl;
	}
	setTexture(M_T[rand()%2]);
}




