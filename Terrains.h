#pragma once

#include <vector>
#include <memory>
#include <string>
#include "json.hpp"

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::string;

class Case {
private:
	int d_positionHorizontale;
	int d_positionVerticale;
	int d_typeCase;
	string d_representation;
public:
	enum TYPECASE {
		LASER,
		MIROIR,
		VIDE,
		MUR,
		CIBLE
	};
	Case() = default;
	Case(int positionHorizontale, int positionVerticale, int typeCase, string representation);
	int positionHorizontale() const;
	int positionVerticale() const;
	virtual int typeCase() const;
	virtual string representation() const;
};


class Terrain {
private:
	vector<vector<Case*>> d_terrain;
	
public:
	Terrain();
	Terrain(int nbLignes, int nbColonnes);
	Terrain(vector<vector<Case*>> Terrain);
	vector<vector<Case*>> initialise(int nbLignes, int nbColonnes);
	nlohmann::json creerTerrainJSON() const;
	void affiche(std::ostream& ost) const;
	void insertCase(int i, int j, Case *c);
	static vector<vector<Case*>> terrainBase(int nbLignes, int nbColonnes);
};