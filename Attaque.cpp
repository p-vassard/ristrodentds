#include "Attaque.h"

#include <PA9.h>
#include "gfx/all_gfx.h"

#include <sstream>
#include "Define.cpp"

char* stringToChar(std::string chaine);
std::string intToString(int nombre);
char* intToChar(int nombre);
void boucleAppuie();
void clearEcranStatus(int y);

Attaque::Attaque() {
	initAttaque();
}

Attaque::Attaque(int id) {
	initAttaque();

	this->id = id;
	changeAttaqueId(id);

}

Attaque::~Attaque() {


}

/**
 *	Remet toutes les valeurs à 0
 */
void Attaque::initAttaque() {
	id = -1;
	
	nom = "";
	description = "";
	niveau = 0;
	coutVie = 0;
	coutEnergie = 0;
	
	degatsVie = 0;
	degatsEnergie = 0;
	
	soinsVie = 0;
	soinsEnergie = 0;
	
	absorptionVie = 0;
	absorptionEnergie = 0;
	
	perceArmure = 0;
	activation = 0;
	
	nombreTours = 1;
	entretienEnergie = 0;
	entretienVie = 0;
	entretienEnergiePourcent = 0;
	entretienViePourcent = 0;
	
	attaquePersoPlus = 0;
	attaqueSpePersoPlus = 0;
	defensePersoPlus = 0;
	defenseSpePersoPlus = 0;
	vitessePersoPlus = 0;
	
	attaqueEnnemiPlus = 0;
	attaqueSpeEnnemiPlus = 0;
	defenseEnnemiPlus = 0;
	defenseSpeEnnemiPlus = 0;
	vitesseEnnemiPlus = 0;
	
	protectionGlaceJoueurPlus = 0;
	protectionFeuJoueurPlus = 0;
	protectionFoudreJoueurPlus = 0;
	
	protectionGlaceEnnemiPlus = 0;
	protectionFeuEnnemiPlus = 0;
	protectionFoudreEnnemiPlus = 0;
	
	return;
}

/**
 *	Change l'attaque en fonction de son id
 */
