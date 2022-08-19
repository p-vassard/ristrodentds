#ifndef PERSONNAGE_H
	#define PERSONNAGE_H
	
	#include <iostream>
	#include <vector>

	class Attaque;
	
	class Personnage
	{
		public:
			//Constructeurs
			Personnage(int id);
			
			//Fonctions Set
			void setNiveau(int niveau);
			
			void setPointsVie(int pointsVie);
			void setPointsVieMax(int pointsVieMax);
			void setPointsEnergie(int pointsEnergie);
			void setPointsEnergieMax(int pointsEnergieMax);
			
			void setAttaque(int attaque);
			void setAttaqueSpe(int attaqueSpe);
			void setDefense(int defense);
			void setDefenseSpe(int defenseSpe);
			void setVitesse(int vitesse);
			void setAttaque(Attaque *attaque, int slot);
					
			void setBonusAttaque(int attaque);
			void setBonusAttaqueSpe(int attaqueSpe);
			void setBonusDefense(int defense);
			void setBonusDefenseSpe(int defenseSpe);
			void setBonusVitesse(int vitesse);
			
			void setProtectionNormal(int protectionNormal);
			void setProtectionGlace(int protectionGlace);
			void setProtectionFeu(int protectionFeu);
			void setProtectionFoudre(int protectionFoudre);
			
			//Fonctions Get
			int id;
			int getNiveau();
			std::string getNomClasse();
			std::string getNom();
			int getClasse();
			
			int getPointsVie();
			int getPointsVieMax();
			int getPointsEnergie();
			int getPointsEnergieMax();
			
			int getAttaque();
			int getAttaqueSpe();
			int getDefense();
			int getDefenseSpe();
			int getVitesse();
			
			int getBonusAttaque();
			int getBonusAttaqueSpe();
			int getBonusDefense();
			int getBonusDefenseSpe();
			int getBonusVitesse();
			
			int getProtectionGlace();
			int getProtectionFeu();
			int getProtectionFoudre();
			
			Attaque* getAttaque(int slot);
			std::vector<Attaque*> getAttaques();
			std::vector<Attaque*> getAttaquesModifiables();
			void remplaceAttaque(Attaque* attaque, int position);
			
			//Fonctions diverses
			bool faitAttaque(int id, Personnage *ennemi, int direction);
			int retirePointsVie(int points);
			int retirePointsEnergie(int points);
			int soinsPointsVie(int points);
			int soinsPointsEnergie(int points);
			int rechargePE();				//utilisé pour "concentration" et la recharge de fin de tour
			void initPE();
			void initBonus();
			void levelUp();
			
			//Changement de status
			bool changeBonusAttaque(int valeur);
			bool changeBonusAttaqueSpe(int valeur);
			bool changeBonusDefense(int valeur);
			bool changeBonusDefenseSpe(int valeur);
			bool changeBonusVitesse(int valeur);
			
			//Changement des protections élémentales
			bool changeBonusGlace(int valeur);
			bool changeBonusFeu(int valeur);
			bool changeBonusFoudre(int valeur);
			
			//Destructeur
			~Personnage();
		
		private:
			std::string nom;
			int niveau;
			int classe;
			
			int pointsVie;
			int pointsVieMax;
			int pointsEnergie;
			int pointsEnergieMax;
			
			int attaque;
			int attaqueSpe;
			int defense;
			int defenseSpe;
			int vitesse;
			
			int bonusAttaque;
			int bonusAttaqueSpe;
			int bonusDefense;
			int bonusDefenseSpe;
			int bonusVitesse;
			
			int protectionGlace;
			int protectionFeu;
			int protectionFoudre;
			
			Attaque *moveset[6];
	};
#endif
