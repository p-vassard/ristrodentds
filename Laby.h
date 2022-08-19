#ifndef LABY_H
	#define LABY_H
	
	#include <vector>
	#include "Piece.h"
	#include "Heros.h"
	#include "Attaque.h"

	class Laby
	{
		public:
			//Constructeurs
			Laby();
			Laby(int tailleX, int tailleY, Heros* joueur);
			
			//Destructeur
			~Laby();
			
			//Fonction de création du laby
			std::vector<Piece*> genereLaby();
			void genereEvenements(std::vector<Piece*>);
			std::vector<int> getMursCassables(int x, int y);
			bool isTeleportable(int x, int y);
			int getNombreMursCassables(int x, int y);
			bool solAdjascent(int x, int y, int interdit);
			
			//Fonction d'affichage
			void afficheLaby();
			void afficheApercu(int nombreCases);
			void afficheApercuOld(int nombreCases);
			void resetAffichageLaby();
			void resetAffichageLabyHero();
			
			//Fonctions liées aux pièces du laby
			Piece* getPiece(int x, int y);
			bool estBord(int x, int y, int dir);
			bool estImpasse(int x, int y);
			int getNombreOuvertures(int x, int y);
			bool estOuvert(int x, int y, int dir);
			bool estBloque(int x, int y, int dir);
			std::vector<int> getOuvertures(int x, int y);
			bool getVisite(int i, int j);
			bool getTileApercue(int i, int j);
			bool getPieceApercue(int i, int j);
			void setValeur(int x, int y, int valeur);
			void setVisite(int x, int y, bool valeur);
			bool pieceExiste(int x, int y);
			
			
			//Fonctions de jeu
			int bougeHeros(int dir);
			int appuieBoutonValider();
			int activeEvenement(int x, int y);
			void objetObtenu(std::string objet);
			
			//Ecran du bas
			void afficheMenu();
			void changeMenu(int direction);
			void nettoieEcranMenu();
			
			//Gestion des graphismes
			void supprimeSprites();
			void chargePalettesLaby();
			void rechargeGFX();
			void afficheNiveau();
			
		private:
			Heros* joueur;	//Le héros, perdu dans le laby
			int tailleX;	//Taille du laby en X
			int tailleY;	//Taille du laby en Y
			std::vector< std::vector< Piece* > > salles;	//Pièces du laby
			
			int numSprites;
			int pageMenu;	//0 : statut, 1 : Objets, 2 : Attaques
	};
#endif
