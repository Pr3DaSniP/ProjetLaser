#include "terrain.h"

terrain::terrain(int nbLignes, int nbColonnes)
	: d_terrain{ initialise(nbLignes, nbColonnes) },
	d_laser{ nullptr }, d_cible{ nullptr }
{}

vector<vector<unique_ptr<objet>>> terrain::initialise(int nbLignes, int nbColonnes) {
	vector<vector<unique_ptr<objet>>> tmp;
	tmp.resize(nbLignes);
	for (auto& t : tmp)
		t.resize(nbColonnes);

	return std::move(tmp);
}

void terrain::insertCase(int i, int j, unique_ptr<objet> c) {
	d_terrain[i][j] = std::move(c);
}

objet* terrain::getObjet(int i, int j) const {
	return d_terrain[i][j].get();
}

vector<vector<objet*>> terrain::getObjets() const {
    vector<vector<objet*>> tmp{d_terrain.size(), vector<objet*>(d_terrain[0].size())};
    for(int i = 0; i < d_terrain.size(); ++i) {
        for(int j = 0; j < d_terrain[i].size(); ++j) {
            tmp[i][j] = getObjet(i,j);
        }
    }
    return tmp;
}

terrain terrain::terrainBase(int nbLignes, int nbColonnes) {
	terrain T{ nbLignes, nbColonnes };

	for (int i = 0; i < nbLignes; ++i) {
		for (int j = 0; j < nbColonnes; ++j) {
			geom::point
				p1{ static_cast<double>(i*TAILLECASE), static_cast<double>(j*TAILLECASE) },
				p2{ static_cast<double>((i+1)*TAILLECASE), static_cast<double>((j+1)*TAILLECASE) }
			;
			if ((i >= 1 && j >= 1) && (i < nbLignes - 1 && j < nbColonnes - 1)) {
				vide v{
					p1,
					p2,
					OBJET::VIDE,
					false
				};
				T.insertCase(
					i, j,
					make_unique<vide>(
						v.getP1(),
						v.getP2(),
						v.getType()
						)
				);
			}
			else {
				mur m{
					p1,
					p2,
					OBJET::MUR,
					false
				};
				T.insertCase(
					i, j,
					make_unique<mur>(
						m.getP1(),
						m.getP2(),
						m.getType()
						)
				);
			}
		}
	}
	return T;
}

nlohmann::json terrain::creerTerrainJSON() const {
	vector<vector<string>> terrainTXT(d_terrain.size(), vector<string>(d_terrain[0].size()));
	for (int i = 0; i < d_terrain.size(); ++i) {
		for (int j = 0; j < d_terrain[i].size(); ++j) {
			switch (d_terrain[i][j]->getType()) {
			case OBJET::MUR:
				terrainTXT[i][j] = "X";
				break;
			case OBJET::LASER:
				terrainTXT[i][j] = "=";
				break;
			case OBJET::VIDE:
				terrainTXT[i][j] = " ";
				break;
			case OBJET::CIBLE:
				terrainTXT[i][j] = "@";
				break;
			}
		}
	}
	nlohmann::json j;
	j["NbLignes"] = terrainTXT.size();
	j["NbColonnes"] = terrainTXT[0].size();
	j["Terrain"] = terrainTXT;
	return j;
}

vector<vector<string>> terrain::terrainTxt() const {
	vector<vector<string>> terrainTXT(d_terrain.size(), vector<string>(d_terrain[0].size()));
	for (int i = 0; i < d_terrain.size(); ++i) {
		for (int j = 0; j < d_terrain[i].size(); ++j) {
			switch (d_terrain[i][j]->getType()) {
			case OBJET::MUR:
				terrainTXT[i][j] = "X";
				break;
			case OBJET::MIROIR_BACKSLASH:
				terrainTXT[i][j] = "\\";
				break;
			case OBJET::MIROIR_SLASH:
				terrainTXT[i][j] = "/";
				break;
			case OBJET::LASER:
				terrainTXT[i][j] = "=";
				break;
			case OBJET::VIDE:
				terrainTXT[i][j] = " ";
				break;
			case OBJET::CIBLE:
				terrainTXT[i][j] = "@";
				break;
			case OBJET::RAYON:
				terrainTXT[i][j] = "-";
				break;
			}
		}
	}
	return terrainTXT;
}

void terrain::affiche(std::ostream& ost) const {
	int n = 0;
	auto tmp = terrainTxt();
	for (int i = 0; i < tmp.size(); ++i) {
		ost << n++ << "\t";
		for (int j = 0; j < tmp[i].size(); j++) {
			ost << tmp[i][j];
		}
		ost << std::endl;
	}
	ost << std::endl;
}

