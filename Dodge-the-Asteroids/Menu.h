#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include "Config.cpp"
using namespace sf;
using namespace std;
class Menu {
private:
	Font fuente;
	Text texto_jugar,texto_info,texto_salir, texto_puntajes;
	
	Texture bg;
	Sprite bgs;
	
	SoundBuffer MenuS;
	Sound MenuSwap;
	
	Text PuntajesAltos[4];
	
	SoundBuffer Enter;
	Sound sEnter;
	
	Texture infoT;
	Sprite infoS;
	
	fstream scores;
	Puntajes puntajes[5];
	
	bool termino;
	bool jugar;
	
	
	int button;
	
	void Scores(RenderWindow *v);
	void Actualizar(float dt,RenderWindow* v);
	void ProcesarEventos(RenderWindow* v);
	void Dibujar(RenderWindow* v);
	void Info(RenderWindow* v);
	
public:
	Menu();
	void Comenzar(RenderWindow *v);
	bool Termino();
	void Reiniciar();
	~Menu();
};

#endif
