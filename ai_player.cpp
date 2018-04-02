#include "ai_player.h"
#include "tile.h"
#include <QDebug>
#include <ctime>

double duration;
std::clock_t start;

AI_player::AI_player(){
    State.resize(6, vector<int> (6,0));
}

void AI_player::AI_MainFunction(Tile *tile[6][6]){
    std::clock_t start;
    start = std::clock();
    Createstate(tile);
    auto action = Alpha_Beta_Search(State);
    auto newState = UpdateState(State, action);
    printState(newState);
    UpdateStateToTile(newState, tile);
    qDebug() << "AI is done.";
    turn++;
    return;
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
    return;
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
    //qDebug() << "Create State";
    return;
}

vector<vector<int>> AI_player::UpdateState(vector<vector<int>> state, pair<pair<int,int>, pair<char, pair<int, int>>> action){
    char action_type = action.second.first;
    int before_x = action.first.first;
    int before_y = action.first.second;
    int after_x = action.second.second.first;
    int after_y = action.second.second.second;
    int tmp = state[before_x][before_y];

    if(action_type == 'm'){
        //qDebug() << "AI Move";
        state[before_x][before_y] = 0;
        state[after_x][after_y] = tmp;
    }
    else if(action_type == 'e'){
        //qDebug() << "AI Eat";
        int mid_x = (before_x + after_x)/2;
        int mid_y = (before_y + after_y)/2;
        state[before_x][before_y] = 0;
        state[after_x][after_y] = tmp;
        state[mid_x][mid_y] = 0;
    }
    else{
       qDebug() << "[error] : Undefined actions type.";
       qDebug() << "Action type: " << action_type << ", value = "<< tmp << before_x << ","<< before_y << "=>" << after_x << "," << after_y;
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

vector<vector<int>> AI_player::getState(){
    return State;
}

bool AI_player::Is_Terminal_State(vector<vector<int>> state){
    int cntBlack = 0, cntWhite = 0;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(state[i][j] == 1) cntWhite++;
            else if(state[i][j] == -1) cntBlack++;
        }
    }
    auto AI_acts = AI_Actions(this->State);
    auto Pl_acts = Player_Actions(this->State);
    if(cntBlack == 0) return true;
    else if(cntWhite == 0) return true;
    else if (AI_acts.empty() && Pl_acts.empty()) return true;
    else return false;
}

vector<pair<pair<int,int>, pair<char, pair<int, int>>>> AI_player::AI_Actions(vector<vector<int>> state){
    vector<pair<pair<int,int>, pair<char, pair<int, int>>>> actions;
    bool left_enemy = false;
    bool right_enemy = false;
    for(int row = 0; row < 6; row++){
        for(int col = 0 ; col < 6; col++){
            if(state[row][col] == 1){
                //upperleft have enemy
                if(row+1<6 && col+1<6){
                    if(state[row+1][col+1] == -1){
                        if(row+2<6 && col+2<6 && state[row+2][col+2] == 0){
                            auto action = make_pair( make_pair(row,col), make_pair('e', make_pair(row+2, col+2)));
                            actions.push_back(action);
                            qDebug() << "AI add the left eat (" << action.first.first << "," << action.first.second << ")" << ", ("<< action.second.first <<", " << action.second.second.first << "," << action.second.second.second << "))";
                            left_enemy=true;
                        }
                    }
                }
                //upperright have enemy
                if(row+1<6 && col-1 >= 0){
                    if(state[row+1][col-1] == -1){
                        if(row+2<6 && col-2 >= 0 && state[row+2][col-2] == 0){
                            auto action = make_pair( make_pair(row,col), make_pair('e', make_pair(row+2, col-2)));
                            actions.push_back(action);
                            qDebug() << "AI add the right eat (" << action.first.first << "," << action.first.second << ")" << ", ("<< action.second.first <<", " << action.second.second.first << "," << action.second.second.second << "))";
                            right_enemy=true;
                        }
                    }
                }
                //upperleft is empty and there is no enemy on the right
                if(!right_enemy && row+1<6 && col+1<6 && state[row+1][col+1] == 0){
                    auto action = make_pair( make_pair(row,col), make_pair('m', make_pair(row+1, col+1)));
                    actions.push_back(action);
                    //qDebug() << "AI add the left move (" << action.first.first << "," << action.first.second << ")" << ", ("<< action.second.first <<", " << action.second.second.first << "," << action.second.second.second << "))";
                }

                //upperright is empty and there is no enemy on the right
                if(!left_enemy && row+1<6 && col-1 >= 0 && state[row+1][col-1]== 0){
                    auto action = make_pair( make_pair(row,col), make_pair('m', make_pair(row+1, col-1)));
                    actions.push_back(action);
                    //qDebug() << "AI add the right move (" << action.first.first << "," << action.first.second << ")" << ", ("<< action.second.first <<", " << action.second.second.first << "," << action.second.second.second << "))";
                }
            }
        }
    }
    return actions;
}

