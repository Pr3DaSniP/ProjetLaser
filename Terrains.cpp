#include "Terrains.h"

Terrain::Terrain() : d_terrain{} {}

Terrain::Terrain(int nbLignes, int nbColonnes) : d_terrain{initialise(nbLignes, nbColonnes)} {}

Terrain::Terrain(vector<vector<Case*>> Terrain) : d_terrain{Terrain} {}

vector<vector<Case*>> Terrain::initialise(int nbLignes, int nbColonnes) {
	vector<vector<Case*>> tB;
	tB.resize(nbLignes);
	for (auto& t : tB)
		t.resize(nbColonnes);
	return tB;
}

vector<vector<Case*>> Terrain::terrainBase(int nbLignes, int nbColonnes) {
	vector<vector<Case*>> tB;
	tB.resize(nbLignes);
	for (auto& t : tB)
		t.resize(nbColonnes);

	for (int i = 0; i < nbLignes; ++i) {
		for (int j = 0; j < nbColonnes; ++j) {
			if ((i >= 1 && j >= 1) && (i < nbLignes - 1 && j < nbColonnes - 1)) {
				Case* c = new Case{ i,j,Case::TYPECASE::VIDE, " " };
				tB[i][j] = c;
			}
			else {
				Case* c = new Case{ i,j,Case::TYPECASE::MUR, "X" };
				tB[i][j] = c;
			}
		}
	}
	return tB;
}

nlohmann::json Terrain::creerTerrainJSON() const {
	vector<vector<string>> terrainTXT(d_terrain.size(), vector<string>(d_terrain[0].size()));
	for (int i = 0; i < d_terrain.size(); ++i) {
		for (int j = 0; j < d_terrain[i].size(); ++j) {
			switch (d_terrain[i][j]->typeCase()) {
			case Case::TYPECASE::MUR:
				terrainTXT[i][j] = "X";
				break;
			case Case::TYPECASE::MIROIR:
				terrainTXT[i][j] = "/";
				break;
			case Case::TYPECASE::LASER:
				terrainTXT[i][j] = "=";
				break;
			case Case::TYPECASE::VIDE:
				terrainTXT[i][j] = " ";
				break;
			case Case::TYPECASE::CIBLE:
				terrainTXT[i][j] = "@";
				break;
			}
		}
	}
	nlohmann::json j;
	j["NbColonnes"] = terrainTXT.size();
	j["NbLignes"] = terrainTXT[0].size();
	j["Terrain"] = terrainTXT;
	return j;
}

void Terrain::insertCase(int i, int j, Case *c) {
	d_terrain[i][j] = c;
}

void Terrain::affiche(std::ostream& ost) const {
	int n = 1;
	for (int i = 0; i < d_terrain.size(); ++i) {
		ost << n++ << "\t";
		for (int j = 0; j < d_terrain[i].size(); ++j) {
			ost << d_terrain[i][j]->representation();
		}
		ost << std::endl;
	}
	ost << std::endl;
}

/*==============================================================================*/

Case::Case(int positionHorizontale, int positionVerticale, int typeCase, string representation) : 
	d_positionHorizontale{ positionHorizontale }, d_positionVerticale{ positionVerticale }, 
	d_typeCase{ typeCase }, d_representation{ representation }
{}

int Case::positionHorizontale() const { return d_positionHorizontale; }
int Case::positionVerticale() const { return d_positionVerticale; }
int Case::typeCase() const { return d_typeCase; }
string Case::representation() const { return d_representation; }
