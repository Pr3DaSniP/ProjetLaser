#ifndef MIROIR_H
#define MIROIR_H
#include "point.h"

class miroir
{
    public:
        /**
          Constructeur de miroir, cree un miroir à partir des deux points x et y (pDepart,pArrivee) qui est un segment tracer vec la fct line du winbgi
          @param geom::point premier point du segment
          @param geom::point deuxième point du segment
        */
        miroir(const geom::point& pDepart , const geom::point& pArrivee);

        ///@return un char qui représente l'inclinaison du miroir 'g' ou 'd'
        bool inclinaison() const;

        ///@return un point qui représente le premier du segment
        geom::point depart() const;
        ///@return un point qui représente le deuxième point du segment
        geom::point arrivee() const;

         /// Incline un miroir à gauche "\"
        void inclineG();

        /// Incline un miroir à droit "/"
        void inclineD();

    protected:

    private:
        bool d_inclinaison;
        geom::point d_depart;
        geom::point d_arrivee;
};

#endif // MIROIR_H

