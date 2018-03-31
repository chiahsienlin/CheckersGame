#ifndef AI_PLAYER_H
#define AI_PLAYER_H
#include "tile.h"
using namespace std;


class AI_player
{
private:
    vector<vector<int>> st;
public:
    AI_player();
    void updateState(Tile* state[6][6]);
    vector<vector<int>> getState();
    void printState();
    //Alpha_Beta_Search(Tile* state);
    //int Max_Player(Tile* state, int alpha, int beta);
    //int Min_Player(Tile* state, int alpha, int beta);
    //vector<int> Actions(Tile* state);
    //int Utility(Tile* state);
    //bool Is_Terminal_State(Tile* state);
    //Tile* Result(Tile* state, vector<int> action);
};

#endif // AI_PLAYER_H
