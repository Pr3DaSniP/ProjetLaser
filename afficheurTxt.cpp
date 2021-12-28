#include "afficheurTxt.h"

void afficheurTxt::afficheTerrain(const terrain& t) const {
	t.affiche(std::cout);
}

void afficheurTxt::afficheResultat(bool result) const {
	result == true ? std::cout << "Vous avez gagne ! :D\n" : std::cout << "Vous avez perdu ! D:\n";
	system("pause");
}
