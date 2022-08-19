#include <PA9.h>
#include "Laby.h"

#include "gfx/all_gfx.h"
#include "Define.cpp"

//Fonctions communes
char* stringToChar(std::string chaine);
void boucleAppuie();
bool combat(Personnage *joueur, Personnage *ennemi);
void fondu(int ecran, int debut, int fin, int duree);

//Constructeurs

/**
 *	Créé un laby vide
 */
Laby::Laby() {
	numSprites = 1;
}

/**
 *	Créé un laby aux dimensions données en paramètres
 */
Laby::Laby(int x, int y, Heros* joueur) {
	
	//Définition de la taille du laby
	tailleX = x;
	tailleY = y;
	
	//Gestion des sprites
	numSprites = 1;
	
	//Définition du héros
	this->joueur = joueur;
	
	//Redéfinition des vecteurs taille
	salles.resize(tailleX);
	for (int i = 0 ; i < tailleX ; i++) {
		salles[i].resize(tailleY);
		for (int j = 0 ; j < tailleY ; j++)
			//Construction du laby
			salles[i][j] = new Piece(i, j);
	}
	
	//Palettes
	chargePalettesLaby();
	
	//Menu
	pageMenu = 1;
	
	//Création du laby et des évènements
	genereEvenements(genereLaby());	
}


//Destructeur

Laby::~Laby() {

	for (int i = 0 ; i < tailleX ; i++)
		for (int j = 0 ; j < tailleY ; j++)
			delete salles[i][j];
}


//Fonction de création du laby

/**
 *	Génère le labyrinthe
 *	Sont en même temps générés les téléporteurs
 */
std::vector<Piece*> Laby::genereLaby() {

	int nbCases = (tailleX*tailleY)>>1;

	/**
	 *	GENERATION DU LABYRINTHE
	 */

	//Initialisation des piles
	std::vector<Piece*> pilePiece;	//Pile des pièces visitées
	std::vector<Piece*> pileCulSac;	//Piles des impasses
	std::vector<Piece*> pileTeleporteurs;	//Piles des téléporteurs (sortie)
	
	//Case de départ ...
	int posActuelleX = PA_RandMinMax(0, tailleX-1);
	int posActuelleY = PA_RandMinMax(0, tailleY-1);
	
	salles[posActuelleX][posActuelleY]->setSol();
	salles[posActuelleX][posActuelleY]->setValeur(1);
	
	//Boucle de création
	do {
		std::vector<int> directionsCassables = getMursCassables(posActuelleX, posActuelleY);
		//Pas de cul de sac : on creuse
		if (!directionsCassables.empty()) {
			//Décision de la direction à prendre
			int directionChoisie = directionsCassables[PA_RandMinMax(0, directionsCassables.size()-1)];
			
			//Ajout de la pièce actuelle à la file
			pilePiece.push_back(salles[posActuelleX][posActuelleY]);
			
			//Changement de position du pointeur
			switch(directionChoisie) {
				case COTE_HAUT : {
					posActuelleY--;
					break;
				}
				case COTE_DROITE : {
					posActuelleX++;
					break;
				}
				case COTE_BAS : {
					posActuelleY++;
					break;
				}
				case COTE_GAUCHE : {
					posActuelleX--;
					break;
				}
			}
			//Changement du type de terrain
			salles[posActuelleX][posActuelleY]->setValeur(1);
			salles[posActuelleX][posActuelleY]->setSol();
			
			//DEBUG, @TODO : DELETE
			//salles[posActuelleX][posActuelleY]->setVisite(true);
		}
		//Cul de sac, on revient en arrière
		else {
			//Téléport ou avancée simple ?
			bool teleport = (PA_RandMinMax(0, 100) <= P_TELEPORT);
			if (teleport
			&& salles[posActuelleX][posActuelleY]->getIdEvenement() == EVT_VIDE
			&& pileTeleporteurs.size() == 0) {
				//Nombre de boubles pour trouver un endroit d'arrivée pour le TP
				int compteurBoucle = nbCases;	
				int posTpX = 0;
				int posTpY = 0;
				
				//Cherche la position d'arrivée du TP
				do {
					posTpX = PA_RandMinMax(0, tailleX-1);
					posTpY = PA_RandMinMax(0, tailleY-1);
				} while (--compteurBoucle != 0
				&& !isTeleportable(posTpX, posTpY));
				
				//Si on n'a rien trouvé (compteur terminé), on ne fait pas de téléporteur
				if (compteurBoucle == 0)
					teleport = false;
					
				//Création du réléporteur
				if (teleport) {
					//Ajout de la pièce à la pile de retour et à la pile des télépoteurs
					pilePiece.push_back(salles[posActuelleX][posActuelleY]);
					pileTeleporteurs.push_back(salles[posActuelleX][posActuelleY]);
					
					//Changement de position dans le laby
					posActuelleX = posTpX;
					posActuelleY = posTpY;
					
					//Changement du type de terrain
					salles[posActuelleX][posActuelleY]->setValeur(1);
					salles[posActuelleX][posActuelleY]->setSol();
					
					//DEBUG, @TODO : DELETE
					//salles[posActuelleX][posActuelleY]->setVisite(true);
				}
			}
			//Si pas de téléport, on revient en arrière
			if (!teleport) {
				//Si c'est une impasse, on place la sortie du téléporteur
				if (pileTeleporteurs.size() > 0
				&& salles[posActuelleX][posActuelleY]->getIdEvenement() == EVT_VIDE) {
					int posTpX = pileTeleporteurs.back()->getPosX();
					int posTpY = pileTeleporteurs.back()->getPosY();
					
					salles[posActuelleX][posActuelleY]->creeEvenementLien(EVT_TELEPORT, salles[posTpX][posTpY]);
					salles[posTpX][posTpY]->creeEvenementLien(EVT_TELEPORT, salles[posActuelleX][posActuelleY]);
					
					pileTeleporteurs.pop_back();
				}
				else
					pileCulSac.push_back(salles[posActuelleX][posActuelleY]);
				
				//On boucle jusqu'à trouver une sortie
				do {
					if (pilePiece.back() == pileTeleporteurs.back())
						pileTeleporteurs.pop_back();
					posActuelleX = pilePiece.back()->getPosX();
					posActuelleY = pilePiece.back()->getPosY();
					pilePiece.pop_back();
			
				} while(!pilePiece.empty() && getNombreMursCassables(posActuelleX, posActuelleY) == 0);
			}
		}
		
		//DEBUG, @TODO : DELETE
		//Affiche progressivement la construction du laby
		/*
		joueur->setPosition(posActuelleX, posActuelleY);
		afficheApercu(5);
		for(int i = 0 ; i < 30 ; i++)
			PA_WaitForVBL();
		*/
	} while(!pilePiece.empty());	//Condition d'arrêt de la boucle générale : plus de pièces dans la liste
	
	return pileCulSac;
}

/**
 *	Place les évènements dans le laby
 *	Trois types d'évènements :
 *		- Evts fixes : entrée et sortie
 *		- Evts aléatoires : combats
 *		- Evts de parcours : clés et portes
 */
