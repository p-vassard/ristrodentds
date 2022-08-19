#ifndef PIECE_H
	#define PIECE_H
	
	#include <vector>
	#include "Heros.h"

	class Piece
	{
		public:
		
			//Constructeurs
			Piece();
			Piece(int x, int y);
			
			//Destructeur
			~Piece();
			
			
			/* LABY */
						
			//Position de la pi�ce dans le laby
			int getPosX();
			int getPosY();
			
			//Type de terrain
			void setSol();
			void setMur();
			bool isSol();
			bool isMur();
			
			//Valeur de la pi�ce
			void setValeur(int entree);
			int getValeur();
			
			//Pi�ce visit�e
			void setVisite(bool valeur);
			bool getVisite();
			
			//Pi�ce aper�ue
			void setApercu(bool valeur);
			bool getApercu();
			
			
			/* EVENEMENTS */
			
			//Cr�ation des �v�nements
			void creeEvenement(int id);
			std::vector<int> creeEvenementRandom(int max);
			void creeEvenementLien(int id, Piece* salleLien);
			
			//Gestion des �v�nements associ�s
			Piece* getPieceAssociee();
			void setLien(Piece* lien);
			
			//Scripts li�s � l'id et au type de l'�v�nement
			int getIdEvenement();
			int getTypeEvenement();
			std::string getNomObjet();
			bool estSolide();
			bool activationAutomatique();
			bool activationDistance();
			bool activationContact();
			
			//Visibilit� de l'�v�nement
			void setEvenementVisible(bool visible);
			bool getEvenementVisible();
					
			//Code de l'�v�nement
			int setEvenementCodeRandom();
			void setEvenementCode(int code);
			int getEvenementCode();
			 
			//Scripts d'activation
			bool activeEvenement(Heros* joueur);
			
			//Fonctions internes � la gestion des �v�nements
			std::string porteGetCouleur(int code);
			std::string porteGetForme(int code);
			
			
		
		private:
			/* LABY */
			int posX;	//Position en X dans le laby
			int posY;	//Position en Y dans le laby
			
			int valeur;	//Valeur de la pi�ce (sert � la construction)
			
			bool visite;	//Pi�ce visit�e ou non
			bool apercu;	//Pi�ce aper�ue ou non
			
			bool mur;		//true si mur, false si sol
			
			
			/* EVENEMENT */
			int evenementType;	//Type de l'�v�nement
			int evenementId;	//Id de l'�v�nement
			int evenementCode;	//Code de l'�v�nement (d�termine les textes, possibilit�s internes � l'�v�nement)
			bool evenementVisible;	//Ev�nement visible ou non
			std::vector<Piece*> evenementsAssocies;	//Liste des �v�nements associ�s (ex : une clef est associ�e � une porte)
	};
#endif
