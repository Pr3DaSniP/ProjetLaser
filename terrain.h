#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <memory>
#include <string>
#include "json.hpp"
#include "objet.h"
#include "vide.h"
#include "mur.h"
#include "laser.h"
#include "cible.h"
#include "miroir.h"
#include "rayon.h"
#include "type.h"

using std::unique_ptr;
using std::vector;
using std::make_unique;
using std::string;

using namespace TYPE;

class terrain {
public:
	// Taille d'une case du terrain pour l'afficheurBGI
	static const int TAILLECASE = 25;

	terrain(int nbLignes, int nbColonnes);

	void insertCase(int i, int j, unique_ptr<objet> c);

	objet* getObjet(int i, int j) const;

	vector<vector<objet*>> getObjets() const;

	static terrain terrainBase(int nbLignes, int nbColonnes);

	nlohmann::json creerTerrainJSON() const;

	vector<vector<string>> terrainTxt() const;

	void affiche(std::ostream& ost) const;

	laser* trouveLaser() const;

	cible* trouveCible() const;

	bool estGagne();

	void propageLaser();
private:
	vector<vector<unique_ptr<objet>>> initialise(int nbLignes, int nbColonnes);

	vector<vector<unique_ptr<objet>>> d_terrain;
	laser* d_laser;
	cible* d_cible;
};

#endif // !TERRAIN_H
