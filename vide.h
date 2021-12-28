#ifndef VIDE_H
#define VIDE_H

#include "objet.h"

class vide : public objet {
public:
	vide(const geom::point& p1, const geom::point& p2, int type, bool estTraverse = false);
	bool estTraverse() const;
	void setTraverse(bool estTraverse);
	virtual ~vide() = default;
private:
	bool d_estTraverse;
};

#endif // !VIDE_H
