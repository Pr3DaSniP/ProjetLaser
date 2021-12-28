#ifndef AFFICHEURTXT_H
#define AFFICHEURTXT_H

#include <iostream>
#include "afficheur.h"

class afficheurTxt : public afficheur {
public:
	virtual void afficheTerrain(const terrain& t) const override;
	virtual void afficheResultat(bool result) const override;
	virtual ~afficheurTxt() = default;
};

#endif // !AFFICHEURTXT_H
