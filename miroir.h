#ifndef MIROIR_H
#define MIROIR_H

#include "objet.h"

class miroir : public objet {
public:
	miroir(const geom::point& p1, const geom::point& p2, int type);
	virtual ~miroir() = default;
};

#endif // !MIROIR_H
