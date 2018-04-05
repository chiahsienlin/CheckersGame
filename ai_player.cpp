#include "ai_player.h"
#include "tile.h"
#include <QDebug>
#include <ctime>
#include <thread>

double duration;
AI_player::AI_player(){
    State.resize(6, vector<int> (6,0));
}

void AI_player::AI_MainFunction(Tile *tile[6][6]){
    Createstate(tile);
    if(!Is_Terminal_State(State)){
        if(!AI_Actions(State).empty()){
            auto action = Alpha_Beta_Search(State);
            auto newState = UpdateState(State, action);
            UpdateStateToTile(newState, tile);
            if(!Is_Terminal_State(newState)){
                string msg ="[AI] I'm done. It's your turn!\n";
                moves->setText(moves->text() + msg.c_str());

                if(Player_Actions(newState).empty()){
                    string msg = "[Judge] You can't move. It's AI's turn!\n";
                    moves->setText(moves->text() + msg.c_str());
                    while(!AI_Actions(newState).empty()){
                        msg = "[AI] I'm moving to end the game...\n";
                        moves->setText(moves->text() + msg.c_str());
                        action = Alpha_Beta_Search(newState);
                        newState = UpdateState(newState, action);
                        UpdateStateToTile(newState, tile);
                        std::this_thread::sleep_for (std::chrono::seconds(1));
                        UpdateBoard(tile);
                    }
                    msg = JudgeFunction(newState);
                    moves->setText(msg.c_str());
                }
            }
            else{
                string msg = JudgeFunction(newState);
                moves->setText(msg.c_str());
            }
        }
        else{
            string msg = "[Judge] AI can't move. Your turn!\n";
            moves->setText(moves->text() + msg.c_str());
        }
    }
    else{
        string msg = JudgeFunction(State);
        moves->setText(msg.c_str());
    }
}

pair<pair<int,int>, pair<char, pair<int, int>>> AI_player::Alpha_Beta_Search(vector<vector<int>> state){
    nodecnt = 0, maxDepth = 0, maxPurn = 0, minPurn = 0;
    auto actions = AI_Actions(state);
    BestAction = actions[rand()%actions.size()];
    start = std::clock();
    int val = Max_Value(state, INT_MIN, INT_MAX, 0);
    qDebug() << "[log] node number generated: " << nodecnt << ", maximum depth: " << maxDepth << ", MAX function pruning times: " << maxPurn << ", MIN function pruning times: " << minPurn << ", Utility: " << val;
    return BestAction;
}

int AI_player::Max_Value(vector<vector<int>> state, int alpha, int beta, int level){
    nodecnt++;
    maxDepth = max(maxDepth,level);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    string t = "Timer: " + to_string((int)duration) + " sec";
    time2->setText(t.c_str());

    if(Is_Terminal_State(state)){ return Evaluation(state); }
    else if(level >= difficulty) {return Evaluation(state); }
    else if(duration >= responseTime) {return Evaluation(state); }

    int val = INT_MIN;
    auto actions = AI_Actions(state);
    for(auto action: actions){
        val = max(val, Min_Value(UpdateState(state, action), alpha, beta, level+1));
        if(val >= beta){
            maxPurn++;
            return val;
        }
        if(val > alpha){
            alpha = val;
            if(level == 0){
                BestAction = action;
                qDebug() << "[+] Best Action (" << BestAction.first.first << "," << BestAction.first.second << ")" << ", ("<< BestAction.second.first <<", " << BestAction.second.second.first << "," << BestAction.second.second.second << ")) with utility = " << val;
            }
        }
    }
    return val;
}

int AI_player::Min_Value(vector<vector<int>> state, int alpha, int beta, int level){
    nodecnt++;
    maxDepth = max(maxDepth,level);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    string t = "Timer: " + to_string((int)duration) + " sec";
    time2->setText(t.c_str());

    if(Is_Terminal_State(state)) return Evaluation(state);
    else if(level >= difficulty) return Evaluation(state);
    else if(duration >= responseTime) return Evaluation(state);

    int val = INT_MAX;
    auto actions = Player_Actions(state);
    for(auto action: actions){
        val = min(val, Max_Value(UpdateState(state, action), alpha, beta, level+1));
        if(val <= alpha){
            minPurn++;
            return val;
        }
        beta = min(beta, val);
    }
    return val;
}

