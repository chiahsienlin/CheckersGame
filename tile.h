#ifndef TILE_H
#define TILE_H
#include <QLabel>
#include <QDebug>
extern int remain_blk, remain_wht;
extern int cnt,turn;
extern double responseTime;
extern int difficulty;
extern QWidget *myWidget;

class Tile: public QLabel
{
public:

    //Fields
    int tileColor,piece,pieceColor,row,col,tileNum;
    char pieceName;

    //Constructors
    Tile(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {};
    Tile(const QString& text, QWidget* pParent = 0, Qt::WindowFlags f = 0) : QLabel(text, pParent, f){};

    //Methods
    void mousePressEvent(QMouseEvent *event);
    void display(char elem);
    void tileDisplay();
};

extern Tile *click1;
extern Tile *tile[6][6];
#endif // TILE_H
