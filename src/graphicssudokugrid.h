#ifndef GRAPHICSSUDOKUGRID_H
#define GRAPHICSSUDOKUGRID_H

#include <array>
#include <QGraphicsItem>

#include "sudoku.h"
#include "sudokusolver.h"

class GridSquare : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GridSquare(int x, int y, int size,QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void keyPressEvent(QKeyEvent * event);
    void setAligned(bool aligned);
    void setValue(int value);
    void setFixed(bool fixed);
    bool isFixed() const;
private:
    const int m_size = 0;
    int m_x = 0;
    int m_y = 0;
    int m_value = 0;
    bool m_is_aligned = false;
    bool m_is_fixed = false;

signals:
    void squareSelected(int x,int y);
};

class GraphicsSudokuGrid : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    GraphicsSudokuGrid(int x, int y, int size,QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void onSquareSelection(int x, int y);
    void keyPressEvent(QKeyEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void setSudokuGrid(Sudoku sud);
    void nextStep();
    void setCurrentGridAsInitial();
    void reset();
    void clearGrid();

    void isSolvable();

private:
    const int m_size = 10;
    int m_square_size = 1;
    int m_x = 0;
    int m_y = 0;
    std::array<std::array<GridSquare*,9>,9> m_grid {};
    std::pair<int,int> m_selected_pos = {0,0};

    Sudoku m_sud = {};
    SudokuSolver m_solver = {};
};

/*Idée d'amélioration:
 * mettre une couleur particulière pour les cases remplies par le resolveur
 * OK (peut -être) : Un indicateur qui indique si l'état actuel du plateau peut mener à la resolution du sudoku
 * Un message de victoire si le sudoku est résolu
 * OK : Un bouton pour reset à l'état initial le sudoku
 * améliorer le resolveur pour prendre en compte des sudokus non deterministes
 * permettre au resolveur de resoudre de facon absolue(depuis la grile de base) ou de facon relative(grille de base + inputs du joueur)
 * OK : un bouton pour pouvoir mettre en place la grille initiale
 * animation de resolution rapide (step by step + 100ms de délai)
 * mettre à l'échelle la fenetre pour ne pas avoir à scroller
 * ...
 */
#endif // GRAPHICSSUDOKUGRID_H
