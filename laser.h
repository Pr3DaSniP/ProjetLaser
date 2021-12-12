#ifndef LASER_H
#define LASER_H

#include "point.h"
#include "caselaser.h"
class laser: public caseLaser
{
    public:

laser(const geom::point& p1, const geom::point& p2,bool isHorizontal);

    ///@return un point qui représente le premier du segment
        geom::point pHautGauche() const;
        ///@return un point qui représente le deuxième point du segment
        geom::point pBasDroit() const;
         ///@return un  boolean indiquant si oui ou non le canon est horizontal ou vertical
        bool isHorizontal() const;
        // Permet de modifier la valeur du booléen isHorizontal de la classe laser
        void setHorizontal();

        void setVertical();

    private:
        geom::point d_pointHautGauche;
        geom::point d_pointBasDroit;
        bool d_isHorizontal;
};

#endif // LASER_H