vector<pair<pair<int,int>, pair<char, pair<int, int>>>> AI_player::Player_Actions(vector<vector<int>> state){
    vector<pair<pair<int,int>, pair<char, pair<int, int>>>> actions;
    bool left_enemy = false;
    bool right_enemy = false;
    for(int row = 0; row < 6; row++){
        for(int col = 0 ; col < 6; col++){
            if(state[row][col] == -1){
                //upperleft have enemy
                if(row-1 >= 0 && col-1 >= 0){
                    if(state[row-1][col-1] == 1){
                        if(row-2 >=0 && col-2 >= 0 && state[row-2][col-2] == 0){
                            auto action = make_pair( make_pair(row,col), make_pair('e', make_pair(row-2, col-2)));
                            actions.push_back(action);
                            //qDebug() << "Player add the left eat (" << action.first.first << "," << action.first.second << ")" << ", ("<< action.second.first <<", " << action.second.second.first << "," << action.second.second.second << "))";
                            left_enemy=true;
                        }
                    }
                }
                //upperright have enemy
                if(row-1 >= 0 && col+1 <6){
                    if(state[row-1][col+1] == 1){
                        if(row-2>=0 && col+2 < 6 && state[row-2][col+2] == 0){
                            auto action = make_pair( make_pair(row,col), make_pair('e', make_pair(row-2, col+2)));
                            actions.push_back(action);
                            //qDebug() << "Player add the right eat (" << action.first.first << "," << action.first.second << ")" << ", ("<< action.second.first <<", " << action.second.second.first << "," << action.second.second.second << "))";
                            right_enemy=true;
                        }
                    }
                }
                //upperleft is empty and there is no enemy on the right
                if(!right_enemy && row-1 >= 0 && col-1 >= 0 && state[row-1][col-1] == 0){
                    auto action = make_pair( make_pair(row,col), make_pair('m', make_pair(row-1, col-1)));
                    actions.push_back(action);
                    //qDebug() << "Player add the left move (" << action.first.first << "," << action.first.second << ")" << ", ("<< action.second.first <<", " << action.second.second.first << "," << action.second.second.second << "))";
                }

                //upperright is empty and there is no enemy on the right
                if(!left_enemy && row-1 >= 0 && col+1 <6 && state[row-1][col+1]== 0){
                    auto action = make_pair( make_pair(row,col), make_pair('m', make_pair(row-1, col+1)));
                    actions.push_back(action);
                    //qDebug() << "Player add the right move (" << action.first.first << "," << action.first.second << ")" << ", ("<< action.second.first <<", " << action.second.second.first << "," << action.second.second.second << "))";
                }
            }
        }
    }
    return actions;
}

int AI_player::Evaluation(vector<vector<int>> state){
    int cntBlack = 0, cntWhite = 0;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(state[i][j] == 1) cntWhite++;
            else if(state[i][j] == -1) cntBlack++;
        }
    }
    return (cntWhite - cntBlack);
}

pair<pair<int,int>, pair<char, pair<int, int>>> AI_player::getActionbyValue(vector<vector<int>> state, int value){
    auto actions = AI_Actions(state);
    qDebug() << "Need to find the action with value" << value;
    for(auto action: actions){
        if(Evaluation(UpdateState(state, action)) == value)
            return action;
    }
    qDebug() << "Action with " << value << " not found.";
    return pair<pair<int,int>, pair<char, pair<int, int>>>();
}

pair<pair<int,int>, pair<char, pair<int, int>>> AI_player::Alpha_Beta_Search(vector<vector<int>> state){
    BestAction = AI_Actions(state)[rand()%2];
    int val = Max_Value(state, INT_MIN, INT_MAX, 0);
    return BestAction;
}

int AI_player::Max_Value(vector<vector<int>> state, int alpha, int beta, int level){
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    qDebug() << "Duration: " << duration << ", level: " << level;
    if(Is_Terminal_State(state)) return Evaluation(state);
    else if(level >= difficulty) return Evaluation(state);
    else if(duration >= responseTime) return Evaluation(state);

    int val = INT_MIN;
    auto actions = AI_Actions(state);
    for(auto action: actions){
        val = max(val, Min_Value(UpdateState(state, action), alpha, beta, level+1));
        if(val >= beta) return val;
        if(val > alpha){
            if(level == 0){
                alpha = val;
                BestAction = action;
                qDebug() << "Best Action (" << BestAction.first.first << "," << BestAction.first.second << ")" << ", ("<< BestAction.second.first <<", " << BestAction.second.second.first << "," << BestAction.second.second.second << "))";
            }
            else{
                alpha = val;
            }
        }
    }
    return val;
}

int AI_player::Min_Value(vector<vector<int>> state, int alpha, int beta, int level){
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    qDebug() << "Duration: " << duration << ", level: " << level << ", difficulty: " << difficulty;
    if(Is_Terminal_State(state)) return Evaluation(state);
    else if(level >= difficulty) return Evaluation(state);
    else if(duration >= responseTime) return Evaluation(state);

    int val = INT_MAX;
    auto actions = Player_Actions(state);
    for(auto action: actions){
        val = min(val, Max_Value(UpdateState(state, action), alpha, beta, level+1));
        if(val <= alpha) return val;
        beta = min(beta, val);
    }
    return val;
}
