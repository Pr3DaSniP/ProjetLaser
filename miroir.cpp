#include"miroir.h"
#include<iostream>

miroir::miroir(const geom::point& pDepart , const geom::point& pArrivee): d_depart{pDepart}, d_arrivee{pArrivee}, d_inclinaison{false}
{}

        ///@return un char qui représente l'inclinaison du miroir 'g' ou 'd'
bool miroir::inclinaison() const
{
    return d_inclinaison;
}

        ///@return un point qui représente le premier du segment
geom::point miroir::depart() const
{
    return d_depart;
}
        ///@return un point qui représente le deuxième point du segment
geom::point miroir::arrivee() const
{
    return d_arrivee;
}

         /// Incline un miroir à gauche "\"
void miroir::inclineG()
{
    d_inclinaison=false;
}

        /// Incline un miroir à droit "/"
void miroir::inclineD()
{
    d_inclinaison=false;
}
