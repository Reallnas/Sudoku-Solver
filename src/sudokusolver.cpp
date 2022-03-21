#include "sudokusolver.h"

#include <iostream>

SudokuSolver::SudokuSolver(Sudoku*  sud)
{
    changeSudoku(sud);
}

void SudokuSolver::resetPossibilities()
{
    for(int x = 0;x<9;x++)
    {
        for(int y = 0;y<9;y++)
        {
            for(int i = 0;i<10;i++)
            {
                m_possibilities[x][y][i] = true;
            }
        }
    }
}

void SudokuSolver::changeSudoku(Sudoku* sud)
{
    m_sud = sud;
    resetPossibilities();
    initPossibilities();
}

void SudokuSolver::initPossibilities()
{
    if(m_sud == nullptr)
        return;

    for(int x = 0;x<9;x++)
    {
        for(int y = 0;y<9;y++)
        {
            //We discard every possibility that is already present in the grid
            erasePossibilityFromAligned(x,y,m_sud->getField(x,y));
            addToQueue(x,y);
        }
    }
}

void SudokuSolver::resetToInitial()
{
    resetPossibilities();
    initPossibilities();
}

std::optional<int> SudokuSolver::getOnlyPossibility(int x, int y)
{
    if(m_sud == nullptr)
        return std::nullopt;

    int id = 0;
    if(x == 6 && y == 3)
    {
        std::cout << "Possibilite case x=6, y=3:" << std::endl;
    }
    for(int i = 1;i<10;i++)
    {
        std::cout << i << " : " << m_possibilities[x][y][i] << std::endl;
        if(m_possibilities[x][y][i])
        {
            if(id != 0)
                return std::nullopt;
            else
                id = i;
        }
    }
    return id;
}

void SudokuSolver::erasePossibilityAndAddToQueue(int x,int y,int value)
{
    if(m_sud == nullptr)
        return;

    for(int i = 0;i<9;i++)
    {
        m_possibilities[i][y][value] = false;
        addToQueue(i,y);
        m_possibilities[x][i][value] = false;
        addToQueue(x,i);
    }
    const int square_x = x / 3;
    const int square_y = y / 3;
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            const int cur_x = 3*square_x + i;
            const int cur_y = 3*square_y +j;
            m_possibilities[cur_x][cur_y][value] = false;
            addToQueue(cur_x,cur_y);
        }
    }
}

void SudokuSolver::erasePossibilityFromAligned(int x,int y,int value)
{
    if(m_sud == nullptr || value == 0)
        return;

    for(int i = 0;i<9;i++)
    {
        m_possibilities[i][y][value] = false;
        m_possibilities[x][i][value] = false;
    }
    const int square_x = x / 3;
    const int square_y = y / 3;
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            m_possibilities[3*square_x + i][3*square_y +j][value] = false;
        }
    }
}

bool SudokuSolver::solve()
{
    if(m_sud == nullptr)
        return false;

    while(!m_to_evaluate.empty())
    {
        const auto [x,y] = m_to_evaluate.front();
        m_to_evaluate.pop();
        if(m_sud->isFieldSet(x,y))
                continue;
        const std::optional<int>& pos = getOnlyPossibility(x,y);
        if(pos.has_value())
        {
            m_sud->setField(x,y,pos.value());
            erasePossibilityAndAddToQueue(x,y,pos.value());
        }

    }
    return m_sud->isSolved();
}

std::array<int,3> SudokuSolver::solveNextStep()
{
    if(m_sud == nullptr)
        return {};

    std::array<int,3> ret = {{0,0,0}};
    bool updated = false;
    while(!m_to_evaluate.empty() && !updated)
    {
        const auto [x,y] = m_to_evaluate.front();
        m_to_evaluate.pop();
        std::cout << "is_evaluating " << x << " " << y << std::endl;
        if(m_sud->isFieldSet(x,y))
                continue;
        const std::optional<int>& pos = getOnlyPossibility(x,y);
        if(pos.has_value())
        {
            m_sud->setField(x,y,pos.value());
            erasePossibilityAndAddToQueue(x,y,pos.value());
            updated = true;
            ret = {{x,y,pos.value()}};
        }
    }
    return ret;
}

void SudokuSolver::addToQueue(int x,int y)
{
    if(m_sud == nullptr)
        return;

    if(!m_sud->isFieldSet(x,y))
        m_to_evaluate.push({x,y});
}
