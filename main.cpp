#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "gestionnaireTerrain.h"
#include "afficheurTxt.h"
#include "afficheurBGI.h"
#include "jeu.h"
#include "terrain.h"
#include "type.h"
#include <memory>

using std::make_unique;
using namespace TYPE;

int main() {
    int choix = 0;
	gestionnaireTerrain ge{ "Terrains.json" };
	while (choix != 3) {
		system("cls");
		std::cout << " +---------------------------------------+ \n";
		std::cout << " | JEU DE DESTRUCTION DE CIBLE PAR LASER | \n";
		std::cout << " +---------------------------------------+ \n\n";
		std::cout << " Que voulez-vous faire ?\n";
		std::cout << "  (1) - Selectionner votre terrain et jouer\n";
		std::cout << "  (2) - Gerer vos terrains\n";
		std::cout << "  (3) - Quitter\n";
		std::cin >> choix;
		switch (choix) {
		case 1:
		{
			// On creer une partie avec un terrain et un afficheur puis on la lance
			system("cls");
			int selec = -1, selectAff = -1;
			std::cout << "Veuiller selectionner un terrain : \n";
			auto terrains = ge.getTerrains();
			int n = 0;
			for (const auto& t : terrains) {
				cout << "Terrain n." << ++n << endl;
				t.affiche(std::cout);
			}
			std::cout << "Votre choix : ";
			std::cin >> selec;
			std::cout << "Il faut choisir votre affichage, 0 pour le mode texte et 1 pour le mode graphique.\nVotre choix :";
			std::cin >> selectAff;
            if(selectAff == 0) {
                afficheurTxt aff{};
                jeu J{ terrains[selec - 1], aff };
                J.exec();
            }
            else if (selectAff == 1) {
                afficheurBGI aff{};
                opengraphsize(1000,1000);
                jeu J{ terrains[selec - 1], aff };
                J.exec();
            }
		}
		break;
		case 2:
			system("cls");
			ge.execute();
			break;
		}
	}
}
