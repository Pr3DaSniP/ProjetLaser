#ifndef CIBLE_H
#define CIBLE_H

#include "objet.h"
#include<vector>

class cible : public objet {
public:
	cible(const geom::point& p1, const geom::point& p2, int type, bool touche = false);
	bool estTouche() const;
	void setTouche(bool touche);
	virtual ~cible() = default;

private:
	bool d_estTouche;
};

#endif // !CIBLE_H
