#ifndef JUEGO_H
#define JUEGO_H
#include "Meteoro.h"
#include "Nave.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Combustible.h"
#include <vector>
#include <string>
#include <fstream>
#include "sfml-input/InputBox.h"
#include "Disparo.h"
using namespace std;
using namespace sf;


class Juego {
private:
	RenderWindow *w;  //La ventana principal del juego
	
	Nave n;           //Objeto de la clase nave
	
	Texture bg;       //Textura del Background
	
	Texture vida;     //Textura de la barra de vida de la nave;
	
	Sprite vidas;     //Sprite de la barra de vida
	
	Texture puntajeT;
	Sprite bgpuntaje;
	
	Clock choque;
	
	Font fuente;      //Fuente principal
	
	Sprite bgs;       //Sprite del Background
	
	Clock tiempo_transcurrido,clock_fuel,clock_shot;  //Reloj del tiempo y otro reloj para saber cada cuanto restar el Combustible
	
	Text t_Transcurrido;        //TExto del tiempo
	
	Text t_fuel;               //Texto de la palabra "Combustible"
	
	Text barra;   //Texto de la palabra vida:
	
	Text DisparosDisponibles;
	
	int dif;
	
	String barra_v;  //String para el texto de la vida
	
	Text Score,texto_mejorPuntaje,nivel;;  
	String score_str;
	int score;
	Clock score_clock;
	
	string time_str,fuel_str_count,fuel_str,str_mejorPuntaje;  //String del tiempo, del contador de combustible y de la palabra combustible
	
	Clock _clock;                             
	
	SoundBuffer lowfuel;
	Sound lowf;
	
	
	SoundBuffer b;       //Sonido que se produce al agarrar el Combustible
	Sound beep;
	
	SoundBuffer Ast;
	Sound AstS;
	
	SoundBuffer Expb;
	Sound ExpS;
	SoundBuffer misilbuffer;
	Sound misilsound;
	bool perdiste,Disparar;       //Variable para saber cuando sucedio el fin del juego
	
	int disparos_generados;
	
	Texture misiles;
	Sprite misil;
	
	vector<Combustible> comb;             //Vector de los combustibles que aparecen en pantalla
	
	vector<Meteoro> meteoros;            //Vector de los meteoros
	
	Music musica;                        //Musica del nivel
	
	Clock Explosion,crear_meteoros;    
	
	Puntajes mejores[5];               //struct de los Puntajes
	fstream archi;                   
	
	Menu m;
	
	vector<Disparo> disparo;
	
	void SpawnCombustible();            //Metodo para crear combustible
	void Reiniciar();                   //Metodo para reiniciar el juego
	void SpawnMeteoros(int n);
	void CompararPuntajes();
	void PantallaDePuntajes(int pos);
	void Eventos();    //Procesa los eventos;
	void ProcesarColisiones();  //Este metodo procesa las colisiones entre los objetos;
	void Actualizar(float dt); 
	void Dibujar();
	void Empezar();
	void GameOver();
public:
	Juego();
	void Start();      //Metodo que comienza el juego;
	~Juego();
};

#endif
