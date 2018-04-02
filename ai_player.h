#ifndef AI_PLAYER_H
#define AI_PLAYER_H
#include "tile.h"
using namespace std;

class AI_player
{
private:
    pair<pair<int,int>, pair<char, pair<int, int>>> BestAction;
    vector<vector<int>> State;
public:
    AI_player();
    void Createstate(Tile* tile[6][6]);
    vector<vector<int>> UpdateState(vector<vector<int>> state, pair<pair<int,int>, pair<char, pair<int, int>>> action);
    vector<vector<int>> getState();
    void printState(vector<vector<int>> state);
    bool Is_Terminal_State(vector<vector<int>> state);
    vector<pair<pair<int,int>, pair<char, pair<int, int>>>> AI_Actions(vector<vector<int>> state);
    vector<pair<pair<int,int>, pair<char, pair<int, int>>>> Player_Actions(vector<vector<int>> state);
    int Evaluation(vector<vector<int>> state);
    int Max_Value(vector<vector<int>> state, int alpha, int beta, int level);
    int Min_Value(vector<vector<int>> state, int alpha, int beta, int level);
    pair<pair<int,int>, pair<char, pair<int, int>>> Alpha_Beta_Search(vector<vector<int>> state);
    pair<pair<int,int>, pair<char, pair<int, int>>> getActionbyValue(vector<vector<int>> state, int value);
    void UpdateStateToTile(vector<vector<int>> state, Tile* tile[][6]);

    //--Main Function--
    void AI_MainFunction(Tile* tile[6][6]);
};

#endif // AI_PLAYER_H
