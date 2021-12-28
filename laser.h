#ifndef LASER_H
#define LASER_H

#include "objet.h"

class laser : public objet {
public:
	laser(const geom::point& p1, const geom::point& p2, int type, int direction);
	int getDirection() const;
	void setDirection(int direction);
	virtual ~laser() = default;
private:
	int d_direction;
};

#endif // !LASER_H