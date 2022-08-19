#include <PA9.h>
#include "Personnage.h"
#include "Attaque.h"
#include "Define.cpp"

//Fonctions.cpp
std::string intToString(int nombre);

//main.cpp
void afficheStatsVieCombat(Personnage *joueur);
void afficheStatsEnergieCombat(Personnage *joueur);

Personnage::Personnage(int id) {
		this->id = id;
		
		if (id == 0) {
			nom = "Joueur";
			classe = CLASSE_GUERRIER;
			
			niveau = 1;
			
			pointsVie = 50;
			pointsVieMax = 50;
			pointsEnergie = 10;
			pointsEnergieMax = 20;
			
			attaque = 10;
			attaqueSpe = 10;
			defense = 10;
			defenseSpe = 10;
			vitesse = 10;
			
			bonusAttaque = 0;
			bonusAttaqueSpe = 0;
			bonusDefense = 0;
			bonusDefenseSpe = 0;
			bonusVitesse = 0;
			
			protectionGlace = 0;
			protectionFeu = 0;
			protectionFoudre = 0;
			
			moveset[0] = new Attaque(2);
			moveset[1] = new Attaque(9);
			moveset[2] = new Attaque(14);
			moveset[3] = new Attaque(19);
			moveset[4] = new Attaque(24);
			moveset[5] = new Attaque(1);
		} else {
			nom = "Ennemi";
			classe = CLASSE_GUERRIER;
			
			niveau = (int)(id*3/4) + PA_RandMinMax((int)(-id/10), (int)(id/5));
			if (niveau < 1)
				niveau = 1;
				
			//pointsVieMax = 40+niveau*(10+PA_RandMinMax(-2, 2));
			pointsVieMax = 1;
			pointsVie = pointsVieMax;
			pointsEnergieMax = 15+niveau+PA_RandMinMax(-5, 10);
			pointsEnergie = pointsEnergieMax;
			
			attaque = 5+niveau*3+PA_RandMinMax(-niveau, niveau);
			attaqueSpe = 5+niveau*3+PA_RandMinMax(-niveau, niveau);
			defense = 5+niveau*3+PA_RandMinMax(-niveau, niveau);
			defenseSpe = 5+niveau*3+PA_RandMinMax(-niveau, niveau);
			vitesse = 5+niveau*3+PA_RandMinMax(-niveau, niveau);
			
			bonusAttaque = 0;
			bonusAttaqueSpe = 0;
			bonusDefense = 0;
			bonusDefenseSpe = 0;
			bonusVitesse = 0;
			
			protectionGlace = PA_RandMinMax(-50, 50);
			protectionFeu = PA_RandMinMax(-50, 50);
			protectionFoudre = PA_RandMinMax(-50, 50);
			
			moveset[0] = new Attaque(0);
			moveset[0]->changeAttaqueRandom(niveau);
			for(int i = 1 ; i < 5 ; i++) {
				moveset[i] = new Attaque(0);
				bool flag;
				do {
					flag = true;
					moveset[i]->changeAttaqueRandom(niveau);
					for(int j = 1 ; j < i ; j++) {
						if (moveset[i]->getId() == moveset[j]->getId())
							flag = false;
					}
				} while(!flag);
			}
			moveset[5] = new Attaque(1);
		}
}

Personnage::~Personnage() {

}


