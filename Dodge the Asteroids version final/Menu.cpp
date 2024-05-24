#include "Menu.h"
#include "Config.cpp"
#include <iomanip>
Menu::Menu() {
	fuente.loadFromFile("Fuentes/arial.ttf");
	
	infoT.loadFromFile("Sprites/info.png");
	infoS.setTexture(infoT);
	
	termino=false;
	jugar=false;
	
	bg.loadFromFile("Sprites/bg_menu.png");
	bgs.setTexture(bg);
	
	MenuS.loadFromFile("Sonidos/MenuSwap.ogg");
	MenuSwap.setBuffer(MenuS);
	MenuSwap.setVolume(100);
	
	Enter.loadFromFile("Sonidos/MenuEnter.ogg");
	sEnter.setBuffer(Enter);
	sEnter.setVolume(20);
	
	//Texto jugar;
	texto_jugar.setFont(fuente);
	texto_jugar.setCharacterSize(40);
	texto_jugar.setColor(Color::Yellow);
	texto_jugar.setString("JUGAR");
	texto_jugar.setPosition(WIDTH/2.9f,HEIGHT/3.0f);
	
	scores.open("score.dat",ios::binary|ios::in);
	if(scores.is_open())
		scores.read((char*)&puntajes,sizeof(puntajes));
	scores.close();
	
	//Texto info
	texto_info.setFont(fuente);
	texto_info.setCharacterSize(40);
	texto_info.setColor(Color::White);
	texto_info.setString("INFO");
	texto_info.setPosition(WIDTH/2.9f,HEIGHT/2.18f);
	
	//Texto Puntajes
	texto_puntajes.setFont(fuente);
	texto_puntajes.setCharacterSize(40);
	texto_puntajes.setColor(Color::White);
	texto_puntajes.setString("PUNTAJES");
	texto_puntajes.setPosition(WIDTH/2.9f,HEIGHT/1.73f);
	
	//Texto salir
	texto_salir.setFont(fuente);
	texto_salir.setCharacterSize(40);
	texto_salir.setColor(Color::White);
	texto_salir.setString("SALIR");
	texto_salir.setPosition(WIDTH/2.9f,HEIGHT/1.42f);
	
	button=0;
	
	PuntajesAltos[0].setFont(fuente); PuntajesAltos[0].setCharacterSize(35); PuntajesAltos[0].setColor(Color::White);
	PuntajesAltos[0].setString("Mejores Puntajes");  PuntajesAltos[0].setPosition(130,200);
	PuntajesAltos[1].setFont(fuente); PuntajesAltos[1].setCharacterSize(25); PuntajesAltos[1].setColor(Color::White);
	PuntajesAltos[1].setPosition(WIDTH/4.1f,HEIGHT/2.25f);
	PuntajesAltos[2].setFont(fuente); PuntajesAltos[2].setCharacterSize(25); PuntajesAltos[2].setColor(Color::White);
	PuntajesAltos[2].setPosition(550,HEIGHT/2.25f);
	PuntajesAltos[3].setFont(fuente); PuntajesAltos[3].setCharacterSize(15); PuntajesAltos[3].setColor(Color::White);
	PuntajesAltos[3].setString("Apreta Escape para volver al Menu");
	
	string aux,aux2;
	aux+="1 "+string(puntajes[0].nombre)+"\n"+"\n";
	aux+="2 "+string(puntajes[1].nombre)+"\n"+"\n";
	aux+="3 "+string(puntajes[2].nombre)+"\n"+"\n"; 
	aux+="4 "+string(puntajes[3].nombre)+"\n"+"\n";
	aux+="5 "+string(puntajes[4].nombre);
	PuntajesAltos[1].setString(aux);
	
	aux2+=ToString(puntajes[0].puntaje)+"\n"+"\n";
	aux2+=ToString(puntajes[1].puntaje)+"\n"+"\n";
	aux2+=ToString(puntajes[2].puntaje)+"\n"+"\n";
	aux2+=ToString(puntajes[3].puntaje)+"\n"+"\n";
	aux2+=ToString(puntajes[4].puntaje);
	PuntajesAltos[2].setString(aux2);
	
}
void Menu::ProcesarEventos(RenderWindow *v){
	Event e;
	while(v->pollEvent(e)){
		if(e.type==Event::Closed) v->close();
		if(e.type==Event::KeyReleased && e.key.code==Keyboard::Return){
			sEnter.play();
			switch(button){
			case 0: 
				jugar=true;
				termino=true;
				break;
			case 1: 
				Info(v);
				break;
			case 2:
				Scores(v);
				break;
			case 3:
				v->close();
				break;
			}
		}
		
		if(e.type==Event::KeyReleased&& e.key.code==Keyboard::W){
			MenuSwap.play();
			if(button==0)
				button=3;
			else button--;
		}
		if(e.type==Event::KeyReleased&& e.key.code==Keyboard::S){
			MenuSwap.play();
			if(button==3)
				button=0;
			else button++;
		}
		
	}
}