laser* terrain::trouveLaser() const {
	laser* l = nullptr;
	int dir = -1;
	for (int i = 0; i < d_terrain.size(); ++i) {
		for (int j = 0; j < d_terrain[i].size(); ++j) {
			if (d_terrain[i][j]->getType() == OBJET::LASER) {
				geom::point p1{
				    static_cast<double>(i*TAILLECASE),
				    static_cast<double>(j*TAILLECASE)
                },
				p2{
				    static_cast<double>((i+1)*TAILLECASE),
				    static_cast<double>((j+1)*TAILLECASE)
                };

				// Le laser est place sur le mur de gauche donc on part vers la droite
				if (j == 0)
					dir = DIRECTION::DROITE;
				// Le laser est place sur le mur de droite donc on part vers la gauche
				if (j == d_terrain[i].size() - 1)
					dir = DIRECTION::GAUCHE;

				// Le laser est place sur le mur d'en haut donc on part vers la bas
				if (i == 0)
					dir = DIRECTION::BAS;
				// Le laser est place sur le mur d'en bas donc on part vers le haut
				if (i == d_terrain.size() - 1)
					dir = DIRECTION::HAUT;

				l = new laser{ p1,p2,OBJET::LASER, dir };
				break;
			}
		}
		if (l != nullptr) break;
	}
	return l;
}

cible* terrain::trouveCible() const {
	cible* c = nullptr;
	for (int i = 0; i < d_terrain.size(); ++i) {
		for (int j = 0; j < d_terrain[i].size(); ++j) {
			if (d_terrain[i][j]->getType() == OBJET::CIBLE) {
				geom::point p1{
				    static_cast<double>(i*TAILLECASE),
				    static_cast<double>(j*TAILLECASE)
                },
				p2{
				    static_cast<double>((i+1)*TAILLECASE),
				    static_cast<double>((j+1)*TAILLECASE)
                };
				c = new cible{ p1,p2,OBJET::CIBLE };
				break;
			}
		}
		if (c != nullptr) break;
	}
	return c;
}

bool terrain::estGagne() {
	if (d_cible->estTouche()) {
		return true;
	}
	else {
		return false;
	}
}

void terrain::propageLaser() {
	bool stop = false;
	d_cible = trouveCible();
	d_laser = trouveLaser();
	int positionHorizontale = (d_laser->getP1().x())/TAILLECASE;
	int positionVerticale = (d_laser->getP1().y())/TAILLECASE;

	while (!stop) {

		switch (d_laser->getDirection()) {
		case DIRECTION::DROITE:
			positionVerticale++;
			break;
		case DIRECTION::GAUCHE:
			positionVerticale--;
			break;
		case DIRECTION::HAUT:
			positionHorizontale--;
			break;
		case DIRECTION::BAS:
			positionHorizontale++;
			break;
		}

		// Si cible
		if (d_terrain[positionHorizontale][positionVerticale]->getType() == OBJET::CIBLE) {
			d_cible->setTouche(true);
			stop = true;
			break;
		}

		// Si vide
		if (d_terrain[positionHorizontale][positionVerticale]->getType() == OBJET::VIDE) {

            geom::point p1{
                static_cast<double>(positionHorizontale*TAILLECASE),
                static_cast<double>(positionVerticale*TAILLECASE)
            },
            p2{
                static_cast<double>((positionHorizontale+1)*TAILLECASE),
                static_cast<double>((positionVerticale+1)*TAILLECASE)
            };

			rayon r{ p1, p2, OBJET::RAYON };
			insertCase(
				positionHorizontale,
				positionVerticale,
				make_unique<rayon>(
					r.getP1(),
					r.getP2(),
					r.getType()
					)
			);
		}

		// Si mur
		if (d_terrain[positionHorizontale][positionVerticale]->getType() == OBJET::MUR) {
			stop = true;
		}

		// Si miroir "/"
		if (d_terrain[positionHorizontale][positionVerticale]->getType() == OBJET::MIROIR_SLASH) {
			switch (d_laser->getDirection()) {
			case DIRECTION::DROITE:
				d_laser->setDirection(DIRECTION::HAUT);
				break;
			case DIRECTION::BAS:
				d_laser->setDirection(DIRECTION::GAUCHE);
				break;
			case DIRECTION::GAUCHE:
				d_laser->setDirection(DIRECTION::BAS);
				break;
			case DIRECTION::HAUT:
				d_laser->setDirection(DIRECTION::DROITE);
				break;
			}
		}

		// Si miroir "\"
		if (d_terrain[positionHorizontale][positionVerticale]->getType() == OBJET::MIROIR_BACKSLASH) {
			switch (d_laser->getDirection()) {
			case DIRECTION::DROITE:
				d_laser->setDirection(DIRECTION::BAS);
				break;
			case DIRECTION::BAS:
				d_laser->setDirection(DIRECTION::DROITE);
				break;
			case DIRECTION::GAUCHE:
				d_laser->setDirection(DIRECTION::HAUT);
				break;
			case DIRECTION::HAUT:
				d_laser->setDirection(DIRECTION::GAUCHE);
				break;
			}
		}
	}
}
