#include <PA9.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include "gfx/all_gfx.h"

#include "Heros.h"
#include "Piece.h"
#include "Attaque.h"
#include "Define.cpp"

char* stringToChar(std::string chaine) {
	return (char*)chaine.c_str();
}

std::string intToString(int nombre) {
	std::ostringstream oss;
    oss << nombre;
   return oss.str();
}

char* intToChar(int nombre) {
	return stringToChar(intToString(nombre));
}

/**
 * 	Renvoit si le joueur valide avec le bouton de validation 
 */
bool boutonValide() {
	return Pad.Newpress.A;
}

/**
 * 	Renvoit si le joueur annule
 */
bool boutonAnnule() {
	return Pad.Newpress.B;
}

/**
 * 	Renvoit si le joueur appuie sur L
 */
bool boutonL() {
	return Pad.Newpress.L;
}

/**
 * 	Renvoit si le joueur appuie sur R
 */
bool boutonR() {
	return Pad.Newpress.R;
}

/**
 * 	Renvoit si le joueur appuie sur Select
 */
bool boutonSelect() {
	return Pad.Newpress.Select;
}

/**
 * 	Renvoit la direction appuyée par le joueur, ou -1 s'il n'appuie sur rien
 */
int appuieDirection() {
	int retour = -1;
	if (Pad.Newpress.Up)
		retour = COTE_HAUT;
	if (Pad.Newpress.Right)
		retour = COTE_DROITE;
	if (Pad.Newpress.Down)
		retour = COTE_BAS;
	if (Pad.Newpress.Left)
		retour = COTE_GAUCHE;
		
	return retour;
}


/**
 *	Pause le jeu jusqu'à ce qu'on appuie sur un bouton
 */
void boucleAppuie() {
	PA_CreateSprite(0, SPR_A, (void*)bouton_A_Sprite, OBJ_SIZE_16X16, 1, PAL_A, 235, 115);
	
	//Attente pré-boucle
	for(int i = 0 ; i < 10 ; i++)
		PA_WaitForVBL();
	//Boucle
	while(!boutonValide() && !boutonAnnule())
		PA_WaitForVBL();
	//Attente post-boucle
	for(int i = 0 ; i < 10 ; i++)
		PA_WaitForVBL();
	
	PA_DeleteSprite(0, SPR_A);
	
	return;
}

/**
 *	Supprime tout le texte présent sur un écran
 */
void nettoieEcran(int ecran) {
	for (int i = 0 ; i < 24 ; i++)
		PA_OutputText(0, 0, i, "                                ");
}

/**
 *	Résoud le bug de l'appui d'un bouton à peu de frames de décalage
 */
void resetBoutons() {
	for(int i = 0 ; i < 10 ; i++)
		PA_WaitForVBL();
	return;
}

/**
 * 	Menu : prend en paramètres un vecteur de textes (éléments du menu), l'écran, la position en x et en y du premier élément, la valeur par défaut et si le bouton "annule" est autorisé
 */
int menu(std::vector<std::string> textes, int ecran, int x, int y, int interligne, int defaut, bool retourPossible) {
	
	resetBoutons();
	
	//Couleur du texte normale
	PA_SetTextTileCol(ecran, COULEUR_TEXTE);
	//Boucle pour afficher chacune des lignes de proposition
	for(u8 i = 0 ; i < textes.size() ; i++) {
		//Changement de couleur si on est sur la proposition sélectionnée
		if (defaut == i)
			PA_SetTextTileCol(ecran, COULEUR_SELECTION);
		else
			PA_SetTextTileCol(ecran, COULEUR_TEXTE);
			
		PA_OutputText(ecran, x, (y+i)*interligne-1, (char*)(textes[i].c_str()));
	}
	
	int choix = -2;
	int selection = defaut;
	//Boucle jusqu'à validation ou annulation
	while(choix == -2) {
		//Si on appuie sur Haut ou Bas
		if ((Pad.Newpress.Up && selection != 0) || (Pad.Newpress.Down && selection != (int)textes.size()-1)) {
			//PA_PlaySimpleSound(5, bouge);
			PA_SetTextTileCol(ecran, COULEUR_TEXTE);
			PA_OutputText(ecran, x, (y+selection)*interligne-1, (char*)(textes[selection].c_str()));
			if (Pad.Newpress.Up)
				selection--;
			if (Pad.Newpress.Down)
				selection++;
			PA_SetTextTileCol(ecran, COULEUR_SELECTION);
			PA_OutputText(ecran, x, (y+selection)*interligne-1, (char*)(textes[selection].c_str()));
		}
		
		//Si on valide
		if (boutonValide()) {
			//PA_PlaySimpleSound(5, valide);
			choix = selection;
		}

		//Si on annule
		if (boutonAnnule()) {
			if (retourPossible) {
				//PA_PlaySimpleSound(5, annule);
				choix = -1;
			}
			//else
				//PA_PlaySimpleSound(5, erreur);
		}
		PA_WaitForVBL();
	}
	
	PA_SetTextTileCol(ecran, COULEUR_TEXTE);
	nettoieEcran(ecran);
	return choix;
}

/**
 *	Ecrit un texte d'obtention d'objet
 */
void objetObtenu(std::string objet, bool musique) {
	//Nettoyage de l'écran
	nettoieEcran(0);
		
	//TODO : musique
	
	//1ere lettre en majuscule
	//char lettre = objet.at(0);
	//lettre = std::toupper(lettre);
	//objet.replace(0, 1, &lettre);
	
	//Ecriture du texte
	PA_OutputText(0, 9, 5, "Objet obtenu :");
	int pasTexte = (int)((32-objet.length())/2);
	PA_SetTextTileCol(0, COULEUR_OBJET_OBTENU);
	PA_OutputText(0, pasTexte, 6, "%s", (char*)(stringToChar(objet)));
	PA_SetTextTileCol(0, COULEUR_TEXTE);
	
	//Attente
	boucleAppuie();
	nettoieEcran(0);
	
	return;
}

/**
 *	Affiche une page d'objets
 */
void afficheObjets(Heros* joueur, int ecran, int x, int y) {

	int pageObjet = 0;
	
	//Titre
	PA_SetTextTileCol(ecran, 6);	//Jaune
	PA_OutputText(ecran, x, y, "Objets");	
	PA_SetTextTileCol(ecran, 0);	//Normal
	
	//Affichage des objets
	int ligne = y+2;
	for (int i = OBJETS_PAR_PAGE*pageObjet ; i < OBJETS_PAR_PAGE*(pageObjet+1) && i < (int)(joueur->getObjets().size()); i++) {
		PA_OutputText(ecran, x, ligne++, "%s", stringToChar(joueur->getObjet(i)->getNomObjet()));	
	}
	
	//Affichage des boutons
	//PA_OutputText(ecran, x, ligne++, "%d", joueur->getObjets().size());	
	return;
}


/**
 *	Fait un fondu
 */
void fondu(int ecran, int debut, int fin, int duree) {
	if (debut > fin) 
		for (int i = debut; i >= fin; i--) {
			if (ecran == 2) {
				PA_SetBrightness(0, i);
				PA_SetBrightness(1, i);
			}
			else
				PA_SetBrightness(ecran, i);
			for(int j = 0 ; j < duree ; j++)
				PA_WaitForVBL();
		}
	else
		for (int i = debut; i <= fin; i++) {
			if (ecran == 2) {
				PA_SetBrightness(0, i);
				PA_SetBrightness(1, i);
			}
			else
				PA_SetBrightness(ecran, i);
			for(int j = 0 ; j < duree ; j++)
				PA_WaitForVBL();
		}
	return;
}
