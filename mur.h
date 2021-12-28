#ifndef MUR_H
#define MUR_H

#include "objet.h"

class mur : public objet {
public:
	mur(const geom::point& p1, const geom::point& p2, int type, bool touche = false);
	bool estTouche() const;
	void setTouche(bool touche);
	virtual ~mur() = default;
private:
	bool d_estTouche;
};

#endif // !MUR_H