#ifndef HEROS_H
	#define HEROS_H
	
	#include <vector>	
	#include "Personnage.h"

	class Piece;

	class Heros
	{
		public:
			Heros();
			Heros(int x, int y);
			
			
			//Gestion du personnage
			Personnage* getPerso();
			void setPerso(Personnage* perso);
			
			
			//Position du héros dans le laby
			void setPosition(int x, int y);
			void setPositionPrecedente(int x, int y);
			int getPosX();
			int getPosY();
			int getPosPrecX();
			int getPosPrecY();
			int getDir();
			void setPosX(int x);
			void setPosY(int y);
			void setPosPrecX(int x);
			void setPosPrecY(int y);
			void setDir(int dir);
			
			//Gestion de l'XP
			int getExp();
			int ajouteExp(int exp);
			
			
			//Gestion des objets
			int ajouteObjet(Piece* objet);
			int retireObjet(Piece* objet);
			bool possedeObjet(Piece* objet);
			std::vector<Piece*> getObjets();
			Piece* getObjet(int index);
			
		private:
			int posX;
			int posY;
			int posPrecX;
			int posPrecY;
			int dir;
			
			Personnage* perso;
			
			int pageObjet;
			std::vector<Piece*> objets;
			
			int exp;
			
	};
#endif
