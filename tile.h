#ifndef TILE_H
#define TILE_H
#include <QLabel>
#include <QDebug>

extern int cnt,turn;
extern double responseTime;
extern int difficulty;
extern QWidget *myWidget;
extern QLabel *moves;
extern QLabel *time1;
extern QLabel *time2;

class Tile: public QLabel{
    public:
        int tileColor,piece,pieceColor,row,col,tileNum;
        char pieceName;

        Tile(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {};
        Tile(const QString& text, QWidget* pParent = 0, Qt::WindowFlags f = 0) : QLabel(text, pParent, f){};
        void mousePressEvent(QMouseEvent *event);
        void display(char elem);
        void tileDisplay();
};

extern void UpdateBoard(Tile *tile[6][6]);
extern Tile *click1;
extern Tile *tile[6][6];
#endif // TILE_H


/* [Description]
 *
 * Tile::Tile(): The constructor.
 * Tile::mousePressEvent(): The mouse event on the checkers board.
 * Tile::display(): Display the checkers pieces on the board.
 * Tile::tileDisplay(): Display the checkers board.
 *
 */