void Laby::genereEvenements(std::vector<Piece*> culSac) {

	int x;
	int y;
	int p;
	int evt;
	
	//Sortie
	evt = PA_RandMinMax(0, culSac.size()-1);
	x = culSac[evt]->getPosX();
	y = culSac[evt]->getPosY();
	salles[x][y]->creeEvenement(EVT_SORTIE);
	culSac.erase(culSac.begin()+evt);
	
	//Entrée
	evt = PA_RandMinMax(0, culSac.size()-1);
	x = culSac[evt]->getPosX();
	y = culSac[evt]->getPosY();
	joueur->setPosition(x, y);
	salles[x][y]->creeEvenement(EVT_ENTREE);
	salles[x][y]->setVisite(true);
	culSac.erase(culSac.begin()+evt);
	
	//Evenements de couloir aléatoires
	for(int i = 0 ; i < tailleX ; i++)
		for(int j = 0 ; j < tailleY ; j++) {
			p = PA_RandMinMax(0, 9);	//Une chance sur 10 d'avoir un évènement de couloir
			if (p == 0 && salles[i][j]->isSol() && salles[i][j]->getIdEvenement() == EVT_VIDE) {
				evt = PA_RandMinMax(0, 99);
				if (evt < P_COMBAT) {
					salles[i][j]->creeEvenement(EVT_COMBAT);
				}
			}
		}
	
	//Parcours du laby
	//Remise des valeurs à 0
	for(int i = 0 ; i < tailleX ; i++)
		for(int j = 0 ; j < tailleY ; j++) {
			salles[i][j]->setValeur(0);
		}
	
	//Variables
	std::vector<Piece*> pilePiece;	//Pile des pièces visitées
	std::vector<Piece*> pileClefs;	//Piles des clefs
	
	//Case de départ ...
	int posActuelleX = x;
	int posActuelleY = y;
	
	do {
		//on avance, si on peut
		bool avance = false;
		if (posActuelleX > 0
		&& salles[posActuelleX-1][posActuelleY]->isSol()
		&& salles[posActuelleX-1][posActuelleY]->getValeur() == 0) {
			pilePiece.push_back(salles[posActuelleX][posActuelleY]);
			posActuelleX = posActuelleX-1;
			salles[posActuelleX][posActuelleY]->setValeur(1);
			avance = true;		
		}
		else if (posActuelleX < tailleX-1
		&& salles[posActuelleX+1][posActuelleY]->isSol()
		&& salles[posActuelleX+1][posActuelleY]->getValeur() == 0) {
			pilePiece.push_back(salles[posActuelleX][posActuelleY]);
			posActuelleX = posActuelleX+1;
			salles[posActuelleX][posActuelleY]->setValeur(1);
			avance = true;		
		}
		else if (posActuelleY > 0
		&& salles[posActuelleX][posActuelleY-1]->isSol()
		&& salles[posActuelleX][posActuelleY-1]->getValeur() == 0) {
			pilePiece.push_back(salles[posActuelleX][posActuelleY]);
			posActuelleY = posActuelleY-1;
			salles[posActuelleX][posActuelleY]->setValeur(1);
			avance = true;		
		}
		else if (posActuelleY < tailleY-1
		&& salles[posActuelleX][posActuelleY+1]->isSol()
		&& salles[posActuelleX][posActuelleY+1]->getValeur() == 0) {
			pilePiece.push_back(salles[posActuelleX][posActuelleY]);
			posActuelleY = posActuelleY+1;
			salles[posActuelleX][posActuelleY]->setValeur(1);
			avance = true;		
		}
		
		//Evènements d'impasses
		if (!avance) {
			//On recule
			if (estImpasse(posActuelleX, posActuelleY)
			&& salles[posActuelleX][posActuelleY]->getIdEvenement() == EVT_VIDE) {
				if (PA_RandMinMax(0, 100) <= P_CLEF)
					pileClefs.push_back(salles[posActuelleX][posActuelleY]);
				else if (PA_RandMinMax(0, 100) <= P_REGEN) {
					salles[posActuelleX][posActuelleY]->creeEvenement(EVT_REGEN);
					salles[posActuelleX][posActuelleY]->setEvenementCode(PA_RandMinMax(1, 5));
				}
				else if (PA_RandMinMax(0, 100) <= P_MODULE) {
					salles[posActuelleX][posActuelleY]->creeEvenement(EVT_MODULE);
					salles[posActuelleX][posActuelleY]->setEvenementCode(PA_RandMinMax(0, 99));
				}
			}
			Piece* retour = pilePiece.back();
			posActuelleX = retour->getPosX();
			posActuelleY = retour->getPosY();
			pilePiece.pop_back();
			salles[posActuelleX][posActuelleY]->setValeur(2);
		}
		else {
			//Porte
			if (//salles[posActuelleX][posActuelleY]->getValeur() == 1
			/*&&*/ PA_RandMinMax(0, 100) <= P_PORTE
			&& !pileClefs.empty()
			&& salles[posActuelleX][posActuelleY]->getIdEvenement() == EVT_VIDE) {
				salles[posActuelleX][posActuelleY]->creeEvenementLien(EVT_PORTE, pileClefs.back());
				pileClefs.back()->creeEvenementLien(EVT_CLEF, salles[posActuelleX][posActuelleY]);
				pileClefs.back()->setEvenementCode(salles[posActuelleX][posActuelleY]->getEvenementCode());
				pileClefs.pop_back();
			}		
		}
		/*
		//DEBUG, @TODO : DELETE
		//Affiche le parcours
		joueur->setPosition(posActuelleX, posActuelleY);
		afficheApercu(5);
		for(int i = 0 ; i < 30 ; i++)
			PA_WaitForVBL();
		*/
	} while(!pilePiece.empty());
	
	//joueur->setPosition(x, y);
	
	return;
}

/**
 * 	Renvoir la liste des murs cassables d'une case
 */
std::vector<int> Laby::getMursCassables(int x, int y) {

	std::vector<int> mursCassable;			//Tableau retourné, contenant les différentes directions possibles (pour éviter les boucles inutiles à la création)
	for (int dir = 0 ; dir < 4 ; dir++) {	//Vérifie les 4 côtés
		if (!estBord(x, y, dir)) {	//Si cette direction ne pointe pas vers un des bords
			switch(dir) {					//Si la valeur de la case adjacente est 0 (non creusée), on le rajoute à la liste
				case COTE_HAUT:
					if(!solAdjascent(x, y-1, COTE_BAS)
					&& salles[x][y-1]->isMur())
						mursCassable.push_back(COTE_HAUT); break;
				case COTE_DROITE:
					if(!solAdjascent(x+1, y, COTE_GAUCHE)
					&& salles[x+1][y]->isMur())
						mursCassable.push_back(COTE_DROITE); break;
				case COTE_BAS:
					if(!solAdjascent(x, y+1, COTE_HAUT)
					&& salles[x][y+1]->isMur())
						mursCassable.push_back(COTE_BAS); break;
				case COTE_GAUCHE:
					if(!solAdjascent(x-1, y, COTE_DROITE)
					&& salles[x-1][y]->isMur())
						mursCassable.push_back(COTE_GAUCHE); break;
				default: break;
			}
		}
	}
	return mursCassable;
}

/**
 *	regarde si la case est propice à être construite (sans rien dessus ni autour)
 */
bool Laby::isTeleportable(int x, int y) {
	bool retour = true;
	if (salles[x][y]->isSol())
		retour = false;
		
	if (retour == true
	&& (salles[x-1][y-1]->isSol()
	|| salles[x+1][y-1]->isSol()
	|| salles[x+1][y+1]->isSol()
	|| salles[x-1][y+1]->isSol()))
		retour = false;
		
	if (retour == true
	&& getNombreMursCassables(x, y) == 0)
		retour = false;
		
	return retour;
}


