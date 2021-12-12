#include "gestionnaireTerrain.h"

#include <iostream>
#include <vector>
#include <fstream>

#include "Terrains.h"
#include "json.hpp"

gestionnaireTerrain::gestionnaireTerrain(const string& nomFichier) :
    d_Terrains{initialisation(nomFichier)}, d_Filename{nomFichier}
{}

void gestionnaireTerrain::execute() {
    auto choix = choixMenu();
    while(choix != 5) {
        switch(choix)
        {
            case 1: creerTerrain(); break;
            case 2: supprimerTerrain(); break;
            case 3: saveToJSON(d_Terrains); break;
			case 4: visualisation(d_Terrains); break;
        }
        choix = choixMenu();
    }
}

int gestionnaireTerrain::choixMenu() {
    int choix = -1;
    do {
        cout << "Voulez vous : \n";
        cout << "(1) Creer un terrain" << '\n';
        cout << "(2) Supprimer un terrain" << '\n';
        cout << "(3) Sauvegarder" << '\n';
		cout << "(4) Visualiser les terrains" << '\n';
		cout << "(5) Quitter" << '\n';
        cin >> choix;
    }
    while(choix < 0 || choix > 5);
    return choix;
}

void gestionnaireTerrain::creerTerrain() {
	int largeur, hauteur, choix, x, y;
	cout << "Largeur du terrain : "; cin >> largeur; cout << endl;
	cout << "Hauteur du terrain : "; cin >> hauteur; cout << endl;
	Terrain T = Terrain::terrainBase(largeur, hauteur);
	bool stop = false;
	bool placerCible = false, placerLaser = false;
	while (!stop) {
		T.affiche(cout);
		cout << "(1) PLACER UN MUR\n(2) PLACER LE LASER\n(3) PLACER LA CIBLE\n(4) SAUVEGARDER\n(5) QUITTER\n"; cin >> choix;
		switch (choix) {
			case 1: {
				cout << "Coordonnees du mur " << largeur << "x" << hauteur << ": "; cin >> x >> y;
				Case* c = new Case{ x,y,Case::TYPECASE::MUR, "X" };
				T.insertCase(x, y, c);
				break;
			}
			case 2:
			{
				if (!placerLaser) {
					cout << "Coordonnees du laser : "; cin >> x >> y;
					Case* c = new Case{ x,y,Case::TYPECASE::LASER, "=" };
					T.insertCase(x, y, c);
					placerLaser = true;
				}
				else {
					cout << "Vous avez deja place un laser" << endl;
					system("timeout /t 3");
				}
				break;
			}	
			case 3: {
				if (!placerCible) {
					cout << "Coordonnees de la cible : "; cin >> x >> y;
					Case* c = new Case{ x,y,Case::TYPECASE::CIBLE, "@" };
					T.insertCase(x, y, c);
					placerCible = true;
				}
				else {
					cout << "Vous avez deja place une cible" << endl;
					system("timeout /t 3");
				}
				break;
			}
			case 4: {
				stop = true;
				break;
			}
		}
	}
	d_Terrains.push_back(T);
}

void gestionnaireTerrain::saveToJSON(vector<Terrain> tTerrain) {
    vector<nlohmann::json> tJSON;
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
    cout << "Il y a " << d_Terrains.size() << " terrains.\nIndex : "; cin >> i;
    d_Terrains.erase(d_Terrains.begin() + (i-1));
}

void gestionnaireTerrain::visualisation(const vector<Terrain>& tTerrain) {
	int n = 0;
	for (const auto& t : tTerrain) {
		cout << "Terrain n." << ++n << endl;
		t.affiche(cout);
		cout << endl;
	}
}

vector<Terrain> gestionnaireTerrain::initialisation(const string& nomFichier) {
	std::ifstream fIN(nomFichier);
	auto json = nlohmann::json::parse(fIN);
	int nombreTerrain = json.size();
	vector<Terrain> tabTerrain(nombreTerrain);
	for (int k = 0; k < nombreTerrain; ++k) {
		vector<vector<string>> TerrainTxt = json[k]["Terrain"].get<vector<vector<string>>>();
		int nbLignes = json[k]["NbLignes"].get<int>();
		int nbColonnes = json[k]["NbColonnes"].get<int>();

		Terrain tB{ nbLignes, nbColonnes };

		for (int i = 0; i < TerrainTxt.size(); ++i) {
			for (int j = 0; j < TerrainTxt[i].size(); j++) {
				if (TerrainTxt[i][j] == "X") {
					Case* c = new Case{ i,j,Case::TYPECASE::MUR, "X" };
					tB.insertCase(i, j, c);
				}
				else if (TerrainTxt[i][j] == " ") {
					Case* c = new Case{ i,j,Case::TYPECASE::VIDE, " " };
					tB.insertCase(i, j, c);
				}
				else if (TerrainTxt[i][j] == "=") {
					Case* c = new Case{ i,j,Case::TYPECASE::LASER, "=" };
					tB.insertCase(i, j, c);
				}
				else if (TerrainTxt[i][j] == "@") {
					Case* c = new Case{ i,j,Case::TYPECASE::CIBLE, "@" };
					tB.insertCase(i, j, c);
				}
				else if (TerrainTxt[i][j] == "/") {
					Case* c = new Case{ i,j,Case::TYPECASE::MIROIR, "/" };
					tB.insertCase(i, j, c);
				}
			}
		}

		tabTerrain[k] = tB;
	}
	return tabTerrain;
}
