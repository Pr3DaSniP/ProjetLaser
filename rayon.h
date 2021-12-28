#ifndef RAYON_H
#define RAYON_H

#include "objet.h"

class rayon : public objet {
public:
	rayon(const geom::point& p1, const geom::point& p2, int type);
	virtual ~rayon() = default;
};

#endif // !RAYON_H