/**
 * 	Renvoi le nombre de murs cassables d'une case
 */
int Laby::getNombreMursCassables(int x, int y) {

	int mursCassable = 0;
	for (int dir = 0 ; dir < 4 ; dir++) {	//Vérifie les 4 côtés
		if (!estBord(x, y, dir)) {	//Si cette direction ne pointe pas vers un des bords
			switch(dir) {					//Si la valeur de la case adjacente est 0 (non creusée), on le rajoute à la liste
				case COTE_HAUT:
					if(!solAdjascent(x, y-1, COTE_BAS)
					&& salles[x][y-1]->isMur())
						mursCassable++; break;
				case COTE_DROITE:
					if(!solAdjascent(x+1, y, COTE_GAUCHE)
					&& salles[x+1][y]->isMur())
						mursCassable++; break;
				case COTE_BAS:
					if(!solAdjascent(x, y+1, COTE_HAUT)
					&& salles[x][y+1]->isMur())
						mursCassable++; break;
				case COTE_GAUCHE:
					if(!solAdjascent(x-1, y, COTE_DROITE)
					&& salles[x-1][y]->isMur())
						mursCassable++; break;
				default: break;
			}
		}
	}
	return mursCassable;
}

/**
 * 	Renvoir la liste des murs cassables d'une case
 */
bool Laby::solAdjascent(int x, int y, int interdit) {

	bool retour = false;
	for (int dir = 0 ; dir < 4 ; dir++) {	//Vérifie les 4 côtés
		if (dir != interdit && !estBord(x, y, dir)) {	//Si cette direction ne pointe pas vers un des bords
			switch(dir) {					//Si la salle est sol, on le rajoute à la liste
				case COTE_HAUT:
					if(salles[x][y-1]->isSol())
						retour = true; break;
				case COTE_DROITE:
					if(salles[x+1][y]->isSol())
						retour = true; break;
				case COTE_BAS:
					if(salles[x][y+1]->isSol())
						retour = true; break;
				case COTE_GAUCHE:
					if(salles[x-1][y]->isSol())
						retour = true; break;
				default: break;
			}
		}		
	}
	return retour;
}


//Fonction d'affichage

/**
 * 	Affiche le labyrinthe sur l'écran du bas (0)
 */
void Laby::afficheLaby() {
	int blanc = PA_RGB(31, 31, 31);
	PA_Init16bitBg(0, 0);
	//Taille auto. des cellules
	int tailleCell;
	int tailleCellX = 256/tailleX;
	int tailleCellY = 192/tailleY;
	if (tailleCellX < tailleCellY)
		tailleCell = tailleCellX;
	else
		tailleCell = tailleCellY;
	
	//Lignes du haut et de gauche
	PA_Draw16bitLine	(0, 0, 0, 0, tailleY*tailleCell, blanc);
	PA_Draw16bitLine	(0, 0, 0, tailleX*tailleCell, 0, blanc);
	
	//Lignes du bas et de droite de chaque salle
	for(int i=0 ; i<tailleX ; i++)
		for(int j=0 ; j<tailleY ; j++) {
			//Affichage des lignes
			if (!this->estOuvert(i, j, COTE_DROITE))
				PA_Draw16bitLine(0, tailleCell*i+tailleCell, tailleCell*j, tailleCell*i+tailleCell, tailleCell*j+tailleCell, blanc);
			if (!this->estOuvert(i, j, COTE_BAS))
				PA_Draw16bitLine(0, tailleCell*i, tailleCell*j+tailleCell, tailleCell*i+tailleCell, tailleCell*j+tailleCell, blanc);
			if (joueur->getPosX() == i && joueur->getPosY() == j)
				PA_Draw16bitRect(0, tailleCell*i+1, tailleCell*j+1, tailleCell*(i+1), tailleCell*(j+1), PA_RGB(31, 10, 10));
		}

}

/**
 *	Reset l'affichage du laby (rechargement GFX et réaffichage)
 */
void Laby::resetAffichageLaby() {
	PA_ResetBgSysScreen(1);
	PA_LoadTiledBg(1, 3, fondLaby);
	for (int i = 0 ; i < 32 ; i++)
		for (int j = 0 ; j < 24; j++)
			PA_SetMapTileAll(1, 0,	i, j, 0);
}

/**
 *	Regénère le personnage sur le laby
 */
void Laby::resetAffichageLabyHero() {
	PA_DeleteSprite(1, SPR_HERO);
	PA_CreateSprite(1, SPR_HERO, (void*)map_hero_Sprite, OBJ_SIZE_16X32, 1, PAL_HERO, 112, 66);
	
	switch(joueur->getDir()) {
		case COTE_HAUT:
			PA_StartSpriteAnim(1, SPR_HERO, 8, 11, 6);
		break;
		case COTE_DROITE:
			PA_StartSpriteAnim(1, SPR_HERO, 4, 7, 6);
			PA_SetSpriteHflip(1, SPR_HERO, 0);
		break;
		case COTE_BAS:
			PA_StartSpriteAnim(1, SPR_HERO, 0, 3, 6);
		break;
		case COTE_GAUCHE:
			PA_SetSpriteHflip(1, SPR_HERO, 1);
			PA_StartSpriteAnim(1, SPR_HERO, 4, 7, 6);
		break;
		default: break;
	}
}

/**
 * 	Affiche l'aperçu du labyrinthe sur l'écran du haut (1)
 */
