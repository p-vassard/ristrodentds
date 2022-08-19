#include <PA9.h>

#include <iostream>
//#include "Fonctions.cpp"
#include "Personnage.h"
#include "Attaque.h"
#include "Laby.h"

#include "gfx/all_gfx.c"
#include "gfx/all_gfx.h"

#include "Define.cpp"

//Sons
//#include "valide.h"
//#include "bouge.h"
//#include "annule.h"
//#include "erreur.h"



//Fonctions internes
int menu(std::vector<std::string> textes, int ecran, int x, int y, int interligne, int defaut, bool retourPossible);
int menuCombat(Personnage *joueur, int ecran, int x, int y, int maxY, int espaceX, int espaceY, int defaut);
void partieRapide();
void nouveauJeu();
void charger();
void jeu(int tailleMoyenne, Heros* joueur);
void test();

//Fonctions communes
char* stringToChar(std::string chaine);
std::string intToString(int nombre);
char* intToChar(int nombre);
void boucleAppuie();
bool boutonValide();
bool boutonAnnule();
bool boutonL();
bool boutonR();
bool boutonSelect();
int appuieDirection();
int combat(Personnage *joueur, Personnage *ennemi);


int main(int argc, char ** argv){
	while(1) {
		PA_Init();		//Initialisation de la librairie principale
		PA_InitVBL();	//Initialisation de la VBL
		//PA_InitSound();	//Inistalisation du son
		PA_InitRand();
		PA_Init16bitBg(0, 0);
		//PA_Init16bitBg(1, 0);
		PA_InitText(1,1);
		PA_InitText(0,1);
		PA_WaitForVBL();
		
		//Cration du menu
		std::vector<std::string> menuPrincipal;
		menuPrincipal.push_back("Niveau 1");
		menuPrincipal.push_back("Niveau 50");
		menuPrincipal.push_back("Niveau 100");
		int choixMenuPrincipal = menu(menuPrincipal, 0, 10, 10, 1, 0, false);
		
		switch(choixMenuPrincipal) {
			case 0 :
				nouveauJeu();
			break;
			case 1 :
				charger();
			break;
			case 2 :
				partieRapide();
			break;
		}
	}
}

/**
 *	Nouvelle partie
 */
void nouveauJeu() {
	//Variables du laby
	int tailleMoyenne = 10;
	Heros* joueur = new Heros();
	jeu(tailleMoyenne, joueur);
}

void charger() {	
	//Variables du laby
	int tailleMoyenne = 108;
	Heros* joueur = new Heros();
	jeu(tailleMoyenne, joueur);
}

void partieRapide() {
	//Variables du laby
	int tailleMoyenne = 208;
	Heros* joueur = new Heros();
	jeu(tailleMoyenne, joueur);
}

void jeu(int tailleMoyenne, Heros* joueur) {
	//Initialisation des fonds et des palettes
	PA_LoadTiledBg(1, 3, fondLaby);
	PA_Init8bitBg(0, 3);
	PA_Load8bitBgPal(0,(void*)fondExploration_Pal);
	PA_Load8bitBitmap(0, fondExploration_Bitmap);
	PA_LoadSpritePal(0, 0, (void*)bouton_A_Pal);
	PA_InitText(1,2);
	
	//Boucle de jeu
	bool gameOver = false;
	while(!gameOver) {
		//Instanciation d'un nouveau labyrinthe
		int tailleLabyX = tailleMoyenne + PA_RandMinMax((int)(-tailleMoyenne/5), (int)(tailleMoyenne/5));
		PA_ResetSpriteSys();
		Laby *labyrinthe = new Laby(tailleLabyX, (tailleMoyenne*2)-tailleLabyX, joueur);
		labyrinthe->resetAffichageLabyHero();
		labyrinthe->afficheApercu(5);
		labyrinthe->afficheMenu();
		labyrinthe->afficheNiveau();
		
		bool sort = false;
		while(!sort && !gameOver) {
			int direction = appuieDirection();
			if (direction != -1) {
				int bouge = labyrinthe->bougeHeros(direction);
				switch(bouge) {
					case 0 : {
						//labyrinthe->afficheApercu(5);
						break;
					}
					case 1 : {
						sort = true;
						break;
					}
					case 2 : {
						gameOver = true;
						break;
					}
				}
			}
			
			if (boutonValide()) {
				int bouge = labyrinthe->appuieBoutonValider();
				switch(bouge) {
					case 0 : {
						//labyrinthe->afficheApercu(5);
						break;
					}
					case 1 : {
						sort = true;
						break;
					}
					case 2 : {
						gameOver = true;
						break;
					}
				}
			}
			if (boutonL())
				labyrinthe->changeMenu(-1);
			if (boutonR())
				labyrinthe->changeMenu(1);
			
			PA_WaitForVBL();
		}
		
		if (!gameOver) {
			//Niveau supérieur
			delete labyrinthe;
			tailleMoyenne += 2;
			if (tailleMoyenne > 100)	//Protection contre les problèmes mémoire
				tailleMoyenne = 100;
		}
	}
	return;
}

void test() {
	PA_LoadTiledBg(1, 0, fondLaby);
	/*
	for (int i = 0 ; i < 32 ; i++)
		for (int j = 0 ; j < 24; j++)
			PA_SetMapTile(1, 0,	i, j, 0);
*/
	int k = 0;
	for (int i = 0 ; i < 32 ; i++)
		for (int j = 0 ; j < 24; j++) {
			PA_RandMinMax(0, 9);
			k = (k+1);
			PA_SetMapTileAll(1, 0,	i, j, fondLaby_Map[k]);
			PA_OutputText(0, i, j, "%d", k);
		}
	
	while(1)
		PA_WaitForVBL();
}