//Level Up
void Personnage::levelUp() {
	switch(classe) {
		case CLASSE_GUERRIER : {
			/*
			Points de vie+5
			Points d'energie+1
			Attaque+5
			AttaqueSpe+1
			Defense+4
			DefenseSpe+3
			Vitesse+1
			*/
			pointsVieMax+=5*PV_PAR_POINT;
			pointsEnergieMax+=1;
			attaque+=5;
			attaqueSpe+=1;
			defense+=4;
			defenseSpe+=3;
			vitesse+=1;
			break;
		}
		case CLASSE_ELEMENTALISTE : {
			/*
			Points de vie+3
			Points d'energie+3
			Attaque+2
			AttaqueSpe+5
			Defense+3
			DefenseSpe+3
			Vitesse+3
			*/
			pointsVieMax+=3*PV_PAR_POINT;
			pointsEnergieMax+=3;
			attaque+=2;
			attaqueSpe+=5;
			defense+=3;
			defenseSpe+=3;
			vitesse+=3;
			break;
		}
		case CLASSE_SCOUT : {
			/*
			Points de vie+3
			Points d'energie+2
			Attaque+3
			AttaqueSpe+3
			Defense+3
			DefenseSpe+2
			Vitesse+4
			*/
			pointsVieMax+=3*PV_PAR_POINT;
			pointsEnergieMax+=2;
			attaque+=3;
			attaqueSpe+=3;
			defense+=3;
			defenseSpe+=2;
			vitesse+=4;
			break;
		}
	}
	//Points au hasard
	for (int i = 0 ; i < 2 ; i++) {
		int carac = PA_RandMinMax(0, 6);
		switch(carac) {
			case 0 : {pointsVieMax+=PV_PAR_POINT; break;}
			case 1 : {pointsEnergieMax++; break;}
			case 2 : {attaque++; break;}
			case 3 : {attaqueSpe++; break;}
			case 4 : {defense++; break;}
			case 5 : {defenseSpe++; break;}
			case 6 : {vitesse++; break;}
		}
	}
	return;
}


//Fonctions Set
void Personnage::setNiveau(int niveau) {
	this->niveau = niveau;
	return;
}

void Personnage::setPointsVie(int pointsVie) {
	this->pointsVie = pointsVie;
	return;
}

void Personnage::setPointsVieMax(int pointsVieMax) {
	this->pointsVieMax = pointsVieMax;
	return;
}

void Personnage::setPointsEnergie(int pointsEnergie) {
	this->pointsEnergie = pointsEnergie;
	return;
}

void Personnage::setPointsEnergieMax(int pointsEnergieMax) {
	this->pointsEnergieMax = pointsEnergieMax;
	return;
}

void Personnage::setAttaque(int attaque) {
	this->attaque = attaque;
	return;
}
void Personnage::setAttaqueSpe(int attaqueSpe) {
	this->attaqueSpe = attaqueSpe;
	return;
}
void Personnage::setDefense(int defense) {
	this->defense = defense;
	return;
}
void Personnage::setDefenseSpe(int defenseSpe) {
	this->defenseSpe = defenseSpe;
	return;
}
void Personnage::setVitesse(int vitesse) {
	this->vitesse = vitesse;
	return;
}
void Personnage::setAttaque(Attaque *attaque, int slot) {
	if (slot >= 0 && slot < 6)
		this->moveset[slot] = attaque;
	return;
}

void Personnage::setBonusAttaque(int bonusAttaque) {
	this->bonusAttaque = bonusAttaque;
	return;
}
void Personnage::setBonusAttaqueSpe(int bonusAttaqueSpe) {
	this->bonusAttaqueSpe = bonusAttaqueSpe;
	return;
}
void Personnage::setBonusDefense(int bonusDefense) {
	this->bonusDefense = bonusDefense;
	return;
}
void Personnage::setBonusDefenseSpe(int bonusDefenseSpe) {
	this->bonusDefenseSpe = bonusDefenseSpe;
	return;
}
void Personnage::setBonusVitesse(int bonusVitesse) {
	this->bonusVitesse = bonusVitesse;
	return;
}

void Personnage::setProtectionGlace(int protectionGlace) {
	this->protectionGlace = protectionGlace;
	return;
}
void Personnage::setProtectionFeu(int protectionFeu) {
	this->protectionFeu = protectionFeu;
	return;
}
void Personnage::setProtectionFoudre(int protectionFoudre) {
	this->protectionFoudre = protectionFoudre;
	return;
}


