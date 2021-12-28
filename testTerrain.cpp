#include "doctest.h"
#include "terrain.h"
#include "type.h"

#include <iostream>
#include <fstream>

using namespace TYPE;

TEST_CASE("Inserer un objet fonctionne correctement")
{
    terrain t{10,10};

    SUBCASE("Inserer un mur fonctionne correctement")
    {
        mur m{ {0,0}, {terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::MUR, false };

        t.insertCase(
                     0,0,
                     std::make_unique<mur>(
                            m.getP1(),
                            m.getP2(),
                            m.getType()
                     )
        );

        REQUIRE_EQ(t.getObjet(0,0)->getType(), OBJET::MUR);
    }

    SUBCASE("Inserer du vide fonctionne correctement")
    {
        vide v{ {0,0}, {terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::VIDE };

        t.insertCase(
                     0,0,
                     std::make_unique<vide>(
                            v.getP1(),
                            v.getP2(),
                            v.getType()
                     )
        );

        REQUIRE_EQ(t.getObjet(0,0)->getType(), OBJET::VIDE);
    }

    SUBCASE("Inserer un laser fonctionne correctement")
    {
        laser l{ {0,0}, {terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::LASER, DIRECTION::DROITE };

        t.insertCase(
                     0,0,
                     std::make_unique<laser>(
                            l.getP1(),
                            l.getP2(),
                            l.getType(),
                            l.getDirection()
                     )
        );

        REQUIRE_EQ(t.getObjet(0,0)->getType(), OBJET::LASER);
    }

    SUBCASE("Inserer une cible fonctionne correctement")
    {
        cible c{ {0,0}, {terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::CIBLE };

        t.insertCase(
                     0,0,
                     std::make_unique<cible>(
                            c.getP1(),
                            c.getP2(),
                            c.getType()
                     )
        );

        REQUIRE_EQ(t.getObjet(0,0)->getType(), OBJET::CIBLE);
    }

    SUBCASE("Inserer un miroir fonctionne correctement")
    {
        SUBCASE("Inserer un miroir '/' fonctionne correctement") {
            miroir m{ {0,0}, {terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::MIROIR_SLASH, INCLINAISON::SLASH};

            t.insertCase(
                         0,0,
                         std::make_unique<miroir>(
                                m.getP1(),
                                m.getP2(),
                                m.getType(),
                                m.inclinaison()
                         )
            );

            REQUIRE_EQ(t.getObjet(0,0)->getType(), OBJET::MIROIR_SLASH);
        }
        SUBCASE("Inserer un miroir '\' fonctionne correctement") {
            miroir m{ {0,0}, {terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::MIROIR_BACKSLASH, INCLINAISON::BACKSLASH};

            t.insertCase(
                         0,0,
                         std::make_unique<miroir>(
                                m.getP1(),
                                m.getP2(),
                                m.getType(),
                                m.inclinaison()
                         )
            );

            REQUIRE_EQ(t.getObjet(0,0)->getType(), OBJET::MIROIR_BACKSLASH);
        }
    }

    SUBCASE("Inserer un rayon fonctionne correctement")
    {
        rayon r{ {0,0}, {terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::RAYON };

        t.insertCase(
                     0,0,
                     std::make_unique<rayon>(
                            r.getP1(),
                            r.getP2(),
                            r.getType()
                     )
        );

        REQUIRE_EQ(t.getObjet(0,0)->getType(), OBJET::RAYON);
    }
}

TEST_CASE("La recuperation d'un objet fonctionne correctement")
{
    terrain t{7,1};

    // Coordonnées
    // P1 ---- P2
    // Si terrain::TAILLECASE = 50
    // 0,0 ---- 50,50
    mur m{ {0,0}, {terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::MUR, false };
    t.insertCase(0,0,std::make_unique<mur>(m.getP1(),m.getP2(),m.getType()));

    // 50,0 ---- 100,50
    vide v{ {terrain::TAILLECASE,0}, {2*terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::VIDE };
    t.insertCase(1,0,std::make_unique<vide>(v.getP1(),v.getP2(),v.getType()));

    // 100,0 ---- 150,50
    laser l{ {2*terrain::TAILLECASE,0}, {3*terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::LASER, DIRECTION::DROITE };
    t.insertCase(2,0, std::make_unique<laser>(l.getP1(),l.getP2(),l.getType(),l.getDirection()));

    // 150,0 ---- 200,50
    cible c{ {3*terrain::TAILLECASE,0}, {4*terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::CIBLE };
    t.insertCase(3,0,std::make_unique<cible>(c.getP1(),c.getP2(),c.getType()));

    // 200,0 ---- 250,50
    miroir m2{ {4*terrain::TAILLECASE,0}, {5*terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::MIROIR_SLASH, INCLINAISON::SLASH};
    t.insertCase(4,0,std::make_unique<miroir>(m2.getP1(),m2.getP2(),m2.getType(), m2.inclinaison()));

    // 250,0 ---- 300,50
    miroir m3{ {5*terrain::TAILLECASE,0}, {6*terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::MIROIR_BACKSLASH, INCLINAISON::BACKSLASH};
    t.insertCase(5,0,std::make_unique<miroir>(m3.getP1(),m3.getP2(),m3.getType(),m3.inclinaison()));

    // 300,0 ---- 350,50
    rayon r{ {6*terrain::TAILLECASE,0}, {7*terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::RAYON };
    t.insertCase(6,0,std::make_unique<rayon>(r.getP1(),r.getP2(),r.getType()));

    SUBCASE("La recuperation du mur fonctionne correctement")
    {
        REQUIRE_EQ(t.getObjet(0,0)->getType(), OBJET::MUR);
    }

    SUBCASE("La recuperation du vide fonctionne correctement")
    {
        REQUIRE_EQ(t.getObjet(1,0)->getType(), OBJET::VIDE);
    }

    SUBCASE("La recuperation du laser fonctionne correctement")
    {
        REQUIRE_EQ(t.getObjet(2,0)->getType(), OBJET::LASER);
    }

    SUBCASE("La recuperation de la cible fonctionne correctement")
    {
        REQUIRE_EQ(t.getObjet(3,0)->getType(), OBJET::CIBLE);
    }

    SUBCASE("La recuperation du miroir '/' fonctionne correctement")
    {
        REQUIRE_EQ(t.getObjet(4,0)->getType(), OBJET::MIROIR_SLASH);
    }

    SUBCASE("La recuperation du miroir '\' fonctionne correctement")
    {
        REQUIRE_EQ(t.getObjet(5,0)->getType(), OBJET::MIROIR_BACKSLASH);
    }

    SUBCASE("La recuperation du rayon fonctionne correctement")
    {
        REQUIRE_EQ(t.getObjet(6,0)->getType(), OBJET::RAYON);
    }

    SUBCASE("La recuperation de tous les objets sous forme de tableau fonctionne correctement")
    {
        auto objets = t.getObjets();
        SUBCASE("La recuperation du mur dans le tableau fonctionne correctement")
        {
            REQUIRE_EQ(objets[0][0]->getType(), OBJET::MUR);
        }
        SUBCASE("La recuperation du vide dans le tableau fonctionne correctement")
        {
            REQUIRE_EQ(objets[1][0]->getType(), OBJET::VIDE);
        }

        SUBCASE("La recuperation du laser dans le tableau fonctionne correctement")
        {
            REQUIRE_EQ(objets[2][0]->getType(), OBJET::LASER);
        }

        SUBCASE("La recuperation de la cible dans le tableau fonctionne correctement")
        {
            REQUIRE_EQ(objets[3][0]->getType(), OBJET::CIBLE);
        }

        SUBCASE("La recuperation du miroir '/' dans le tableau fonctionne correctement")
        {
            REQUIRE_EQ(objets[4][0]->getType(), OBJET::MIROIR_SLASH);
        }

        SUBCASE("La recuperation du miroir '\' dans le tableau fonctionne correctement")
        {
            REQUIRE_EQ(objets[5][0]->getType(), OBJET::MIROIR_BACKSLASH);
        }

        SUBCASE("La recuperation du rayon dans le tableau fonctionne correctement")
        {
            REQUIRE_EQ(objets[6][0]->getType(), OBJET::RAYON);
        }
    }
}

TEST_CASE("La creation du terrain en format texte fonctionne correctement")
{

    terrain t = terrain::terrainBase(10,10);

    // 250,0 ---- 300,50
    laser l{ {5*terrain::TAILLECASE,0}, {6*terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::LASER, DIRECTION::DROITE };
    t.insertCase(5,0, std::make_unique<laser>(l.getP1(),l.getP2(),l.getType(),l.getDirection()));

    // 300,0 ---- 350,50
    cible c{ {6*terrain::TAILLECASE,0}, {7*terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::CIBLE };
    t.insertCase(6,0,std::make_unique<cible>(c.getP1(),c.getP2(),c.getType()));

    // 350,0 ---- 400,50
    rayon r{ {7*terrain::TAILLECASE,0}, {8*terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::RAYON };
    t.insertCase(7,0,std::make_unique<rayon>(r.getP1(),r.getP2(),r.getType()));

    auto txt = t.terrainTxt();

    REQUIRE_EQ(txt.size(), 10);
    for(int i = 0; i < txt.size(); ++i)
       REQUIRE_EQ(txt[i].size(), 10);

    SUBCASE("Le coin superieur gauche est un mur avec comme format texte 'X'")
    {
        REQUIRE_EQ(txt[0][0], "X");
    }
    SUBCASE("Le milieu est du avec comme format texte ' '")
    {
        REQUIRE_EQ(txt[5][5], " ");
    }
    SUBCASE("La case [5][0] est un laser au format texte '='")
    {
        REQUIRE_EQ(txt[5][0], "=");
    }
    SUBCASE("La case [6][0] est une cible au format texte '@'")
    {
        REQUIRE_EQ(txt[6][0], "@");
    }
    SUBCASE("La case [7][0] est un rayon au format texte '-'")
    {
        REQUIRE_EQ(txt[7][0], "-");
    }
}

TEST_CASE("Les fonctions pour le bon deroulement du jeu fonctionnent correctement")
{
    /*
    *   [X][X][@][X][X]
    *   [X][ ][ ][ ][X]
    *   [=][ ][/][ ][X]
    *   [X][ ][ ][ ][X]
    *   [X][X][X][X][X]
    */
    terrain t = terrain::terrainBase(5,5);

    laser l{ {2*terrain::TAILLECASE,0}, {3*terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::LASER, DIRECTION::DROITE };
    t.insertCase(2,0, std::make_unique<laser>(l.getP1(),l.getP2(),l.getType(),l.getDirection()));

    SUBCASE("Trouver le laser fonctionne correctement")
    {
        auto l = t.trouveLaser();
        REQUIRE_EQ(l->getType(), OBJET::LASER);
    }

    cible c{ {0,2*terrain::TAILLECASE}, {0, 3*terrain::TAILLECASE}, OBJET::CIBLE };
    t.insertCase(0,2,std::make_unique<cible>(c.getP1(),c.getP2(),c.getType()));

    SUBCASE("Trouver la cible fonctionne correctement")
    {
        auto c = t.trouveCible();
        REQUIRE_EQ(c->getType(), OBJET::CIBLE);
    }

    miroir m{ {2*terrain::TAILLECASE, 2*terrain::TAILLECASE}, {3*terrain::TAILLECASE, 3*terrain::TAILLECASE}, OBJET::MIROIR_SLASH, INCLINAISON::SLASH};
    t.insertCase(2,2,std::make_unique<miroir>(m.getP1(),m.getP2(),m.getType(), m.inclinaison()));

    SUBCASE("La propagation du laser se deroule proprement")
    {
        /*
        *   [X][X][@][X][X]
        *   [X][ ][-][ ][X]
        *   [=][-][/][ ][X]
        *   [X][ ][ ][ ][X]
        *   [X][X][X][X][X]
        */
        t.propageLaser();
        REQUIRE_EQ(t.getObjet(2,1)->getType(), OBJET::RAYON);
        REQUIRE_EQ(t.getObjet(1,2)->getType(), OBJET::RAYON);
    }

    SUBCASE("La verification de la victoire fonctionne correctement")
    {
        t.propageLaser();
        bool win = t.estGagne();
        REQUIRE_EQ(win, true);
    }
}

TEST_CASE("Le terrain au format JSON se genere correctement")
{
    /*
    *   [X][X][@][X][X]
    *   [X][ ][ ][ ][X]
    *   [=][ ][ ][ ][X]
    *   [X][ ][ ][ ][X]
    *   [X][X][X][X][X]
    *
    *   {
    *       "NbColonnes":5,
    *       "NbLignes":5,
    *       "Terrain":[
    *           ["X","X","@","X","X"],
    *           ["X"," "," "," ","X"],
    *           ["="," "," "," ","X"],
    *           ["X"," "," "," ","X"],
    *           ["X","X","X","X","X"]
    *       ]
    *   }
    *
    */
    terrain t = terrain::terrainBase(5,5);

    laser l{ {2*terrain::TAILLECASE,0}, {3*terrain::TAILLECASE, terrain::TAILLECASE}, OBJET::LASER, DIRECTION::DROITE };
    t.insertCase(2,0, std::make_unique<laser>(l.getP1(),l.getP2(),l.getType(),l.getDirection()));
    cible c{ {0,2*terrain::TAILLECASE}, {0, 3*terrain::TAILLECASE}, OBJET::CIBLE };
    t.insertCase(0,2,std::make_unique<cible>(c.getP1(),c.getP2(),c.getType()));

    string attendu = string("") + "{\"NbColonnes\":5,\"NbLignes\":5,\"Terrain\":[[\"X\",\"X\",\"@\",\"X\",\"X\"],[\"X\",\" \",\" \",\" \",\"X\"],[\"=\",\" \",\" \",\" \",\"X\"],[\"X\",\" \",\" \",\" \",\"X\"],[\"X\",\"X\",\"X\",\"X\",\"X\"]]}";
    auto json = t.creerTerrainJSON();

    REQUIRE_EQ(json.dump(-1), attendu);
}
