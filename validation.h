#ifndef VALIDATION_H
#define VALIDATION_H
#include "tile.h"

extern Tile *tile[6][6];
//extern int exp[60], max;
extern std::vector<int> eat;
extern std::vector<int> exp;

class validation
{
    int flag,retVal;

public:
    validation();
    int chooser(Tile *temp);
    int validatePawn(Tile *temp);
    void orange();
    int check(Tile *temp);
};

#endif // VALIDATION_H
