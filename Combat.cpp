#include <PA9.h>
#include <sstream>
#include <iostream>
#include <vector>

#include "gfx/all_gfx.h"

#include "Personnage.h"
#include "Attaque.h"
#include "Define.cpp"

//Fonctions communes
char* stringToChar(std::string chaine);
bool boutonValide();
void boucleAppuie();
void fondu(int ecran, int debut, int fin, int duree);

/**
 *	Nettoie les textes de l'écran du haut
 */
void clearEcranStatus(int y) {
	for(int i = y ; i <= 23 ; i++)
		PA_OutputText(1, 0, i, "                               ");
	return;
}

/**
 *	Gère le menu des combats
 */
int menuCombat(Personnage *joueur, int ecran, int x, int y, int maxY, int espaceX, int espaceY, int defaut) {

	std::vector<Attaque*> actions = joueur->getAttaques();
	
	//Modifie les stats avec les attaques passives
	
	
	//Affichage du premier élément
	actions[0]->afficheDescriptionCombat(ecran, 1, 9);
	
	//Couleur du texte normale
	PA_SetTextTileCol(ecran, COULEUR_TEXTE);
	
	//Boucle pour afficher chacune des lignes de proposition
	for(u8 i = 0 ; i < actions.size() ; i++) {
		//Changement de couleur si on est sur la proposition sélectionnée
		if (defaut == i)
			actions[i]->estFaisable(joueur)?PA_SetTextTileCol(ecran, COULEUR_SELECTION):PA_SetTextTileCol(ecran, COULEUR_SELECTION_IMPOSSIBLE);
		else
			actions[i]->estFaisable(joueur)?PA_SetTextTileCol(ecran, COULEUR_TEXTE):PA_SetTextTileCol(ecran, COULEUR_IMPOSSIBLE);
		
		PA_OutputText(ecran, (int)(i/maxY)*espaceX+x, (i%maxY)*espaceY+y, "%s", stringToChar(actions[i]->getNom()));
	}
	
	int choix = -1;
	u8 selection = defaut;
	//Boucle jusqu'à validation ou annulation
	while(choix == -1) {
		int selectionTest = selection;
		bool appuie = false;
		
		//Si on appuie sur une direction
		if (Pad.Newpress.Up) {
			selectionTest--;
			appuie = true;
		}
		if (Pad.Newpress.Down) {
			selectionTest++;
			appuie = true;
		}
		if (Pad.Newpress.Right) {
			selectionTest+=maxY;
			appuie = true;
		}
		if (Pad.Newpress.Left) {
			selectionTest-=maxY;
			appuie = true;
		}
		//On vérifie si la sélection est cohérente
		if (appuie && selectionTest >=0 && selectionTest < (int)actions.size()) {
			//On remet la couleur normale de l'ancien texte
			if (actions[selection]->estFaisable(joueur))
				PA_SetTextTileCol(ecran, COULEUR_TEXTE);
			else
				PA_SetTextTileCol(ecran, COULEUR_IMPOSSIBLE);
			PA_OutputText(ecran, (int)(selection/maxY)*espaceX+x, (selection%maxY)*espaceY+y, "%s", stringToChar(actions[selection]->getNom()));
			
			//On change la position du pointeur
			selection = selectionTest;
			
			//On change la couleur de la nouvelle sélection
			if (actions[selection]->estFaisable(joueur))
				PA_SetTextTileCol(ecran, COULEUR_SELECTION);
			else
				PA_SetTextTileCol(ecran, COULEUR_SELECTION_IMPOSSIBLE);
			PA_OutputText(ecran, (int)(selection/maxY)*espaceX+x, (selection%maxY)*espaceY+y, "%s", stringToChar(actions[selection]->getNom()));
			
			//On joue le son
			//PA_PlaySimpleSound(5, bouge);
			
			//Affichage des infos du skill surligné
			actions[selection]->afficheDescriptionCombat(ecran, 1, 9);
			
		}
		
		
		//Si on valide
		if (boutonValide()) {
			if (actions[selection]->estFaisable(joueur)) {
				//PA_PlaySimpleSound(5, valide);
				choix = selection;
			}
			//else
				//PA_PlaySimpleSound(5, erreur);
		}

		PA_WaitForVBL();
	}
	
	return choix;
}


/**
 *	Affiche la barre de vie aux coordonnées indiquées
 */
void affichebarreVie(Personnage *joueur, int ecran, int x, int y, int tailleX, int tailleY) {

	int valeur= joueur->getPointsVie();
	int valeurMax = joueur->getPointsVieMax();
	int finBarre = (int)(tailleX*valeur/valeurMax);
	
	for(int i = 0 ; i < tailleY ; i++) {	//Traçage de toutes les lignes horizontales à la suite
		int couleur;
		if (i < (int)(tailleY/3))
			couleur = 254;
		else if (i >= (int)(2*tailleY/3))
			couleur = 252;
		else
			couleur = 253;
			
		PA_Draw8bitLine(ecran, x+finBarre, y+i, x+tailleX, y+i, 255);
		if (valeur > 0)
			PA_Draw8bitLine(ecran, x, y+i, x+finBarre, y+i, couleur);
	}
	
	return;
}