void Attaque::changeAttaqueId(int id) {

	initAttaque();
	
	//Liste des attaques
	this->id = id;
	switch(id) {
		case 0 :
			nom = "";
			description = "";
			coutEnergie = 0;
			degatsVie = 0;
			type = TYPE_NORMAL;
			element = ELT_NEUTRE;
		break;
		case 1 :
			niveau = 0;
			nom = "Recharge";
			description = "Regagne quelque PE";
			coutEnergie = 0;
			degatsVie = 0;
			type = TYPE_NORMAL;
			element = ELT_NEUTRE;
		break;
		
		//ATTAQUES
		//Normal
		case 2 :
			niveau = 1;
			nom = "Coup de poing";
			description = "Frappe l'ennemi avec son poing";
			coutEnergie = 1;
			degatsVie = 5;
			type = TYPE_NORMAL;
			element = ELT_NEUTRE;
		break;
		case 3 :
			niveau = 1;
			nom = "Coup de pied";
			description = "Frappe l'ennemi avec son pied";
			coutEnergie = 1;
			degatsVie = 6;
			type = TYPE_NORMAL;
			element = ELT_NEUTRE;
		break;
		case 4 :
			niveau = 1;
			nom = "Frappe";
			description = "Attaque l'ennemi sans arme";
			coutEnergie = 1;
			degatsVie = 7;
			type = TYPE_NORMAL;
			element = ELT_NEUTRE;
		break;
		case 5 :
			niveau = 5;
			nom = "Force";
			description = "Attaque simple";
			coutEnergie = 3;
			degatsVie = 14;
			type = TYPE_NORMAL;
			element = ELT_NEUTRE;
		break;
		case 6 :
			niveau = 20;
			nom = "Plasma";
			description = "Utilise le plasma pour attaquer";
			coutEnergie = 5;
			degatsVie = 21;
			type = TYPE_SPECIAL;
			element = ELT_NEUTRE;
		break;
		case 7 :
			niveau = 50;
			nom = "Désintégration";
			description = "Broie l'ennemi";
			coutEnergie = 7;
			degatsVie = 30;
			type = TYPE_SPECIAL;
			element = ELT_NEUTRE;
		break;
		case 8 :
			niveau = 75;
			nom = "Puissance";
			description = "Décuple sa force et attaque";
			coutEnergie = 15;
			degatsVie = 75;
			type = TYPE_NORMAL;
			element = ELT_NEUTRE;
			attaquePersoPlus = 10;
		break;
		//Glace
		case 9 :
			niveau = 1;
			nom = "Grêle";
			description = "Projette des billes de glace";
			coutEnergie = 3;
			degatsVie = 14;
			type = TYPE_NORMAL;
			element = ELT_GLACE;
		break;
		case 10 :
			niveau = 10;
			nom = "Engelures";
			description = "Attaque de glace baissant la force";
			coutEnergie = 5;
			degatsVie = 20;
			type = TYPE_SPECIAL;
			element = ELT_GLACE;
			attaqueEnnemiPlus = -5;
		break;
		case 11 :
			niveau = 25;
			nom = "Frigorification";
			description = "Attaque de glace baissant la force";
			coutEnergie = 7;
			degatsVie = 32;
			type = TYPE_SPECIAL;
			element = ELT_GLACE;
		break;
		case 12 :
			niveau = 50;
			nom = "Azote liquide";
			description = "Projette un liquide gelé";
			coutEnergie = 10;
			degatsVie = 42;
			type = TYPE_SPECIAL;
			element = ELT_GLACE;
		break;
		case 13 :
			niveau = 75;
			nom = "Zéro absolu";
			description = "Gèle l'atmosphère";
			coutEnergie = 20;
			degatsVie = 90;
			type = TYPE_SPECIAL;
			element = ELT_GLACE;
			vitesseEnnemiPlus = -10;
		break;
		//Feu
		case 14 :
			niveau = 1;
			nom = "Etincelles";
			description = "Provoque de légères brûlures";
			coutEnergie = 3;
			degatsVie = 12;
			type = TYPE_SPECIAL;
			element = ELT_FEU;
		break;
		case 15 :
			niveau = 10;
			nom = "Marteau de feu";
			description = "Attaque avec un marteau enflammé";
			coutEnergie = 4;
			degatsVie = 18;
			type = TYPE_NORMAL;
			element = ELT_FEU;
			attaquePersoPlus = 5;
		break;
		case 16 :
			niveau = 25;
			nom = "Chaleur";
			description = "Augmente la température de la pièce";
			coutEnergie = 8;
			degatsVie = 37;
			type = TYPE_SPECIAL;
			element = ELT_FEU;
			protectionGlaceJoueurPlus = 10;
		break;
		case 17 :
			niveau = 50;
			nom = "Laser";
			description = "Envoi un rayon de lumière brûlant";
			coutEnergie = 12;
			degatsVie = 50;
			type = TYPE_SPECIAL;
			element = ELT_FEU;
		break;
		case 18 :
			niveau = 75;
			nom = "Lave";
			description = "Fait fondre la roche et le métal";
			coutEnergie = 17;
			degatsVie = 80;
			type = TYPE_NORMAL;
			element = ELT_FEU;
		break;
		//Foudre
		case 19 :
			niveau = 1;
			nom = "Choc";
			description = "Créé une petite décharge";
			coutEnergie = 3;
			degatsVie = 16;
			type = TYPE_SPECIAL;
			element = ELT_FOUDRE;
		break;
		case 20 :
			niveau = 10;
			nom = "Foudre";
			description = "Envoi un rayon de foudre";
			coutEnergie = 6;
			degatsVie = 22;
			type = TYPE_SPECIAL;
			element = ELT_FOUDRE;
		break;
		case 21 :
			niveau = 25;
			nom = "Eclair";
			description = "Transforme l'énergie en foudre";
			coutEnergie = 10;
			degatsVie = 42;
			type = TYPE_SPECIAL;
			element = ELT_FOUDRE;
		break;
		case 22 :
			niveau = 50;
			nom = "Tonnerre";
			description = "Créé la foudre et de fortes vibrations";
			coutEnergie = 15;
			degatsVie = 50;
			type = TYPE_SPECIAL;
			element = ELT_FOUDRE;
		break;
		case 23 :
			niveau = 75;
			nom = "Tesla";
			description = "L'attaque utilme de foudre";
			coutEnergie = 25;
			degatsVie = 125;
			type = TYPE_SPECIAL;
			element = ELT_FOUDRE;
			attaquePersoPlus = -5;
			attaqueSpePersoPlus = -5;
			defensePersoPlus = -5;
			defenseSpePersoPlus = -5;
			vitessePersoPlus = -5;
		break;
		
		//SOINS
		case 24 :
			niveau = 1;
			nom = "Regénération";
			description = "Réparations sommaires";
			coutEnergie = 5;
			soinsVie = 35;
			type = TYPE_NORMAL;
			element = ELT_NEUTRE;
		break;
		case 26 :
			niveau = 5;
			nom = "Source de vie";
			description = "Utilise une eau réparatrice";
			coutEnergie = 10;
			soinsVie = 75;
			type = TYPE_SPECIAL;
			element = ELT_GLACE;
		break;
		case 27 :
			niveau = 10;
			nom = "Eau appaisante";
			description = "Utilise une eau soignant les tissus métaliques";
			coutEnergie = 15;
			soinsVie = 125;
			type = TYPE_SPECIAL;
			element = ELT_GLACE;
		break;
		case 28 :
			niveau = 20;
			nom = "Eau de vie";
			description = "Utilise une eau regénératrice";
			coutEnergie = 25;
			soinsVie = 200;
			type = TYPE_SPECIAL;
			element = ELT_GLACE;
		break;
		case 29 :
			niveau = 50;
			nom = "Cryogénisation";
			description = "Soigne grandement";
			coutEnergie = 35;
			soinsVie = 350;
			type = TYPE_SPECIAL;
			element = ELT_GLACE;
		break;
		case 30 :
			niveau = 5;
			nom = "Feu appaisant";
			description = "Soigne par la chaleur artificielle";
			coutEnergie = 10;
			soinsVie = 75;
			type = TYPE_SPECIAL;
			element = ELT_FEU;
		break;
		case 31 :
			niveau = 4;
			nom = "Batterie";
			description = "Apporte une nouvelle source d'énergie";
			coutEnergie = 15;
			soinsVie = 50;
			soinsEnergie = 10;
			type = TYPE_SPECIAL;
			element = ELT_FOUDRE;
		break;
		case 32 :
			niveau = 14;
			nom = "Source énergie";
			description = "Soigne par la foudre";
			coutEnergie = 25;
			soinsVie = 150;
			soinsEnergie = 15;
			type = TYPE_SPECIAL;
			element = ELT_FOUDRE;
		break;
	}
	return;
}

