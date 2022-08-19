#include <PA9.h>
#include <vector>
#include "Heros.h"

Heros::Heros() {
	pageObjet = 0;
	this->perso = new Personnage(0);
}

Heros::Heros(int x, int y) {
	setPosition(x, y);
	pageObjet = 0;
	this->perso = new Personnage(0);
}	

//Gestion du personnage
Personnage* Heros::getPerso() {
	return this->perso;	
}

void Heros::setPerso(Personnage* perso) {
	this->perso = perso;
	return;	
}

//Position du héros dans le laby

/**
 * 	Redéfinit la position du joueur
 */
void Heros::setPosition(int x, int y) {
	this->posX = x;
	this->posY = y;
	return;
}

/**
 * 	Redéfinit la position du joueur au tour précédent
 */
void Heros::setPositionPrecedente(int x, int y) {
	this->posPrecX = x;
	this->posPrecY = y;
	return;
}

/**
 * 	Renvoit la position en X du joueur
 */
int Heros::getPosX() {
	return posX;
}

/**
 * 	Renvoit la position en Y du joueur
 */
int Heros::getPosY() {
	return posY;
}

/**
 * 	Renvoit la position en X du joueur au dernier tour
 */
int Heros::getPosPrecX() {
	return posPrecX;
}

/**
 * 	Renvoit la position en Y du joueur au dernier tour
 */
int Heros::getPosPrecY() {
	return posPrecY;
}

/**
 *	Renvoit la direction du héros
 */
int Heros::getDir() {
	return dir;
}

/**
 * 	Redéfinit la position du joueur en X
 */
void Heros::setPosX(int x) {
	this->posX = x;
	return;
}

/**
 * 	Redéfinit la position du joueur en Y
 */
void Heros::setPosY(int y) {
	this->posY = y;
	return;
}

/**
 * 	Redéfinit la position du joueur en X au tour précédent
 */
void Heros::setPosPrecX(int x) {
	this->posPrecX = x;
	return;
}

/**
 * 	Redéfinit la position du joueur en Y au tour précédent
 */
void Heros::setPosPrecY(int y) {
	this->posPrecY = y;
	return;
}

/**
 *	Redéfinit la direction du héros
 */
void Heros::setDir(int dir) {
	this->dir = dir;
}


//Gestion de l'XP


//Objets

/**
 *	Ajoute un objet à la pile des objets
 */
int Heros::ajouteObjet(Piece* objet) {
	this->objets.push_back(objet);
	return this->objets.size();
}

/**
 *	Retire un objet à la pile des objets
 */
int Heros::retireObjet(Piece* objet) {
	for (int i = 0 ; i < (int)this->objets.size() ; i++)
		if (this->objets[i] == objet)
			this->objets.erase(this->objets.begin()+i);
	return this->objets.size();
}

/**
 *	Vérifie si le joueur possède un objet
 */
 bool Heros::possedeObjet(Piece* objet) {
	bool retour = false;
	for (int i = 0 ; i < (int)this->objets.size() ; i++)
		if (this->objets[i] == objet)
			retour = true;
	return retour;
}

/**
 *	Retourne la pile des objets
 */
std::vector<Piece*> Heros::getObjets() {
	return this->objets;
}

/**
 *
 */
Piece* Heros::getObjet(int index) {
	return this->objets[index];	
}





