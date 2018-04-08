#ifndef VALIDATION_H
#define VALIDATION_H
#include "tile.h"
#include <unordered_set>

extern Tile *tile[6][6];
extern std::vector<int> eat;
extern std::vector<int> valid_mv;


class validation{
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

/* [Description]
 *
 *  validation::validation(): The constructor.
 *  validation::chooser(): Choose which tile is valid to move.
 *  validation::valiateMoves(): Move to the valid tiles.
 *  validation::orange(): Mark the pressed tile to orange.
 *  validation::check(): Renew the retVal flag to 0.
 *  validation::CreateState(): Given the 2D array of Tiles class pointers, transform to the binary 2D vetor stored in State.
 *  validation::CreateValidCheckersSet(): Check if there is force-to-jump steps and add it to the valid set.
 *
 */
