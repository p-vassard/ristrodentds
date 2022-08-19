#ifndef ATTAQUE_H
	#define ATTAQUE_H
	
	#include <iostream>
	#include "Personnage.h"

	class Attaque
	{
		public:
			//Constructeurs
			Attaque();
			Attaque(int id);
			void initAttaque();
			void changeAttaqueId(int id);
			void changeAttaqueRandom(int niveauMax);
			
			//Fonctions Get
			std::string getNom();
			std::string getDescription();
			int getCoutEnergie();
			std::string getDetails();
			void afficheDescriptionCombat(int ecran, int posX, int posY);
			std::string getTexteType();
			std::string getTexteElement();
			int getCouleur();
			int getId();
			
			//Fonctions Set
			void creeModule(int id, int niveau);
			
			//Divers
			void appliqueBonus(Personnage *joueur);
			bool faitAttaque(Personnage *joueur, Personnage *ennemi, int direction, int ecran, int x, int y);
			bool estFaisable(Personnage *joueur);
			//Destructeur
			~Attaque();
		
		private:
			int id;
			
			std::string nom;			//Nom qui sera affiché
			std::string description;	//Description qui sera affichée
			int niveau;					//Niveau de l'attaque, doit correspondre à peu près au niveau du perso
			bool type;					//0 : normal, 1 : spécial
			
			int activation;				//Si 0 : à activer via le menu, si 1 : passif
			
			int coutEnergie;			//Coût de base
			int coutVie;				//Optionnel, coût de sacrifice en plus
			
			int degatsVie;				//Dégâts de base
			int degatsEnergie;			//Dégâts sur l'énergie de l'ennemi
			
			int soinsVie;				//Soins indépendants de l'absorption
			int soinsEnergie;			//Soins indépendants de l'absorption
			
			int absorptionVie;			//0-100 (%)
			int absorptionEnergie;		//0-100 (%)
			
			int perceArmure;			//0-100
			int element;				//Element de l'attaque
			
			int nombreTours;			//nombre de tours où le skill se lance, le coût se faisant à l'activation seulement
			int entretienEnergie;		//Coût d'entretiens
			int entretienVie;
			int entretienEnergiePourcent;
			int entretienViePourcent;
			
			int attaquePersoPlus;
			int attaqueSpePersoPlus;
			int defensePersoPlus;
			int defenseSpePersoPlus;
			int vitessePersoPlus;
			
			int attaqueEnnemiPlus;
			int attaqueSpeEnnemiPlus;
			int defenseEnnemiPlus;
			int defenseSpeEnnemiPlus;
			int vitesseEnnemiPlus;
			
			int protectionGlaceJoueurPlus;
			int protectionFeuJoueurPlus;
			int protectionFoudreJoueurPlus;
			
			int protectionGlaceEnnemiPlus;
			int protectionFeuEnnemiPlus;
			int protectionFoudreEnnemiPlus;

			int script;					//id du script à activer (0 si aucun)
	};
#endif
