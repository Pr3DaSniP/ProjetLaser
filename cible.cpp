#include "cible.h"
#include "objet.h"
#include<iostream>

cible::cible(const geom::point& p1, const geom::point& p2, int type, bool touche)
	: objet{ p1,p2,type }, d_estTouche{ touche }
{}

bool cible::estTouche() const {
	return d_estTouche;
}

void cible::setTouche(bool touche) {
	d_estTouche = touche;
}

