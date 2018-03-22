#include "validation.h"

validation::validation()
{
    //Nothing here
}

int validation::chooser(Tile *temp)
{
    flag=validatePawn(temp);
    orange();
    return flag;
}

int validation::validatePawn(Tile *temp)
{
    int row,col;

    row=temp->row;
    col=temp->col;
    retVal=0;
    //Black(bottom)
    if(!temp->pieceColor)
    {
        //upperleft
        if(row-1 >= 0 && col-1 >= 0){
            //have enemy
            if(tile[row-1][col-1]->piece){
                if(row-2 >=0 && col-2 >= 0 && !tile[row-2][col-2]->piece && tile[row-1][col-1]->pieceColor == 1){
                    exp.push_back(tile[row-2][col-2]->tileNum);
                    eat.push_back(tile[row-1][col-1]->tileNum);
                    retVal=1;
                }
            }
            //empty
            else{
                exp.push_back(tile[row-1][col-1]->tileNum);
                retVal=1;
            }
        }
        //upperright
        if(row-1 >= 0 && col+1 <6){
            //have enemy
            if(tile[row-1][col+1]->piece){
                if(row-2>=0 && col+2 < 6 && !tile[row-2][col+2]->piece && tile[row-1][col+1]->pieceColor == 1){
                    exp.push_back(tile[row-2][col+2]->tileNum);
                    eat.push_back(tile[row-1][col+1]->tileNum);
                    retVal=1;
                }
            }
            //empty
            else{
                exp.push_back(tile[row-1][col+1]->tileNum);
                retVal=1;
            }
        }
    }
    //White(top)
    else
    {
        //upperleft
        if(row+1<6 && col+1<6){
            //have enemy
            if(tile[row+1][col+1]->piece){
                if(row+2<6 && col+2<6 && !tile[row+2][col+2]->piece && tile[row+1][col+1]->pieceColor == 0){
                    exp.push_back(tile[row+2][col+2]->tileNum);
                    eat.push_back(tile[row+1][col+1]->tileNum);
                    qDebug() << "Add left enemy.   vector size = " << eat.size();
                    retVal=1;
                }
            }
            //empty
            else{
                exp.push_back(tile[row+1][col+1]->tileNum);
                retVal=1;
            }

        }
        //upperright
        if(row+1<6 && col-1 >= 0){
            //have enemy
            if(tile[row+1][col-1]->piece){
                if(row+2<6 && col-2 >= 0 && !tile[row+2][col-2]->piece && tile[row+1][col-1]->pieceColor == 0){
                    exp.push_back(tile[row+2][col-2]->tileNum);
                    eat.push_back(tile[row+1][col-1]->tileNum);
                    qDebug() << "Add right enemy.   vector size = " << eat.size();
                    retVal=1;
                }
            }
            //empty
            else{
                exp.push_back(tile[row+1][col-1]->tileNum);
                retVal=1;
            }
        }
    }
    return retVal;
}

int validation::check(Tile *temp)
{
    retVal=0;
    return retVal;
}

void validation::orange()
{
    int i;
    for(i=0;i<exp.size();i++)
        tile[exp[i]/6][exp[i]%6]->setStyleSheet("QLabel {background-color: yellow;}");
}
