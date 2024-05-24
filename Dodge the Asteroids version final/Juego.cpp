#include "Juego.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Config.cpp"
#include <sstream>
using namespace sf;

Juego::Juego() {
	w=new RenderWindow(VideoMode(WIDTH,HEIGHT,BPP),"Dodge the Asteroids");
	
	//Apertura del archivo
	archi.open("score.dat",ios::binary|ios::in);
	if(archi.is_open())
		archi.read((char*)&mejores,sizeof(mejores));
	archi.close();
	//musica del nivel
	musica.openFromFile("Sonidos//saitama.ogg");
	musica.setLoop(true);
	musica.setVolume(10);
	
	//sounido de los misiles
	misiles.loadFromFile("Sprites/misiles.png");
	misil.setTexture(misiles);
	misil.setScale(0.5f,0.5f);
	
	//Textura y sprite del background
	bg.loadFromFile("Sprites//bg.png");
	bgs.setTexture(bg);
	
	//Textura, sprite, escala y posicion de la barra de vida
	vida.loadFromFile("Sprites//Lifebar.png");
	vidas.setTexture(vida);
	vidas.setScale(6.0f,4.0f);
	vidas.setPosition(40,-55);
	
	//Sonido que se reproduce al juntar Combustible
	b.loadFromFile("Sonidos//combustible.ogg");
	beep.setBuffer(b);
	beep.setVolume(30);
	
	misilbuffer.loadFromFile("Sonidos//misilsound.ogg");
	misilsound.setBuffer(misilbuffer);
	misilsound.setVolume(20);
	
	//fuente ingame
	fuente.loadFromFile("Fuentes/perfect.ttf");
	
	w->setKeyRepeatEnabled(false);
	
	//Texto del Tiempo 
	t_Transcurrido.setFont(fuente);
	t_Transcurrido.setColor(Color::White);
	t_Transcurrido.setCharacterSize(20);
	t_Transcurrido.setPosition(670,-1);
	
	
	//Texto de combustible : 
	t_fuel.setFont(fuente);
	t_fuel.setColor(Color::White);
	t_fuel.setCharacterSize(20);
	t_fuel.setPosition(0,50);
	
	
	//Texto Score
	Score.setFont(fuente);
	Score.setColor(Color::White);
	Score.setCharacterSize(20);
	Score.setPosition(0,25);
	
	//Texto nivel
	nivel.setFont(fuente);
	nivel.setColor(Color::White);
	nivel.setCharacterSize(20);
	nivel.setPosition(525,0);
	
	//Texto barra de vida
	barra.setFont(fuente);
	barra.setColor(Color::White);
	barra.setCharacterSize(20);
	barra_v="Vida: ";
	barra.setString(barra_v);
	
	//Texto del mejor Puntaje
	texto_mejorPuntaje.setFont(fuente);
	texto_mejorPuntaje.setColor(Color::White);
	texto_mejorPuntaje.setCharacterSize(20);
	str_mejorPuntaje="Record: "+ToString(mejores[0].puntaje);
	texto_mejorPuntaje.setString(str_mejorPuntaje);
	texto_mejorPuntaje.setPosition(WIDTH/2.5f,0);
	
	//Texto de los disparos
	DisparosDisponibles.setFont(fuente);
	DisparosDisponibles.setColor(Color::White);
	DisparosDisponibles.setCharacterSize(20);
	DisparosDisponibles.setString("Disparos: ");
	DisparosDisponibles.setPosition(0,560);
	
	misil.setPosition(100,550);
	
	//Sonido de bajo combustible (No anda)
	lowfuel.loadFromFile("Sonidos//lowfuel.ogg");
	lowf.setBuffer(lowfuel);
	lowf.setVolume(20);
	
	//Sonido de la colision con los asteroides
	Ast.loadFromFile("Sonidos/Colision_Asteroide.ogg");
	AstS.setBuffer(Ast);
	AstS.setLoop(false);
	AstS.setVolume(30);
	
	Expb.loadFromFile("Sonidos/Explosion.ogg");
	ExpS.setBuffer(Expb);
	ExpS.setLoop(false);
	ExpS.setVolume(30);
	
	puntajeT.loadFromFile("Sprites/puntajesbg.png");
	bgpuntaje.setTexture(puntajeT);
}
void Juego::Reiniciar(){
	//Rectangulo para mostrar una parte de la textura de la barra de vida
	vidas.setTextureRect(IntRect(0,0,32,20));
	score=0;
	n.setScale(1.7f,1.7f);
	n.SetVida(100);
	n.SetCombustible(100);
	
	//Rectangulo para mostrar una parte de la textura de la nave
	n.setTextureRect(IntRect(0,0,28,16));
	
	//Reproducir musica
	musica.play();
	
	//Vacia el vector de Combustible,el de meteoros y el de disparos
	comb.clear();
	meteoros.clear();
	disparo.clear();
	
	//Crea meteoros
	SpawnMeteoros(15);
	
	//reinicia el reloj que sirve para saber cada cuanto tiempo descontar Combustible
	clock_fuel.restart();
	
	clock_shot.restart();
	
	//posicion inicial de la nave
	n.setPosition(175, 130);
	
	//relojes
	tiempo_transcurrido.restart();
	score_clock.restart();
	
	//variable de fin de juego
	perdiste=false;
	
	Disparar=false;
	
	disparos_generados=0;
	misil.setTextureRect(IntRect(0,0,1,1));
	crear_meteoros.restart();
	
	dif=0;
}
void Juego::Start(){
	m.Comenzar(w);
	while(m.Termino()){
		Reiniciar();
		_clock.restart();
		while(w->isOpen() && !perdiste){
			Eventos();
			ProcesarColisiones();
			Dibujar();
			Actualizar(_clock.restart().asSeconds());
		}
		
		
		CompararPuntajes();
		m.Reiniciar();
		m.Comenzar(w);
	}
	
	
}
void Juego::Eventos(){
	Event e;
	while(w->pollEvent(e)) {
		if(e.type == Event::Closed)
			w->close();	

		//actualiza la textura de la nave si no se presiona una tecla
		if(n.GetVida()>0 && e.type==Event::KeyReleased){
			n.setTextureRect(IntRect(0,0,28,16));
		}
		
		if(n.GetVida()>0 && e.type==Event::KeyReleased && e.key.code==Keyboard::Space){
			if(Disparar){
				IntRect misilRect=misil.getTextureRect();
				if(disparo.size()<3){
					misilRect.width-=70;
					Disparo shot(n.getPosition());
					disparo.push_back(shot);
					misil.setTextureRect(misilRect);
					disparos_generados++;
					misilsound.play();
				}
				if(disparos_generados==3){
					disparos_generados=0;
					Disparar=false;
				}
			}
			
		}
		
		if(n.GetCombustible()>0 && n.GetCombustible()<=30){
			if(lowf.getStatus()==Sound::Stopped)
			lowf.play();
		}else{
			lowf.stop();
		}
	}
}
void Juego::Actualizar(float dt){
	//variables de la velocidad vertical y horizontal
	float hor=0.0f,ver=0.0f;
	if(n.GetVida()>0 && Keyboard::isKeyPressed(Keyboard::W)&&n.getPosition().y>0 && n.GetCombustible()>0){
		IntRect rectnave=n.getTextureRect();
		rectnave.left=28;
		n.setTextureRect(rectnave);
		ver-=250;
	}
	if(n.GetVida()>0 && Keyboard::isKeyPressed(Keyboard::S)&& (n.getPosition().y<(HEIGHT-25)) &&n.GetCombustible()>0){
		IntRect rectnave=n.getTextureRect();
		rectnave.left=56;
		n.setTextureRect(rectnave);
		ver+=250;}
	if(n.GetVida()>0 && Keyboard::isKeyPressed(Keyboard::A)&& n.getPosition().x>0 && n.GetCombustible()>0)
		hor-=250;
	if(n.GetVida()>0 && Keyboard::isKeyPressed(Keyboard::D)&&(n.getPosition().x<(WIDTH-46))&& n.GetCombustible()>0)
		hor+=250;
	
	//aplica la velocidad a la nave
	n.SetSpeed(hor,ver);
	//mueve la nave
	n.Mover(dt);
	
	//Actualiza los objetos en pantalla
	for(size_t i=0;i<meteoros.size();i++)
		meteoros[i].Actualizar(dt,dif);
	for(int i=0; i<comb.size();i++){
		comb[i].Actualizar(dt,0);
	}
	
	
	// reloj para aumentar score pasado 10 seg
	if(score_clock.getElapsedTime().asSeconds()>10.0f){
		score+=10;
		score_clock.restart();
	}
	
	//Crea combustible
	if((comb.size()<=1) && n.GetCombustible()<100){
		SpawnCombustible();
	}
	
	//Crea Meteoros
	if(crear_meteoros.getElapsedTime().asSeconds()>20){
		if(meteoros.size()<40);
		SpawnMeteoros(5);
		crear_meteoros.restart();
		if(dif<4)dif++;
		
	}

	
	//Actualiza el texto de record
	if(score>mejores[0].puntaje){
		str_mejorPuntaje="Record: "+ToString(score);
		texto_mejorPuntaje.setString(str_mejorPuntaje);
	}
	//Quema Combustible
	if(clock_fuel.getElapsedTime().asSeconds()>4){
		clock_fuel.restart();
		n.BurnCombustible();
	}
	
	for(int i=0;i<disparo.size();i++){
		disparo[i].Actualizar(dt);
		if(disparo[i].getPosition().x>750){
			disparo.erase(disparo.begin()+i);
		}
		
	}
	if(clock_shot.getElapsedTime().asSeconds()>15){
		Disparar=true;
		disparo.clear();
		disparos_generados=0;
		misil.setTextureRect(IntRect(0,0,200,100));
		clock_shot.restart();
		disparo.clear();
	}
	
	if(n.getPosition().x<-100)GameOver();
	
	if(n.NaveExploto()){
		if(ExpS.getStatus()==Sound::Stopped)ExpS.play();
	  if(n.TerminoExplosion()){
		  ExpS.stop();
		  GameOver();
	  }
	}
	
	nivel.setString("Nivel: "+ToString(dif+1));
	
	if(n.GetVida()==0)musica.stop();
	
	if(choque.getElapsedTime().asSeconds()>0.2f)n.setColor(Color::White);
	
	//string y texto del tiempo,combustible, score
	time_str="Tiempo: "+ToString(int(tiempo_transcurrido.getElapsedTime().asSeconds()))+"s";
	t_Transcurrido.setString(time_str);
	fuel_str="Combustible: "+ToString(n.GetCombustible())+"%";
	t_fuel.setString(fuel_str);
	score_str="Score: "+ToString(score);
	Score.setString(score_str);
}