/**
 *	Change l'attaque au hasard
 */
void Attaque::changeAttaqueRandom(int niveauMax) {

	do
	{
		int valeur = PA_RandMinMax(2, NB_ATTAQUES);
		this->changeAttaqueId(valeur);
	} while(this->niveau > niveauMax);
	
	return;
}

/**
 *	Retourne le nom de l'attaque
 */
std::string Attaque::getNom() {
	return this->nom;
}

/**
 *	Retourne le nom de l'attaque
 */
std::string Attaque::getDescription() {
	return this->description;
}

/**
 *	Retourne le coût en énergie
 */
int Attaque::getCoutEnergie() {
	return this->coutEnergie;
}

/**
 *	Retourne le type d'attaque (normal/spéciale)
 */
std::string Attaque::getTexteType() {
	return this->type==TYPE_NORMAL?"Physique":"Spéciale";
}

/**
 *	Retourne le nom de l'élément
 */
std::string Attaque::getTexteElement() {
	std::string texteElement;
	switch(this->element) {
		case ELT_NEUTRE : texteElement = "Neutre"; break;
		case ELT_FEU : texteElement = "Feu"; break;
		case ELT_FOUDRE : texteElement = "Foudre"; break;
		case ELT_GLACE : texteElement = "Glace"; break;
		default: texteElement = "?"; break;
	}
	return texteElement;
}


/**
 *	Retourne les détails à afficher : physique/spécial et le coût en PE
 */
std::string Attaque::getDetails() {
	std::ostringstream retour;
	if (this->activation == 0)
		retour << (this->type==TYPE_NORMAL?"Physique":"Spéciale") << " " << this->coutEnergie << "PE";
	else
		retour << "Passif";
	return retour.str();
}

/**
 *	Affiche la description de l'attaque
 */
void Attaque::afficheDescriptionCombat(int ecran, int posX, int posY) {
	/*
	Nom attaque
	Element, type
	Coûts
	
	Description texte	
	*/
	
	//Nettoie l'écran
	for(int i = 0 ; i < 7 ; i++)
		PA_OutputText(ecran, 0, posY+i, "%s", "                                ");
	
	
	//Nom
	PA_SetTextTileCol(0, COULEUR_ELEM_NEUTRE);	PA_OutputText(ecran, posX, posY, "%s", stringToChar(this->nom));
	//Element
	if (this->activation == 0) {
		PA_SetTextTileCol(0, getCouleur());			PA_OutputText(ecran, posX, posY+1, "%s", stringToChar(getTexteElement()));
	}
	else {
		PA_SetTextTileCol(0, COULEUR_ELEM_NEUTRE);	PA_OutputText(ecran, posX, posY+1, "Passif");
	}
	//Type
	if (this->activation == 0) {
		PA_SetTextTileCol(0, COULEUR_ELEM_NEUTRE);	PA_OutputText(ecran, posX+8, posY+1, "%s", stringToChar(getTexteType()));
	}
	//Coûts
	std::string couts = "";
	if (this->coutVie > 0)
		couts += (intToString(this->coutVie)) + " PV";
	if (this->coutEnergie > 0) {
		if (this->coutVie > 0)
			couts += ", ";
		couts += (intToString(this->coutEnergie)) + " PE";
	}
	PA_SetTextTileCol(0, COULEUR_ELEM_NEUTRE);	PA_OutputText(ecran, posX, posY+2, "%s", stringToChar(couts));
	
	//Description
	PA_SetTextTileCol(0, COULEUR_ELEM_NEUTRE);	PA_OutputText(ecran, posX, posY+4, "%s", stringToChar(this->description));
	
	return;
}


