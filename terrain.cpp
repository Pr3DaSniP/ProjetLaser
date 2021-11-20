#include "terrain.h"

Terrain::Terrain() {}

Terrain::Terrain(int hauteur, int largeur) :
    d_hauteur{hauteur}, d_largeur{largeur}, d_map{terrainBase(hauteur, largeur)}
{}

Terrain::Terrain(int hauteur, int largeur, std::vector<std::vector<std::string>> map) :
    d_hauteur{hauteur}, d_largeur{largeur}, d_map{map}
{}

int Terrain::largeur() const { return d_largeur; }

int Terrain::hauteur() const { return d_hauteur; }

void Terrain::setObstacle(int x, int y, const std::string& s) {
    d_map[x][y] = s;
}

void Terrain::affiche(std::ostream& ost) const {
	int n = 1;
	for (int i = 0; i < d_map.size(); ++i) {
		ost << n++ << "\t";
		for (int j = 0; j < d_map[i].size(); ++j) {
			if (d_map[i][j] == "_") {
				ost << " ";
			}
			else {
				ost << d_map[i][j];
			}
		}
		ost << std::endl;
	}
	ost << std::endl;
}

std::vector<std::vector<std::string>> Terrain::terrainBase(int largeur, int hauteur) {
	std::vector<std::vector<std::string>> tB(largeur, std::vector<std::string>(hauteur));
	for (int i = 0; i < largeur; ++i) {
		for (int j = 0; j < hauteur; ++j) {
			if ((i >= 1 && j >= 1) && (i < largeur-1 && j < hauteur-1)) {
				tB[i][j] = " ";
			}
			else {
				tB[i][j] = "X";
			}
		}
	}
	return tB;
}

std::vector<std::vector<std::string>> Terrain::map() const { return d_map; }

nlohmann::json Terrain::creerTerrainJSON() const {
	nlohmann::json j;
	j["Largeur"] = d_largeur;
	j["Hauteur"] = d_hauteur;
	j["Terrain"] = d_map;
	return j;
}