void Juego::Dibujar(){
	
	w->clear();
	w->draw(bgs);
	w->draw(n);
	for(size_t i=0;i<meteoros.size();i++)
		w->draw(meteoros[i]);
	
	for(int i=0;i<comb.size();i++){
		w->draw(comb[i]);
	}
	for(int i=0;i<disparo.size();i++)
		w->draw(disparo[i]);
	w->draw(t_Transcurrido);
	w->draw(t_fuel);
	w->draw(Score);
	w->draw(vidas);
	w->draw(barra);
	w->draw(texto_mejorPuntaje);
	w->draw(misil);
	w->draw(DisparosDisponibles);
	w->draw(nivel);
	w->display();
	
}
void Juego::SpawnCombustible(){
	for(int i=0;i<4;i++){
		Combustible fuel;
		comb.push_back(fuel);
	}
}
void Juego::SpawnMeteoros(int n){
	for(int i=0;i<n;i++){
		Meteoro m;
		meteoros.push_back(m);
	}
}
void Juego::ProcesarColisiones(){
	FloatRect NaveBounds = n.getGlobalBounds();
	for(size_t i=0;i<meteoros.size();i++){
		if(NaveBounds.intersects(meteoros[i].getGlobalBounds())&& n.GetVida()>0){
			
				n.QuitarVida();
				IntRect barra=vidas.getTextureRect();
				barra.left+=32;
				vidas.setTextureRect(barra);
				AstS.play();
				meteoros.erase(meteoros.begin()+i);
				choque.restart();
				n.setColor(Color::Red);
		}
		
	}
	
	
	
	for(int i=0;i<disparo.size();i++){
		for(int j=0;j<meteoros.size();j++){
			if(disparo[i].getGlobalBounds().intersects(meteoros[j].getGlobalBounds()) &&n.GetVida()>0){
				meteoros.erase(meteoros.begin()+j);
				disparo.erase(disparo.begin()+i);
				AstS.play();
				
			}
		}
		
	}
	for(size_t i=0;i<comb.size();i++){
		if(NaveBounds.intersects(comb[i].getGlobalBounds()) && n.GetVida()>0){
			beep.play();
			n.AddCombustible();
			score+=20;
			comb.erase(comb.begin()+i);
		}
		
	}
}
void Juego::GameOver(){
	musica.stop();
	perdiste=true;
	
}
void Juego::CompararPuntajes(){
	if(score>mejores[0].puntaje){
		PantallaDePuntajes(0);
	}else if(score>mejores[1].puntaje){
		PantallaDePuntajes(1);
	}else if(score>mejores[2].puntaje){
		PantallaDePuntajes(2);
	}else if(score>mejores[3].puntaje){
		PantallaDePuntajes(3);
	}else if(score>mejores[4].puntaje){
		PantallaDePuntajes(4);
	}else{
		PantallaDePuntajes(5);} 
}

