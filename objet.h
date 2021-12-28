#ifndef OBJET_H
#define OBJET_H

#include "point.h"

class objet {
public:
	objet(const geom::point& p1, const geom::point& p2, int type);
	geom::point getP1() const;
	geom::point getP2() const;
	int getType() const;
	void setP1(const geom::point& p);
	void setP2(const geom::point& p);
	void settype(int type);
	virtual ~objet() = default;

private:
	int d_type;
	geom::point d_p1, d_p2;
};


#endif // !OBJET_H