void Laby::afficheApercu(int nombreCases) {

	int infX = 7;
	int infY = 5;
	
	//SUPPRESSION DES SPRITES
	for(int i = 1 ; i < numSprites ; i++)
		PA_DeleteSprite(1, i);
	numSprites = 1;
	resetAffichageLabyHero();
	
	//AFFICHAGE DU LABY
	
	for (int y = 0 ; y < 24 ; y++)
		for (int x = 0 ; x < 32; x++) {
			//PA_OutputText(1, x, y, " ");
			//Place pour le bloc de niveau
			if (x < 11  && y < 2)
				PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[0]);
			else {
				//Définit dans quel coin du bloc de 16x16 on se situe
				bool gauche = !(x & 1);
				bool haut = !(y & 1);
				//Position dans le labyrinthe (peut être négatif et supérieur à la taille du laby)
				int xLaby = joueur->getPosX() - infX + (x-(gauche?0:1))/2;
				int yLaby = joueur->getPosY() - infY + (y-(haut?0:1))/2;
						
				if (getTileApercue(x, y)) {
					//On vérifie si c'est le sol
					if (xLaby >= 0 && yLaby >= 0
					&& xLaby < tailleX
					&& yLaby < tailleY
					&& salles[xLaby][yLaby]->isSol())
					{
						//Pièces visitées
						if (getVisite(xLaby, yLaby)
						|| getVisite(xLaby-1, yLaby)
						|| getVisite(xLaby, yLaby-1)
						|| getVisite(xLaby+1, yLaby)
						|| getVisite(xLaby, yLaby+1))
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[1]);
						else {
							//Coins à la place des pièces non visitées
							if (gauche && haut)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[10]);
							else if (!gauche && haut)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[11]);
							else if (gauche && !haut)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[12]);
							else if (!gauche && !haut)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[13]);
						}						
					}
					//Si ce n'est pas un sol mais qu'on est dans le laby
					else if (xLaby >= 0 && yLaby >= 0
					&& xLaby < tailleX
					&& yLaby < tailleY) {
						//On regarde quel est le côté du bloc de 16*16 concerné
						if (gauche && haut) {
							int mur = 0;
							if (xLaby > 0 && salles[xLaby-1][yLaby]->isSol() && getVisite(xLaby-1, yLaby))
								mur += 1;
							if (yLaby > 0 && salles[xLaby][yLaby-1]->isSol() && getVisite(xLaby, yLaby-1))
								mur += 10;
								
							if (mur == 1)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[4]);
							else if (mur == 10)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[3]);
							else if (mur == 11)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[6]);
							else if (xLaby > 0 && yLaby > 0 &&
									salles[xLaby-1][yLaby-1]->isSol())
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[10]);
							else
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[0]);
							
						}
						else if (!gauche && haut) {
							int mur = 0;
							if (xLaby < tailleX-1 && salles[xLaby+1][yLaby]->isSol() && getVisite(xLaby+1, yLaby))
								mur += 1;
							if (yLaby > 0 && salles[xLaby][yLaby-1]->isSol() && getVisite(xLaby, yLaby-1))
								mur += 10;
								
							if (mur == 1)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[5]);
							else if (mur == 10)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[3]);
							else if (mur == 11)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[7]);
							else if (xLaby < tailleX-1 && yLaby > 0 && 
									salles[xLaby+1][yLaby-1]->isSol())
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[11]);
							else
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[0]);
						}
						else if (gauche && !haut) {
							int mur = 0;
							if (xLaby > 0 && salles[xLaby-1][yLaby]->isSol() && getVisite(xLaby-1, yLaby))
								mur += 1;
							if (yLaby < tailleY-1 && salles[xLaby][yLaby+1]->isSol() && getVisite(xLaby, yLaby+1))
								mur += 10;
								
							if (mur == 1)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[4]);
							else if (mur == 10)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[2]);
							else if (mur == 11)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[8]);
							else if (xLaby > 0 && yLaby < tailleY-1 && 
									salles[xLaby-1][yLaby+1]->isSol())
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[12]);
							else
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[0]);
						}
						else if (!gauche && !haut) {
							int mur = 0;
							if (xLaby < tailleX-1 && salles[xLaby+1][yLaby]->isSol() && getVisite(xLaby+1, yLaby))
								mur += 1;
							if (yLaby < tailleY-1 && salles[xLaby][yLaby+1]->isSol() && getVisite(xLaby, yLaby+1))
								mur += 10;
								
							if (mur == 1)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[5]);
							else if (mur == 10)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[2]);
							else if (mur == 11)
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[9]);
							else if (xLaby < tailleX-1 && yLaby < tailleY-1 && 
									salles[xLaby+1][yLaby+1]->isSol())
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[13]);
							else
								PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[0]);
						}
						else
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[0]);
					}
					//Pour chaque bord du laby
					//Gauche
					else if(xLaby == -1 
					&& yLaby >= 0 && yLaby < tailleY			
					&& !gauche
					&& !(haut && yLaby == 0 && !salles[xLaby+1][yLaby]->isSol())
					&& !(!haut && yLaby == tailleY-1 && !salles[xLaby+1][yLaby]->isSol())) {
						if (salles[xLaby+1][yLaby]->isSol())
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[5]);
						else if (!gauche && haut && yLaby >= 0 &&
								salles[xLaby+1][yLaby-1]->isSol())
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[11]);
						else if (!gauche && !haut && yLaby < tailleY+1 &&
								salles[xLaby+1][yLaby+1]->isSol())
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[13]);
						else
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[0]);
					}
					//Droite
					else if(xLaby == tailleX
					&& yLaby >= 0 && yLaby < tailleY	
					&& gauche
					&& !(haut && yLaby == 0 && !salles[xLaby-1][yLaby]->isSol())
					&& !(!haut && yLaby == tailleY-1 && !salles[xLaby-1][yLaby]->isSol())) {
						if (salles[xLaby-1][yLaby]->isSol())
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[4]);
						else if (gauche && haut && yLaby >= 0 &&
							salles[xLaby-1][yLaby-1]->isSol())
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[10]);
						else if (gauche && !haut && yLaby < tailleY+1 &&
							salles[xLaby-1][yLaby+1]->isSol())
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[12]);
						else
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[0]);
					}
					//Haut
					else if(yLaby == -1
					&& xLaby >= 0 && xLaby < tailleX
					&& !haut
					&& !(gauche && xLaby == 0 && !salles[xLaby][yLaby+1]->isSol())
					&& !(!gauche && xLaby == tailleX-1 && !salles[xLaby][yLaby+1]->isSol())) {
						if (salles[xLaby][yLaby+1]->isSol())
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[2]);
						else if (gauche && !haut && xLaby >= 0 &&
							salles[xLaby-1][yLaby+1]->isSol())
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[12]);
						else if (!gauche && !haut && xLaby < tailleX+1 &&
							salles[xLaby+1][yLaby+1]->isSol())
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[13]);
						else
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[0]);
					}
					//Bas
					else if(yLaby == tailleY
					&& xLaby >= 0 && xLaby < tailleX
					&& haut
					&& !(gauche && xLaby == 0 && !salles[xLaby][yLaby-1]->isSol())
					&& !(!gauche && xLaby == tailleX-1 && !salles[xLaby][yLaby-1]->isSol())) {
						if (salles[xLaby][yLaby-1]->isSol())
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[3]);
						else if (gauche && haut && xLaby >= 0 &&
							salles[xLaby-1][yLaby-1]->isSol())
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[10]);
						else if (!gauche && haut && xLaby < tailleX+1 &&
							salles[xLaby+1][yLaby-1]->isSol())
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[11]);
						else
							PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[0]);
					}
					
					//Dans les coins extrêmes
					
					//Haut gauche
					else if (xLaby == -1 && yLaby == -1
							&& !gauche && !haut
							&& salles[xLaby+1][yLaby+1]->isSol())
						PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[13]);
					//Bas gauche
					else if (xLaby == -1 && yLaby == tailleY
							&& !gauche && haut
							&& salles[xLaby+1][yLaby-1]->isSol())
						PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[11]);
					//Haut droit
					else if (xLaby == tailleX && yLaby == -1
							&& gauche && !haut
							&& salles[xLaby-1][yLaby+1]->isSol())
						PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[12]);
					//Bas droit
					else if (xLaby == tailleX && yLaby == tailleY
						&& gauche && haut
						&& salles[xLaby-1][yLaby-1]->isSol())
					PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[10]);
					//En dehors du laby
					else
						PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[0]);
				}
				else
					PA_SetMapTileAll(1, 3,	x, y, fondLaby_Map[0]);
				
				//AFFICHAGE DES EVENEMENTS
				if (xLaby >= 0 && yLaby >= 0
				&& xLaby < tailleX
				&& yLaby < tailleY
				&& haut && gauche
				&& salles[xLaby][yLaby]->isSol()
				&& salles[xLaby][yLaby]->getIdEvenement() != EVT_VIDE
				&& salles[xLaby][yLaby]->getEvenementVisible()
				&& getPieceApercue(xLaby, yLaby)) {
					switch(salles[xLaby][yLaby]->getIdEvenement()) {
						case EVT_SORTIE : {
							PA_CreateSprite(1, numSprites++,(void*)map_escalier_Sprite, OBJ_SIZE_16X16, 1, PAL_ESCALIER, x<<3, y<<3);
							break;
						}
						case EVT_TELEPORT : {
							PA_CreateSprite(1, numSprites++,(void*)map_teleporteur_Sprite, OBJ_SIZE_16X16, 1, PAL_TELEPORT, x<<3, y<<3);
							break;
						}
						case EVT_COMBAT : {
							PA_CreateSprite(1, numSprites++,(void*)map_combat_Sprite, OBJ_SIZE_16X16, 1, PAL_COMBAT, x<<3, y<<3);
							break;
						}
						case EVT_MODULE : {
							PA_CreateSprite(1, numSprites++,(void*)map_coffre_Sprite, OBJ_SIZE_16X16, 1, PAL_COFFRE, x<<3, y<<3);
							break;
						}
						case EVT_REGEN : {
							PA_CreateSprite(1, numSprites++,(void*)map_regen_Sprite, OBJ_SIZE_16X16, 1, PAL_REGEN, x<<3, y<<3);
							PA_SetSpriteAnim(1, numSprites-1, salles[xLaby][yLaby]->getEvenementCode()>0?0:1);
							break;
						}
						case EVT_PORTE : {
							PA_CreateSprite(1, numSprites++,(void*)map_porte_Sprite, OBJ_SIZE_16X16, 1, PAL_PORTE, x<<3, y<<3);
							break;
						}
						case EVT_CLEF : {
							PA_CreateSprite(1, numSprites++,(void*)map_coffre_Sprite, OBJ_SIZE_16X16, 1, PAL_COFFRE, x<<3, y<<3);
							break;
						}
					}
				}
			}
		}	
	return;
}

