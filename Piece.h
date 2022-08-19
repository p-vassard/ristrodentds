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
						
			//Position de la pièce dans le laby
			int getPosX();
			int getPosY();
			
			//Type de terrain
			void setSol();
			void setMur();
			bool isSol();
			bool isMur();
			
			//Valeur de la pièce
			void setValeur(int entree);
			int getValeur();
			
			//Pièce visitée
			void setVisite(bool valeur);
			bool getVisite();
			
			//Pièce aperçue
			void setApercu(bool valeur);
			bool getApercu();
			
			
			/* EVENEMENTS */
			
			//Création des évènements
			void creeEvenement(int id);
			std::vector<int> creeEvenementRandom(int max);
			void creeEvenementLien(int id, Piece* salleLien);
			
			//Gestion des évènements associés
			Piece* getPieceAssociee();
			void setLien(Piece* lien);
			
			//Scripts liés à l'id et au type de l'évènement
			int getIdEvenement();
			int getTypeEvenement();
			std::string getNomObjet();
			bool estSolide();
			bool activationAutomatique();
			bool activationDistance();
			bool activationContact();
			
			//Visibilité de l'évènement
			void setEvenementVisible(bool visible);
			bool getEvenementVisible();
					
			//Code de l'évènement
			int setEvenementCodeRandom();
			void setEvenementCode(int code);
			int getEvenementCode();
			 
			//Scripts d'activation
			bool activeEvenement(Heros* joueur);
			
			//Fonctions internes à la gestion des évènements
			std::string porteGetCouleur(int code);
			std::string porteGetForme(int code);
			
			
		
		private:
			/* LABY */
			int posX;	//Position en X dans le laby
			int posY;	//Position en Y dans le laby
			
			int valeur;	//Valeur de la pièce (sert à la construction)
			
			bool visite;	//Pièce visitée ou non
			bool apercu;	//Pièce aperçue ou non
			
			bool mur;		//true si mur, false si sol
			
			
			/* EVENEMENT */
			int evenementType;	//Type de l'évènement
			int evenementId;	//Id de l'évènement
			int evenementCode;	//Code de l'évènement (détermine les textes, possibilités internes à l'évènement)
			bool evenementVisible;	//Evènement visible ou non
			std::vector<Piece*> evenementsAssocies;	//Liste des évènements associés (ex : une clef est associée à une porte)
	};
#endif
