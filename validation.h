#ifndef VALIDATION_H
#define VALIDATION_H
#include "tile.h"
#include <unordered_set>

extern Tile *tile[6][6];
extern std::vector<int> eat;
extern std::vector<int> valid_mv;

class validation
{
    int flag,retVal;
    std::unordered_set<int> v_checks;
    std::vector<std::vector<int>> State;

public:
    validation();
    int chooser(Tile *temp);
    int valiateMoves(Tile *temp);
    void orange();
    int check(Tile *temp);
    void CreateState(Tile* tile[6][6]);
    void CreateValidCheckersSet();
};
extern validation *valid;
#endif // VALIDATION_H
