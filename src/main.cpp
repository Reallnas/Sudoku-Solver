#include <iostream>
#include <array>

#include <QApplication>
#include <QPushButton>

#include "sudoku.h"
#include "sudokusolver.h"
#include "mainwindow.h"

template <class T,std::size_t S>
void printArray(const std::array<T,S>& arr)
{
    std::cout << '[';
    for(const auto& elt: arr)
    {
        std::cout << elt;
        std::cout << "; ";
    }
    std::cout << ']' << std::endl;
}

int main(int argc, char *argv[])
{
    Sudoku sud({{{{0,0,0,0,0,0,0,0,0}},
                 {{0,1,0,0,2,0,0,3,0}},
                 {{0,0,0,0,0,0,0,0,0}},
                 {{0,0,0,0,0,0,0,0,0}},
                 {{0,4,0,0,5,0,0,6,0}},
                 {{0,0,0,0,0,0,0,0,0}},
                 {{0,0,0,0,0,0,0,0,0}},
                 {{0,7,0,0,8,0,0,9,0}},
                 {{0,0,0,0,0,0,0,0,0}}}});

    /*std::cout << sud.getField(1,1) << std::endl;
    std::cout << sud.getField(7,4) << std::endl;
    printArray(sud.getLine(4));
    printArray(sud.getColumn(4));
    printArray(sud.getSquare(4,4));*/

    Sudoku facile({{{{0,0,8,2,4,7,9,0,3}},
                    {{0,3,0,1,0,0,0,8,0}},
                    {{9,1,7,0,0,3,0,5,0}},
                    {{0,6,0,3,0,0,0,0,0}},
                    {{0,7,0,0,5,8,0,6,0}},
                    {{1,0,9,6,7,0,0,0,0}},
                    {{2,9,6,0,0,1,3,0,0}},
                    {{0,0,0,4,3,9,0,0,6}},
                    {{0,0,3,5,2,6,0,0,1}}}});

    Sudoku moyen({{{{0,0,0,0,7,9,0,0,0}},
                   {{0,0,0,0,0,8,2,1,0}},
                   {{9,0,0,1,6,2,0,3,4}},
                   {{0,0,3,7,0,6,8,0,0}},
                   {{7,1,0,0,0,5,9,0,6}},
                   {{5,0,0,8,0,0,0,0,0}},
                   {{2,7,0,9,1,0,5,0,0}},
                   {{0,0,0,0,0,0,0,0,0}},
                   {{8,3,6,0,0,0,0,0,0}}}});
    SudokuSolver sol(&moyen);
    /*
    for(int x = 0;x<9;x++)
    {
        for(int y = 0;y<9;y++)
        {*/
            //printArray(sol.m_possibilities[1][2]);
       /* }
    }*/
    //std::cout << sol.solve() << std::endl;

    QApplication app(argc, argv);

    MainWindow win;
    win.show();

    return app.exec();
}
