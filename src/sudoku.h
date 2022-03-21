#ifndef SUDOKU_H
#define SUDOKU_H

#include <array>

class Sudoku {
public:
    //Coordinates go from 0 to 8 and start from the top-left handcorner
    //------>x
    //|
    //|
    //\/
    //y

    Sudoku() = default;
    Sudoku(const std::array<std::array<int,9>,9>& grid);

    int getField(int x, int y);
    void setField(int x, int y, int value);
    bool isFieldSet(int x, int y);

    std::array<int,9> getLine(int y);
    std::array<int,9> getColumn(int x);
    std::array<int,9> getSquare(int x,int y);

    void reset();
    void clear();

    bool isLineValid(int y);
    bool isColumnValid(int x);
    bool isSquareValid(int sx,int sy);
    bool isSolved();

    bool isLineSolvable(int y);
    bool isColumnSolvable(int x);
    bool isSquareSolvable(int sx,int sy);
    bool isSolvable();


    void setCurrentGridAsInitial();

    bool isInputValid(const std::array<std::array<int,9>,9>& grid);

private:
    std::array<std::array<int,9>,9> m_grid {};
    std::array<std::array<int,9>,9> m_initial_grid {};
};

#endif // SUDOKU_H