/**
 * 	Affiche l'aperçu du labyrinthe sur l'écran du haut (1)
 *	Le nombre de cases est celui autour du perso
 */
void Laby::afficheApercuOld(int nombreCases) {

	//Définition des couleurs
	int couleurMurs = PA_RGB(31, 31, 31);
	int couleurFond = PA_RGB(0, 0, 0);
	int couleurApercu = PA_RGB(10, 10, 10);
	int couleurJoueur = PA_RGB(31, 10, 10);
	
	//Taille auto. des cellules
	int tailleCell = 17;
	
	//Bordures pour centrer l'aperçu à l'écran
	int bordureX = (256-(nombreCases*2+1)*tailleCell)/2;
	int bordureY = (192-(nombreCases*2+1)*tailleCell)/2;
	
	//Masquer l'ancien aperçu
	//Gauche
	if (joueur->getPosX() < nombreCases)
		
		PA_Draw16bitRect(1, bordureX,
							bordureY,
							bordureX+tailleCell*(nombreCases-joueur->getPosX()),
							bordureY+tailleCell*(nombreCases*2+1),
						couleurFond);
	//Haut
	if (joueur->getPosY() < nombreCases)
		PA_Draw16bitRect(1, bordureX,
							bordureY,
							bordureX+tailleCell*(nombreCases*2+1),
							bordureY+tailleCell*(nombreCases-joueur->getPosY()),
						couleurFond);
	//Droite
	if (this->tailleX - joueur->getPosX() < nombreCases)
		PA_Draw16bitRect(1, bordureX+(nombreCases+(tailleX-joueur->getPosX()))*tailleCell,
							0,
							256,
							192,
						couleurFond);
	//Bas
	if (this->tailleY - joueur->getPosY() < nombreCases)
		PA_Draw16bitRect(1, 0,
							bordureY+(nombreCases+(tailleY-joueur->getPosY()))*tailleCell,
							256,
							192,
						couleurFond);
	
	//Positions à afficher
	int graphX = 0;
	int graphY;
	
	//DEBUG
	/*
	PA_Draw16bitRect(1, 0,
						0,
						256,
						192,
					couleurJoueur);
	*/
	
	//Effacement des murs
	
	for(int i=0 ; i<256/tailleCell ; i++) {
		PA_Draw16bitLine(1, tailleCell*i+bordureX,
							0,
							tailleCell*i+bordureX,
							192,
						couleurFond);
	}
	for(int i=0 ; i<192/tailleCell ; i++) {
		PA_Draw16bitLine(1, 0,
							tailleCell*i+bordureY,
							256,
							tailleCell*i+bordureY,
						couleurFond);
	}
	
	//Suppression des anciennes sprites
	for (int i = 0 ; i <= numSprites ; i++) {
		PA_DeleteSprite(1, i);
	}
	numSprites = 0;
	
	//Lignes du bas et de droite de chaque salle
	for(int i=joueur->getPosX()-nombreCases ; i<joueur->getPosX()+nombreCases ; i++) {
		graphY = 0;
		
		if (i >=0 && i < tailleX) {
			for(int j=joueur->getPosY()-nombreCases ; j<joueur->getPosY()+nombreCases ; j++) {
				if (j >=0 && j < tailleY) {
				
					//Si la salle n'a jamais été visitée, on efface le fond
					if (!salles[i][j]->getApercu() && !salles[i][j]->getVisite()) {
						PA_Draw16bitRect(1, tailleCell*graphX+1+bordureX,
											tailleCell*graphY+1+bordureY,
											tailleCell*(graphX+1)+bordureX,
											tailleCell*(graphY+1)+bordureY,
										couleurFond);
					}
					//On affiche la salle uniquement si elle a déjà été visitée
					if (salles[i][j]->getApercu() ) {
						PA_Draw16bitRect(1, tailleCell*graphX+1+bordureX,
											tailleCell*graphY+1+bordureY,
											tailleCell*(graphX+1)+bordureX,
											tailleCell*(graphY+1)+bordureY,
										couleurApercu);
					
						
						//Evenements : on affiche l'évènement que si le joueur n'est pas dessus
						if (salles[i][j]->getIdEvenement() != EVT_VIDE && salles[i][j]->getEvenementVisible() && (i != joueur->getPosX() || j != joueur->getPosY()))	{
							switch(salles[i][j]->getTypeEvenement()) {
								
								case TYPE_EVT_DIVERS :
									if (salles[i][j]->getIdEvenement() == EVT_SORTIE)
										PA_CreateSprite(1, numSprites++,(void*)map_escalier_Sprite, OBJ_SIZE_16X16,1, PAL_ESCALIER, tailleCell*graphX+1+bordureX, tailleCell*graphY+1+bordureY);
									if (salles[i][j]->getIdEvenement() == EVT_LEVEL_UP)
										PA_CreateSprite(1, numSprites++,(void*)map_coffre_Sprite, OBJ_SIZE_16X16,1, PAL_COFFRE, tailleCell*graphX+1+bordureX, tailleCell*graphY+1+bordureY);
								break;
								case TYPE_EVT_TELEPORT :
									PA_CreateSprite(1, numSprites++,(void*)map_teleporteur_Sprite, OBJ_SIZE_16X16,1, PAL_TELEPORT, tailleCell*graphX+1+bordureX, tailleCell*graphY+1+bordureY);
								break;
								
								case TYPE_EVT_MONSTRE :
									PA_CreateSprite(1, numSprites++,(void*)map_combat_Sprite, OBJ_SIZE_16X16,1, PAL_COMBAT, tailleCell*graphX+1+bordureX, tailleCell*graphY+1+bordureY);
								break;
								
								case TYPE_EVT_PORTE :
									if (salles[i][j]->getIdEvenement() == EVT_PORTE)
										PA_CreateSprite(1, numSprites++,(void*)map_porte_Sprite, OBJ_SIZE_16X16,1, PAL_PORTE, tailleCell*graphX+1+bordureX, tailleCell*graphY+1+bordureY);
									else
									if (salles[i][j]->getIdEvenement() == EVT_CLEF)
										PA_CreateSprite(1, numSprites++,(void*)map_coffre_Sprite, OBJ_SIZE_16X16,1, PAL_COFFRE, tailleCell*graphX+1+bordureX, tailleCell*graphY+1+bordureY);
								break;
								
							}
						}
					}
										
					if (salles[i][j]->getVisite()) {
						
						if (!estOuvert(i, j, COTE_HAUT)) {
							PA_Draw16bitLine(1, tailleCell*graphX+bordureX,
												tailleCell*graphY+bordureY,
												tailleCell*graphX+tailleCell+bordureX,
												tailleCell*graphY+bordureY,
											couleurMurs);
						}
						if (!estOuvert(i, j, COTE_DROITE)) {
							PA_Draw16bitLine(1, tailleCell*graphX+tailleCell+bordureX,
												tailleCell*graphY+bordureY,
												tailleCell*graphX+tailleCell+bordureX,
												tailleCell*graphY+tailleCell+bordureY,
											couleurMurs);
						}
						if (!estOuvert(i, j, COTE_BAS)) {
							PA_Draw16bitLine(1, tailleCell*graphX+bordureX,
												tailleCell*graphY+tailleCell+bordureY,
												tailleCell*graphX+tailleCell+bordureX,
												tailleCell*graphY+tailleCell+bordureY,
											couleurMurs);
						}
						if (!estOuvert(i, j, COTE_GAUCHE)) {
							PA_Draw16bitLine(1, tailleCell*graphX+bordureX,
												tailleCell*graphY+bordureY,
												tailleCell*graphX+bordureX,
												tailleCell*graphY+tailleCell+bordureY,
											couleurMurs);
						}
						
						if (joueur->getPosX() == i && joueur->getPosY() == j)
							PA_Draw16bitRect(1, tailleCell*graphX+1+bordureX,
												tailleCell*graphY+1+bordureY,
												tailleCell*(graphX+1)+bordureX,
												tailleCell*(graphY+1)+bordureY,
											couleurJoueur);
					}
				}
				graphY++;
			}
		}
		
		graphX++;
	}
	
}


