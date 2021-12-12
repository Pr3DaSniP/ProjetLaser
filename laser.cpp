#include"laser.h"

laser::laser(const geom::point& p1, const geom::point& p2,bool isHorizontal): laser{p1, p2}, d_isHorizontal{isHorizontal}
{}

        ///@return un point qui représente le premier du segment
geom::point laser::pHautGauche() const
{
    return d_pointHautGauche;
}
        ///@return un point qui représente le deuxième point du segment
geom::point laser::pBasDroit() const
{
    return d_pointBasDroit;
}
         ///@return un  boolean indiquant si oui ou non le canon est horizontal ou vertical
bool laser::isHorizontal() const
{
    return d_isHorizontal;
}
        // Permet de mettre la valeur du booléen isHorizontal de la classe laser à l'horizontal
void laser::setHorizontal()
{
    d_isHorizontal= true;
}

void laser::setVertical()
{
    d_isHorizontal=false;
}
