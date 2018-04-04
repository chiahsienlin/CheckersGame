#include "validation.h"

validation::validation(){
     State.resize(6, std::vector<int>(6,0));
}

int validation::chooser(Tile *temp){
    CreateState(tile);
    CreateValidCheckersSet();
    if(v_checks.find(temp->tileNum) != v_checks.end()){
        flag=valiateMoves(temp);
        orange();
        return flag;
    }
    else
        return 0;
}

int validation::valiateMoves(Tile *temp){
    int row,col;
    row=temp->row;
    col=temp->col;
    retVal=0;
    bool leftenemy = false;
    bool rightenemy = false;
    //Black(bottom)
    if(!temp->pieceColor){
        //upperleft have enemy
        if(row-1 >= 0 && col-1 >= 0){
            if(tile[row-1][col-1]->piece && tile[row-1][col-1]->pieceColor == 1){
                if(row-2 >=0 && col-2 >= 0 && !tile[row-2][col-2]->piece){
                    valid_mv.push_back(tile[row-2][col-2]->tileNum);
                    eat.push_back(tile[row-1][col-1]->tileNum);
                    retVal=1;
                    leftenemy=true;
                }
            }
        }
        //upperright have enemy
        if(row-1 >= 0 && col+1 <6){
            if(tile[row-1][col+1]->piece && tile[row-1][col+1]->pieceColor == 1){
                if(row-2>=0 && col+2 < 6 && !tile[row-2][col+2]->piece){
                    valid_mv.push_back(tile[row-2][col+2]->tileNum);
                    eat.push_back(tile[row-1][col+1]->tileNum);
                    retVal=1;
                    rightenemy=true;
                }
            }
        }
        //upperleft is empty and there is no enemy on the right
        if(!rightenemy && row-1 >= 0 && col-1 >= 0 && !tile[row-1][col-1]->piece){
            valid_mv.push_back(tile[row-1][col-1]->tileNum);
            retVal=1;
        }
        //upperright is empty and there is no enemy on the left
        if(!leftenemy && row-1 >= 0 && col+1 <6 && !tile[row-1][col+1]->piece){
            valid_mv.push_back(tile[row-1][col+1]->tileNum);
            retVal=1;
        }
    }
    return retVal;
}

int validation::check(Tile *temp){
    retVal=0;
    return retVal;
}

void validation::orange(){
    for(int i=0;i<valid_mv.size();i++)
        tile[valid_mv[i]/6][valid_mv[i]%6]->setStyleSheet("QLabel {background-color: yellow;}");
}

void validation::CreateState(Tile* tile[6][6]){
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

void validation::CreateValidCheckersSet(){
    bool ForceJump = false;
    v_checks.clear();
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(State[i][j] == -1 && i-1>=0 && j-1>=0 && State[i-1][j-1] == 1 && i-2>=0 && j-2>=0 && State[i-2][j-2] == 0){
                ForceJump = true;
                break;
            }
            else if(State[i][j] == -1 && i-1 >=0 && j+1 <6 && State[i-1][j+1] == 1 && i-2 >=0 && j+2 <6 && State[i-2][j+2] == 0){
                ForceJump = true;
                break;
            }
        }
    }
    //add the ForceJump checkers
    if(ForceJump){
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 6; j++){
                if(State[i][j] == -1 && i-1>=0 && j-1>=0 && State[i-1][j-1] == 1 && i-2>=0 && j-2>=0 && State[i-2][j-2] == 0){
                    int tilenum = i*6 + j;
                    v_checks.emplace(tilenum);
                }
                else if(State[i][j] == -1 && i-1 >=0 && j+1 <6 && State[i-1][j+1] == 1 && i-2 >=0 && j+2 <6 && State[i-2][j+2] == 0){
                    int tilenum = i*6 + j;
                    v_checks.emplace(tilenum);
                }
            }
        }
    }
    else{
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 6; j++){
                int tilenum = i*6 + j;
                v_checks.emplace(tilenum);
            }
        }
    }
}
