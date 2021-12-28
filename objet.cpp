#include "objet.h"

objet::objet(const geom::point& p1, const geom::point& p2, int type)
	: d_p1{ p1 }, d_p2{ p2 }, d_type{ type }
{}

geom::point objet::getP1() const {
	return d_p1;
}

void objet::setP1(const geom::point& p){
        d_p1.moveTo(p.x(), p.y());
}

geom::point objet::getP2() const {
	return d_p2;
}

void objet::setP2(const geom::point& p){
        d_p2.moveTo(p.x(), p.y());
}

int objet::getType() const {
	return d_type;
}

void objet::setType(int type){
        d_type= type;
}
