#include "mur.h"

mur::mur(const geom::point& p1, const geom::point& p2, int type, bool touche)
	: objet{ p1,p2,type }, d_estTouche{ touche } 
{}

bool mur::estTouche() const { 
	return d_estTouche; 
}

void mur::setTouche(bool touche) { 
	d_estTouche = touche; 
}