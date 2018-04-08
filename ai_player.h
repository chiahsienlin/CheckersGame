#ifndef AI_PLAYER_H
#define AI_PLAYER_H
#include "tile.h"
using namespace std;

class AI_player{
    private:
        pair<pair<int,int>, pair<char, pair<int, int>>> BestAction;
        vector<vector<int>> State;
        std::clock_t start;
        int nodecnt, maxDepth, maxPurn, minPurn;
    public:
        //AI's methods
        AI_player();
        void Createstate(Tile* tile[6][6]);
        vector<vector<int>> UpdateState(vector<vector<int>> state, pair<pair<int,int>, pair<char, pair<int, int>>> action);
        vector<vector<int>> getState();
        void printState(vector<vector<int>> state);
        bool Is_Terminal_State(vector<vector<int>> state);
        vector<pair<pair<int,int>, pair<char, pair<int, int>>>> AI_Actions(vector<vector<int>> state);
        vector<pair<pair<int,int>, pair<char, pair<int, int>>>> Player_Actions(vector<vector<int>> state);
        int Evaluation(vector<vector<int>> state);
        int Utility(vector<vector<int>> state);
        int Max_Value(vector<vector<int>> state, int alpha, int beta, int level);
        int Min_Value(vector<vector<int>> state, int alpha, int beta, int level);
        pair<pair<int,int>, pair<char, pair<int, int>>> Alpha_Beta_Search(vector<vector<int>> state);
        void UpdateStateToTile(vector<vector<int>> state, Tile* tile[][6]);
        string JudgeFunction(vector<vector<int>> state);

        //-- AI's Main Function--
        void AI_MainFunction(Tile* tile[6][6]);
};
extern AI_player *ai;
#endif // AI_PLAYER_H


/* [Description] (The details please see the report.pdf)
 *
 * AI_Player::AI_player(): The constructor.
 * AI_Player::Createstate(): Given the 2D array of Tiles class pointers, transform to the binary 2D vetor stored in State.
 * AI_Player::UpdateState(): Given a state and a action, return the updated state after the action.
 * AI_Player::getState(): Return the State.
 * AI_Player::printState(): Given a state, print it.
 * AI_Player::Is_Terminal_State(): Given a state, check if it is the terminal state.
 * AI_Player::AI_Actions(): Given a state, return the AI's available actions.
 * AI_Player::Player_Actions(): Given a state, return the Player's available actions.
 * AI_Player::Evaluation(): Given a state, return the evaluation value.
 * AI_Player::Utility(): Given a state, return the utility value.
 * AI_Player::Max_Value(): In the alpha-beta search, represents the AI Player.
 * AI_Player::Min_Value(): In the alpha-beta search, represents the human being's Player.
 * AI_Player::Alpha_Beta_Search(): Given a state, return the best action by the alpha-beta search algorithm.
 * AI_Player::UpdateStateToTile(): Given a state, transform to the 2D array of Tiles class pointers.
 * AI_Player::JudgeFunction(): Given a state, return a judgement msg.
 *
*/