//Fonctions liées aux pièces du laby

/**
 * 	Renvoit un pointeur vers la pièce de coordonnées x, y
 */
Piece* Laby::getPiece(int x, int y) {
	return salles[x][y];
}

/**
 * 	Renvoie si la direction dir de la case pointée par x et y pointe vers le bord du laby
 */
bool Laby::estBord(int x, int y, int dir) {
	bool retour = false;
	switch(dir) {
		case COTE_HAUT: if (y == 0) retour = true; break;
		case COTE_DROITE: if (x == tailleX-1) retour = true; break;
		case COTE_BAS: if (y == tailleY-1) retour = true; break;
		case COTE_GAUCHE: if (x == 0) retour = true; break;
		default: break;
	}
	
	return retour;
}

/**
 *	Vérifie si la case est une impasse
 */
bool Laby::estImpasse(int x, int y) {
	int ouvertures = 0;
	for (int dir = 0 ; dir < 4 ; dir++) {	//Vérifie les 4 côtés
		if (!estBord(x, y, dir)) {	//Si cette direction ne pointe pas vers un des bords
			switch(dir) {					//Si la valeur de la case adjacente est 0 (non creusée), on le rajoute à la liste
				case COTE_HAUT:
					if(salles[x][y-1]->isSol())
						ouvertures++; break;
				case COTE_DROITE:
					if(salles[x+1][y]->isSol())
						ouvertures++; break;
				case COTE_BAS:
					if(salles[x][y+1]->isSol())
						ouvertures++; break;
				case COTE_GAUCHE:
					if(salles[x-1][y]->isSol())
						ouvertures++; break;
				default: break;
			}
		}
	}
	return ouvertures==1;
}

/**
 *	Renvoie le nombre d'ouvertures d'une pièce
 */
int Laby::getNombreOuvertures(int x, int y) {
	int ouvertures = 0;
	for (int dir = 0 ; dir < 4 ; dir++) {	//Vérifie les 4 côtés
		if (!estBord(x, y, dir)) {	//Si cette direction ne pointe pas vers un des bords
			switch(dir) {					//Si la valeur de la case adjacente est 0 (non creusée), on le rajoute à la liste
				case COTE_HAUT:
					if(salles[x][y-1]->isSol())
						ouvertures++; break;
				case COTE_DROITE:
					if(salles[x+1][y]->isSol())
						ouvertures++; break;
				case COTE_BAS:
					if(salles[x][y+1]->isSol())
						ouvertures++; break;
				case COTE_GAUCHE:
					if(salles[x-1][y]->isSol())
						ouvertures++; break;
				default: break;
			}
		}
	}
	return ouvertures;
}

/**
 * 	Regarde si la pièce(x, y) est ouverte dans la direction dir
 */
bool Laby::estOuvert(int x, int y, int dir) {
	bool retour = false;
	switch(dir) {
		case COTE_HAUT: 	
			if (!estBord(x, y, COTE_HAUT))
				retour = salles[x][y-1]->isSol();
			break;
		case COTE_DROITE:	
			if (!estBord(x, y, COTE_DROITE))
				retour = salles[x+1][y]->isSol();
			break;
		case COTE_BAS:	
			if (!estBord(x, y, COTE_BAS))
				retour = salles[x][y+1]->isSol();
			break;
		case COTE_GAUCHE:	
			if (!estBord(x, y, COTE_GAUCHE))
				retour = salles[x-1][y]->isSol();
			break;
		default: break;
	}
	
	return retour;
}

/**
 *	Vérifie si une direction est bloquée (évènement genre "porte")
 */
bool Laby::estBloque(int x, int y, int dir) {
	bool retour = false;
	switch(dir) {
		case COTE_HAUT: 	
			if (!estBord(x, y, COTE_HAUT))
				retour = salles[x][y-1]->estSolide();
			break;
		case COTE_DROITE:	
			if (!estBord(x, y, COTE_DROITE))
				retour = salles[x+1][y]->estSolide();
			break;
		case COTE_BAS:	
			if (!estBord(x, y, COTE_BAS))
				retour = salles[x][y+1]->estSolide();
			break;
		case COTE_GAUCHE:	
			if (!estBord(x, y, COTE_GAUCHE))
				retour = salles[x-1][y]->estSolide();
			break;
		default: break;
	}
	
	return retour;
}

/**
 *
 */
std::vector<int> Laby::getOuvertures(int x, int y) {
	std::vector<int> retour;
	for(int dir = 0 ; dir < 4 ; dir++) {
		if (this->estOuvert(x, y, dir))
			retour.push_back(dir);
	}
	return retour;
}

/**
 *	Regarde si la salle a été visitée
 */
 bool Laby::getVisite(int x, int y) {
	if (x < tailleX && y < tailleY && x >= 0 && y >= 0)
		return salles[x][y]->getVisite();
	else
		return false;
}