/**
 *	Affiche la barre de vie avec les coordonnées par défaut
 */
void afficheStatsVieCombat(Personnage *joueur) {
	affichebarreVie(joueur, 0, BARRES_POS_X, BARRES_POS_Y_VIE, BARRES_TAILLE_X, BARRES_TAILLE_Y);	//Affiche la barre de vie
	PA_OutputText(0, 1, 4, "            ");	//Efface le texte déjà présent
	PA_OutputText(0, 1, 4, "PV %d/%d", joueur->getPointsVie(), joueur->getPointsVieMax());	//Affichage des nouvelles données
	return;
}

/**
 *	Affiche la barre d'énergie aux coordonnées indiquées
 */
void affichebarreEnergie(Personnage *joueur, int ecran, int x, int y, int tailleX, int tailleY) {
	int valeur = joueur->getPointsEnergie();
	int valeurMax = joueur->getPointsEnergieMax();
	int finBarre = (int)(tailleX*valeur/valeurMax);
		
	for(int i = 0 ; i < tailleY ; i++) {	//Traçage de toutes les lignes horizontales à la suite
		int couleur;
		if (i < (int)(tailleY/3))
			couleur = 251;
		else if (i >= (int)(2*tailleY/3))
			couleur = 249;
		else
			couleur = 250;
			
		PA_Draw8bitLine(ecran, x+finBarre, y+i, x+tailleX, y+i, 255);
		if (valeur > 0)
			PA_Draw8bitLine(ecran, x, y+i, x+finBarre, y+i, couleur);
	}
	return;
}

/**
 *	Affiche la barre d'énergie avec les coordonnées par défaut
 */
void afficheStatsEnergieCombat(Personnage *joueur) {
	affichebarreEnergie(joueur, 0, BARRES_POS_X, BARRES_POS_Y_ENERGIE, BARRES_TAILLE_X, BARRES_TAILLE_Y);	//Affiche la barre d'énergie
	PA_OutputText(0, 1, 6, "            ");	//Efface le texte déjà présent
	PA_OutputText(0, 1, 6, "PE %d/%d", joueur->getPointsEnergie(), joueur->getPointsEnergieMax());	//Affichage des nouvelles données
	return;
}

/**
 *	Initialise les combats
 */
void initCombatGFX() {
	//Affichage des décors et personnages
	//Ecran du haut
	PA_ResetBgSysScreen(1);
	PA_ResetSpriteSys();
	PA_Init16bitBg(1, 3);
	PA_Load16bitBitmap(1, fondCombat01_Bitmap);
	
	//Ecran du bas
	PA_Init8bitBg(0, 3);
	PA_Load8bitBgPal(0,(void*)fondCadreCombat_Pal);
	PA_Load8bitBitmap(0,fondCadreCombat_Bitmap);
	
	PA_LoadSpritePal(1, 0, (void*)alpha_combat_Pal);
	PA_LoadSpritePal(1, 2, (void*)alpha_attaque_normale_Pal);
	PA_LoadSpritePal(1, 1, (void*)ennemi_Pal);
	
	PA_CreateSprite(1, ID_SPRITE_HEROS,(void*)alpha_combat_Sprite, OBJ_SIZE_32X64,1, 0, 9, 69);
	PA_CreateSprite(1, ID_SPRITE_ENNEMI,(void*)ennemi_Sprite, OBJ_SIZE_32X32,1, 1, 175, 85);
	
	//Couleurs
	PA_SetBgPalCol(0, 255, PA_RGB(5, 0, 0)); //255 : couleur de fond de barres de vie/énergie
	
	PA_SetBgPalCol(0, 254, PA_RGB(10, 31, 10)); //254 : vert clair (barre de vie)
	PA_SetBgPalCol(0, 253, PA_RGB(5, 29, 5)); //253 : vert (barre de vie)
	PA_SetBgPalCol(0, 252, PA_RGB(0, 27, 0)); //252 : vert foncé (barre de vie)
	
	PA_SetBgPalCol(0, 251, PA_RGB(31, 15, 10)); //251 : rouge clair (barre d'énergie)
	PA_SetBgPalCol(0, 250, PA_RGB(31, 10, 5)); //251 : rouge (barre d'énergie)
	PA_SetBgPalCol(0, 249, PA_RGB(31, 5, 0)); //251 : rouge foncé (barre d'énergie)
	
	return;
}

/**
 *	
 */
void initStats(Personnage *joueur) {
	std::vector<Attaque*> actions = joueur->getAttaques();
	for(u8 i = 0 ; i < actions.size() ; i++)
		actions[i]->appliqueBonus(joueur);
}

