#ifndef MURS_H
#define MURS_H

#include "objets_terrain.h";

class murs : public objets_terrain {
private:
    std::string d_representation;
public:
    murs(double x, double y, const std::string& representation);
    virtual ~murs() = default;
    virtual void affiche() const override;
    std::string representation() const;
};

#endif // MURS_H