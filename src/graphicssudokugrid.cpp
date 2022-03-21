#include "graphicssudokugrid.h"

#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsView>


GridSquare::GridSquare(int x, int y, int size,QGraphicsItem *parent) : QGraphicsItem(parent),m_size(size),m_x(x),m_y(y)
{
    //setFlag(QGraphicsItem::ItemIsFocusable);
}

QRectF GridSquare::boundingRect() const
{
    return QRectF(0,0,m_size,m_size);
}

void GridSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    constexpr int epaisseur = 2;
    constexpr int epaisseur_thick = 4;
    constexpr int decalage = 0; //epaisseur/2;
    constexpr int decalage_thick = epaisseur_thick/2;
    static const QPen black_pen = QPen(QBrush(Qt::black, Qt::SolidPattern),epaisseur);
    static const QPen thick_black_pen = QPen(QBrush(Qt::black, Qt::SolidPattern),epaisseur_thick);

    if(m_is_aligned)
    {
        painter->fillRect(boundingRect(),Qt::lightGray);
    }

    painter->setPen(black_pen);
    if(m_y % 3 == 0)
    {
        painter->setPen(thick_black_pen);
        painter->drawLine(decalage_thick,decalage_thick,m_size-decalage_thick,decalage_thick);
        painter->setPen(black_pen);
    }
    else
        painter->drawLine(0,decalage,m_size,decalage);

    if((m_x+1) % 3 == 0)
    {
        painter->setPen(thick_black_pen);
        painter->drawLine(m_size-decalage_thick,m_size-decalage_thick,m_size-decalage_thick,decalage_thick);
        painter->setPen(black_pen);
    }
    else
        painter->drawLine(m_size-decalage,m_size,m_size-decalage,0);

    if((m_y+1) % 3 == 0)
    {
        painter->setPen(thick_black_pen);
        painter->drawLine(m_size-decalage_thick,m_size-decalage_thick,decalage_thick,m_size-decalage_thick);
        painter->setPen(black_pen);
    }
    else
        painter->drawLine(m_size,m_size-decalage,0,m_size-decalage);

    if(m_x % 3 == 0)
    {
        painter->setPen(thick_black_pen);
        painter->drawLine(decalage_thick,decalage_thick,decalage_thick,m_size-decalage_thick);
        painter->setPen(black_pen);
    }
    else
        painter->drawLine(decalage,0,decalage,m_size);

    //painter->setPen(QPen(QBrush(Qt::red, Qt::SolidPattern),2));
    //painter->drawRect(boundingRect());

    if(m_value != 0)
    {
        QFont font = painter->font();
        font.setPixelSize(48);
        painter->setFont(font);
        if(m_is_fixed)
            painter->setPen(black_pen);
        else
            painter->setPen(QPen(QBrush(Qt::darkGray, Qt::SolidPattern),epaisseur));
        painter->drawText(boundingRect(),Qt::AlignCenter,QString::number(m_value));
    }

}

void GridSquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    //setFocus();
    emit squareSelected(m_x,m_y);
}

/*void GridSquare::keyPressEvent(QKeyEvent * event)
{
    if(event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9)
        m_value = event->key() - Qt::Key_0;
    update();
    QGraphicsItem::keyPressEvent(event);
}*/

void GridSquare::setAligned(bool aligned)
{
    m_is_aligned = aligned;
    update();
}

void GridSquare::setValue(int value)
{
    if(!m_is_fixed && value >= 0 && value <= 9)
    {
        m_value = value;
        update();
    }
}

void GridSquare::setFixed(bool fixed)
{
    m_is_fixed = fixed;
    update();
}

bool GridSquare::isFixed() const
{
    return m_is_fixed;
}


GraphicsSudokuGrid::GraphicsSudokuGrid(int x, int y, int size,QGraphicsItem* parent) : QGraphicsItemGroup(parent), m_size(size),m_x(x),m_y(y)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    m_square_size = m_size/9;
    for(int x = 0;x<9;x++)
    {
        for(int y = 0;y<9;y++)
        {
            const int pos_x = m_square_size*x;
            const int pos_y = m_square_size*y;
            m_grid[x][y] = new GridSquare(x,y,m_square_size);
            m_grid[x][y]->setPos(pos_x,pos_y);
            addToGroup(m_grid[x][y]);

            //QObject::connect(m_grid[x][y],&GridSquare::squareSelected,this,&GraphicsSudokuGrid::onSquareSelection);
        }
    }
    setFocus();
}

