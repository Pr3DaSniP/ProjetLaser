#include "afficheurBGI.h"
#include "type.h"
using namespace TYPE;

void afficheurBGI::afficheTerrain(const terrain& t) const {
    int decalage = 100;

    auto tmp = t.getObjets();
    for(int i = 0; i < tmp.size(); ++i) {
        std::string s = std::to_string(i);
        afficheTexte(
                        decalage/2,
                        (i+1)*terrain::TAILLECASE+decalage,
                        s.c_str()
        );

        for(int j = 0; j < tmp[i].size(); ++j) {

            /*
            std::string s = std::to_string(k++);
            if(j == 0) {
                afficheTexte(
                        (i+1)*terrain::TAILLECASE+decalage,
                        decalage/2,
                        s.c_str()
                );
            }
            */

            int type = tmp[i][j]->getType();
            int x1 = tmp[i][j]->getP1().x() + decalage,
                y1 = tmp[i][j]->getP1().y() + decalage,
                x2 = tmp[i][j]->getP2().x() + decalage,
                y2 = tmp[i][j]->getP2().y() + decalage;
            switch(type)
            {
            case OBJET::MUR:
                afficheMur(y1,x1,y2,x2);
                break;
            case OBJET::VIDE:
                afficheVide(y1,x1,y2,x2);
                break;
            case OBJET::LASER:
                afficheLaser(y1,x1,y2,x2);
                break;
            case OBJET::CIBLE:
                afficheCible(y1,x1,y2,x2);
                break;
            case OBJET::MIROIR_SLASH:
                afficheMiroirSlash(y1,x1,y2,x2);
                break;
            case OBJET::MIROIR_BACKSLASH:
                afficheMiroirBackSlash(y1,x1,y2,x2);
                break;
            case OBJET::RAYON:
                afficheRayon(y1,x1,y2,x2);
                break;
            }
        }
    }
}

void afficheurBGI::afficheResultat(bool result) const {
    result == true ? afficheTexte(500,500,"Vous avez gagné ! :D") : afficheTexte(500,500,"Vous avez perdu ! D:");
    getch();
}

void afficheurBGI::afficheContour(int x1, int y1, int x2, int y2) const {
    setcolor(WHITE);
    rectangle(x1,y1,x2,y2);
}

void afficheurBGI::afficheVide(int x1, int y1, int x2, int y2) const {
    setcolor(BLACK);
    bar(x1,y1,x2,y2);

    // Pour bien voir les delimitations du terrain, pas obligatoire mais moche apres
    afficheContour(x1,y1,x2,y2);
}

void afficheurBGI::afficheMur(int x1, int y1, int x2, int y2) const {
    setcolor(DARKGRAY);
    bar(x1,y1,x2,y2);

    // Pour bien voir les delimitations du terrain, pas obligatoire mais moche apres
    afficheContour(x1,y1,x2,y2);
}

void afficheurBGI::afficheMiroirSlash(int x1, int y1, int x2, int y2) const {
    setcolor(MAGENTA);
    rectangle(x1,y1,x2,y2);
    line(x2,y1,x1, y2);

    // Pour bien voir les delimitations du terrain, pas obligatoire mais moche apres
    afficheContour(x1,y1,x2,y2);
}

void afficheurBGI::afficheMiroirBackSlash(int x1, int y1, int x2, int y2) const {
    setcolor(GREEN);
    rectangle(x1,y1,x2,y2);
    line(x1,y1,x2,y2);

    // Pour bien voir les delimitations du terrain, pas obligatoire mais moche apres
    afficheContour(x1,y1,x2,y2);
}

void afficheurBGI::afficheLaser(int x1, int y1, int x2, int y2) const {
    setcolor(YELLOW);
    rectangle(x1,y1,x2,y2);
    line(x1,y1,x2,y2);
    rectangle(x1,y1,x2,y2);
    line(x2,y1,x1, y2);

    // Pour bien voir les delimitations du terrain, pas obligatoire mais moche apres
    afficheContour(x1,y1,x2,y2);
}

void afficheurBGI::afficheCible(int x1, int y1, int x2, int y2) const {
    setcolor(WHITE);
    rectangle(x1,y1,x2,y2);
    setcolor(RED);
    circle(((x1+x2)/2)+1,((y1+y2)/2)+1,terrain::TAILLECASE/2);
    setcolor(WHITE);
    circle(((x1+x2)/2)+1,((y1+y2)/2)+1,terrain::TAILLECASE/4);

    // Pour bien voir les delimitations du terrain, pas obligatoire mais moche apres
    afficheContour(x1,y1,x2,y2);
}

void afficheurBGI::afficheRayon(int x1, int y1, int x2, int y2) const {
    setcolor(RED);
    circle((x1+x2)/2,(y1+y2)/2,8);

    // Pour bien voir les delimitations du terrain, pas obligatoire mais moche apres
    afficheContour(x1,y1,x2,y2);
}

void afficheurBGI::afficheTexte(int x, int y, const char* numero) const {
    settextjustify(RIGHT_TEXT,CENTER_TEXT);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,terrain::TAILLECASE/9);
    outtextxy(x, y, numero);
}
