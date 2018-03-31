#include "ai_player.h"
#include "tile.h"
#include <QDebug>

AI_player::AI_player(){
    st.resize(6, vector<int> (6,0));
}

void AI_player::updateState(Tile* state[6][6]){
    for(int i = 0 ; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(state[i][j]->piece == 0){
                st[i][j] = 0;
            }
            else{
                if(state[i][j]->pieceColor == 1)
                    st[i][j] = 1;//white
                else
                    st[i][j] = -1;//black
            }
        }
    }
    qDebug() << "Update";
}

void AI_player::printState(){
    string tmp;
    for(int i = 0; i < st.size(); i++){
        for(int j = 0; j < st[i].size(); j++){
            if(st[i][j] >= 0)
                tmp += " "+ to_string(st[i][j]);
            else
                tmp += to_string(st[i][j]);
        }
        qDebug() << QString::fromStdString(tmp);
        tmp.clear();
    }
    return;
}

vector<vector<int>> AI_player::getState(){

}
