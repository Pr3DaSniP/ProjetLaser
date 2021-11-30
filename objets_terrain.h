#ifndef OBJETS_TERRAIN_H
#define OBJETS_TERRAIN_H

class objets_terrain {
public:
    objets_terrain(double x, double y);
    virtual ~objets_terrain() = default;
    virtual void affiche() const = 0;
    double x() const;
    double y() const;
private:
    double d_x, d_y;
};

#endif // OBJETS_TERRAIN_H