/**
 *	Retourne la couleur de l'élément de l'attaque
 */
int Attaque::getCouleur() {

	int retour = 0;
	switch(this->element) {
		case ELT_NEUTRE : retour = COULEUR_ELEM_NEUTRE; break;
		case ELT_FEU : retour = COULEUR_ELEM_FEU; break;
		case ELT_FOUDRE : retour = COULEUR_ELEM_FOUDRE; break;
		case ELT_GLACE : retour = COULEUR_ELEM_GLACE; break;
	}
	return retour;
}

/**
 *	Retourne l'id de l'attaque
 */
int Attaque::getId() {
	return this->id;
}

/**
 *	Créé un module aléatoire
 */
void Attaque::creeModule(int id, int niveau) {
	int bonus;
	/*
	Définition du bonus
	0 : fréquent (un seul bonus)
	1 : précieux (deux bonus)
	2 : rare (trois bonus)
	*/
	if (id <= 59) {
		bonus = 1;
		nom = "Module nv1";
	}
	else if (id <= 89) {
		bonus = 2;
		nom = "Module nv2";
	}
	else {
		bonus = 3;
		nom = "Module nv3";
	}
	
	//Création de chacun des bonus
	for(int i = 0 ; i < bonus ; i++) {
		
		int typeBonus = PA_RandMinMax(0, 99);
		/*
		0 : Attaque				12%		12
		1 : Attaque spé			12%		24
		2 : Défense				12%		36
		3 : Défense spé			12%		48
		4 : Vitesse				12%		60
		5 : Protection Glace	10%		70
		6 : Protection Foudre	10%		80
		7 : Protection Feu		10%		90
		8 : Dégâts+				5%		95
		9 : AbsorptionVie		2%		97
		10: PerceArmure			2%		99
		11: DégâtsEnergie+		1%		100
		
		TOTAL					100
		*/
		if (typeBonus < 12)
			attaquePersoPlus = PA_RandMinMax(1, niveau);
		else if (typeBonus < 24)
			attaqueSpePersoPlus = PA_RandMinMax(1, niveau);
		else if (typeBonus < 36)
			defensePersoPlus = PA_RandMinMax(1, niveau);
		else if (typeBonus < 48)
			defenseSpePersoPlus = PA_RandMinMax(1, niveau);
		else if (typeBonus < 60)
			vitessePersoPlus = PA_RandMinMax(1, niveau);
			
		else if (typeBonus < 70)
			protectionGlaceJoueurPlus = PA_RandMinMax(1, (int)(niveau/3)+5);
		else if (typeBonus < 80)
			protectionFoudreJoueurPlus = PA_RandMinMax(1, (int)(niveau/3)+5);
		else if (typeBonus < 90)
			protectionFeuJoueurPlus = PA_RandMinMax(1, (int)(niveau/3)+5);
			
		else if (typeBonus < 95)
			degatsVie = PA_RandMinMax(1, (int)(niveau/3)+1);
		else if (typeBonus < 97)
			absorptionVie = PA_RandMinMax(1, 5);
		else if (typeBonus < 99)
			perceArmure = PA_RandMinMax(1, 10);
		else if (typeBonus < 100)
			degatsEnergie = PA_RandMinMax(1, 5);
	}
	
	//Création de la description
	description = "";
	if (attaquePersoPlus > 0)
		description += "Attaque + " + intToString(attaquePersoPlus) + "\n";
	if (attaqueSpePersoPlus > 0)
		description += "Attaque Spéciale + " + intToString(attaqueSpePersoPlus) + "\n";
	if (defensePersoPlus > 0)
		description += "Défense + " + intToString(defensePersoPlus) + "\n";
	if (defenseSpePersoPlus > 0)
		description += "Défense Spéciale + " + intToString(defenseSpePersoPlus) + "\n";
	if (vitessePersoPlus > 0)
		description += "Vitesse + " + intToString(vitessePersoPlus) + "\n";
	if (protectionGlaceJoueurPlus > 0)
		description += "Protection glace + " + intToString(protectionGlaceJoueurPlus) + "%" + "\n";
	if (protectionFoudreJoueurPlus > 0)
		description += "Protection foudre + " + intToString(protectionFoudreJoueurPlus) + "%" + "\n";
	if (protectionFeuJoueurPlus > 0)
		description += "Protection feu + " + intToString(protectionFeuJoueurPlus) + "%" + "\n";
	if (degatsVie > 0)
		description += "Dégats + " + intToString(degatsVie) + "\n";
	if (absorptionVie > 0)
		description += "Absorption de vie + " + intToString(absorptionVie) + "\n";
	if (perceArmure > 0)
		description += "Perce armure + " + intToString(perceArmure) + "\n";
	if (degatsEnergie > 0)
		description += "Dégats Energie + " + intToString(degatsEnergie) + "\n";
	
	this->id = 0;
	activation = 1;	//Mise en mode passif
	return;
}