void Juego::PantallaDePuntajes(int pos){
	Font fuente2;
	fuente2.loadFromFile("Fuentes/arial.ttf");
	Text texto;
	texto.setFont(fuente2);
	texto.setColor(Color::White);
	texto.setCharacterSize(20);
	texto.setString("INGRESE NOMBRE PARA GUARDAR \nSU PUNTAJE:");
	texto.setPosition(100,50);

	string name; char *c_name;
	InputText NombreTexto(fuente2,10,Color::White);
	NombreTexto.setFont(fuente2);
	NombreTexto.setMaxChars(10);
	NombreTexto.setColor(Color::White);
	NombreTexto.setCharacterSize(20);
	NombreTexto.setSingleWord(true);
	NombreTexto.setPosition(315,75);
	
	bool WindowScore=true;
	if(pos==5)WindowScore=false;
	
	while(w->isOpen() && WindowScore==true){
		
		Event e;
		while(w->pollEvent(e)){
			if(e.type==Event::Closed)
				w->close();
			else if(e.type==Event::KeyReleased&&e.key.code==Keyboard::Return){
				name=NombreTexto.getValue();
				WindowScore=false;
			}else NombreTexto.processEvent(e);
		}
		w->draw(bgpuntaje);
		NombreTexto.update();
		w->draw(texto);
		w->draw(NombreTexto);
		w->display();
	}
	c_name=new char[10];
	name.copy(c_name,10,0);
	if(pos==4){
		mejores[4].puntaje=score;
		for(int i=0;i<10;i++){
			mejores[4].nombre[i]=c_name[i];
		}
	}else if(pos == 3){
		mejores[4].puntaje=mejores[3].puntaje;
		for(int i=0;i<10;i++){
			mejores[4].nombre[i]=mejores[3].nombre[i];
		}
		mejores[3].puntaje=score;
		for(int i=0;i<10;i++){
			mejores[3].nombre[i]=c_name[i];
		}
	}else if(pos==2){
		mejores[4].puntaje=mejores[3].puntaje;
		for(int i=0;i<10;i++){
			mejores[4].nombre[i]=mejores[3].nombre[i];
		}
		mejores[3].puntaje=mejores[2].puntaje;
		for(int i=0;i<10;i++){
			mejores[3].nombre[i]=mejores[2].nombre[i];
		}
		mejores[2].puntaje=score;
		for(int i=0;i<10;i++){
			mejores[2].nombre[i]=c_name[i];
		}
	}else if(pos==1){
		mejores[4].puntaje=mejores[3].puntaje;
		for(int i=0;i<10;i++){
			mejores[4].nombre[i]=mejores[3].nombre[i];
		}
		mejores[3].puntaje=mejores[2].puntaje;
		for(int i=0;i<10;i++){
			mejores[3].nombre[i]=mejores[2].nombre[i];
		}
		mejores[2].puntaje=mejores[1].puntaje;
		for(int i=0;i<10;i++){
			mejores[2].nombre[i]=mejores[1].nombre[i];
		}
		mejores[1].puntaje=score;
		for(int i=0;i<10;i++){
			mejores[1].nombre[i]=c_name[i];
		}
	}else if(pos==0){
		mejores[4].puntaje=mejores[3].puntaje;
		for(int i=0;i<10;i++){
			mejores[4].nombre[i]=mejores[3].nombre[i];
		}
		mejores[3].puntaje=mejores[2].puntaje;
		for(int i=0;i<10;i++){
			mejores[3].nombre[i]=mejores[2].nombre[i];
		}
		mejores[2].puntaje=mejores[1].puntaje;
		for(int i=0;i<10;i++){
			mejores[2].nombre[i]=mejores[1].nombre[i];
		}
		mejores[1].puntaje=mejores[0].puntaje;
		for(int i=0;i<10;i++){
			mejores[1].nombre[i]=mejores[0].nombre[i];
		}
		mejores[0].puntaje=score;
		for(int i=0;i<10;i++){
			mejores[0].nombre[i]=c_name[i];
		}
	}
	
	archi.open("score.dat",ios::binary|ios::out|ios::trunc);
	archi.write((char*)&mejores,sizeof(mejores));
	archi.close();
}
Juego::~Juego() {
}
