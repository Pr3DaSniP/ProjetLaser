#include "gestionnaireTerrain.h"

#include <iostream>
#include <vector>
#include <fstream>

#include "terrain.h"
#include "json.hpp"

gestionnaireTerrain::gestionnaireTerrain(const std::string& nomFichier) :
    d_Terrains{initialisation(nomFichier)}, d_Filename{nomFichier}
{}

void gestionnaireTerrain::execute() {
    auto choix = choixMenu();
    while(choix != 5) {
        switch(choix)
        {
            case 1: creerTerrain(); break;
            case 2: supprimerTerrain(); break;
			case 3: visualisation(); break;
            case 4: saveToJSON(d_Terrains); break;
        }
        choix = choixMenu();
    }
}

int gestionnaireTerrain::choixMenu() {
    int choix = -1;
    do {
        std::cout << "Voulez vous : \n";
        std::cout << "(1) Creer un terrain" << '\n';
        std::cout << "(2) Supprimer un terrain" << '\n';
		std::cout << "(3) Afficher les terrains" << '\n';
        std::cout << "(4) Sauvegarder" << '\n';
		std::cout << "(5) Quitter" << '\n';
        std::cin >> choix;
    }
    while(choix < 0 || choix > 5);
    return choix;
}

void gestionnaireTerrain::creerTerrain() {
	int largeur, hauteur, choix, x, y;
	std::cout << "Largeur du terrain : "; std::cin >> largeur; std::cout << std::endl;
	std::cout << "Hauteur du terrain : "; std::cin >> hauteur; std::cout << std::endl;
	Terrain T{hauteur, largeur};
	bool stop = false;
	bool placerCible = false, placerLaser = false;
	while (!stop) {
		T.affiche(std::cout);
		std::cout << "(1) PLACER UN MUR\n(2) PLACER LE LASER\n(3) PLACER LA CIBLE\n(4) SAUVEGARDER\n(5) QUITTER\n"; std::cin >> choix;
		switch (choix) {
			case 1:
				std::cout << "Coordonnees du mur " << largeur << "x" << hauteur << ": "; std::cin >> x >> y;
				T.setObstacle(x,y,"X");
				break;
			case 2:
				if (!placerLaser) {
					std::cout << "Coordonnees du laser : "; std::cin >> x >> y;
					T.setObstacle(x,y,"#");
					placerLaser = true;
				}
				else {
					std::cout << "Vous avez deja place un laser" << std::endl;
					system("timeout /t 3>nul");
				}
				break;
			case 3:
				if (!placerCible) {
					std::cout << "Coordonnees de la cible : "; std::cin >> x >> y;
					T.setObstacle(x,y,"@");
					placerCible = true;
				}
				else {
					std::cout << "Vous avez deja place une cible" << std::endl;
					system("timeout /t 3>nul");
				}
				break;
			case 4:
				stop = true;
				break;
			case 5:
				break;
		}
	}
	d_Terrains.push_back(T);
}

void gestionnaireTerrain::saveToJSON(std::vector<Terrain> tTerrain) {
    std::vector<nlohmann::json> tJSON;
	for (int i = 0; i < tTerrain.size(); ++i) {
		tJSON.push_back(tTerrain[i].creerTerrainJSON());
	}
	std::ofstream fOUT(d_Filename);
	fOUT.seekp(0, std::ios::beg);
	nlohmann::json j = tJSON;
	fOUT << j.dump(4);
}

void gestionnaireTerrain::supprimerTerrain() {
    int i = 0;
    std::cout << "Il y a " << d_Terrains.size() << " terrains.\nIndex : "; std::cin >> i;
    d_Terrains.erase(d_Terrains.begin() + (i-1));
}

std::vector<Terrain> gestionnaireTerrain::initialisation(const std::string& nomFichier) {
	std::ifstream fIN(nomFichier);
	auto json = nlohmann::json::parse(fIN);
	int nombreTerrain = json.size();
	std::vector<Terrain> tabTerrain(nombreTerrain);
	for (int i = 0; i < nombreTerrain; ++i) {
		Terrain T{
			json[i]["Hauteur"].get<int>(),
			json[i]["Largeur"].get<int>(),
			json[i]["Terrain"].get<std::vector<std::vector<std::string>>>()
		};
		tabTerrain[i] = T;
	}
	return tabTerrain;
}

void gestionnaireTerrain::visualisation() const {
	for (const auto& t : d_Terrains) {
		t.affiche(std::cout);
	}
}