#include "gestionnaireTerrain.h"

#include <iostream>
#include <vector>
#include <fstream>
#include "json.hpp"
#include "terrain.h"

#include "type.h"
using namespace TYPE;

/* INCLUDE OBJETS */
#include "mur.h"
#include "vide.h"
#include "laser.h"
#include "cible.h"

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
			case 5: break;
        }
        choix = choixMenu();
    }
}

int gestionnaireTerrain::choixMenu() {
    int choix = -1;
    do {
		system("cls");
		cout << " +--------------------------+ \n";
		cout << " | GESTIONNAIRE DE TERRAINS | \n";
		cout << " +--------------------------+ \n\n";
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
	int largeur, hauteur, choix, x, y, dir;
	cout << "Largeur du terrain : "; cin >> largeur; cout << endl;
	cout << "Hauteur du terrain : "; cin >> hauteur; cout << endl;
	terrain T = terrain::terrainBase(largeur, hauteur);
	bool stop = false;
	bool placerCible = false, placerLaser = false;
	while (!stop) {
		T.affiche(cout);
		cout << "(1) PLACER UN MUR\n(2) PLACER LE LASER\n(3) PLACER LA CIBLE\n(4) SUPPRIMER UN ELEMENT\n(5) QUITTER\n"; cin >> choix;
		switch (choix) {
			case 1: {
				cout << "Coordonnees du mur " << largeur << "x" << hauteur << ": "; cin >> x >> y;
				geom::point
					p1{
					    static_cast<double>(x*terrain::TAILLECASE),
					    static_cast<double>(y*terrain::TAILLECASE)
                    },
					p2{
					    static_cast<double>((x+1)*terrain::TAILLECASE),
					    static_cast<double>((y+1)*terrain::TAILLECASE)
                    };
				mur m{p1,p2,OBJET::MUR,false};
				T.insertCase(
					x, y,
					make_unique<mur>(
						m.getP1(),
						m.getP2(),
						m.getType(),
						m.estTouche()
					)
				);
				break;
			}
			case 2:
			{
				if (!placerLaser) {
					cout << "Coordonnees du laser : "; cin >> x >> y;
					geom::point
					p1{
					    static_cast<double>(x*terrain::TAILLECASE),
					    static_cast<double>(y*terrain::TAILLECASE)
                    },
					p2{
					    static_cast<double>((x+1)*terrain::TAILLECASE),
					    static_cast<double>((y+1)*terrain::TAILLECASE)
                    };
					cout << "Direction du laser (0=DROITE, 1=HAUT, 2=GAUCHE, 3=BAS) : "; cin >> dir;
					laser l{ p1,p2,OBJET::LASER, dir };
					T.insertCase(
						x, y,
						make_unique<laser>(
							l.getP1(),
							l.getP2(),
							l.getType(),
							l.getDirection()
						)
					);
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
					geom::point
					p1{
					    static_cast<double>(x*terrain::TAILLECASE),
					    static_cast<double>(y*terrain::TAILLECASE)
                    },
					p2{
					    static_cast<double>((x+1)*terrain::TAILLECASE),
					    static_cast<double>((y+1)*terrain::TAILLECASE)
                    };
					cible c{ p1,p2,OBJET::CIBLE };
					T.insertCase(
						x, y,
						make_unique<cible>(
							c.getP1(),
							c.getP2(),
							c.getType()
						)
					);
					placerCible = true;
				}
				else {
					cout << "Vous avez deja place une cible" << endl;
					system("timeout /t 3");
				}
				break;
			}
			case 4: {
				cout << "Coordonnees : "; cin >> x >> y;
				geom::point
					p1{
					    static_cast<double>(x*terrain::TAILLECASE),
					    static_cast<double>(y*terrain::TAILLECASE)
                    },
					p2{
					    static_cast<double>((x+1)*terrain::TAILLECASE),
					    static_cast<double>((y+1)*terrain::TAILLECASE)
                    };
				vide v{ p1,p2,OBJET::VIDE };
				T.insertCase(
					x, y,
					make_unique<vide>(
						v.getP1(),
						v.getP2(),
						v.getType()
					)
				);
				break;
			}
			case 5: {
				stop = true;
				break;
			}
		}
	}
	d_Terrains.push_back(std::move(T));

}

void gestionnaireTerrain::saveToJSON(vector<terrain>& tTerrain) {
    vector<nlohmann::json> tJSON;
	for (unsigned i = 0; i < tTerrain.size(); ++i) {
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

void gestionnaireTerrain::visualisation(const vector<terrain>& tTerrain) {
	int n = 0;
	for (const auto& t : tTerrain) {
		cout << "Terrain n." << ++n << endl;
		t.affiche(cout);
		cout << endl;
	}
	system("pause");
}

vector<terrain> gestionnaireTerrain::initialisation(const string& nomFichier) {
	std::ifstream fIN(nomFichier);
	auto json = nlohmann::json::parse(fIN);
	int nombreTerrain = json.size();
	vector<terrain> tabTerrain;
	for (int k = 0; k < nombreTerrain; ++k) {
		vector<vector<string>> TerrainTxt = json[k]["Terrain"].get<vector<vector<string>>>();
		int nbLignes = json[k]["NbLignes"].get<int>();
		int nbColonnes = json[k]["NbColonnes"].get<int>();

		terrain tB{ nbLignes, nbColonnes };

		for (unsigned i = 0; i < TerrainTxt.size(); ++i) {
			for (unsigned j = 0; j < TerrainTxt[i].size(); j++) {
				if (TerrainTxt[i][j] == "X") {
					geom::point
					p1{
					    static_cast<double>(i*terrain::TAILLECASE),
					    static_cast<double>(j*terrain::TAILLECASE)
                    },
					p2{
					    static_cast<double>((i+1)*terrain::TAILLECASE),
					    static_cast<double>((j+1)*terrain::TAILLECASE)
                    };
					mur m{ p1,p2,OBJET::MUR,false };
					tB.insertCase(
						i, j,
						make_unique<mur>(
							m.getP1(),
							m.getP2(),
							m.getType(),
							m.estTouche()
							)
					);
				}
				else if (TerrainTxt[i][j] == " ") {
					geom::point
					p1{
					    static_cast<double>(i*terrain::TAILLECASE),
					    static_cast<double>(j*terrain::TAILLECASE)
                    },
					p2{
					    static_cast<double>((i+1)*terrain::TAILLECASE),
					    static_cast<double>((j+1)*terrain::TAILLECASE)
                    };
					vide v{ p1,p2,OBJET::VIDE };
					tB.insertCase(
						i, j,
						make_unique<vide>(
							v.getP1(),
							v.getP2(),
							v.getType()
							)
					);
				}
				else if (TerrainTxt[i][j] == "=") {
					geom::point
					p1{
					    static_cast<double>(i*terrain::TAILLECASE),
					    static_cast<double>(j*terrain::TAILLECASE)
                    },
					p2{
					    static_cast<double>((i+1)*terrain::TAILLECASE),
					    static_cast<double>((j+1)*terrain::TAILLECASE)
                    };

					unsigned dir = -1;
					// Le laser est place sur le mur de gauche donc on part vers la droite
					if (j == 0)
						dir = DIRECTION::DROITE;
					// Le laser est place sur le mur de droite donc on part vers la gauche
					if (j == TerrainTxt[i].size() - 1)
						dir = DIRECTION::GAUCHE;

					// Le laser est place sur le mur d'en haut donc on part vers la bas
					if (i == 0)
						dir = DIRECTION::BAS;
					// Le laser est place sur le mur d'en bas donc on part vers le haut
					if (i == TerrainTxt.size() - 1)
						dir = DIRECTION::HAUT;

					laser l{ p1,p2,OBJET::LASER, static_cast<int>(dir) };
					tB.insertCase(
						i, j,
						make_unique<laser>(
							l.getP1(),
							l.getP2(),
							l.getType(),
							l.getDirection()
						)
					);
				}
				else if (TerrainTxt[i][j] == "@") {
					geom::point
					p1{
					    static_cast<double>(i*terrain::TAILLECASE),
					    static_cast<double>(j*terrain::TAILLECASE)
                    },
					p2{
					    static_cast<double>((i+1)*terrain::TAILLECASE),
					    static_cast<double>((j+1)*terrain::TAILLECASE)
                    };
					cible c{ p1,p2,OBJET::CIBLE };
					tB.insertCase(
						i, j,
						make_unique<cible>(
							c.getP1(),
							c.getP2(),
							c.getType()
						)
					);
				}
			}
		}
		tabTerrain.push_back(std::move(tB));
	}
	return tabTerrain;
}

vector<terrain> gestionnaireTerrain::getTerrains()
{
    return std::move(d_Terrains);
}