//Fonctions get
int Personnage::getNiveau() {
	return this->niveau;
}
std::string Personnage::getNomClasse(){
	std::string nomClasse;
	switch(this->classe) {
		case CLASSE_ENNEMI :		nomClasse = "Ennemi"; break;
		case CLASSE_GUERRIER :		nomClasse = "Guerrier"; break;
		case CLASSE_ELEMENTALISTE : nomClasse = "Elémentaliste"; break;
		case CLASSE_SCOUT :			nomClasse = "Scout"; break;
		default:					nomClasse =	"Erreur"; break;
	}
	return nomClasse;
}
std::string Personnage::getNom() {
	return this->nom;
}
int Personnage::getClasse() {
	return this->classe;
}
int Personnage::getPointsVie() {
	return this->pointsVie;
}
int Personnage::getPointsVieMax() {
	return this->pointsVieMax;
}
int Personnage::getPointsEnergie() {
	return this->pointsEnergie;
}
int Personnage::getPointsEnergieMax() {
	return this->pointsEnergieMax;
}


int Personnage::getAttaque() {
	return this->attaque;
}
int Personnage::getAttaqueSpe() {
	return this->attaqueSpe;
}
int Personnage::getDefense() {
	return this->defense;
}
int Personnage::getDefenseSpe() {
	return this->defenseSpe;
}
int Personnage::getVitesse() {
	return this->vitesse;
}

int Personnage::getBonusAttaque() {
	return this->bonusAttaque;
}
int Personnage::getBonusAttaqueSpe() {
	return this->bonusAttaqueSpe;
}
int Personnage::getBonusDefense() {
	return this->bonusDefense;
}
int Personnage::getBonusDefenseSpe() {
	return this->bonusDefenseSpe;
}
int Personnage::getBonusVitesse() {
	return this->bonusVitesse;
}

int Personnage::getProtectionGlace() {
	return this->protectionGlace;
}
int Personnage::getProtectionFeu() {
	return this->protectionFeu;
}
int Personnage::getProtectionFoudre() {
	return this->protectionFoudre;
}

Attaque* Personnage::getAttaque(int slot) {
	if (slot >= 0 && slot < 6)
		return this->moveset[slot];
	else
		return new Attaque();
}

std::vector<Attaque*> Personnage::getAttaques() {
	std::vector<Attaque*> actions;
	
	for (int i = 0 ; i < 6 ; i++){
		if (moveset[i]->getId() >= 0)
			actions.push_back(moveset[i]);
	}
	return actions;
}

std::vector<Attaque*> Personnage::getAttaquesModifiables() {
	std::vector<Attaque*> actions;
	
	for (int i = 0 ; i < 5 ; i++){
		if (moveset[i]->getId() >= 0)
			actions.push_back(moveset[i]);
	}
	return actions;
}

void Personnage::remplaceAttaque(Attaque* attaque, int position) {
	delete this->moveset[position];
	this->moveset[position] = attaque;
	return;
}

//FONCTIONS DIVERSES
bool Personnage::faitAttaque(int id, Personnage *ennemi, int direction) {
	bool retour = this->moveset[id]->faitAttaque((Personnage*)this, ennemi, direction, 1, 1, 18);
	return retour;
}

int Personnage::retirePointsVie(int points) {
	//On ne dépasse pas le min
	if (this->pointsVie < points)
		points = this->pointsVie;
	
	if (this->id == 0) {	//Si c'est le joueur, on affiche les stats
		//Calcul du nombre de points à retirer par frame lors de l'animation
		int pointsFrame = (int)(points/BARRES_NOMBRE_CHANGE);
		
		//On retire les points de vie au fur et à mesure
		for(int i = 0 ; i < BARRES_NOMBRE_CHANGE ; i++) {
			this->pointsVie-=pointsFrame;
			afficheStatsVieCombat(this);	//Affichage de la barre de vie
			for(int j = 0 ; j < BARRES_FRAMES_CHANGE ; j++)
				PA_WaitForVBL();	
		}
		
		//On retire les derniers points de vie
		this->pointsVie -= points-(pointsFrame*BARRES_NOMBRE_CHANGE);
		afficheStatsVieCombat(this);
	}
	else
		this->pointsVie -= points;
	
	return points;
}