void Menu::Dibujar(RenderWindow *v){
	v->clear(Color::Black);
	v->draw(bgs);
	v->draw(texto_jugar);
	v->draw(texto_info);
	v->draw(texto_puntajes);
	v->draw(texto_salir);
	v->display();
}
void Menu::Comenzar(RenderWindow *v){
	while(v->isOpen() && !jugar){
		ProcesarEventos(v);
		Dibujar(v);
		
		switch (button){
		case 0: 
			texto_jugar.setColor(Color::Yellow);
			texto_info.setColor(Color::White);
			texto_puntajes.setColor(Color::White);
			texto_salir.setColor(Color::White);
			break;
		case 1: 
			texto_jugar.setColor(Color::White);
			texto_info.setColor(Color::Yellow);
			texto_puntajes.setColor(Color::White);
			texto_salir.setColor(Color::White);
			break;
		case  2: 
			texto_jugar.setColor(Color::White);
			texto_info.setColor(Color::White);
			texto_puntajes.setColor(Color::Yellow);
			texto_salir.setColor(Color::White);
			break;
		case 3: 
			texto_jugar.setColor(Color::White);
			texto_info.setColor(Color::White);
			texto_puntajes.setColor(Color::White);
			texto_salir.setColor(Color::Yellow);
			break;
			
		}
		
	}
}
void Menu::Info(RenderWindow* v){
	bool info=true;
	while(v->isOpen() && info==true){
		Event e1;
		while(v->pollEvent(e1)){
			if(e1.type==Event::KeyReleased && e1.key.code==Keyboard::Escape){
				info=false;
			}
			if(e1.type==Event::Closed) v->close();
		}
		v->clear();
		v->draw(infoS);
		v->display();
	}
}
void Menu::Scores(RenderWindow *v){
	bool puntuacion=true;
	while(v->isOpen() && puntuacion==true){
		Event e;
		while(v->pollEvent(e)){
			if(e.type==Event::KeyReleased && e.key.code==Keyboard::Escape){
				puntuacion=false;
			}
			if(e.type==Event::Closed) v->close();
		}
		v->clear();
		v->draw(bgs);
		v->draw(PuntajesAltos[0]);
		v->draw(PuntajesAltos[1]);
		v->draw(PuntajesAltos[2]);
		v->draw(PuntajesAltos[3]);
		v->display();
	}
}
bool Menu::Termino(){
	return termino;
}

void Menu::Reiniciar(){
	termino = false;
	jugar = false;
	
	scores.open("score.dat",ios::binary|ios::in);
	if(scores.is_open())
		scores.read((char*)&puntajes,sizeof(puntajes));
	scores.close();
	
	string aux,aux2;
	aux+="1 "+string(puntajes[0].nombre)+"\n"+"\n";
	aux+="2 "+string(puntajes[1].nombre)+"\n"+"\n";
	aux+="3 "+string(puntajes[2].nombre)+"\n"+"\n"; 
	aux+="4 "+string(puntajes[3].nombre)+"\n"+"\n";
	aux+="5 "+string(puntajes[4].nombre);
	PuntajesAltos[1].setString(aux);
	
	aux2+=ToString(puntajes[0].puntaje)+"\n"+"\n";
	aux2+=ToString(puntajes[1].puntaje)+"\n"+"\n";
	aux2+=ToString(puntajes[2].puntaje)+"\n"+"\n";
	aux2+=ToString(puntajes[3].puntaje)+"\n"+"\n";
	aux2+=ToString(puntajes[4].puntaje);
	PuntajesAltos[2].setString(aux2);
}

Menu::~Menu() {
	
}
