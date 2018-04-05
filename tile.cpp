#include "tile.h"
#include "validation.h"
#include "ai_player.h"
#include <thread>

void validate(Tile *temp,int c);
void disOrange();
void AI_Start();
void Player_Start(Tile *temp, int retValue);
void EatFunction(Tile * temp);
void MoveFunction(Tile * temp, int retValue);
void RenewBoard(Tile * temp);

void AI_Start(){
    ai->AI_MainFunction(tile);
    UpdateBoard(tile);
    turn++;
}

void Player_Start(Tile *temp, int retValue){
    for(int i = 0; i < valid_mv.size(); i++){
        if(temp->tileNum == valid_mv[i]){
            EatFunction(temp);
            MoveFunction(temp, retValue);
            RenewBoard(temp);
            ai->Createstate(tile);
            if(!ai->Is_Terminal_State(ai->getState())){
                if(turn%2 == 1){
                    std::thread th_ai(AI_Start);
                    th_ai.detach();
                }
            }
            else{
                string msg = ai->JudgeFunction(ai->getState());
                moves->setText(msg.c_str());
            }
        }
        else
            cnt=1;
    }
}

void validate(Tile *temp, int c){
    int retValue;
    //First click
    if(c == 1){
        if(temp->piece){
            retValue = valid->chooser(temp);
            if(retValue){
                click1= new Tile();
                temp->setStyleSheet("QLabel {background-color: orange;}");
                click1=temp;
            }
            else
                cnt=0;
        }
        else
            cnt=0;
    }
    else{
        //Unclick the original chosen one
        if(temp->tileNum == click1->tileNum){
            click1->tileDisplay();
            disOrange();
            valid_mv.clear();
            eat.clear();
            cnt=0;
        }
        else{
            ai->Createstate(tile);
            if(!ai->Is_Terminal_State(ai->getState())){
                if(!ai->Player_Actions(ai->getState()).empty()){
                   Player_Start(temp, retValue);
                }
            }
            else{
                string msg = ai->JudgeFunction(ai->getState());
                moves->setText(msg.c_str());
            }
        }
    }
}

void Tile::tileDisplay(){
    if(this->tileColor)
        this->setStyleSheet("QLabel {background-color: rgb(100, 100, 100);}:hover{background-color: rgb(80,80,80);}");
    else
        this->setStyleSheet("QLabel {background-color: rgb(250, 250, 250);}:hover{background-color: rgb(200,200,200);}");
}

void disOrange(){
    for(int i=0;i<valid_mv.size();i++)
        tile[valid_mv[i]/6][valid_mv[i]%6]->tileDisplay();
}

void UpdateBoard(Tile *tile[6][6]){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(tile[i][j]->piece){
                if(tile[i][j]->pieceColor)
                    tile[i][j]->display('W');
                else
                    tile[i][j]->display('B');
            }
            else
                tile[i][j]->display('N');
        }
    }
}

void Tile::mousePressEvent(QMouseEvent *event){
    if(turn%2 == 0)
        validate(this,++cnt);
}

void Tile::display(char elem){
    this->pieceName=elem;
    if(this->pieceColor && this->piece){
        this->setPixmap(QPixmap(":/Images/white.svg"));
    }
    else if(this->piece){
        this->setPixmap(QPixmap(":/Images/black.svg"));
    }
    else
        this->clear();
}

void EatFunction(Tile * temp){
    if(!eat.empty()){
        for(int j = 0; j < eat.size(); j++){
            int tilenum = eat[j];
            int row_eat = tilenum/6;
            int col_eat = tilenum%6;
            int slope_des_start = (temp->row - click1->row)/(temp->col - click1->col);
            int slope_eat_start = (row_eat - click1->row)/(col_eat - click1->col);

            if(slope_des_start == slope_eat_start){
                tile[row_eat][col_eat]->piece=0;
                tile[row_eat][col_eat]->clear();
            }
        }
        eat.clear();
    }
}

void MoveFunction(Tile * temp, int retValue){
    click1->piece=0;
    temp->piece=1;
    temp->pieceColor=click1->pieceColor;
    temp->pieceName=click1->pieceName;
    retValue=valid->check(click1);
    disOrange();
    valid_mv.clear();
    cnt=0;
    turn++;
}

void RenewBoard(Tile * temp){
    click1->display(click1->pieceName);
    temp->display(click1->pieceName);
    click1->tileDisplay();
    temp->tileDisplay();
}
