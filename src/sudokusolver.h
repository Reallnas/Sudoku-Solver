#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <array>
#include <queue>
#include <optional>

#include "sudoku.h"

class SudokuSolver
{
public:
    SudokuSolver(Sudoku* sud = nullptr);

    void initPossibilities();
    void resetPossibilities();
    void resetToInitial();
    std::optional<int> getOnlyPossibility(int x, int y);

    void erasePossibilityFromAligned(int x,int y,int value);
    void erasePossibilityAndAddToQueue(int x,int y,int value);

    bool solve();
    //return x,y,value of the solved field
    std::array<int,3> solveNextStep();

    void addToQueue(int x,int y);
    void changeSudoku(Sudoku* sud = nullptr);

private:
    Sudoku* m_sud = nullptr;
    //The first address of the boolean array is not used
    //Its size is ten to allow a direct mapping between possibilities and actual values
    std::array<std::array<std::array<bool,10>,9>,9> m_possibilities {};
    std::queue<std::pair<int,int>> m_to_evaluate;
};
#endif // SUDOKUSOLVER_H
