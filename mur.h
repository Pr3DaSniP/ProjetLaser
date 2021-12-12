#ifndef MUR_H
#define MUR_H
#include "point.h"

class mur
{
    public:

        mur(const geom::point& droite, const geom::point& gauche, const geom::point& haut, const geom::point& bas);
        geom::point droite() const;
        geom::point gauche() const;
        geom::point haut() const;
        geom::point bas() const;

     private:
        geom::point d_gauche ;
        geom::point d_droite;
        geom::point d_haut ;
        geom::point d_bas;
};


#endif // MUR_H