/**
 *	Regarde si la tile a été aperçue
 */
 bool Laby::getTileApercue(int x, int y) {
	int infX = 7;
	int infY = 5;
	bool gauche = !(x & 1);
	bool haut = !(y & 1);
	int xLaby = joueur->getPosX() - infX + (x-(gauche?0:1))/2;
	int yLaby = joueur->getPosY() - infY + (y-(haut?0:1))/2;
	
	bool retour = false;
	
	//Si c'est le sol
	if (getVisite(xLaby, yLaby))
		retour = true;
	
	if (haut && gauche && (
	getVisite(xLaby-1, yLaby-1)
	|| getVisite(xLaby, yLaby-1)
	|| getVisite(xLaby-1, yLaby)))
		retour = true;
	
	if (haut && !gauche && (
	getVisite(xLaby+1, yLaby-1)
	|| getVisite(xLaby, yLaby-1)
	|| getVisite(xLaby+1, yLaby)))
		retour = true;
	
	if (!haut && !gauche && (
	getVisite(xLaby+1, yLaby+1)
	|| getVisite(xLaby, yLaby+1)
	|| getVisite(xLaby+1, yLaby)))
		retour = true;
	
	if (!haut && gauche && (
	getVisite(xLaby-1, yLaby+1)
	|| getVisite(xLaby, yLaby+1)
	|| getVisite(xLaby-1, yLaby)))
		retour = true;
	
	return retour;
 }
 
 /**
  *	Regarde si la pièce a été aperçue
  */
 bool Laby::getPieceApercue(int i, int j) {
	return (getVisite(i, j) || getVisite(i-1, j) || getVisite(i+1, j) || getVisite(i, j-1) || getVisite(i, j+1));
 }

/**
 * 	Donne une valeur donnée à une salle désignée par x et y
 */
void Laby::setValeur(int x, int y, int valeur) {
	(*salles[x][y]).setValeur(valeur);
	return;
}

/**
 *	Définit si la salle a été visitée
 */
 void Laby::setVisite(int x, int y, bool valeur) {
	salles[x][y]->setVisite(valeur);
	
	return;
}

/**
 *	Retourne True si la pièce est dans le laby, False si elle est en dehors
 */
bool Laby::pieceExiste(int x, int y) {
	return (x >= 0 && y >=0 && x < tailleX && y < tailleY);
}


//Fonctions de jeu

/**
 * 	Regarde si le héros peut bouger dans la direction indiquée, et le bouge si c'est possible
 *  Renvoit 0 si rien, 1 si sortie trouvée, 2 si Game Over
 */
int Laby::bougeHeros(int dir) {

	//Récupère les paramètres de la future case
	int futurX = joueur->getPosX();
	int futurY = joueur->getPosY();
	joueur->setDir(dir);
	resetAffichageLabyHero();
	
	switch(dir) {
		case COTE_HAUT: futurY--; break;
		case COTE_DROITE: futurX++; break;
		case COTE_BAS: futurY++; break;
		case COTE_GAUCHE: futurX--;	break;
		default: break;
	}
	
	//Définit si le joueur peut avancer
	bool avance = true;
	int retour = 0;
	if (!estOuvert(joueur->getPosX(), joueur->getPosY(), dir)	//Cas général
	|| estBloque(joueur->getPosX(), joueur->getPosY(), dir))	//Evènements
		avance = false;/*
	if (salles[joueur->getPosX()][joueur->getPosY()]->getIdEvenement()  == EVT_PORTE
	 && salles[joueur->getPosX()][joueur->getPosY()]->getEvenementVisible())	//Si on se trouve sur une porte, on ne peut que reculer
		if (futurX != joueur->getPosPrecX() || futurY != joueur->getPosPrecY())
			avance = false;
	*/
	if (avance) {
		//nettoieEcranMenu();
		
		joueur->setPosPrecX(joueur->getPosX());
		joueur->setPosPrecY(joueur->getPosY());
		
		joueur->setPosX(futurX);
		joueur->setPosY(futurY);
		
		//Visite de la case
		setVisite(joueur->getPosX(), joueur->getPosY(), true);
		
		//Activation de l'évènement
		if (salles[joueur->getPosX()][joueur->getPosY()]->activationAutomatique())
			retour = activeEvenement(joueur->getPosX(), joueur->getPosY());
		
		afficheApercu(5);
	}
	
	return retour;
}

/**
 *	Active l'événement sur lequel le héros est et celui en face de lui
 */
int Laby::appuieBoutonValider() {

	//Variables
	int x = joueur->getPosX();
	int y = joueur->getPosY();
	int retour = 0;
	
	//On teste l'évènement devant le héros
	switch(joueur->getDir()) {
		case COTE_HAUT: y--; break;
		case COTE_DROITE: x++; break;
		case COTE_BAS: y++; break;
		case COTE_GAUCHE: x--;	break;
		default: break;
	}
	if (pieceExiste(x, y)
	&& salles[x][y]->getIdEvenement() != EVT_VIDE && salles[x][y]->getEvenementVisible()
	&& salles[x][y]->activationDistance()) {
		retour = activeEvenement(x, y);
		afficheApercu(5);
	}
	else {
		//Si pas d'activation, activation de l'événement sous le héros
		x = joueur->getPosX();
		y = joueur->getPosY();
		if (salles[x][y]->getIdEvenement() != EVT_VIDE && salles[x][y]->getEvenementVisible()
		&& salles[x][y]->activationContact()) {
			retour = activeEvenement(x, y);
			afficheApercu(5);
		}
	}
	
	return retour;
}

/**
 *	Active un événement
 */
int Laby::activeEvenement(int x, int y) {

	int retour = 0;
	
	//Actions pré-évènement
	int idPiece = salles[x][y]->getIdEvenement();
	if (idPiece == EVT_COMBAT) {
		fondu(2, 0, -31, 2);	//fondu (disparition)
	}
	
	//int codeEvenement = salles[x][y]->getEvenementCode();
	if (idPiece != EVT_VIDE && salles[x][y]->getEvenementVisible()) {
		nettoieEcranMenu();
		if(salles[x][y]->activeEvenement(joueur)) {
			switch(idPiece) {
				case EVT_CLEF : {
					objetObtenu(salles[x][y]->getNomObjet());
					break;
				}
				case EVT_LEVEL_UP : {
					objetObtenu(salles[x][y]->getNomObjet());
					joueur->getPerso()->levelUp();
					break;
				}
				case EVT_SORTIE : {
					retour = 1;
				}
				case EVT_COMBAT : {
					salles[x][y]->activeEvenement(joueur);
				}
				case EVT_TELEPORT : {
					Piece* casesTP = salles[x][y]->getPieceAssociee();
					joueur->setPosX(casesTP->getPosX());
					joueur->setPosY(casesTP->getPosY());
					setVisite(x, y, true);
					setVisite(joueur->getPosX(), joueur->getPosY(), true);
				}
			}
			
		}
		//rechargeGFX();
		afficheMenu();
	}
	
	
	//Actions post-évènement
	if (idPiece == EVT_COMBAT) {
		rechargeGFX();
		resetAffichageLabyHero();
		afficheApercu(5);
		afficheNiveau();
		fondu(2, -31, 0, 2);	//fondu (réapparition)
	}
	
	return retour;
}




//Ecran du bas

