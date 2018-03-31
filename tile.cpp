#include "tile.h"
#include "validation.h"
#include "ai_player.h"

validation *valid = new validation();
AI_player *ai = new AI_player();

void validate(Tile *temp,int c);
void disOrange();

void Tile::mousePressEvent(QMouseEvent *event)
{
    validate(this,++cnt);
}

void Tile::display(char elem)
{
    this->pieceName=elem;

    if(this->pieceColor && this->piece)
    {
        this->setPixmap(QPixmap(":/Images/pawn_white.svg"));
    }

    else if(this->piece)
    {
        this->setPixmap(QPixmap(":/Images/pawn_black.svg"));
    }
    else
        this->clear();
}

void validate(Tile *temp, int c)
{
    int retValue,i;

    if(c==1)
    {
        if(temp->piece && (temp->pieceColor==turn%2))
        {
            retValue=valid->chooser(temp);

            if(retValue)
            {
                click1= new Tile();
                temp->setStyleSheet("QLabel {background-color: orange;}");
                click1=temp;
            }
            else
            {
                cnt=0;
            }
        }
        else
        {
            qDebug()<<"Rascel, clicking anywhere";
            cnt=0;
        }
    }
    else
    {
        //unclick the original chosen one
        if(temp->tileNum==click1->tileNum){
            click1->tileDisplay();
            disOrange();
            exp.clear();
            eat.clear();
            cnt=0;
            qDebug() << "Unclick";
        }
        else{
            qDebug() << "Move";
            for(i=0;i<exp.size();i++){
                if(temp->tileNum==exp[i]){
                    if(!eat.empty()){
                        for(int x = 0; x < eat.size(); x++){
                            int tilenum = eat[x];
                            int row_eat = tilenum/6;
                            int col_eat = tilenum%6;
                            int slope_des_start = (temp->row - click1->row)/(temp->col - click1->col);
                            int slope_eat_start = (row_eat - click1->row)/(col_eat - click1->col);

                            if(slope_des_start == slope_eat_start){
                                qDebug() << "Eat!";
                                tile[row_eat][col_eat]->piece=0;
                                tile[row_eat][col_eat]->clear();
                                if(tile[row_eat][col_eat]->pieceColor)
                                    remain_wht--;
                                else
                                    remain_blk--;
                                qDebug() << "white remains: " << remain_wht << "  black remains: " << remain_blk;
                            }
                        }
                        eat.clear();
                    }
                    click1->piece=0;
                    temp->piece=1;

                    temp->pieceColor=click1->pieceColor;
                    temp->pieceName=click1->pieceName;

                    click1->display(click1->pieceName);
                    temp->display(click1->pieceName);

                    click1->tileDisplay();
                    temp->tileDisplay();

                    ai->updateState(tile);
                    ai->printState();
                    retValue=valid->check(click1);

                    disOrange();

                    exp.clear();

                    turn++;
                    cnt=0;
                }
                else
                    cnt=1;
            }
        }
    }
}

void Tile::tileDisplay()
{
    if(this->tileColor)
        this->setStyleSheet("QLabel {background-color: rgb(100, 100, 100);}:hover{background-color: rgb(80,80,80);}");
    else
        this->setStyleSheet("QLabel {background-color: rgb(250, 250, 250);}:hover{background-color: rgb(200,200,200);}");
}

void disOrange()
{
    for(int i=0;i<exp.size();i++)
        tile[exp[i]/6][exp[i]%6]->tileDisplay();
}
