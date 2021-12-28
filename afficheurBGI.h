#ifndef AFFICHEURBGI_H
#define AFFICHEURBGI_H

#include "graphics.h"
#include "afficheur.h"

class afficheurBGI : public afficheur {
public:
	virtual void afficheTerrain(const terrain& t) const override;
	virtual void afficheResultat(bool result) const override;

	void afficheContour(int x1, int y1, int x2, int y2) const;
	void afficheVide(int x1, int y1, int x2, int y2) const;
	void afficheMur(int x1, int y1, int x2, int y2) const;
	void afficheMiroirSlash(int x1, int y1, int x2, int y2) const;
	void afficheMiroirBackSlash(int x1, int y1, int x2, int y2) const;
	void afficheLaser(int x1, int y1, int x2, int y2) const;
	void afficheCible(int x1, int y1, int x2, int y2) const;
	void afficheRayon(int x1, int y1, int x2, int y2) const;
	void afficheTexte(int x, int y, const char* numero) const;

	virtual ~afficheurBGI() = default;
};

#endif // !AFFICHEURBGI_H