int Personnage::retirePointsEnergie(int points) {
	if (this->pointsEnergie < points)
		points = this->pointsEnergie;
	
	if (this->id == 0) {	//Si c'est le joueur, on affiche les stats
		//Calcul du nombre de points à retirer par frame lors de l'animation
		int pointsFrame = (int)(points/BARRES_NOMBRE_CHANGE);
		
		//On retire les points de vie au fur et à mesure
		for(int i = 0 ; i < BARRES_NOMBRE_CHANGE ; i++) {
			this->pointsEnergie-=pointsFrame;
			afficheStatsEnergieCombat(this);	//Affichage de la barre de vie
			for(int j = 0 ; j < BARRES_FRAMES_CHANGE ; j++)
				PA_WaitForVBL();	
		}
		
		//On retire les derniers points de vie
		this->pointsEnergie -= points-(pointsFrame*BARRES_NOMBRE_CHANGE);
		afficheStatsEnergieCombat(this);
	}
	else
		this->pointsEnergie -= points;
	
	return points;
}

int Personnage::soinsPointsVie(int points) {
	//On ne dépasse pas le max
	if (this->pointsVie+points > this->pointsVieMax)
		points = this->pointsVieMax-this->pointsVie;
	
	if (this->id == 0) {	//Si c'est le joueur, on affiche les stats
		//Calcul du nombre de points à ajouter par frame lors de l'animation
		int pointsFrame = (int)(points/BARRES_NOMBRE_CHANGE);
		
		//On ajoute les points de vie au fur et à mesure
		for(int i = 0 ; i < BARRES_NOMBRE_CHANGE ; i++) {
			this->pointsVie+=pointsFrame;
			afficheStatsVieCombat(this);	//Affichage de la barre de vie
			for(int j = 0 ; j < BARRES_FRAMES_CHANGE ; j++)
				PA_WaitForVBL();	
		}
		
		//On ajoute les derniers points de vie
		this->pointsVie += points-(pointsFrame*BARRES_NOMBRE_CHANGE);
		afficheStatsVieCombat(this);
	}
	else
		this->pointsVie += points;
	
	return points;
}

int Personnage::soinsPointsEnergie(int points) {
	//On ne dépasse pas le max
	if (this->pointsEnergie+points > this->pointsEnergieMax)
		points = this->pointsEnergieMax-this->pointsEnergie;
	
	if (this->id == 0) {	//Si c'est le joueur, on affiche les stats
		//Calcul du nombre de points à ajouter par frame lors de l'animation
		int pointsFrame = (int)(points/BARRES_NOMBRE_CHANGE);
		
		//On ajoute les points de vie au fur et à mesure
		for(int i = 0 ; i < BARRES_NOMBRE_CHANGE ; i++) {
			this->pointsEnergie+=pointsFrame;
			afficheStatsEnergieCombat(this);	//Affichage de la barre de vie
			for(int j = 0 ; j < BARRES_FRAMES_CHANGE ; j++)
				PA_WaitForVBL();	
		}
		
		//On ajoute les derniers points de vie
		this->pointsEnergie += points-(pointsFrame*BARRES_NOMBRE_CHANGE);
		afficheStatsEnergieCombat(this);
	}
	else
		this->pointsEnergie += points;
	
	return points;
}

int Personnage::rechargePE() {
	int recharge = (int)(this->pointsEnergieMax/10);		//10% de recharge
	if (recharge+this->pointsEnergie > this->pointsEnergieMax)	//On ne dépasse pas le max de PE
		recharge = this->pointsEnergieMax-this->pointsEnergie;
		
	if (this->id == 0) {	//Si c'est le joueur, on affiche les stats
		for(int i = 0 ; i < recharge ; i++) {
			this->pointsEnergie++;
			afficheStatsEnergieCombat(this);
			for(int j = 0 ; j < (int)((DUREE_RECHARGE_PE)/recharge) ; j++)
				PA_WaitForVBL();
		}
	}
	else
		this->pointsEnergie+=recharge;
		
	return recharge;
}

