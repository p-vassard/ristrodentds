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
			
			std::string nom;			//Nom qui sera affich�
			std::string description;	//Description qui sera affich�e
			int niveau;					//Niveau de l'attaque, doit correspondre � peu pr�s au niveau du perso
			bool type;					//0 : normal, 1 : sp�cial
			
			int activation;				//Si 0 : � activer via le menu, si 1 : passif
			
			int coutEnergie;			//Co�t de base
			int coutVie;				//Optionnel, co�t de sacrifice en plus
			
			int degatsVie;				//D�g�ts de base
			int degatsEnergie;			//D�g�ts sur l'�nergie de l'ennemi
			
			int soinsVie;				//Soins ind�pendants de l'absorption
			int soinsEnergie;			//Soins ind�pendants de l'absorption
			
			int absorptionVie;			//0-100 (%)
			int absorptionEnergie;		//0-100 (%)
			
			int perceArmure;			//0-100
			int element;				//Element de l'attaque
			
			int nombreTours;			//nombre de tours o� le skill se lance, le co�t se faisant � l'activation seulement
			int entretienEnergie;		//Co�t d'entretiens
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

			int script;					//id du script � activer (0 si aucun)
	};
#endif
