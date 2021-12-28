#include "laser.h"

laser::laser(const geom::point& p1, const geom::point& p2, int type, int direction)
	: objet{ p1,p2,type }, d_direction{ direction } 
{}

int laser::getDirection() const { 
	return d_direction; 
}

void laser::setDirection(int direction) { 
	d_direction = direction; 
}