void Personnage::initPE() {
	this->pointsEnergie = (int)(this->pointsEnergieMax/2);

}

void Personnage::initBonus() {
	bonusAttaque = 0;
	bonusAttaqueSpe = 0;
	bonusDefense = 0;
	bonusDefenseSpe = 0;
	bonusVitesse = 0;
	return;	
}

bool Personnage::changeBonusAttaque(int valeur) {
	bool retour = false;
	//On ne change la caractéristique que si elle est inférieure à la limite
	if (this->bonusAttaque < (int)(LIMITE_BONUS*this->attaque) && this->bonusAttaque > (int)(-LIMITE_BONUS*this->attaque)) {
		this->bonusAttaque += valeur;
		retour = true;
	}
	return retour;
}

bool Personnage::changeBonusAttaqueSpe(int valeur) {
	bool retour = false;
	//On ne change la caractéristique que si elle est inférieure à la limite
	if (this->bonusAttaqueSpe < (int)(LIMITE_BONUS*this->attaqueSpe) && this->bonusAttaqueSpe > (int)(-LIMITE_BONUS*this->attaqueSpe)) {
		this->bonusAttaqueSpe += valeur;
		retour = true;
	}
	return retour;
}

bool Personnage::changeBonusDefense(int valeur) {
	bool retour = false;
	//On ne change la caractéristique que si elle est inférieure à la limite
	if (this->bonusDefense < (int)(LIMITE_BONUS*this->defense) && this->bonusDefense > (int)(-LIMITE_BONUS*this->defense)) {
		this->bonusDefense += valeur;
		retour = true;
	}
	return retour;
}

bool Personnage::changeBonusDefenseSpe(int valeur) {
	bool retour = false;
	//On ne change la caractéristique que si elle est inférieure à la limite
	if (this->bonusDefenseSpe < (int)(LIMITE_BONUS*this->defenseSpe) && this->bonusDefenseSpe > (int)(-LIMITE_BONUS*this->defenseSpe)) {
		this->bonusDefenseSpe += valeur;
		retour = true;
	}
	return retour;
}

bool Personnage::changeBonusVitesse(int valeur) {
	bool retour = false;
	//On ne change la caractéristique que si elle est inférieure à la limite
	if (this->bonusVitesse < (int)(LIMITE_BONUS*this->vitesse) && this->bonusVitesse > (int)(-LIMITE_BONUS*this->vitesse)) {
		this->bonusVitesse += valeur;
		retour = true;
	}
	return retour;
}

/**
	Règles sur les changements de protections élémentales
	On applique le bonus que s'il est supérieur à la protection actuelle (pas d'addition)
	Le bonus peut être négatif, mais de même il n'est pas additionnable. Ex : une attaque provoquant un bonus de -25% ne fera pas descendre en dessous de -25% la protection totale.
*/
bool Personnage::changeBonusGlace(int valeur) {
	bool retour = false;
	if ((valeur > 0 && valeur > this->protectionGlace) || (valeur < 0 && valeur < this->protectionGlace)) {
		this->protectionGlace = valeur;
		retour = true;
	}
	return retour;
}

bool Personnage::changeBonusFeu(int valeur) {
	bool retour = false;
	if ((valeur > 0 && valeur > this->protectionFeu) || (valeur < 0 && valeur < this->protectionFeu)) {
		this->protectionFeu = valeur;
		retour = true;
	}
	return retour;
}

bool Personnage::changeBonusFoudre(int valeur) {
	bool retour = false;
	if ((valeur > 0 && valeur > this->protectionFoudre) || (valeur < 0 && valeur < this->protectionFoudre)) {
		this->protectionFoudre = valeur;
		retour = true;
	}
	return retour;
}