QRectF GraphicsSudokuGrid::boundingRect() const
{
    return QRectF(0,0,m_size,m_size);
}

/*void GraphicsSudokuGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(QBrush(Qt::red, Qt::SolidPattern),2));
    painter->drawRect(boundingRect());
}*/

void GraphicsSudokuGrid::keyPressEvent(QKeyEvent * event)
{
    const int value = event->key() - Qt::Key_0;
    if(value >= 0 && value <= 9)
    {
        m_sud.setField(m_selected_pos.first,m_selected_pos.second,value);
        m_grid[m_selected_pos.first][m_selected_pos.second]->setValue(value);
    }

    if(event->key() == Qt::Key_F)
    {
        setCurrentGridAsInitial();
    }
    if(event->key() == Qt::Key_A)
    {
        nextStep();
        std::cout << "next step" << std::endl;
    }
    QGraphicsItemGroup::keyPressEvent(event);
}

void GraphicsSudokuGrid::onSquareSelection(int x, int y)
{
    for(int i = 0;i<9;i++)
    {
        m_grid[i][m_selected_pos.second]->setAligned(false);
        m_grid[m_selected_pos.first][i]->setAligned(false);
    }
    m_selected_pos = {x,y};
    for(int i = 0;i<9;i++)
    {
        m_grid[i][y]->setAligned(true);
        m_grid[x][i]->setAligned(true);
    }
    //std::cout << x << " " << y << std::endl;
}


void GraphicsSudokuGrid::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    const int x = static_cast<int>(event->pos().x()/ m_square_size);
    const int y = static_cast<int>(event->pos().y() / m_square_size);
    //QGraphicsItem::mousePressEvent(event);
    onSquareSelection(x,y);
}

void GraphicsSudokuGrid::setSudokuGrid(Sudoku sud)
{
    m_sud = sud;
    m_solver.changeSudoku(&m_sud);
    for(int x = 0;x<9;x++)
    {
        for(int y = 0;y<9;y++)
        {
            m_grid[x][y]->setValue(m_sud.getField(x,y));
            if(m_sud.getField(x,y) != 0)
                m_grid[x][y]->setFixed(true);
        }
    }
}

void GraphicsSudokuGrid::nextStep()
{
    const std::array<int,3> changed = m_solver.solveNextStep();
    std::cout << changed[0] << " " << changed[1] << " " << changed[2] << std::endl;
    if(changed[2] != 0)
        m_grid[changed[0]][changed[1]]->setValue(changed[2]);
    else
         std::cout << m_sud.isSolved() << std::endl;
}

void GraphicsSudokuGrid::setCurrentGridAsInitial()
{
    m_sud.setCurrentGridAsInitial();
    for(int x = 0;x<9;x++)
    {
        for(int y = 0;y<9;y++)
        {
            if(m_sud.getField(x,y) != 0)
                m_grid[x][y]->setFixed(true);
        }
    }
}

void GraphicsSudokuGrid::reset()
{
    m_sud.reset();
    m_solver.resetToInitial();
    for(int x = 0;x<9;x++)
    {
        for(int y = 0;y<9;y++)
        {
            m_grid[x][y]->setFixed(false);
            m_grid[x][y]->setValue(m_sud.getField(x,y));
            if(m_sud.getField(x,y) != 0)
                m_grid[x][y]->setFixed(true);
        }
    }

}

void GraphicsSudokuGrid::clearGrid()
{
    m_sud.clear();
    m_solver.resetToInitial();
    for(int x = 0;x<9;x++)
    {
        for(int y = 0;y<9;y++)
        {
            m_grid[x][y]->setFixed(false);
            m_grid[x][y]->setValue(0);
        }
    }
}

void GraphicsSudokuGrid::isSolvable()
{
    std::cout << m_sud.isSolvable() << std::endl;
}
