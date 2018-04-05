#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextEdit>
#include "mainwindow.h"
#include "tile.h"
#include "validation.h"
#include "ai_player.h"
#include <thread>

int cnt = 0,turn = 0;
double responseTime = 15.00;
int difficulty = 16;
std::vector<int> valid_mv;
std::vector<int> eat;
Tile *click1 = NULL;
Tile *tile[6][6] = {{ NULL }};
QLabel *moves;
QLabel *time2;
validation *valid = new validation();
AI_player *ai = new AI_player();

class Border{
public:
    Border();
    void outline(QWidget *baseWidget, int xPos, int yPos, int Pos){
         QLabel *outLabel = new QLabel(baseWidget);
        if(!Pos)
            outLabel->setGeometry(xPos,yPos,552,20);        //Horizontal Borders
        else
            outLabel->setGeometry(xPos,yPos,20,512);        //Vertical Borders
        outLabel->setStyleSheet("QLabel { background-color :rgb(80, 50, 50); color : black; }");
    }
};
void AI_StartFirst();
void accessories(QWidget *baseWidget);
void chessBoard(QWidget *baseWidget, Tile *tile[6][6]);

int main(int argc, char *argv[]){
    int answer = 0;
    int level = 1;
    QApplication a(argc, argv);
    QTextStream cout(stdout);
    QWidget *myWidget = new QWidget();
    myWidget->setGeometry(0,0,1370,700);
    accessories(myWidget);
    chessBoard(myWidget,tile);

    do{
        bool ok;
        QInputDialog dialog;
        level = dialog.getInt(0, "Difficulty", "level 1 to 5", 1,1,5,1,&ok,Qt::CustomizeWindowHint);
        if(ok){
            QString response = QString("The Level you choose is %1.\n").arg(level);
            answer = QMessageBox::question(0, "Are you sure?", response, QMessageBox::Yes | QMessageBox::No | QMessageBox::Close);
            if(answer == QMessageBox::Close) return 0;
        }
        else
            return 0;
    }while(answer == QMessageBox::No);
    do{
        bool ok;
        QInputDialog dialog;
        turn = dialog.getInt(0, "Who first?", "0. You first  1. AI first", 0,0,1,1,&ok,Qt::CustomizeWindowHint);
        if(ok){
            QString response;
            if(!turn)
                response= QString("You choose You first.");
            else
                response = QString("You choose AI first.");
            answer = QMessageBox::question(0, "Are you sure?", response, QMessageBox::Yes | QMessageBox::No | QMessageBox::Close);
            if(answer == QMessageBox::Close) return 0;
        }
        else
            return 0;
    }while(answer == QMessageBox::No);

    difficulty = level*3 + 1;
    std::thread th_m;
    if(turn){
        th_m = std::thread(AI_StartFirst);
        th_m.detach();
    }
    myWidget->show();
    return a.exec();
}

void AI_StartFirst(){
    ai->Createstate(tile);
    auto action = ai->Alpha_Beta_Search(ai->getState());
    auto newState = ai->UpdateState(ai->getState(), action);
    ai->UpdateStateToTile(newState, tile);
    UpdateBoard(tile);
    string msg = "[AI] I'm done. It's your turn!\n";
    moves->setText(msg.c_str());
    turn++;
}

void accessories(QWidget *baseWidget){
    QLabel *player2 = new QLabel(baseWidget);
    QLabel *name2 = new QLabel("AI Player", baseWidget);
    time2 = new QLabel("Timer: 0 sec", baseWidget);

    QLabel *player1 = new QLabel(baseWidget);
    QLabel *name1 = new QLabel("You", baseWidget);

    name1->setGeometry(125,610,80,20);
    player1->setGeometry(100,500,100,100);
    player1->setPixmap(QPixmap(":/Images/profile.png"));

    name2->setGeometry(125,210,80,20);
    time2->setGeometry(120,235,80,20);
    player2->setGeometry(100,100,100,100);
    player2->setPixmap(QPixmap(":/Images/profile.png"));

    moves = new QLabel(baseWidget);
    moves->setGeometry(1000,105,250,550);
    moves->setStyleSheet("QLabel {background-color: white;}");

}

void chessBoard(QWidget *baseWidget, Tile *tile[6][6]){
    int k = 0,hor,ver;
    //Create 36 tiles (allocate memories to the objects of Tile class)
    ver = 125;
    for(int i = 0; i < 6; i++){
        hor = 350;
        for(int j = 0; j < 6; j++){
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
    for(int j = 0; j < 6; j++){
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