void Attaque::appliqueBonus(Personnage *joueur) {
	
	//Changement de stats allié
	if (this->attaquePersoPlus != 0)
		joueur->changeBonusAttaque(this->attaquePersoPlus);
	if (this->attaqueSpePersoPlus != 0)
		joueur->changeBonusAttaqueSpe(this->attaqueSpePersoPlus);
	if (this->defensePersoPlus != 0)
		joueur->changeBonusDefense(this->defensePersoPlus);
	if (this->defenseSpePersoPlus != 0)
		joueur->changeBonusDefenseSpe(this->defenseSpePersoPlus);
	if (this->vitessePersoPlus != 0)
		joueur->changeBonusVitesse(this->vitessePersoPlus);
	
	//Protections élémentales joueur
	if (this->protectionGlaceJoueurPlus != 0)
		joueur->changeBonusGlace(this->protectionGlaceJoueurPlus);
	if (this->protectionFeuJoueurPlus != 0)
		joueur->changeBonusFeu(this->protectionFeuJoueurPlus);
	if (this->protectionFoudreJoueurPlus != 0)
		joueur->changeBonusFoudre(this->protectionFoudreJoueurPlus);
	
	return;
}

/**
 *	Retourne true si l'attaque est lançable, false sinon
 */
bool Attaque::estFaisable(Personnage *joueur) {
	bool faisable = true;	//Par défaut, l'attaque est faisable
	
	if (this->activation == 0) {
		if (this->coutEnergie > joueur->getPointsEnergie())	//Comparaison du coût en énergie
			faisable = false;
		
		if (this->coutVie > joueur->getPointsVie())
			faisable = false;
	}
	else
		faisable = false;
	
	return faisable;
}

/**
 *	Affectue une attaque sur un autre personnage et affiche tous les détails
 */
