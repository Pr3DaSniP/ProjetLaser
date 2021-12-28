#include "vide.h"

vide::vide(const geom::point& p1, const geom::point& p2, int type, bool estTraverse)
	: objet{ p1,p2,type }, d_estTraverse{ estTraverse } 
{}

bool vide::estTraverse() const { 
	return d_estTraverse;
}

void vide::setTraverse(bool estTraverse) { 
	d_estTraverse = estTraverse; 
}