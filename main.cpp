#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


const int M = 20;
const int N = 20;

int lung=3;
int punteggio = 0, start = 0, countclass = 0;

fstream fp; //settaggio file classifica

string uploadpunti, uploadpunti_a, uploadpunti_b, uploadpunti_c, puntitemp[100];

int classifica[100] = {0};

int campo[M][N];

struct Punto
{int x,y;} a[100], frutta[1];

bool check() {
	if(a[lung-1].x<0 || a[lung-1].x>=N || a[lung-1].y<0 || a[lung-1].y>=M) return 0;
	
	for(int i=0; i<lung-1; i++) if(a[lung-1].x==a[i].x && a[lung-1].y==a[i].y) return 0;
	
	return 1;
};

bool checkeat() {
	if(a[lung-1].x==frutta[0].x && a[lung-1].y==frutta[0].y) return 0;
	
	return 1;
}



int main() {
	
	srand(time(0));
	
	//Inizializzazione finestra e sfondo
	sf::RenderWindow window(sf::VideoMode(1080,1080), "Snake");
		
	window.clear();
	
	sf::RectangleShape sfondo(sf::Vector2f(1080.f,1080.f));
	sfondo.setFillColor(sf::Color::Black);
	sfondo.setPosition(0.f, 0.f);
	
	window.draw(sfondo);
	window.display();
	
	

	//Settaggio Font
	sf::Font font;
	font.loadFromFile("file/arial.ttf");


	//Creazione testo, colorazione, settaggio font, settaggio carattere, settaggio stile	
	sf::Text testo_a, testo_b, crediti;
	
	testo_a.setString("Snake"); //titolo
	testo_a.setFont(font);
	testo_a.setCharacterSize(72);
	testo_a.setFillColor(sf::Color::White);
	testo_a.setStyle(sf::Text::Bold);
	testo_a.setPosition(450.f, 180.f);
	
	window.draw(testo_a);
	
	testo_b.setString("Clicca spazio per giocare"); //descrizioni
	testo_b.setFont(font);
	testo_b.setCharacterSize(36);
	testo_b.setFillColor(sf::Color::White);
	testo_b.setStyle(sf::Text::Bold);
	testo_b.setPosition(348.f, 360.f);
	
	window.draw(testo_b);
	
	crediti.setString("Made by Panca278"); //titolo
	crediti.setFont(font);
	crediti.setCharacterSize(24);
	crediti.setFillColor(sf::Color::White);
	crediti.setStyle(sf::Text::Bold);
	crediti.setPosition(840.f, 48.f);
	
	window.draw(crediti);
	window.display();
	
	window.clear();
	window.display();

	
	
	sf::Texture texture, texture_f; //settaggio texture e creazione sprite
	
	texture.loadFromFile("image/snake.png");
	
	sf::Sprite s;
	
	s.setTexture(texture);
	
	texture_f.loadFromFile("image/frutta.png");
	
	sf::Sprite f;
	
	f.setTexture(texture_f);
	
	f.setTextureRect(sf::IntRect(0, 0, 32, 32));
	
	
	sf::Texture background;
	
	background.loadFromFile("image/campo.png");
	
	sf::Sprite back;
	
	back.setTexture(background);
	
	
	
	sf::Text punti; //settaggio testo punteggio
	
	punti.setString("0");
	punti.setFont(font);
	punti.setCharacterSize(36);
	punti.setFillColor(sf::Color::Black);
	punti.setStyle(sf::Text::Bold);
	punti.setPosition(700.f, 35.f);
	
	window.display();
			
	
	
	sf::Clock clock; //settaggio timer
	
	int e=0, k=0, dx=0, dy=0, dir=1, checkdir=1;
	float timer = 0, delay=0.2;
	
	for(int i=0; i<3; i++) {
		a[i].x=i;
		a[i].y=0;
	}
	
	frutta[0].x = rand()%20;
	frutta[0].y = rand()%20;
	
	sf::Event event;
	
	//Cuore
	while(window.isOpen()) {
				
	  if(start==0) {
	  	
		while (window.pollEvent(event)) { //Eventi
			switch (event.type) {
				
				case sf::Event::Closed: //Chiusura finestra
					window.close();
					break;
					
				case sf::Event::Resized: //Resize sfondo quando la finestra viene allargata
					window.setSize(sf::Vector2u(1080.f,1080.f));
					window.display();
					break;
					
				case sf::Event::KeyPressed: //start
					if(event.key.code == sf::Keyboard::Space) { start++; sf::sleep(sf::milliseconds(1000)); }
					
					break;
				
			}			
		}

	  } else if(start==1) {
	  					
		srand(time(NULL));
		window.clear();
		
		float tempo=clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=tempo;
    
		while (window.pollEvent(event)) { //Eventi
			switch (event.type) {
				
				case sf::Event::Closed: //Chiusura finestra
					window.close();
					break;
					
				case sf::Event::Resized: //Resize sfondo quando la finestra viene allargata
					window.setSize(sf::Vector2u(1080.f,1080.f));
					window.display();
					break;
								
				case sf::Event::KeyPressed: //Pressione tasti tastiera
					if(event.key.code == sf::Keyboard::Left) { if(checkdir==0) { dir=3; checkdir++; } } //sinistra
					else if(event.key.code == sf::Keyboard::Right) { if(checkdir==0) { dir=1; checkdir++; } } //destra
					else if(event.key.code == sf::Keyboard::Up) { if(checkdir!=0) { dir=0; checkdir--; } } //alto
					else if(event.key.code == sf::Keyboard::Down) { if(checkdir!=0) { dir=2; checkdir--; } } //basso
												
					break;
				
			}				
		}
				
				
		
		for(int i=0; i<M; i++) {
			for(int z=0; z<N; z++) {
				campo[i][z]=0;
			}
		}
		
		
		
		if(delay<timer) { //movimento
			
			if(dir==0) { dx=0; dy=-1; }
			else if(dir==1) { dx=1; dy=0; }
			else if(dir==2) { dx=0; dy=1; }
			else if(dir==3) { dx=-1; dy=0; }
			
			for(int i=0; i<lung; i++) {			
				if(i==lung-1) { a[i].x+=dx; a[i].y+=dy; }
				else { a[i].x=a[i+1].x; a[i].y=a[i+1].y; }
				
				campo[a[i].x][a[i].y]=1;
			}
			
			
			timer=0;
		}
		
		
		
		if(!checkeat()) {
			
			lung++;
			if(dir==0) { a[lung-1].x=a[lung-2].x; a[lung-1].y=a[lung-2].y-1; }
			else if(dir==1) { a[lung-1].x=a[lung-2].x+1; a[lung-1].y=a[lung-2].y;}
			else if(dir==2) { a[lung-1].x=a[lung-2].x; a[lung-1].y=a[lung-2].y+1;}
			else if(dir==3) { a[lung-1].x=a[lung-2].x-1; a[lung-1].y=a[lung-2].y;}
			
			punteggio+=100;
			stringstream ss;
			ss<<punteggio;
			ss>>uploadpunti;
			punti.setString(uploadpunti);
			
			while(e==0) {
				frutta[0].x = rand()%20;
				frutta[0].y = rand()%20;
				
				if(campo[frutta[0].x][frutta[0].y]==0) e++;
			}
			
		}
		
		
		
		if(!check()) start++;

		
		e=0; //reset variabili
		
		f.setPosition(frutta[0].x*32,frutta[0].y*32);
		f.move(32,32);
		window.draw(f);


		
		for(int i=0; i<lung; i++) {
			if(i==lung-1) s.setTextureRect(sf::IntRect(dir*32, 0, 32, 32));
			else s.setTextureRect(sf::IntRect(128, 0, 32, 32));
			
			s.setPosition(a[i].x*32,a[i].y*32);
			s.move(32,32);
			window.draw(s);
		}


		
		window.draw(back);
		window.draw(punti);
		window.display();
		
	  } else if(start==2) {
	  	
	  	if(k==0) { //preparazione schermata finale
	  	
	  		int max, t;
	  		
			sf::sleep(sf::milliseconds(3000)); k++;
			
			
			
			fp.open("file/punteggio.txt", ios::app);
			fp << punteggio; //scrittura punteggio nel file
			fp << "\n";
			fp.close();
			
			fp.open("file/punteggio.txt", ios::in);
			stringstream rr[100]; //settaggio punti classifica
			while(getline(fp,puntitemp[countclass])) {
				rr[countclass]<<puntitemp[countclass];
				rr[countclass]>>punteggio;
				classifica[countclass] = punteggio;
				countclass++;
			}
		
			for(int i=0; i<countclass; i++) { //ordine decrescente punteggi		
				max=i;
			
				for (int z=i+1; z<countclass; z++) {
					if (classifica[z]>classifica[max]) {
						max=z;
					}
				}

				t = classifica[max];
				classifica[max] = classifica[i];
				classifica[i] = t;
					
			}
			
		}
	  	
	  	
	  	
	  	while (window.pollEvent(event)) { //Eventi
			switch (event.type) {
				
				case sf::Event::Closed: //Chiusura finestra
					window.close();
					break;
					
				case sf::Event::Resized: //Resize sfondo quando la finestra viene allargata
					window.setSize(sf::Vector2u(1080.f,1080.f));
					window.display();
					break;
					
				case sf::Event::KeyPressed: //end
					if(event.key.code == sf::Keyboard::Space) start++;
					
					break;
				
			}			
		}
					
		
		
	  	window.clear();
	
		sf::Text testo_e, testo_f, testo_g, classifica_a, classifica_b, classifica_c;
	
		testo_e.setString("Il tuo punteggio: "); //punteggio finale
		testo_e.setFont(font);
		testo_e.setCharacterSize(48);
		testo_e.setFillColor(sf::Color::White);
		testo_e.setStyle(sf::Text::Bold);
		testo_e.setPosition(270.f, 180.f);
	
		window.draw(testo_e);
	
		punti.setCharacterSize(48);
		punti.setFillColor(sf::Color::Green);
		punti.setStyle(sf::Text::Bold);
		punti.setPosition(690.f, 180.f);
	
		window.draw(punti);	
	
		testo_f.setString("Clicca spazio per terminare");
		testo_f.setFont(font);
		testo_f.setCharacterSize(48);
		testo_f.setFillColor(sf::Color::White);
		testo_f.setStyle(sf::Text::Bold);
		testo_f.setPosition(348.f, 360.f);
	
		window.draw(testo_f);
		
		testo_g.setString("Classifica:\n\tPrimo:\n\tSecondo:\n\tTerzo:");
		testo_g.setFont(font);
		testo_g.setCharacterSize(48);
		testo_g.setFillColor(sf::Color::White);
		testo_g.setStyle(sf::Text::Bold);
		testo_g.setPosition(180.f, 500.f);
	
		window.draw(testo_g);
		
	
		stringstream tt, uu, vv; //settaggio punti classifica
		tt<<classifica[0];
		tt>>uploadpunti_a;
		classifica_a.setString(uploadpunti_a);
		uu<<classifica[1];
		uu>>uploadpunti_b;
		classifica_b.setString(uploadpunti_b);
		vv<<classifica[2];
		vv>>uploadpunti_c;
		classifica_c.setString(uploadpunti_c);
		
		classifica_a.setFont(font);
		classifica_a.setCharacterSize(48);
		classifica_a.setFillColor(sf::Color::Red);
		classifica_a.setStyle(sf::Text::Bold);
		classifica_a.setPosition(480.f, 550.f);
	
		window.draw(classifica_a);
		
		classifica_b.setFont(font);
		classifica_b.setCharacterSize(48);
		classifica_b.setFillColor(sf::Color::Red);
		classifica_b.setStyle(sf::Text::Bold);
		classifica_b.setPosition(480.f, 600.f);
	
		window.draw(classifica_b);
		
		classifica_c.setFont(font);
		classifica_c.setCharacterSize(48);
		classifica_c.setFillColor(sf::Color::Red);
		classifica_c.setStyle(sf::Text::Bold);
		classifica_c.setPosition(480.f, 650.f);
	
		window.draw(classifica_c);
				
		window.display();
		
	  } else {
	  	
	  	fp.close();
	  	break;
	  	
	  }
	}
	


	window.clear();
	window.display();	
	
	return 0;
}