int AI_player::Evaluation(vector<vector<int>> state){
    int whiteBound = 0, BlackBound = 5;
    int cntBlack = 0, cntWhite = 0;
    int safeBlack = 0, safeWhite = 0;
    int DangerousBack = 0, DangerousWhite = 0;

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(state[i][j] == 1){
                whiteBound = min(whiteBound, i);
                cntWhite++;
                if(i==0 || i==5 || j==0 || j==5)
                    safeWhite++;
                else{
                    if((i-1>=0 && j-1>=0 && state[i-1][j-1] != 0) && (i-1>=0 && j+1<6 && state[i-1][j+1] != 0)) safeWhite++;
                    if((i-1>=0 && j-1>=0 && state[i-1][j-1] != 0) && (i+1<6 && j+1<6 && state[i+1][j+1] != 0)) safeWhite++;
                    if((i-1>=0 && j+1<6 && state[i-1][j+1] != 0) && (i+1<6 && j-1>=0 && state[i+1][j-1] != 0)) safeWhite++;
                    if((i-1>=0 && j-1>=0 && state[i-1][j-1] == 0) && (i+1<6 && j+1<6 && state[i+1][j+1] == 0)) safeWhite++;
                    if((i-1>=0 && j+1<6 && state[i-1][j+1] == 0) && (i+1<6 && j-1>=0 && state[i+1][j-1] == 0)) safeWhite++;
                    if((i-1>=0 && j-1>=0 && state[i-1][j-1] == 0) && (i+1<6 && j+1<6 && state[i+1][j+1] == -1)) DangerousWhite++;
                    if((i-1>=0 && j+1<6 && state[i-1][j+1] == 0) && (i+1<6 && j-1>=0 && state[i+1][j-1] == -1)) DangerousWhite++;
                }
            }
            else if(state[i][j] == -1){
                BlackBound = max(BlackBound, i);
                cntBlack++;
                if(i==0 || i==5 || j==0 || j==5)
                    safeBlack++;
                else{
                    if((i+1<6 && j-1>=0 && state[i+1][j-1] != 0) && (i+1<6 && j+1<6 && state[i+1][j+1] != 0)) safeBlack++;
                    if((i+1<6 && j-1>=0 && state[i+1][j-1] != 0) && (i-1>=0 && j+1<6 && state[i-1][j+1] != 0)) safeBlack++;
                    if((i+1<6 && j+1<6 && state[i+1][j+1] != 0) && (i-1>=0 && j-1>=0 && state[i-1][j-1] != 0)) safeBlack++;
                    if((i+1<6 && j-1>=0 && state[i+1][j-1] == 0) && (i-1>=0 && j+1<6 && state[i-1][j+1] == 0)) safeBlack++;
                    if((i+1<6 && j+1<6 && state[i+1][j+1] == 0) && (i-1>=0 && j-1>=0 && state[i-1][j-1] == 0)) safeBlack++;
                    if((i+1<6 && j-1>=0 && state[i+1][j-1] == 0) && (i-1>=0 && j+1<6 && state[i-1][j+1] == 1) && (i-2>=0 && j+2<6 && state[i-2][j+2] != 0)) DangerousBack++;
                    if((i+1<6 && j+1<6 && state[i+1][j+1] == 0) && (i-1>=0 && j-1>=0 && state[i-1][j-1] == 1) && (i-2>=0 && j-2>=0 && state[i-2][j-2] != 0)) DangerousBack++;
                }
            }
        }
    }
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(state[i][j] == 1 && i >= BlackBound)
               safeWhite++;
            else if(state[i][j] == -1 && i <= whiteBound)
               safeBlack++;
        }
    }
    int res = (cntWhite - cntBlack)*300 + (safeWhite - safeBlack)*600 + (DangerousBack)*200 - (DangerousWhite)*400;
    return res;
}

vector<pair<pair<int,int>, pair<char, pair<int, int>>>> AI_player::AI_Actions(vector<vector<int>> state){
    vector<pair<pair<int,int>, pair<char, pair<int, int>>>> actions;
    bool ForceJump = false;
    for(int row = 0; row < 6; row++){
        for(int col = 0 ; col < 6; col++){
            if(state[row][col] == 1){
                //upperleft enemy
                if(row+1<6 && col+1<6){
                    if(state[row+1][col+1] == -1){
                        if(row+2<6 && col+2<6 && state[row+2][col+2] == 0){
                            auto action = make_pair( make_pair(row,col), make_pair('e', make_pair(row+2, col+2)));
                            actions.push_back(action);
                            ForceJump=true;
                        }
                    }
                }
                //upperright enemy
                if(row+1<6 && col-1 >= 0){
                    if(state[row+1][col-1] == -1){
                        if(row+2<6 && col-2 >= 0 && state[row+2][col-2] == 0){
                            auto action = make_pair( make_pair(row,col), make_pair('e', make_pair(row+2, col-2)));
                            actions.push_back(action);
                            ForceJump=true;
                        }
                    }
                }
                //Force Jump or move to left empty tile
                if(!ForceJump && row+1<6 && col+1<6 && state[row+1][col+1] == 0){
                    auto action = make_pair( make_pair(row,col), make_pair('m', make_pair(row+1, col+1)));
                    actions.push_back(action);
                }
                //Force Jump or move to right empty tile
                if(!ForceJump && row+1<6 && col-1 >= 0 && state[row+1][col-1]== 0){
                    auto action = make_pair( make_pair(row,col), make_pair('m', make_pair(row+1, col-1)));
                    actions.push_back(action);
                }
            }
        }
    }
    //Force Jump Check
    if(ForceJump){
        for(int i = 0; i < actions.size(); i++){
            if(actions[i].second.first == 'm'){
                actions.erase(actions.begin()+i);
                i--;
            }
        }
    }
    return actions;
}

