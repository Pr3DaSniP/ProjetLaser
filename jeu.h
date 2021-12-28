#ifndef JEU_H
#define JEU_H

#include <memory>
#include "type.h"
#include "terrain.h"
#include "miroir.h"

using std::make_unique;
using std::unique_ptr;

using namespace TYPE;

/* à remplacer par un afficheur */
#include <iostream>
#include "afficheur.h"

class jeu {
public:
	jeu(terrain& terrain, afficheur& aff);

	void exec();
private:
	terrain* d_terrain;

	/* à rajouter */
	afficheur* d_afficheur;
};

#endif // !JEU_H