/**
 *	Fonction de combat
 */
 int combat(Personnage *joueur, Personnage *ennemi) {

	initCombatGFX();
	initStats(joueur);
	initStats(ennemi);

	//Variables du combat
	int tour = 0;
	bool attaquesDecouvertes[] = {false, false, false, false, false, false}; 
	
	while(1) {
		tour++;
		
		//Nom du perso
		PA_OutputText(0, 1, 1, "%s", stringToChar(joueur->getNom()));
		
		//Affichage des stats joueur
		PA_OutputText(0, 1, 4, "PV %d/%d", joueur->getPointsVie(), joueur->getPointsVieMax());
		PA_OutputText(0, 1, 6, "PE %d/%d", joueur->getPointsEnergie(), joueur->getPointsEnergieMax());
		
		//Affichage des stats de l'ennemi
		int coordY = 2;
		for(int i = 0 ; i < 5 ; i++) {
			if (attaquesDecouvertes[i])
				PA_OutputText(0, 16, coordY++, "%s", stringToChar(ennemi->getAttaque(i)->getNom()));
		}
		while(coordY < 7)
			PA_OutputText(0, 16, coordY++, "???");

		//Affichage des barres
		affichebarreVie(joueur, 0, BARRES_POS_X, BARRES_POS_Y_VIE, BARRES_TAILLE_X, BARRES_TAILLE_Y);		//Personnage, écran, posX, posY, tailleX, tailleY
		affichebarreEnergie(joueur, 0, BARRES_POS_X, BARRES_POS_Y_ENERGIE, BARRES_TAILLE_X, BARRES_TAILLE_Y);	//Personnage, écran, posX, posY, tailleX, tailleY

		//Affichage du numéro du tour
		PA_OutputText(1, 1, 18, "Tour %d", tour);
		
		//Fondu (apparition)
		if (tour == 1)
			fondu(2, -31, 0, 2);
		
		
		//DECISION DU JOUEUR
		//Récupération des attaques
		//std::vector<Attaque*> actions = joueur->getAttaques();
		//Menu de combat
		int decisionJoueur = menuCombat(joueur, 0, 1, 18, 3, 15, 2, 0);
		
		//Décision de l'ennemi (@TODO : une fonction IA)
		int decisionEnnemi = 0;
		do {
			decisionEnnemi = PA_RandMinMax(0, 5);
		} while(ennemi->getAttaque(decisionEnnemi)->getCoutEnergie() > ennemi->getPointsEnergie());
		
		//ATTAQUES + ANIMATIONS + TEXTES D'INFO
		//Si la vitesse du joueur est supérieure à celle de l'ennemi, on fait celle du joueur d'abord
		PA_InitText(1, 1);
		int fin = 0;	//0 : combat non terminé, 1 : joueur gagne, 2 : joueur perd
		if (joueur->getVitesse() >= ennemi->getVitesse()) {
			if (joueur->faitAttaque(decisionJoueur, ennemi, GAUCHE_DROITE))
				fin = 1;
			if (fin != 1 && ennemi->faitAttaque(decisionEnnemi, joueur, DROITE_GAUCHE))
				fin = 2;
		}
		else {
			if (ennemi->faitAttaque(decisionEnnemi, joueur, DROITE_GAUCHE))
				fin = 2;
			
			if (fin != 2 && joueur->faitAttaque(decisionJoueur, ennemi, GAUCHE_DROITE))
				fin = 1;
		}
		
		//Ajout de l'attaque à la liste des attaques vues
		if (ennemi->getAttaque(decisionEnnemi)->getId() > 1)
			attaquesDecouvertes[decisionEnnemi] = true;
			
		//Test de fin de combat (pré-poisons)
		if (fin != 0) {
			if (fin == 1)
				PA_OutputText(1, 1, 18, "%s est HS !", stringToChar(ennemi->getNom()));
			if (fin == 2)
				PA_OutputText(1, 1, 18, "%s est HS !", stringToChar(joueur->getNom()));
			boucleAppuie();
			joueur->initPE();
			joueur->initBonus();
			fondu(2, 0, -31, 2);
			clearEcranStatus(18);
			return fin;
		}
			
		//Evenements de fin du tour (poisons etc..)
		//TODO
		
		//Test de fin de combat (post-poisons)
		if (fin != 0) {
			//Fin de combat : remise à 0 des PE
			fondu(2, 0, -31, 2);
			
			return fin;
		}
			
		//Recharge des PE
		joueur->rechargePE();
		ennemi->rechargePE();
		
		//Réinitialisation du texte des écrans
		PA_InitText(0, 1);
		PA_InitText(1, 1);
	}
	while(1)
		PA_WaitForVBL();

	PA_ResetSpriteSys();
		
	return 0;
}
