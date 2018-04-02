#include "validation.h"

validation::validation(){
}

int validation::chooser(Tile *temp){
    flag=validatePawn(temp);
    orange();
    return flag;
}

int validation::validatePawn(Tile *temp){
    int row,col;
    row=temp->row;
    col=temp->col;
    retVal=0;
    bool right_enemy = false;
    bool left_enemy = false;
    //Black(bottom)
    if(!temp->pieceColor){
        //upperleft have enemy
        if(row-1 >= 0 && col-1 >= 0){
            if(tile[row-1][col-1]->piece && tile[row-1][col-1]->pieceColor == 1){
                if(row-2 >=0 && col-2 >= 0 && !tile[row-2][col-2]->piece){
                    exp.push_back(tile[row-2][col-2]->tileNum);
                    eat.push_back(tile[row-1][col-1]->tileNum);
                    retVal=1;
                    left_enemy=true;
                }
            }
        }
        //upperright have enemy
        if(row-1 >= 0 && col+1 <6){
            if(tile[row-1][col+1]->piece && tile[row-1][col+1]->pieceColor == 1){
                if(row-2>=0 && col+2 < 6 && !tile[row-2][col+2]->piece){
                    exp.push_back(tile[row-2][col+2]->tileNum);
                    eat.push_back(tile[row-1][col+1]->tileNum);
                    retVal=1;
                    right_enemy=true;
                }
            }
        }
        //upperleft is empty and there is no enemy on the right
        if(!right_enemy && row-1 >= 0 && col-1 >= 0 && !tile[row-1][col-1]->piece){
            exp.push_back(tile[row-1][col-1]->tileNum);
            retVal=1;
        }
        //upperright is empty and there is no enemy on the left
        if(!left_enemy && row-1 >= 0 && col+1 <6 && !tile[row-1][col+1]->piece){
            exp.push_back(tile[row-1][col+1]->tileNum);
            retVal=1;
        }
    }
    /*------------------- For 2P Game----------------------------------------
    //White(top)
    else{
        //upperleft have enemy
        if(row+1<6 && col+1<6){
            if(tile[row+1][col+1]->piece && tile[row+1][col+1]->pieceColor == 0){
                if(row+2<6 && col+2<6 && !tile[row+2][col+2]->piece){
                    exp.push_back(tile[row+2][col+2]->tileNum);
                    eat.push_back(tile[row+1][col+1]->tileNum);
                    //qDebug() << "Add left enemy.   vector size = " << eat.size();
                    retVal=1;
                    left_enemy=true;
                }
            }
        }
        //upperright have enemy
        if(row+1<6 && col-1 >= 0){
            if(tile[row+1][col-1]->piece && tile[row+1][col-1]->pieceColor == 0){
                if(row+2<6 && col-2 >= 0 && !tile[row+2][col-2]->piece){
                    exp.push_back(tile[row+2][col-2]->tileNum);
                    eat.push_back(tile[row+1][col-1]->tileNum);
                    //qDebug() << "Add right enemy.   vector size = " << eat.size();
                    retVal=1;
                    right_enemy=true;
                }
            }
        }
        //upperleft is empty and there is no enemy on the right
        if(!right_enemy && row+1<6 && col+1<6 && !tile[row+1][col+1]->piece){
            exp.push_back(tile[row+1][col+1]->tileNum);
            retVal=1;
        }

        //upperright is empty and there is no enemy on the right
        if(!left_enemy && row+1<6 && col-1 >= 0 && !tile[row+1][col-1]->piece){
            exp.push_back(tile[row+1][col-1]->tileNum);
            retVal=1;
        }
    }*/
    return retVal;
}

int validation::check(Tile *temp){
    retVal=0;
    return retVal;
}

void validation::orange(){
    for(int i=0;i<exp.size();i++)
        tile[exp[i]/6][exp[i]%6]->setStyleSheet("QLabel {background-color: yellow;}");
}