vector<pair<pair<int,int>, pair<char, pair<int, int>>>> AI_player::Player_Actions(vector<vector<int>> state){
    vector<pair<pair<int,int>, pair<char, pair<int, int>>>> actions;
    bool ForceJump = false;
    for(int row = 0; row < 6; row++){
        for(int col = 0 ; col < 6; col++){
            if(state[row][col] == -1){
                //upperleft enemy
                if(row-1 >= 0 && col-1 >= 0){
                    if(state[row-1][col-1] == 1){
                        if(row-2 >=0 && col-2 >= 0 && state[row-2][col-2] == 0){
                            auto action = make_pair( make_pair(row,col), make_pair('e', make_pair(row-2, col-2)));
                            actions.push_back(action);
                            ForceJump=true;
                        }
                    }
                }
                //upperright enemy
                if(row-1 >= 0 && col+1 <6){
                    if(state[row-1][col+1] == 1){
                        if(row-2>=0 && col+2 < 6 && state[row-2][col+2] == 0){
                            auto action = make_pair( make_pair(row,col), make_pair('e', make_pair(row-2, col+2)));
                            actions.push_back(action);
                            ForceJump=true;
                        }
                    }
                }
                //upperleft is empty and there is no enemy on the right
                if(!ForceJump && row-1 >= 0 && col-1 >= 0 && state[row-1][col-1] == 0){
                    auto action = make_pair( make_pair(row,col), make_pair('m', make_pair(row-1, col-1)));
                    actions.push_back(action);
                }
                //upperright is empty and there is no enemy on the right
                if(!ForceJump && row-1 >= 0 && col+1 <6 && state[row-1][col+1]== 0){
                    auto action = make_pair( make_pair(row,col), make_pair('m', make_pair(row-1, col+1)));
                    actions.push_back(action);
                }
            }
        }
    }
    //Force Jump Check
    if(ForceJump){
        for(int i = 0; i < actions.size(); i++){
            if(actions[i].second.first == 'm'){
                actions.erase(actions.begin()+i);
                i--;
            }
        }
    }
    return actions;
}

bool AI_player::Is_Terminal_State(vector<vector<int>> state){
    int cntBlack = 0, cntWhite = 0;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(state[i][j] == 1) cntWhite++;
            else if(state[i][j] == -1) cntBlack++;
        }
    }
    auto AI_acts = AI_Actions(state);
    auto Pl_acts = Player_Actions(state);
    if(cntBlack == 0) return true;
    else if(cntWhite == 0) return true;
    else if (AI_acts.empty() && Pl_acts.empty()) return true;
    else return false;
}

string AI_player::JudgeFunction(vector<vector<int> > state) {
    int Blackcnt = 0, Whitecnt = 0;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(state[i][j] == 1)
                Whitecnt++;
            else if(state[i][j] == -1)
                Blackcnt++;
        }
    }
    int val = Whitecnt - Blackcnt;
    string msg;
    if(val > 0)
         msg = "[Judge] Game Over. AI WIN, you LOSE.\n";
    else if(val == 0)
         msg = "[Judge] Game Over. DRAW, no winner.\n";
    else
         msg = "[Judge] Game Over. You WIN, AI LOSE.\n";
    return msg;
}

vector<vector<int>> AI_player::getState(){
    return State;
}

void AI_player::Createstate(Tile* tile[6][6]){
    for(int i = 0 ; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(tile[i][j]->piece == 0){
                State[i][j] = 0;
            }
            else{
                if(tile[i][j]->pieceColor == 1)
                    State[i][j] = 1;//white
                else
                    State[i][j] = -1;//black
            }
        }
    }
}

void AI_player::UpdateStateToTile(vector<vector<int>> state, Tile* tile[][6]){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(state[i][j] == 1){
                tile[i][j]->piece = 1;
                tile[i][j]->pieceColor = 1;
            }
            else if(state[i][j] == -1){
                tile[i][j]->piece = 1;
                tile[i][j]->pieceColor = 0;
            }
            else{
                tile[i][j]->piece=0;
            }
        }
    }
}

vector<vector<int>> AI_player::UpdateState(vector<vector<int>> state, pair<pair<int,int>, pair<char, pair<int, int>>> action){
    char action_type = action.second.first;
    int before_x = action.first.first;
    int before_y = action.first.second;
    int after_x = action.second.second.first;
    int after_y = action.second.second.second;
    int tmp = state[before_x][before_y];

    if(action_type == 'm'){
        state[before_x][before_y] = 0;
        state[after_x][after_y] = tmp;
    }
    else if(action_type == 'e'){
        int mid_x = (before_x + after_x)/2;
        int mid_y = (before_y + after_y)/2;
        state[before_x][before_y] = 0;
        state[after_x][after_y] = tmp;
        state[mid_x][mid_y] = 0;
    }
    else{
       qDebug() << "[error] : Undefined actions type.";
    }
    return state;
}

void AI_player::printState(vector<vector<int>> state){
    string tmp;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(state[i][j] >= 0)
                tmp += " "+ to_string(state[i][j]);
            else
                tmp += to_string(state[i][j]);
        }
        qDebug() << QString::fromStdString(tmp);
        tmp.clear();
    }
}
