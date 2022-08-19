//COTES
#define COTE_HAUT 	0
#define COTE_DROITE 1
#define COTE_BAS 	2
#define COTE_GAUCHE 3

//EVENTS
#define EVT_VIDE				000
#define EVT_ENTREE				001
#define EVT_SORTIE				002
#define EVT_LEVEL_UP			003
#define EVT_TELEPORT			101
#define EVT_COMBAT				201
#define EVT_MODULE				301
#define EVT_REGEN				701
#define EVT_PORTE				801
#define EVT_CLEF				802

//PROBABILITE DES EVENEMENTS	(%)

//Couloirs	(total = 100)
#define P_COMBAT				50			

//Probabilités autres
#define P_TELEPORT				20	//un téléport toutes les 20 impasses environ
#define P_PORTE					10	//5 porte toutes les 100 cases environ
#define P_CLEF					25	//25% de chance de trouver une clef dans un cul de sac
#define P_REGEN					10	//10% de chance de trouver un regénérateur
#define P_MODULE				10	//10% de chance de trouver un coffre de module

//Nombre de types d'évènements
#define TYPE_EVT_MAX	1

//Types d'évènements
#define TYPE_EVT_DIVERS				0
#define TYPE_EVT_TELEPORT			1
#define TYPE_EVT_MONSTRE			2
#define TYPE_EVT_COFFRE 			3
#define TYPE_EVT_COFFRE_PIEGE		4
#define TYPE_EVT_PNJ				5
#define TYPE_EVT_RELIQUE			6
#define TYPE_EVT_SOINS				7
#define TYPE_EVT_PORTE				8

//SPRITES ECRAN HAUT
#define PAL_HERO					0
#define PAL_TELEPORT				1
#define PAL_ESCALIER				2
#define PAL_PORTE					3
#define PAL_CLEF					4
#define PAL_COMBAT					5
#define PAL_COFFRE					6
#define PAL_REGEN					7

#define SPR_HERO					0

//SPRITES ET PALETTES
#define PAL_A						0
#define PAL_L						1
#define PAL_R						2

#define SPR_A						0
#define SPR_L						1
#define SPR_R						2

#define OBJETS_PAR_PAGE 5

#define COULEUR_PV_BAS 1
#define COULEUR_PV_HAUT 2

//COULEUR TEXTE
//0 : blanc, 1 : rouge, 2 : vert, 3 : bleu foncé, 4 : violet,
//5 : bleu clair, 6 : jaune, 7 : gris, 8 : gris foncé, 9 : noir
#define COULEUR_TEXTE 					0
#define COULEUR_SELECTION 				1
#define COULEUR_IMPOSSIBLE 				8
#define COULEUR_SELECTION_IMPOSSIBLE 	3
#define COULEUR_OBJET_OBTENU 			1
#define COULEUR_PV_BAS 					1
#define COULEUR_PV_HAUT 				2
#define COULEUR_ELEM_NEUTRE 			0
#define COULEUR_ELEM_FOUDRE 			6
#define COULEUR_ELEM_FEU 				1
#define COULEUR_ELEM_GLACE 				5
#define COULEUR_ELEM_TERRE 				7
#define COULEUR_TITRE_EVT	 			1

//COMBATS
#define CLASSE_ENNEMI 0
#define CLASSE_GUERRIER 1
#define CLASSE_ELEMENTALISTE 2
#define CLASSE_SCOUT 3

//Type d'attaque
#define TYPE_NORMAL false
#define TYPE_SPECIAL true

//Sens des animss de combat
#define GAUCHE_DROITE 0
#define DROITE_GAUCHE 1

//Id sprites
#define ID_SPRITE_HEROS 0
#define ID_SPRITE_ENNEMI 1

#define NB_ATTAQUES 32

#define BARRES_NOMBRE_CHANGE 5
#define BARRES_FRAMES_CHANGE 5
#define DUREE_RECHARGE_PE 20

#define LIMITE_BONUS 2	//signifie "X fois la carac de base max

#define PV_PAR_POINT 5

//Définition des éléments
#define ELT_NEUTRE	0
#define ELT_FEU 	1
#define ELT_FOUDRE 	2
#define ELT_GLACE 	3
#define BONUS_ELEMENT 1.5

//Positions et tailles des barres de vie et d'énergie
#define BARRES_POS_X 8
#define BARRES_POS_Y_VIE 25
#define BARRES_POS_Y_ENERGIE 41
#define BARRES_TAILLE_X 110
#define BARRES_TAILLE_Y 5
