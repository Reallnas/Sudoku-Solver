#include "mainwindow.h"

#include <QMenuBar>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "graphicssudokugrid.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //QMenu *file_menu = menuBar()->addMenu("&File");
    QMenu *grid_menu = menuBar()->addMenu("&Grid");




    constexpr int square_size = 80;
    QGraphicsScene* scene = new QGraphicsScene(0,0,square_size*11,square_size*11);
    scene->setBackgroundBrush(QBrush(Qt::white, Qt::SolidPattern));

    GraphicsSudokuGrid* grid = new GraphicsSudokuGrid(square_size,square_size,square_size*9);
    grid->setPos(square_size,square_size);
    scene->addItem(grid);
    grid->setSudokuGrid(Sudoku({{{{0,0,8,2,4,7,9,0,3}},
                          {{0,3,0,1,0,0,0,8,0}},
                          {{9,1,7,0,0,3,0,5,0}},
                          {{0,6,0,3,0,0,0,0,0}},
                          {{0,7,0,0,5,8,0,6,0}},
                          {{1,0,9,6,7,0,0,0,0}},
                          {{2,9,6,0,0,1,3,0,0}},
                          {{0,0,0,4,3,9,0,0,6}},
                          {{0,0,3,5,2,6,0,0,1}}}}));

    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);

    grid_menu->addAction("Set as initial",grid,&GraphicsSudokuGrid::setCurrentGridAsInitial);
    grid_menu->addAction("Reset to initial",grid,&GraphicsSudokuGrid::reset);
    grid_menu->addAction("Clear",grid,&GraphicsSudokuGrid::clearGrid);
    grid_menu->addAction("Is grid solvable ?",grid,&GraphicsSudokuGrid::isSolvable);
}