bool Attaque::faitAttaque(Personnage *joueur, Personnage *ennemi, int direction, int ecran, int x, int y) {
	clearEcranStatus(y);
	if(this->id == 1) {	/* Attaque 1 : CONCENTRATION*/
		
		PA_OutputText(ecran, x, y, "%s se concentre.", stringToChar(joueur->getNom()));
		boucleAppuie();
		clearEcranStatus(y);
		
		//Appel à la fonction de recharge des PE
		int gainPE = joueur->rechargePE();
		
		if (gainPE > 0)
			PA_OutputText(ecran, x, y, "%s gagne %d points\nd'énergie !", stringToChar(joueur->getNom()), gainPE);
		else
			PA_OutputText(ecran, x, y, "Mais son énergie est déjà au\nmaximum.");
		boucleAppuie();
		clearEcranStatus(y);
	}
	else {		/* Attaques diverses et communes*/
		//Affichage du premier texte
		PA_OutputText(ecran, x, y, "%s utilise %s.", stringToChar(joueur->getNom()), stringToChar(this->nom));
		boucleAppuie();
		
		//On retire les PV et PE concommés pour l'attaque
		joueur->retirePointsVie(this->coutVie);
		joueur->retirePointsEnergie(this->coutEnergie);
		
		//Animation ...
		if (direction == GAUCHE_DROITE && this->id == 2) {
			PA_DeleteSprite	(1, ID_SPRITE_HEROS);
			PA_CreateSprite(1, ID_SPRITE_HEROS, (void*)alpha_attaque_normale_Sprite, OBJ_SIZE_32X64,1, 1, 9, 69);
			PA_SetSpritePal	(1 , ID_SPRITE_HEROS, 2);
			PA_UpdateSpriteGfx(1, ID_SPRITE_HEROS, (void*)alpha_attaque_normale_Sprite);
			PA_StartSpriteAnim(1, ID_SPRITE_HEROS, 0, 3, 7);	//Dure 60/7*4 frames
			PA_SetSpriteNCycles	(1, ID_SPRITE_HEROS, 1);	//Ecran, id sprite, ?, nombre boucles
			for(int i = 0 ; i < (int)(60/7*4) ; i++)	//attente 2 secondes
				PA_WaitForVBL();
			PA_StartSpriteAnim(1, ID_SPRITE_HEROS, 3, 3, 7);
			for(int i = 0 ; i < 30 ; i++)	//attente 2 secondes
				PA_WaitForVBL();
			PA_StartSpriteAnim(1, ID_SPRITE_HEROS, 4, 4, 7);
			//PA_DeleteSprite	(1, ID_SPRITE_HEROS);
			PA_UpdateSpriteGfx(1, ID_SPRITE_HEROS, (void*)alpha_combat_Sprite);
			//PA_CreateSprite(1, ID_SPRITE_HEROS, (void*)alpha_combat_Sprite, OBJ_SIZE_32X64, 1, 0, 9, 69);
		}
		boucleAppuie();
		
		//Dégâts
		if (this->degatsVie > 0) {
			//Calcul des dégâts sur la vie : dégâts = (baseDégâts+attaque-[(100-perceArmure)/100]*defense)*bonusElement
			int degats = this->degatsVie;
			if (this->type == TYPE_NORMAL) {
				degats += joueur->getAttaque()+joueur->getBonusAttaque();
				degats -= (int)(((100-this->perceArmure)/100)*(ennemi->getDefense() + ennemi->getBonusDefense()));
			}
			else {
				degats += joueur->getAttaqueSpe()+joueur->getBonusAttaqueSpe();
				degats -= (int)(((100-this->perceArmure)/100)*(ennemi->getDefenseSpe() + ennemi->getBonusDefenseSpe()));
			}
			
			switch(this->element) {
				case ELT_FEU :
					degats = (int)(degats*(100-ennemi->getProtectionFeu())/100);
					break;
				case ELT_GLACE :
					degats = (int)(degats*(100-ennemi->getProtectionGlace())/100);
					break;
				case ELT_FOUDRE :
					degats = (int)(degats*(100-ennemi->getProtectionFoudre())/100);
					break;
			}
			
			if (degats <=0)
				degats = 1;
			
			//Retrait des points de vie de l'adversaire
			degats = ennemi->retirePointsVie(degats);
			
			//Affichage du texte d'info du nombre de dégâts
			clearEcranStatus(y);
			PA_OutputText(ecran, x, y, "%s subit %d points de\ndommages !", stringToChar(ennemi->getNom()), degats);
			boucleAppuie();
			clearEcranStatus(y);
			
			//Si l'attaque absorbe des PV
			if (this->absorptionVie > 0) {
				int recuperation = joueur->soinsPointsVie((int)((degats*this->absorptionVie)/100));
				if (recuperation > 0) {
					PA_OutputText(ecran, x, y, "%s absorbe %d points\nde vie !", stringToChar(joueur->getNom()), recuperation);
					boucleAppuie();
					clearEcranStatus(y);	
				}
			}
			//Si l'attaque absorbe des PE
			if (this->absorptionEnergie > 0) {
				int recuperation = joueur->soinsPointsEnergie((int)((degats*this->absorptionEnergie)/100));
				if (recuperation > 0) {
					PA_OutputText(ecran, x, y, "%s absorbe %d points\nd'énergie !", stringToChar(joueur->getNom()), recuperation);
					boucleAppuie();
					clearEcranStatus(y);	
				}
			}
		}
		//Soins PV
		if (this->soinsVie > 0) {
			int recuperation = this->soinsVie;
			switch(this->element) {
				case ELT_FEU : {
					recuperation = (int)((this->soinsVie*(100-joueur->getProtectionFeu())/100));
					break;
				}
				case ELT_GLACE : {
					recuperation = (int)((this->soinsVie*(100-joueur->getProtectionGlace())/100));
					break;
				}
				case ELT_FOUDRE : {
					recuperation = (int)((this->soinsVie*(100-joueur->getProtectionFoudre())/100));
					break;
				}
			}
			recuperation = joueur->soinsPointsVie(recuperation);
			clearEcranStatus(y);
			if (recuperation > 0)
				PA_OutputText(ecran, x, y, "%s récupère %d points\nde vie !", stringToChar(joueur->getNom()), recuperation);
			else
				PA_OutputText(ecran, x, y, "Les points de vie de %s\nsont déjà au maximum !", stringToChar(joueur->getNom()), recuperation);
			boucleAppuie();
			clearEcranStatus(y);
		}
		//Soins PE
		if (this->soinsEnergie > 0) {
			int recuperation = this->soinsEnergie;
			switch(this->element) {
				case ELT_FEU :
					recuperation = (int)((this->soinsEnergie*(100-joueur->getProtectionFeu())/100));
					break;
				case ELT_GLACE :
					recuperation = (int)((this->soinsEnergie*(100-joueur->getProtectionGlace())/100));
					break;
				case ELT_FOUDRE :
					recuperation = (int)((this->soinsEnergie*(100-joueur->getProtectionFoudre())/100));
					break;
			}
			recuperation = joueur->soinsPointsEnergie(recuperation);
			clearEcranStatus(y);
			if (recuperation > 0)
				PA_OutputText(ecran, x, y, "%s récupère %d points\nd'énergie !", stringToChar(joueur->getNom()), recuperation);
			else
				PA_OutputText(ecran, x, y, "Les points d'énergie de\n%ssont déjà au maximum !", stringToChar(joueur->getNom()), recuperation);
			boucleAppuie();
			clearEcranStatus(y);
		}
		
		//Changement de stats allié
		if (this->attaquePersoPlus != 0) {
			bool change = joueur->changeBonusAttaque(this->attaquePersoPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->attaquePersoPlus > 0)
					PA_OutputText(ecran, x, y, "L'attaque de %s\naugmente !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "L'attaque de %s\ndiminue !", stringToChar(joueur->getNom()));
			} else {
				if (this->attaquePersoPlus > 0)
					PA_OutputText(ecran, x, y, "L'attaque de %s\nest à son maximum !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "L'attaque de %s\nest à son minimum !", stringToChar(joueur->getNom()));
			}
			boucleAppuie();
			clearEcranStatus(y);
		}
		if (this->attaqueSpePersoPlus != 0) {
			bool change = joueur->changeBonusAttaqueSpe(this->attaqueSpePersoPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->attaqueSpePersoPlus > 0)
					PA_OutputText(ecran, x, y, "L'attaque spéciale de\n%s augmente !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "L'attaque spéciale de\n%s diminue !", stringToChar(joueur->getNom()));
			} else {
				if (this->attaqueSpePersoPlus > 0)
					PA_OutputText(ecran, x, y, "L'attaque spéciale de\n%s est à son maximum !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "L'attaque spéciale de\n%s est à son minimum !", stringToChar(joueur->getNom()));
			}
			boucleAppuie();
			clearEcranStatus(y);
		}
		if (this->defensePersoPlus != 0) {
			bool change = joueur->changeBonusDefense(this->defensePersoPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->defensePersoPlus > 0)
					PA_OutputText(ecran, x, y, "La défense de %s\naugmente !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "La défense de %s\ndiminue !", stringToChar(joueur->getNom()));
			} else {
				if (this->defensePersoPlus > 0)
					PA_OutputText(ecran, x, y, "La défense de %s\nest à son maximum !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "La défense de %s\nest à son minimum !", stringToChar(joueur->getNom()));
			}
			boucleAppuie();
			clearEcranStatus(y);
		}
		if (this->defenseSpePersoPlus != 0) {
			bool change = joueur->changeBonusDefenseSpe(this->defenseSpePersoPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->defenseSpePersoPlus > 0)
					PA_OutputText(ecran, x, y, "La défense spéciale de\n%s augmente !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "La défense spéciale de\n%s diminue !", stringToChar(joueur->getNom()));
			} else {
				if (this->defenseSpePersoPlus > 0)
					PA_OutputText(ecran, x, y, "La défense spéciale de\n%s est à son maximum !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "La défense spéciale de\n%s est à son minimum !", stringToChar(joueur->getNom()));
			}
			boucleAppuie();
			clearEcranStatus(y);
		}
		if (this->vitessePersoPlus != 0) {
			bool change = joueur->changeBonusVitesse(this->vitessePersoPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->vitessePersoPlus > 0)
					PA_OutputText(ecran, x, y, "La vitesse de %s\naugmente !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "La vitesse de %s\ndiminue !", stringToChar(joueur->getNom()));
			} else {
				if (this->vitessePersoPlus > 0)
					PA_OutputText(ecran, x, y, "La vitesse de %s\nest à son maximum !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "La vitesse de %s\nest à son minimum !", stringToChar(joueur->getNom()));
			}
			
			boucleAppuie();
			clearEcranStatus(y);
		}
		
		//Changement de stats ennemi
		if (this->attaqueEnnemiPlus != 0) {
			bool change = ennemi->changeBonusAttaque(this->attaqueEnnemiPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->attaqueEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "L'attaque de %s\naugmente !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "L'attaque de %s\ndiminue !", stringToChar(ennemi->getNom()));
			} else {
				if (this->attaqueEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "L'attaque de %s\nest à son maximum !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "L'attaque de %s\nest à son minimum !", stringToChar(ennemi->getNom()));
			}
			boucleAppuie();
			clearEcranStatus(y);
		}
		if (this->attaqueSpeEnnemiPlus != 0) {
			bool change = ennemi->changeBonusAttaqueSpe(this->attaqueSpeEnnemiPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->attaqueSpeEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "L'attaque spéciale de\n%s augmente !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "L'attaque spéciale de\n%s diminue !", stringToChar(ennemi->getNom()));
			} else {
				if (this->attaqueSpeEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "L'attaque spéciale de\n%s est à son maximum !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "L'attaque spéciale de\n%s est à son minimum !", stringToChar(ennemi->getNom()));
			}
			boucleAppuie();
			clearEcranStatus(y);
		}
		if (this->defenseEnnemiPlus != 0) {
			bool change = ennemi->changeBonusDefense(this->defenseEnnemiPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->defenseEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "La défense de %s\naugmente !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "La défense de %s\ndiminue !", stringToChar(ennemi->getNom()));
			} else {
				if (this->defenseEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "La défense de %s\nest à son maximum !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "La défense de %s\nest à son minimum !", stringToChar(ennemi->getNom()));
			}
			boucleAppuie();
			clearEcranStatus(y);
		}
		if (this->defenseSpeEnnemiPlus != 0) {
			bool change = ennemi->changeBonusDefenseSpe(this->defenseSpeEnnemiPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->defenseSpeEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "La défense spéciale de\n%s augmente !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "La défense spéciale de\n%s diminue !", stringToChar(ennemi->getNom()));
			} else {
				if (this->defenseSpeEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "La défense spéciale de\n%s est à son maximum !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "La défense spéciale de\n%s est à son minimum !", stringToChar(ennemi->getNom()));
			}
			boucleAppuie();
			clearEcranStatus(y);
		}
		if (this->vitesseEnnemiPlus != 0) {
			bool change = ennemi->changeBonusVitesse(this->vitesseEnnemiPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->vitesseEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "La vitesse de %s\naugmente !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "La vitesse de %s\ndiminue !", stringToChar(ennemi->getNom()));
			} else {
				if (this->vitesseEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "La vitesse de %s\nest à son maximum !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "La vitesse de %s\nest à son minimum !", stringToChar(ennemi->getNom()));
			}
			
			boucleAppuie();
			clearEcranStatus(y);
		}
		
		//Protections élémentales joueur
		if (this->protectionGlaceJoueurPlus != 0) {
			bool change = joueur->changeBonusGlace(this->protectionGlaceJoueurPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->protectionGlaceJoueurPlus > 0)
					PA_OutputText(ecran, x, y, "La protection contre la glace\nde %s augmente !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "La protection contre la glace\nde %s diminue !", stringToChar(joueur->getNom()));		
				boucleAppuie();
				clearEcranStatus(y);
			}
		}
		if (this->protectionFeuJoueurPlus != 0) {
			bool change = joueur->changeBonusFeu(this->protectionFeuJoueurPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->protectionFeuJoueurPlus > 0)
					PA_OutputText(ecran, x, y, "La protection contre le feu\nde %s augmente !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "La protection contre le feu\nde %s diminue !", stringToChar(joueur->getNom()));
				boucleAppuie();
				clearEcranStatus(y);
			}
		}
		if (this->protectionFoudreJoueurPlus != 0) {
			bool change = joueur->changeBonusFoudre(this->protectionFoudreJoueurPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->protectionFoudreJoueurPlus > 0)
					PA_OutputText(ecran, x, y, "La protection contre la foudre\nde %s augmente !", stringToChar(joueur->getNom()));
				else
					PA_OutputText(ecran, x, y, "La protection contre la foudre\nde %s diminue !", stringToChar(joueur->getNom()));
				boucleAppuie();
				clearEcranStatus(y);
			}
		}
		
		//Protections élémentales ennemi
		if (this->protectionGlaceEnnemiPlus != 0) {
			bool change = ennemi->changeBonusGlace(this->protectionGlaceEnnemiPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->protectionGlaceEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "La protection contre la glace\nde %s augmente !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "La protection contre la glace\nde %s diminue !", stringToChar(ennemi->getNom()));		
				boucleAppuie();
				clearEcranStatus(y);
			}
		}
		if (this->protectionFeuEnnemiPlus != 0) {
			bool change = ennemi->changeBonusFeu(this->protectionFeuEnnemiPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->protectionFeuEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "La protection contre le feu\nde %s augmente !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "La protection contre le feu\nde %s diminue !", stringToChar(ennemi->getNom()));
				boucleAppuie();
				clearEcranStatus(y);
			}
		}
		if (this->protectionFoudreEnnemiPlus != 0) {
			bool change = ennemi->changeBonusFoudre(this->protectionFoudreEnnemiPlus);
			clearEcranStatus(y);	//Nettoyage du texte
			if (change) {
				if (this->protectionFoudreEnnemiPlus > 0)
					PA_OutputText(ecran, x, y, "La protection contre la foudre\nde %s augmente !", stringToChar(ennemi->getNom()));
				else
					PA_OutputText(ecran, x, y, "La protection contre la foudre\nde %s diminue !", stringToChar(ennemi->getNom()));
				boucleAppuie();
				clearEcranStatus(y);
			}
		}
	}
	
	if (ennemi->getPointsVie() == 0)
		return true;
	else
		return false;
}