/**
 *	Affiche le menu du joueur
 */
void Laby::afficheMenu() {
	//Nettoyage de l'écran
	this->nettoieEcranMenu();

	//Boutons L et R
	PA_CreateSprite(0, SPR_L, (void*)bouton_L_Sprite, OBJ_SIZE_16X16, 1, PAL_L, 12, 4);
	PA_CreateSprite(0, SPR_R, (void*)bouton_R_Sprite, OBJ_SIZE_16X16, 1, PAL_R, 228, 4);
	
	
	//Texte
	switch(this->pageMenu) {
		case 0 : {	//Statut
		
			//Entête
			PA_SetTextTileCol(0, COULEUR_TEXTE);
			PA_OutputText(0, 12, 1, "Objets Attaques");
			PA_SetTextTileCol(0, COULEUR_SELECTION);
			PA_OutputText(0, 5, 1, "Statut");
			
			
			//Affichage des stats
			PA_SetTextTileCol(0, COULEUR_SELECTION);
			PA_OutputText(0, 2, 3, "%s", stringToChar(this->joueur->getPerso()->getNomClasse()));
			
			PA_SetTextTileCol(0, COULEUR_TEXTE);
			PA_OutputText(0, 2, 4, "PV :");
			
			//Points de vie
			int pv = this->joueur->getPerso()->getPointsVie();
			int pvMax = this->joueur->getPerso()->getPointsVieMax();
			PA_SetTextTileCol(0, pv>(int)(pvMax/5)?COULEUR_PV_HAUT:COULEUR_PV_BAS);
			PA_OutputText(0, 7, 4, "%d/%d", pv, pvMax);
			PA_SetTextTileCol(0, COULEUR_TEXTE);
			PA_OutputText(0, 2, 6, "PE : %d", this->joueur->getPerso()->getPointsEnergieMax());
			
			//Caractéristiques
			PA_OutputText(0, 2, 7, "Attaque : %d", this->joueur->getPerso()->getAttaque());
			PA_OutputText(0, 2, 8, "Att.spé : %d", this->joueur->getPerso()->getAttaqueSpe());
			PA_OutputText(0, 2, 9, "Défense : %d", this->joueur->getPerso()->getDefense());
			PA_OutputText(0, 2, 10, "Déf.spé : %d", this->joueur->getPerso()->getDefenseSpe());
			PA_OutputText(0, 2, 11, "Vitesse : %d", this->joueur->getPerso()->getVitesse());
			
			break;
		}
		case 1 : {	//Objets
			
			//Entête
			PA_SetTextTileCol(0, COULEUR_TEXTE);
			PA_OutputText(0, 5, 1, "Statut        Attaques");
			PA_SetTextTileCol(0, COULEUR_SELECTION);
			PA_OutputText(0, 12, 1, "Objets");
			PA_SetTextTileCol(0, COULEUR_TEXTE);
			
			//Affichage des objets
			if (joueur->getObjets().empty())
				PA_OutputText(0, 2, 3, "Aucun objets");	
			else
				for (int i = 0 ; i < (int)(joueur->getObjets().size()); i++) {
					PA_OutputText(0, 2, i+3, "%s", stringToChar(joueur->getObjet(i)->getNomObjet()));	
				}
			break;
		}
		case 2 : {	//Attaques
			//Entête
			PA_SetTextTileCol(0, COULEUR_TEXTE);
			PA_OutputText(0, 5, 1, "Statut Objets");
			PA_SetTextTileCol(0, COULEUR_SELECTION);
			PA_OutputText(0, 19, 1, "Attaques");
			
			//Affichage des attaques
			for (int i = 0 ; i < 5 ; i++) {
				PA_SetTextTileCol(0, this->joueur->getPerso()->getAttaque(i)->getCouleur());
				PA_OutputText(0, 2, 3*i+3, stringToChar(this->joueur->getPerso()->getAttaque(i)->getNom()));
				PA_SetTextTileCol(0, COULEUR_ELEM_NEUTRE);
				PA_OutputText(0, 2, 3*i+4, stringToChar(this->joueur->getPerso()->getAttaque(i)->getDetails()));
			}
			break;
		}
	}
}

/**
 *	Change la page du menu
 */
void Laby::changeMenu(int direction) {
	this->pageMenu = (this->pageMenu+direction+3)%3;
	this->afficheMenu();
	
	//Attente pour éviter de switcher deux fois
	for(int i = 0 ; i < 10 ; i++)
		PA_WaitForVBL();
	return;
}

/**
 *	Affiche le message "Objet Obtenu"
 */
void Laby::objetObtenu(std::string objet) {
	//Nettoyage de l'écran
	nettoieEcranMenu();
		
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
	nettoieEcranMenu();
	
	return;
}

/**
 *	Supprime tout le texte présent sur un écran
 */
void Laby::nettoieEcranMenu() {
	//Texte
	for (int i = 0 ; i < 24 ; i++)
		PA_OutputText(0, 0, i, "                                ");
		
	//Sprites
	PA_DeleteSprite(0, SPR_A);
	PA_DeleteSprite(0, SPR_L);
	PA_DeleteSprite(0, SPR_R);
}



//Fonctions systèmes

/**
 *	Supprime les sprites du laby
 */
void Laby::supprimeSprites() {

	//Suppression des anciennes sprites
	for (int i = 1 ; i <= numSprites ; i++) {
		PA_DeleteSprite(1, i);
	}
	numSprites = 1;
	return;
}

/**
 *	Charges les palettes utilisées dans le labyrinthe
 */
void Laby::chargePalettesLaby() {
	PA_LoadSpritePal(1, PAL_HERO, (void*)map_hero_Pal);
	PA_LoadSpritePal(1, PAL_TELEPORT, (void*)map_teleporteur_Pal);
	PA_LoadSpritePal(1, PAL_ESCALIER, (void*)map_escalier_Pal);
	PA_LoadSpritePal(1, PAL_PORTE, (void*)map_porte_Pal);
	PA_LoadSpritePal(1, PAL_CLEF, (void*)map_clef_Pal);
	PA_LoadSpritePal(1, PAL_COFFRE, (void*)map_coffre_Pal);
	PA_LoadSpritePal(1, PAL_COMBAT, (void*)map_combat_Pal);
	PA_LoadSpritePal(1, PAL_REGEN, (void*)map_regen_Pal);
	
	PA_LoadSpritePal(0, PAL_L, (void*)bouton_L_Pal);
	PA_LoadSpritePal(0, PAL_R, (void*)bouton_R_Pal);
	PA_LoadSpritePal(0, PAL_A, (void*)bouton_A_Pal);
	return;
}

/**
 *	Recharge tous les graphismes
 */
void Laby::rechargeGFX() {
	PA_ResetSpriteSys();
	
	PA_ResetBgSysScreen(1);
	PA_LoadTiledBg(1, 3, fondLaby);
	PA_InitText(1,2);
	
	PA_Init8bitBg(0, 3);
	PA_Load8bitBgPal(0,(void*)fondExploration_Pal);
	PA_Load8bitBitmap(0, fondExploration_Bitmap);
	
	chargePalettesLaby();
	
	return;
}

/**
 *	Affiche quel est le niveau en cours
 */
void Laby::afficheNiveau() {
	PA_OutputText(1, 0, 0, "Niveau %d", ((tailleX+tailleY)/2-10)/2+1);
}
