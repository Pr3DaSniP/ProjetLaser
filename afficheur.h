#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include "terrain.h"

class afficheur {
public:
	virtual void afficheTerrain(const terrain& t) const = 0;
	virtual void afficheResultat(bool result) const = 0;
	virtual ~afficheur() = default;
};

#endif // AFFICHEUR_H