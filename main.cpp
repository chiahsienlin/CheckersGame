#include <QApplication>
#include "mainwindow.h"
#include "tile.h"

int cnt=0,turn=0;
int remain_blk = 6, remain_wht = 6;
std::vector<int> exp;
std::vector<int> eat;
Tile *click1 = NULL;
Tile *tile[6][6] = { { NULL } };

class Border
{
public:
    Border();
    void outline(QWidget *baseWidget, int xPos, int yPos, int Pos)
    {
         QLabel *outLabel = new QLabel(baseWidget);

        if(!Pos)
            outLabel->setGeometry(xPos,yPos,552,20);        //Horizontal Borders

        else
            outLabel->setGeometry(xPos,yPos,20,512);        //Vertical Borders

        outLabel->setStyleSheet("QLabel { background-color :rgb(80, 50, 50); color : black; }");
    }
};

void accessories(QWidget *baseWidget)
{
    QLabel *player2 = new QLabel(baseWidget);
    QLabel *name2 = new QLabel("Player 2", baseWidget);
    QLabel *time2 = new QLabel("00:00:00", baseWidget);

    QLabel *player1 = new QLabel(baseWidget);
    QLabel *name1 = new QLabel("Player 1", baseWidget);
    QLabel *time1 = new QLabel("00:00:00", baseWidget);

    QLabel *moves = new QLabel(baseWidget);

    name1->setGeometry(125,610,80,20);
    time1->setGeometry(120,635,80,20);
    player1->setGeometry(100,500,100,100);
    player1->setPixmap(QPixmap(":/Images/profile.png"));

    name2->setGeometry(125,210,80,20);
    time2->setGeometry(120,235,80,20);
    player2->setGeometry(100,100,100,100);
    player2->setPixmap(QPixmap(":/Images/profile.png"));

    moves->setGeometry(1000,105,250,550);
    moves->setStyleSheet("QLabel {background-color: white;}");
}

void chessBoard(QWidget *baseWidget, Tile *tile[6][6])
{
    int i,j,k=0,hor,ver;

    //Create 36 tiles (allocating memories to the objects of Tile class)
    ver=125;
    for(i=0;i<6;i++)
    {
        hor=350;
        for(j=0;j<6;j++)
        {
            tile[i][j] = new Tile(baseWidget);
            tile[i][j]->tileColor=(i+j)%2;
            tile[i][j]->piece=0;
            tile[i][j]->row=i;
            tile[i][j]->col=j;
            tile[i][j]->tileNum=k++;
            tile[i][j]->tileDisplay();
            tile[i][j]->setGeometry(hor,ver,64,64);
            hor+=64;
        }
        ver+=64;
    }

    for(j = 0; j < 6; j++){
        if(j%2 == 1){
            tile[0][j]->piece=1;
            tile[0][j]->pieceColor=1;
            tile[0][j]->display('W');

            tile[4][j]->piece=1;
            tile[4][j]->pieceColor=0;
            tile[4][j]->display('B');
        }
        else{
            tile[1][j]->piece=1;
            tile[1][j]->pieceColor=1;
            tile[1][j]->display('W');

            tile[5][j]->piece=1;
            tile[5][j]->pieceColor=0;
            tile[5][j]->display('B');
        }
    }

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget *myWidget = new QWidget();
    myWidget->setGeometry(0,0,1370,700);

    accessories(myWidget);
    chessBoard(myWidget,tile);
    myWidget->show();
    return a.exec();
}

