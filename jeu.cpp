#include "jeu.h"

jeu::jeu(terrain& terrain, afficheur& aff)
	: d_terrain{ &terrain }, d_afficheur{ &aff }
{}

void jeu::exec() {
    int tailleCase = terrain::TAILLECASE;
	d_afficheur->afficheTerrain(*d_terrain);

	bool encore = true;
	int choix, x, y, type, stop;
	std::cout << "Il faut maintenant placer des miroirs\n";
	while (encore) {
        std::cout << "(1) Ajouter un miroir\n(2) Supprimer un miroir\n"; std::cin >> choix;
        if(choix == 1) {
            std::cout << "Coordonnees du miroir : "; std::cin >> x >> y;
            std::cout << "Type du miroir (0=/,1=\\): "; std::cin >> type;
            geom::point
            p1{
                static_cast<double>(x*tailleCase),
                static_cast<double>(y*tailleCase)
            },
            p2{
                static_cast<double>((x+1)*tailleCase),
                static_cast<double>((y+1)*tailleCase)
            };
            if (type == 1) {
                d_terrain->insertCase(x, y, make_unique<miroir>(p1, p2, OBJET::MIROIR_BACKSLASH));
            }
            else if (type == 0) {
                d_terrain->insertCase(x, y, make_unique<miroir>(p1, p2, OBJET::MIROIR_SLASH));
            }
        }
        else if(choix == 2) {
            std::cout << "Coordonnees du miroir a supprimer : "; std::cin >> x >> y;
            geom::point
            p1{
                static_cast<double>(x*tailleCase),
                static_cast<double>(y*tailleCase)
            },
            p2{
                static_cast<double>((x+1)*tailleCase),
                static_cast<double>((y+1)*tailleCase)
            };
            if (d_terrain->getObjet(x,y)->getType() == OBJET::MIROIR_SLASH || d_terrain->getObjet(x,y)->getType() == OBJET::MIROIR_BACKSLASH) {
                d_terrain->insertCase(x, y, make_unique<vide>(p1, p2, OBJET::VIDE));
            }
        }
		d_afficheur->afficheTerrain(*d_terrain);
		std::cout << "Stop (0=oui,1=non) ? \n"; std::cin >> stop;
		if (stop == 0) encore = false; else encore = true;
	}

	d_terrain->propageLaser();
	bool win = d_terrain->estGagne();
	d_afficheur->afficheTerrain(*d_terrain);
	d_afficheur->afficheResultat(win);
}
